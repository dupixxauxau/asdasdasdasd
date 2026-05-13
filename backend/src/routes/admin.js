const express = require('express');
const pool = require('../config/database');
const { authRequired, adminRequired } = require('../middleware/auth');
const { createLicense, renewLicense } = require('../services/license');

const router = express.Router();
router.use(authRequired, adminRequired);

async function logAction(adminId, action, targetUserId, details) {
  await pool.query(
    'INSERT INTO admin_logs (admin_id, action, target_user_id, details) VALUES ($1, $2, $3, $4)',
    [adminId, action, targetUserId, details]
  );
}

// GET /api/admin/users
router.get('/users', async (req, res) => {
  const { page = 1, limit = 20, search } = req.query;
  const offset = (page - 1) * limit;
  let query = `
    SELECT u.id, u.name, u.email, u.role, u.active, u.email_verified, u.created_at,
           l.id as license_id, l.plan_type, l.status as license_status, l.expires_at
    FROM users u
    LEFT JOIN LATERAL (
      SELECT * FROM licenses WHERE user_id = u.id ORDER BY created_at DESC LIMIT 1
    ) l ON true
  `;
  const params = [];
  if (search) {
    query += ' WHERE u.name ILIKE $1 OR u.email ILIKE $1';
    params.push(`%${search}%`);
  }
  query += ` ORDER BY u.created_at DESC LIMIT ${limit} OFFSET ${offset}`;

  const result = await pool.query(query, params);
  const count = await pool.query('SELECT COUNT(*) FROM users' + (search ? ' WHERE name ILIKE $1 OR email ILIKE $1' : ''), search ? [`%${search}%`] : []);

  res.json({
    users: result.rows,
    total: parseInt(count.rows[0].count),
    page: parseInt(page),
    pages: Math.ceil(count.rows[0].count / limit),
  });
});

// PUT /api/admin/users/:id/toggle
router.put('/users/:id/toggle', async (req, res) => {
  const { id } = req.params;
  const result = await pool.query('UPDATE users SET active = NOT active WHERE id = $1 RETURNING id, name, active', [id]);
  if (result.rows.length === 0) return res.status(404).json({ error: 'Usuário não encontrado.' });
  const user = result.rows[0];
  await logAction(req.user.id, user.active ? 'activate_user' : 'deactivate_user', id);
  res.json({ message: `Usuário ${user.active ? 'ativado' : 'desativado'}.`, user });
});

// POST /api/admin/licenses
router.post('/licenses', async (req, res) => {
  try {
    const { user_id, plan_id } = req.body;
    const license = await createLicense(user_id, plan_id);
    await logAction(req.user.id, 'create_license', user_id, `plan_id=${plan_id}`);
    res.json({ message: 'Licença criada.', license });
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

// PUT /api/admin/licenses/:id/renew
router.put('/licenses/:id/renew', async (req, res) => {
  try {
    const { days } = req.body;
    if (!days || days < 1) return res.status(400).json({ error: 'Informe a quantidade de dias.' });
    const license = await renewLicense(req.params.id, days);
    await logAction(req.user.id, 'renew_license', license.user_id, `days=${days}`);
    res.json({ message: 'Licença renovada.', license });
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

// PUT /api/admin/licenses/:id/cancel
router.put('/licenses/:id/cancel', async (req, res) => {
  const result = await pool.query(
    "UPDATE licenses SET status = 'cancelled' WHERE id = $1 RETURNING *",
    [req.params.id]
  );
  if (result.rows.length === 0) return res.status(404).json({ error: 'Licença não encontrada.' });
  await logAction(req.user.id, 'cancel_license', result.rows[0].user_id);
  res.json({ message: 'Licença cancelada.', license: result.rows[0] });
});

// PUT /api/admin/licenses/:id/plan
router.put('/licenses/:id/plan', async (req, res) => {
  try {
    const { plan_id } = req.body;
    const plan = await pool.query('SELECT * FROM plans WHERE id = $1', [plan_id]);
    if (plan.rows.length === 0) return res.status(404).json({ error: 'Plano não encontrado.' });

    const p = plan.rows[0];
    const now = new Date();
    const expires = new Date(now.getTime() + p.duration_days * 24 * 60 * 60 * 1000);

    const result = await pool.query(
      "UPDATE licenses SET plan_type = $1, status = 'active', starts_at = $2, expires_at = $3 WHERE id = $4 RETURNING *",
      [p.name, now, expires, req.params.id]
    );
    if (result.rows.length === 0) return res.status(404).json({ error: 'Licença não encontrada.' });
    await logAction(req.user.id, 'change_plan', result.rows[0].user_id, `new_plan=${p.name}`);
    res.json({ message: 'Plano alterado.', license: result.rows[0] });
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

// GET /api/admin/payments
router.get('/payments', async (req, res) => {
  const { page = 1, limit = 20 } = req.query;
  const offset = (page - 1) * limit;
  const result = await pool.query(`
    SELECT p.*, u.name as user_name, u.email as user_email
    FROM payments p JOIN users u ON p.user_id = u.id
    ORDER BY p.created_at DESC LIMIT $1 OFFSET $2
  `, [limit, offset]);
  const count = await pool.query('SELECT COUNT(*) FROM payments');
  res.json({
    payments: result.rows,
    total: parseInt(count.rows[0].count),
    page: parseInt(page),
  });
});

// GET /api/admin/logs
router.get('/logs', async (req, res) => {
  const { page = 1, limit = 50 } = req.query;
  const offset = (page - 1) * limit;
  const result = await pool.query(`
    SELECT al.*, a.name as admin_name, t.name as target_name, t.email as target_email
    FROM admin_logs al
    LEFT JOIN users a ON al.admin_id = a.id
    LEFT JOIN users t ON al.target_user_id = t.id
    ORDER BY al.created_at DESC LIMIT $1 OFFSET $2
  `, [limit, offset]);
  res.json(result.rows);
});

// GET /api/admin/stats
router.get('/stats', async (req, res) => {
  const users = await pool.query('SELECT COUNT(*) FROM users');
  const active = await pool.query("SELECT COUNT(*) FROM licenses WHERE status IN ('active', 'trial') AND expires_at > NOW()");
  const revenue = await pool.query("SELECT COALESCE(SUM(amount), 0) as total FROM payments WHERE status = 'approved'");
  const monthly = await pool.query("SELECT COALESCE(SUM(amount), 0) as total FROM payments WHERE status = 'approved' AND paid_at >= DATE_TRUNC('month', NOW())");

  res.json({
    total_users: parseInt(users.rows[0].count),
    active_licenses: parseInt(active.rows[0].count),
    total_revenue: parseFloat(revenue.rows[0].total),
    monthly_revenue: parseFloat(monthly.rows[0].total),
  });
});

module.exports = router;
