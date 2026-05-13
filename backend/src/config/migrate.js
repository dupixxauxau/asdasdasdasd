const pool = require('./database');

const migrate = async () => {
  console.log('Running database migrations...');

  await pool.query(`
    CREATE TABLE IF NOT EXISTS plans (
      id SERIAL PRIMARY KEY,
      name VARCHAR(50) UNIQUE NOT NULL,
      duration_days INTEGER NOT NULL,
      price DECIMAL(10,2) NOT NULL,
      active BOOLEAN DEFAULT true,
      created_at TIMESTAMP DEFAULT NOW()
    );

    CREATE TABLE IF NOT EXISTS users (
      id SERIAL PRIMARY KEY,
      name VARCHAR(255) NOT NULL,
      email VARCHAR(255) UNIQUE NOT NULL,
      password_hash VARCHAR(255) NOT NULL,
      email_verified BOOLEAN DEFAULT false,
      email_token VARCHAR(255),
      role VARCHAR(20) DEFAULT 'client' CHECK (role IN ('client', 'admin')),
      active BOOLEAN DEFAULT true,
      created_at TIMESTAMP DEFAULT NOW()
    );

    CREATE TABLE IF NOT EXISTS licenses (
      id SERIAL PRIMARY KEY,
      user_id INTEGER REFERENCES users(id) ON DELETE CASCADE,
      plan_type VARCHAR(50) NOT NULL,
      status VARCHAR(20) DEFAULT 'active' CHECK (status IN ('active', 'expired', 'cancelled', 'trial')),
      starts_at TIMESTAMP NOT NULL,
      expires_at TIMESTAMP NOT NULL,
      trial_used BOOLEAN DEFAULT false,
      created_at TIMESTAMP DEFAULT NOW()
    );

    CREATE TABLE IF NOT EXISTS payments (
      id SERIAL PRIMARY KEY,
      user_id INTEGER REFERENCES users(id) ON DELETE CASCADE,
      license_id INTEGER REFERENCES licenses(id) ON DELETE SET NULL,
      gateway VARCHAR(50) NOT NULL,
      gateway_id VARCHAR(255),
      status VARCHAR(20) DEFAULT 'pending' CHECK (status IN ('pending', 'approved', 'rejected', 'refunded')),
      amount DECIMAL(10,2) NOT NULL,
      paid_at TIMESTAMP,
      created_at TIMESTAMP DEFAULT NOW()
    );

    CREATE TABLE IF NOT EXISTS admin_logs (
      id SERIAL PRIMARY KEY,
      admin_id INTEGER REFERENCES users(id) ON DELETE SET NULL,
      action VARCHAR(255) NOT NULL,
      target_user_id INTEGER REFERENCES users(id) ON DELETE SET NULL,
      details TEXT,
      created_at TIMESTAMP DEFAULT NOW()
    );

    CREATE INDEX IF NOT EXISTS idx_licenses_user_id ON licenses(user_id);
    CREATE INDEX IF NOT EXISTS idx_licenses_status ON licenses(status);
    CREATE INDEX IF NOT EXISTS idx_licenses_expires_at ON licenses(expires_at);
    CREATE INDEX IF NOT EXISTS idx_payments_user_id ON payments(user_id);
    CREATE INDEX IF NOT EXISTS idx_users_email ON users(email);
    CREATE INDEX IF NOT EXISTS idx_users_email_token ON users(email_token);
  `);

  // Clean duplicate plans (if any from previous runs)
  await pool.query(`
    DELETE FROM plans WHERE id NOT IN (SELECT MIN(id) FROM plans GROUP BY name);
  `);

  // Add unique constraint on plans.name if not exists
  await pool.query(`
    DO $$ BEGIN
      IF NOT EXISTS (SELECT 1 FROM pg_constraint WHERE conname = 'plans_name_key') THEN
        ALTER TABLE plans ADD CONSTRAINT plans_name_key UNIQUE (name);
      END IF;
    END $$;
  `);

  console.log('Migrations completed successfully!');
  await pool.end();
};

migrate().catch(err => {
  console.error('Migration failed:', err);
  process.exit(1);
});
