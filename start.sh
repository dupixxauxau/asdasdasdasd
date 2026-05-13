#!/bin/bash
# ══════════════════════════════════════════
# Planejamento Semanal SaaS — Start Script
# ══════════════════════════════════════════

set -e

echo "========================================"
echo " Planejamento Semanal — SaaS"
echo "========================================"

# Check Node.js
if ! command -v node &> /dev/null; then
  echo "[ERRO] Node.js nao encontrado. Instale com: curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash - && sudo apt-get install -y nodejs"
  exit 1
fi
echo "[OK] Node.js $(node -v)"

# Check PostgreSQL
if ! command -v psql &> /dev/null; then
  echo "[ERRO] PostgreSQL nao encontrado. Instale com: sudo apt-get install -y postgresql"
  exit 1
fi
echo "[OK] PostgreSQL instalado"

# Install dependencies
echo ""
echo "[1/4] Instalando dependencias..."
cd backend
npm install --production
cd ..

# Check .env
if [ ! -f backend/.env ]; then
  echo ""
  echo "[AVISO] Arquivo backend/.env nao encontrado!"
  echo "Copiando .env.example para .env..."
  cp backend/.env.example backend/.env
  echo ""
  echo "IMPORTANTE: Edite backend/.env com suas configuracoes:"
  echo "  - DB_HOST, DB_USER, DB_PASS (PostgreSQL)"
  echo "  - JWT_SECRET (troque para uma senha forte)"
  echo "  - SMTP_HOST, SMTP_USER, SMTP_PASS (para emails)"
  echo "  - MP_ACCESS_TOKEN (Mercado Pago)"
  echo ""
  read -p "Pressione ENTER para continuar ou Ctrl+C para editar o .env primeiro..."
fi

# Run migrations
echo ""
echo "[2/4] Criando tabelas no banco..."
cd backend
node src/config/migrate.js
cd ..

# Seed data
echo ""
echo "[3/4] Inserindo dados iniciais..."
cd backend
node src/config/seed.js
cd ..

# Start server
echo ""
echo "[4/4] Iniciando servidor..."
echo ""
echo "========================================"
echo " Servidor rodando!"
echo " Acesse: http://localhost:${PORT:-3001}"
echo ""
echo " Admin: admin@planejamento.com"
echo " Senha: admin123"
echo "========================================"
echo ""

cd backend
node src/server.js
