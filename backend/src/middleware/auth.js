const jwt = require('jsonwebtoken');
const pool = require('../config/database');

const JWT_SECRET = process.env.JWT_SECRET || 'dev-secret-change-me';

function generateToken(user) {
  return jwt.sign(
    { id: user.id, email: user.email, role: user.role },
    JWT_SECRET,
    { expiresIn: process.env.JWT_EXPIRES_IN || '7d' }
  );
}

async function authRequired(req, res, next) {
  const header = req.headers.authorization;
  if (!header || !header.startsWith('Bearer ')) {
    return res.status(401).json({ error: 'Token não fornecido.' });
  }

  try {
    const token = header.split(' ')[1];
    const decoded = jwt.verify(token, JWT_SECRET);
    const result = await pool.query('SELECT id, name, email, role, active, email_verified FROM users WHERE id = $1', [decoded.id]);
    if (result.rows.length === 0) {
      return res.status(401).json({ error: 'Usuário não encontrado.' });
    }
    const user = result.rows[0];
    if (!user.active) {
      return res.status(403).json({ error: 'Conta desativada. Entre em contato com o suporte.' });
    }
    req.user = user;
    next();
  } catch (err) {
    return res.status(401).json({ error: 'Token inválido ou expirado.' });
  }
}

function adminRequired(req, res, next) {
  if (!req.user || req.user.role !== 'admin') {
    return res.status(403).json({ error: 'Acesso restrito a administradores.' });
  }
  next();
}

async function licenseRequired(req, res, next) {
  const result = await pool.query(
    "SELECT * FROM licenses WHERE user_id = $1 AND status IN ('active', 'trial') AND expires_at > NOW() ORDER BY expires_at DESC LIMIT 1",
    [req.user.id]
  );
  if (result.rows.length === 0) {
    return res.status(403).json({ error: 'Licença expirada ou inexistente. Adquira um plano para continuar.' });
  }
  req.license = result.rows[0];
  next();
}

module.exports = { generateToken, authRequired, adminRequired, licenseRequired };
