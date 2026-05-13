const nodemailer = require('nodemailer');

let transporter;

function getTransporter() {
  if (transporter) return transporter;

  if (process.env.NODE_ENV === 'development' && !process.env.SMTP_HOST) {
    // In dev without SMTP config, log emails to console
    transporter = {
      sendMail: async (opts) => {
        console.log('\n=== EMAIL (dev mode) ===');
        console.log('To:', opts.to);
        console.log('Subject:', opts.subject);
        console.log('Body:', opts.html || opts.text);
        console.log('========================\n');
        return { messageId: 'dev-' + Date.now() };
      }
    };
  } else {
    transporter = nodemailer.createTransport({
      host: process.env.SMTP_HOST,
      port: parseInt(process.env.SMTP_PORT || '587'),
      secure: process.env.SMTP_PORT === '465',
      auth: {
        user: process.env.SMTP_USER,
        pass: process.env.SMTP_PASS,
      },
    });
  }
  return transporter;
}

async function sendActivationEmail(email, name, token) {
  const url = `${process.env.FRONTEND_URL || 'http://localhost:3000'}/ativar?token=${token}`;
  const html = `
    <div style="font-family:Arial,sans-serif;max-width:500px;margin:0 auto;padding:20px;border:1px solid #e0e0e0;border-radius:8px;">
      <h2 style="color:#2e7d32;">Planejamento Semanal</h2>
      <p>Olá <strong>${name}</strong>,</p>
      <p>Obrigado por se cadastrar! Para ativar sua conta, clique no botão abaixo:</p>
      <div style="text-align:center;margin:30px 0;">
        <a href="${url}" style="background:#2e7d32;color:#fff;padding:12px 30px;border-radius:6px;text-decoration:none;font-weight:bold;">
          Ativar minha conta
        </a>
      </div>
      <p style="font-size:13px;color:#666;">Se o botão não funcionar, copie e cole este link: <br>${url}</p>
      <hr style="border:none;border-top:1px solid #eee;margin:20px 0;">
      <p style="font-size:12px;color:#999;">Planejamento Semanal - Educação Infantil</p>
    </div>
  `;
  await getTransporter().sendMail({
    from: process.env.EMAIL_FROM || '"Planejamento Semanal" <noreply@planejamento.com>',
    to: email,
    subject: 'Ative sua conta - Planejamento Semanal',
    html,
  });
}

module.exports = { sendActivationEmail };
