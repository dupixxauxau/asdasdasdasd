const express = require('express');
const pool = require('../config/database');
const { authRequired } = require('../middleware/auth');
const { createLicense } = require('../services/license');

const router = express.Router();

// POST /api/payment/create - Create a Mercado Pago preference
router.post('/create', authRequired, async (req, res) => {
  try {
    const { plan_id } = req.body;
    if (!plan_id) return res.status(400).json({ error: 'Plano não informado.' });

    const plan = await pool.query('SELECT * FROM plans WHERE id = $1 AND active = true', [plan_id]);
    if (plan.rows.length === 0) return res.status(404).json({ error: 'Plano não encontrado.' });

    const p = plan.rows[0];

    // If MP_ACCESS_TOKEN is configured, create real preference
    if (process.env.MP_ACCESS_TOKEN && process.env.MP_ACCESS_TOKEN !== 'your-mercado-pago-access-token') {
      const { MercadoPagoConfig, Preference } = require('mercadopago');
      const client = new MercadoPagoConfig({ accessToken: process.env.MP_ACCESS_TOKEN });
      const preference = new Preference(client);

      const result = await preference.create({
        body: {
          items: [{
            title: `Planejamento Semanal - ${p.name}`,
            quantity: 1,
            unit_price: parseFloat(p.price),
            currency_id: 'BRL',
          }],
          payer: {
            email: req.user.email,
          },
          back_urls: {
            success: `${process.env.FRONTEND_URL}/pagamento/sucesso?plan_id=${p.id}`,
            failure: `${process.env.FRONTEND_URL}/pagamento/erro`,
            pending: `${process.env.FRONTEND_URL}/pagamento/pendente`,
          },
          auto_return: 'approved',
          external_reference: JSON.stringify({ user_id: req.user.id, plan_id: p.id }),
          notification_url: `${process.env.BACKEND_URL || 'http://localhost:3001'}/api/payment/webhook`,
        }
      });

      // Record payment as pending
      await pool.query(
        'INSERT INTO payments (user_id, gateway, gateway_id, status, amount) VALUES ($1, $2, $3, $4, $5)',
        [req.user.id, 'mercadopago', result.id, 'pending', p.price]
      );

      return res.json({
        checkout_url: result.init_point,
        preference_id: result.id,
      });
    }

    // Dev mode: simulate payment
    const license = await createLicense(req.user.id, p.id);
    await pool.query(
      'INSERT INTO payments (user_id, license_id, gateway, status, amount, paid_at) VALUES ($1, $2, $3, $4, $5, NOW())',
      [req.user.id, license.id, 'dev-simulate', 'approved', p.price]
    );

    res.json({
      message: 'Pagamento simulado (modo dev). Licença ativada!',
      license,
      dev_mode: true,
    });
  } catch (err) {
    console.error('Payment create error:', err);
    res.status(500).json({ error: 'Erro ao processar pagamento.' });
  }
});

// POST /api/payment/webhook - Mercado Pago webhook
router.post('/webhook', async (req, res) => {
  try {
    const { type, data } = req.body;
    if (type === 'payment') {
      const paymentId = data.id;

      if (process.env.MP_ACCESS_TOKEN && process.env.MP_ACCESS_TOKEN !== 'your-mercado-pago-access-token') {
        const { MercadoPagoConfig, Payment } = require('mercadopago');
        const client = new MercadoPagoConfig({ accessToken: process.env.MP_ACCESS_TOKEN });
        const payment = new Payment(client);

        const mpPayment = await payment.get({ id: paymentId });

        if (mpPayment.status === 'approved') {
          const ref = JSON.parse(mpPayment.external_reference);
          const license = await createLicense(ref.user_id, ref.plan_id);

          await pool.query(
            "UPDATE payments SET status = 'approved', license_id = $1, paid_at = NOW() WHERE gateway_id = $2",
            [license.id, mpPayment.preference_id || paymentId]
          );
        }
      }
    }
    res.sendStatus(200);
  } catch (err) {
    console.error('Webhook error:', err);
    res.sendStatus(200);
  }
});

module.exports = router;
