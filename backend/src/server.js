require('dotenv').config();
const express = require('express');
const cors = require('cors');
const cron = require('node-cron');
const path = require('path');
const { checkExpiredLicenses } = require('./services/license');

const app = express();
const PORT = process.env.PORT || 3001;

// Middleware
app.use(cors({ origin: process.env.FRONTEND_URL || 'http://localhost:3000' }));
app.use(express.json());

// Routes
app.use('/api/auth', require('./routes/auth'));
app.use('/api/license', require('./routes/license'));
app.use('/api/plans', require('./routes/plans'));
app.use('/api/payment', require('./routes/payment'));
app.use('/api/admin', require('./routes/admin'));

// Serve static frontend in production
if (process.env.NODE_ENV === 'production') {
  app.use(express.static(path.join(__dirname, '../../frontend/build')));
  app.get('*', (req, res) => {
    res.sendFile(path.join(__dirname, '../../frontend/build/index.html'));
  });
}

// Health check
app.get('/api/health', (req, res) => res.json({ status: 'ok', time: new Date() }));

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
