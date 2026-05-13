const express = require('express');
const pool = require('../config/database');

const router = express.Router();

// GET /api/plans
router.get('/', async (req, res) => {
  const result = await pool.query('SELECT id, name, duration_days, price FROM plans WHERE active = true ORDER BY price ASC');
  res.json(result.rows);
});

module.exports = router;
