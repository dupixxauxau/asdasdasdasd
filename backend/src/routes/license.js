const express = require('express');
const { authRequired } = require('../middleware/auth');
const { startTrial, getUserActiveLicense } = require('../services/license');

const router = express.Router();

// POST /api/license/trial
router.post('/trial', authRequired, async (req, res) => {
  try {
    if (!req.user.email_verified) {
      return res.status(403).json({ error: 'Ative seu email antes de usar o trial.' });
    }
    const license = await startTrial(req.user.id);
    res.json({ message: 'Trial de 2 horas ativado!', license });
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

// GET /api/license/status
router.get('/status', authRequired, async (req, res) => {
  const license = await getUserActiveLicense(req.user.id);
  if (!license) {
    return res.json({ active: false, message: 'Sem licença ativa.' });
  }
  const remaining = new Date(license.expires_at) - new Date();
  res.json({
    active: true,
    license: {
      id: license.id,
      plan_type: license.plan_type,
      status: license.status,
      starts_at: license.starts_at,
      expires_at: license.expires_at,
      remaining_hours: Math.max(0, remaining / (1000 * 60 * 60)),
      remaining_days: Math.max(0, remaining / (1000 * 60 * 60 * 24)),
    },
  });
});

module.exports = router;
