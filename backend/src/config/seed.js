const pool = require('./database');
const bcrypt = require('bcrypt');

const seed = async () => {
  console.log('Seeding database...');

  // Insert default plans
  await pool.query(`
    INSERT INTO plans (name, duration_days, price) VALUES
      ('Mensal', 30, 29.90),
      ('Trimestral', 90, 69.90),
      ('Anual', 365, 199.90)
    ON CONFLICT DO NOTHING;
  `);

  // Create default admin user
  const adminExists = await pool.query("SELECT id FROM users WHERE email = 'admin@planejamento.com'");
  if (adminExists.rows.length === 0) {
    const hash = await bcrypt.hash('admin123', 12);
    await pool.query(
      "INSERT INTO users (name, email, password_hash, email_verified, role) VALUES ($1, $2, $3, true, 'admin')",
      ['Administrador', 'admin@planejamento.com', hash]
    );
    console.log('Admin user created: admin@planejamento.com / admin123');
  }

  console.log('Seeding completed!');
  await pool.end();
};

seed().catch(err => {
  console.error('Seeding failed:', err);
  process.exit(1);
});
