const pool = require('../config/database');

const TRIAL_HOURS = parseInt(process.env.TRIAL_DURATION_HOURS || '2');

async function startTrial(userId) {
  // Check if user already used trial
  const existing = await pool.query(
    "SELECT id FROM licenses WHERE user_id = $1 AND trial_used = true",
    [userId]
  );
  if (existing.rows.length > 0) {
    throw new Error('Trial já utilizado. Adquira um plano para continuar.');
  }

  const now = new Date();
  const expires = new Date(now.getTime() + TRIAL_HOURS * 60 * 60 * 1000);

  const result = await pool.query(
    `INSERT INTO licenses (user_id, plan_type, status, starts_at, expires_at, trial_used)
     VALUES ($1, 'trial', 'trial', $2, $3, true) RETURNING *`,
    [userId, now, expires]
  );
  return result.rows[0];
}

async function createLicense(userId, planId) {
  const plan = await pool.query('SELECT * FROM plans WHERE id = $1 AND active = true', [planId]);
  if (plan.rows.length === 0) throw new Error('Plano não encontrado.');

  const p = plan.rows[0];
  const now = new Date();
  const expires = new Date(now.getTime() + p.duration_days * 24 * 60 * 60 * 1000);

  // Deactivate any existing active license
  await pool.query(
    "UPDATE licenses SET status = 'expired' WHERE user_id = $1 AND status IN ('active', 'trial')",
    [userId]
  );

  const result = await pool.query(
    `INSERT INTO licenses (user_id, plan_type, status, starts_at, expires_at)
     VALUES ($1, $2, 'active', $3, $4) RETURNING *`,
    [userId, p.name, now, expires]
  );
  return result.rows[0];
}

async function renewLicense(licenseId, extraDays) {
  const lic = await pool.query('SELECT * FROM licenses WHERE id = $1', [licenseId]);
  if (lic.rows.length === 0) throw new Error('Licença não encontrada.');

  const current = lic.rows[0];
  const baseDate = current.status === 'active' && new Date(current.expires_at) > new Date()
    ? new Date(current.expires_at)
    : new Date();
  const newExpires = new Date(baseDate.getTime() + extraDays * 24 * 60 * 60 * 1000);

  const result = await pool.query(
    "UPDATE licenses SET status = 'active', expires_at = $1 WHERE id = $2 RETURNING *",
    [newExpires, licenseId]
  );
  return result.rows[0];
}

async function checkExpiredLicenses() {
  const result = await pool.query(
    "UPDATE licenses SET status = 'expired' WHERE status IN ('active', 'trial') AND expires_at < NOW() RETURNING id, user_id"
  );
  return result.rows;
}

async function getUserActiveLicense(userId) {
  const result = await pool.query(
    "SELECT * FROM licenses WHERE user_id = $1 AND status IN ('active', 'trial') AND expires_at > NOW() ORDER BY expires_at DESC LIMIT 1",
    [userId]
  );
  return result.rows[0] || null;
}

module.exports = { startTrial, createLicense, renewLicense, checkExpiredLicenses, getUserActiveLicense };
