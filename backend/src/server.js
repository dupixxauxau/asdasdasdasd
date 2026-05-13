require('dotenv').config();
const express = require('express');
const cors = require('cors');
const cron = require('node-cron');
const path = require('path');
const fs = require('fs');
const { checkExpiredLicenses } = require('./services/license');

const app = express();
const PORT = process.env.PORT || 3001;

// Middleware
app.use(cors({ origin: process.env.FRONTEND_URL || '*' }));
app.use(express.json());

// API Routes
app.get('/api/health', (req, res) => res.json({ status: 'ok', time: new Date() }));
app.use('/api/auth', require('./routes/auth'));
app.use('/api/license', require('./routes/license'));
app.use('/api/plans', require('./routes/plans'));
app.use('/api/payment', require('./routes/payment'));
app.use('/api/admin', require('./routes/admin'));

// Serve static frontend (same port)
const frontendPath = path.join(__dirname, '../../frontend/public');
app.use(express.static(frontendPath));

// Serve planejamento-semanal.html if it exists at root
const appHtmlPath = path.join(__dirname, '../../planejamento-semanal.html');
if (fs.existsSync(appHtmlPath)) {
  app.get('/planejamento-semanal.html', (req, res) => res.sendFile(appHtmlPath));
}

// SPA fallback: any non-API route serves index.html
app.get('*', (req, res) => {
  res.sendFile(path.join(frontendPath, 'index.html'));
});

// Cron: check expired licenses every 5 minutes
cron.schedule('*/5 * * * *', async () => {
  try {
    const expired = await checkExpiredLicenses();
    if (expired.length > 0) {
      console.log(`[CRON] ${expired.length} license(s) expired.`);
    }
  } catch (err) {
    console.error('[CRON] Error checking licenses:', err);
  }
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
