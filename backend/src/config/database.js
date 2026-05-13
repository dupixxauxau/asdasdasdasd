const { Pool } = require('pg');
require('dotenv').config();

const pool = new Pool({
  host: process.env.DB_HOST || 'localhost',
  port: parseInt(process.env.DB_PORT || '5432'),
  database: process.env.DB_NAME || 'planejamento_saas',
  user: process.env.DB_USER || 'postgres',
  password: process.env.DB_PASS || 'postgres',
});

pool.on('error', (err) => {
  console.error('Database pool error:', err);
});

module.exports = pool;
