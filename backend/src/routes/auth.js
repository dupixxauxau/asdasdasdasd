const express = require('express');
const bcrypt = require('bcrypt');
const { v4: uuidv4 } = require('uuid');
const pool = require('../config/database');
const { generateToken, authRequired } = require('../middleware/auth');
const { sendActivationEmail } = require('../services/email');
const { getUserActiveLicense } = require('../services/license');

const router = express.Router();

// POST /api/auth/register
router.post('/register', async (req, res) => {
  try {
    const { name, email, password } = req.body;
    if (!name || !email || !password) {
      return res.status(400).json({ error: 'Nome, email e senha são obrigatórios.' });
    }
    if (password.length < 6) {
      return res.status(400).json({ error: 'Senha deve ter no mínimo 6 caracteres.' });
    }

    const exists = await pool.query('SELECT id FROM users WHERE email = $1', [email.toLowerCase()]);
    if (exists.rows.length > 0) {
      return res.status(409).json({ error: 'Email já cadastrado.' });
    }

    const hash = await bcrypt.hash(password, 12);
    const token = uuidv4();

    const result = await pool.query(
      'INSERT INTO users (name, email, password_hash, email_token) VALUES ($1, $2, $3, $4) RETURNING id, name, email, role',
      [name.trim(), email.toLowerCase().trim(), hash, token]
    );

    await sendActivationEmail(email, name, token);

    res.status(201).json({
      message: 'Cadastro realizado! Verifique seu email para ativar a conta.',
      user: result.rows[0],
    });
  } catch (err) {
    console.error('Register error:', err);
    res.status(500).json({ error: 'Erro ao cadastrar. Tente novamente.' });
  }
});

// POST /api/auth/login
router.post('/login', async (req, res) => {
  try {
    const { email, password } = req.body;
    if (!email || !password) {
      return res.status(400).json({ error: 'Email e senha são obrigatórios.' });
    }

    const result = await pool.query('SELECT * FROM users WHERE email = $1', [email.toLowerCase()]);
    if (result.rows.length === 0) {
      return res.status(401).json({ error: 'Email ou senha incorretos.' });
    }

    const user = result.rows[0];
    const valid = await bcrypt.compare(password, user.password_hash);
    if (!valid) {
      return res.status(401).json({ error: 'Email ou senha incorretos.' });
    }

    if (!user.active) {
      return res.status(403).json({ error: 'Conta desativada. Entre em contato com o suporte.' });
    }

    if (!user.email_verified) {
      return res.status(403).json({ error: 'Email não verificado. Verifique sua caixa de entrada.' });
    }

    const license = await getUserActiveLicense(user.id);
    const token = generateToken(user);

    res.json({
      token,
      user: {
        id: user.id,
        name: user.name,
        email: user.email,
        role: user.role,
      },
      license: license ? {
        id: license.id,
        plan_type: license.plan_type,
        status: license.status,
        expires_at: license.expires_at,
      } : null,
    });
  } catch (err) {
    console.error('Login error:', err);
    res.status(500).json({ error: 'Erro ao fazer login.' });
  }
});

// GET /api/auth/activate?token=xxx
router.get('/activate', async (req, res) => {
  try {
    const { token } = req.query;
    if (!token) return res.status(400).json({ error: 'Token inválido.' });

    const result = await pool.query(
      'UPDATE users SET email_verified = true, email_token = NULL WHERE email_token = $1 AND email_verified = false RETURNING id, name, email',
      [token]
    );

    if (result.rows.length === 0) {
      return res.status(400).json({ error: 'Token inválido ou conta já ativada.' });
    }

    res.json({ message: 'Email verificado com sucesso! Você já pode fazer login.', user: result.rows[0] });
  } catch (err) {
    console.error('Activate error:', err);
    res.status(500).json({ error: 'Erro ao ativar conta.' });
  }
});

// GET /api/auth/me
router.get('/me', authRequired, async (req, res) => {
  const license = await getUserActiveLicense(req.user.id);
  res.json({
    user: req.user,
    license: license ? {
      id: license.id,
      plan_type: license.plan_type,
      status: license.status,
      starts_at: license.starts_at,
      expires_at: license.expires_at,
    } : null,
  });
});

// POST /api/auth/resend-activation
router.post('/resend-activation', async (req, res) => {
  try {
    const { email } = req.body;
    const result = await pool.query('SELECT * FROM users WHERE email = $1 AND email_verified = false', [email.toLowerCase()]);
    if (result.rows.length === 0) {
      return res.json({ message: 'Se o email existir, um novo link será enviado.' });
    }
    const user = result.rows[0];
    const token = uuidv4();
    await pool.query('UPDATE users SET email_token = $1 WHERE id = $2', [token, user.id]);
    await sendActivationEmail(email, user.name, token);
    res.json({ message: 'Email de ativação reenviado.' });
  } catch (err) {
    console.error('Resend error:', err);
    res.status(500).json({ error: 'Erro ao reenviar email.' });
  }
});

module.exports = router;
