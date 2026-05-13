# Planejamento Semanal — SaaS

Sistema SaaS para o Planejamento Semanal de Educacao Infantil com controle de usuarios, licencas, trial e pagamentos via Mercado Pago.

## Stack

- **Backend:** Node.js + Express
- **Banco:** PostgreSQL
- **Auth:** JWT + bcrypt
- **Email:** Nodemailer
- **Pagamento:** Mercado Pago
- **Frontend:** HTML/CSS/JS

## Setup

### 1. Banco de dados

```bash
# Instalar PostgreSQL e criar o banco
createdb planejamento_saas
```

### 2. Backend

```bash
cd backend
cp .env.example .env  # edite com suas credenciais
npm install
npm run db:migrate
npm run db:seed       # cria admin + planos padrao
npm run dev
```

Admin padrao: `admin@planejamento.com` / `admin123`

### 3. Frontend

```bash
cd frontend
npx serve public -l 3000
```

## Estrutura

```
backend/
  src/
    config/     - database, migrations, seed
    middleware/  - auth (JWT)
    routes/     - auth, license, plans, payment, admin
    services/   - email, license
    server.js   - Express app
frontend/
  public/
    index.html  - SPA (login, register, client, admin)
```

## Planos

| Plano      | Duracao  | Preco   |
|------------|----------|---------|
| Mensal     | 30 dias  | R$29,90 |
| Trimestral | 90 dias  | R$69,90 |
| Anual      | 365 dias | R$199,90|

## Regras

- Trial de 2h apos ativacao do email (1x por usuario)
- Licencas expiram automaticamente (cron a cada 5min)
- Admin pode criar/renovar/cancelar licencas manualmente
