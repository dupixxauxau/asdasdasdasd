# Planejamento Semanal — SaaS

Sistema SaaS para o Planejamento Semanal de Educacao Infantil com controle de usuarios, licencas, trial e pagamentos via Mercado Pago.

## Inicio Rapido

```bash
# 1. Criar banco PostgreSQL
sudo -u postgres createdb planejamento_saas

# 2. Configurar
cp backend/.env.example backend/.env
nano backend/.env   # edite com suas credenciais

# 3. Iniciar tudo
./start.sh
```

Acesse: `http://localhost:3001`
Admin: `admin@planejamento.com` / `admin123`

## Deploy na VPS (Ubuntu/Debian)

### 1. Requisitos

```bash
# Node.js 20
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
sudo apt-get install -y nodejs

# PostgreSQL
sudo apt-get install -y postgresql

# Git
sudo apt-get install -y git
```

### 2. Clonar e configurar

```bash
cd /var/www
git clone https://github.com/dupixxauxau/asdasdasdasd.git planejamento
cd planejamento

# Criar banco
sudo -u postgres createdb planejamento_saas
sudo -u postgres psql -c "ALTER USER postgres PASSWORD 'SUA_SENHA_AQUI';"

# Configurar .env
cp backend/.env.example backend/.env
nano backend/.env
```

No `.env`, configure:
- `PORT=3001` (ou a porta que preferir)
- `DB_PASS=SUA_SENHA_AQUI`
- `JWT_SECRET=uma-chave-secreta-forte-aleatoria`
- `SMTP_*` (para envio de emails)
- `MP_ACCESS_TOKEN` (Mercado Pago)

### 3. Setup e iniciar

```bash
chmod +x start.sh
./start.sh
```

### 4. Manter rodando com PM2

```bash
sudo npm install -g pm2

# Iniciar
pm2 start backend/src/server.js --name planejamento-saas

# Iniciar automaticamente ao ligar o servidor
pm2 startup
pm2 save
```

### 5. Nginx (proxy reverso com dominio)

```nginx
server {
    listen 80;
    server_name seudominio.com.br;

    location / {
        proxy_pass http://localhost:3001;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection 'upgrade';
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_cache_bypass $http_upgrade;
    }
}
```

```bash
# Instalar e configurar
sudo apt-get install -y nginx
sudo nano /etc/nginx/sites-available/planejamento
sudo ln -s /etc/nginx/sites-available/planejamento /etc/nginx/sites-enabled/
sudo nginx -t && sudo systemctl reload nginx

# HTTPS com Let's Encrypt (gratis)
sudo apt-get install -y certbot python3-certbot-nginx
sudo certbot --nginx -d seudominio.com.br
```

## Stack

- **Backend:** Node.js + Express
- **Banco:** PostgreSQL
- **Auth:** JWT + bcrypt
- **Email:** Nodemailer
- **Pagamento:** Mercado Pago
- **Frontend:** HTML/CSS/JS (servido pelo mesmo servidor)

## Estrutura

```
start.sh            - Script para iniciar tudo
package.json        - Scripts npm (start, setup, dev)
backend/
  .env.example      - Template de configuracao
  src/
    server.js       - Express app (API + frontend)
    config/         - database, migrations, seed
    middleware/      - auth (JWT)
    routes/         - auth, license, plans, payment, admin
    services/       - email, license
frontend/
  public/
    index.html      - SPA (login, cadastro, dashboard)
planejamento-semanal.html  - App de planejamento
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
- Frontend e API rodam na mesma porta (um unico `node` serve tudo)

## Comandos

```bash
./start.sh          # Setup completo + iniciar
npm start           # Iniciar servidor (producao)
npm run dev         # Iniciar com hot-reload (desenvolvimento)
npm run setup       # Instalar deps + migrar + seed
npm run db:migrate  # Criar/atualizar tabelas
npm run db:seed     # Inserir dados iniciais
```
