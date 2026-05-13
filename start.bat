@echo off
chcp 65001 >nul
title Planejamento Semanal - SaaS

echo ========================================
echo  Planejamento Semanal — SaaS
echo ========================================
echo.

:: Check Node.js
where node >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERRO] Node.js nao encontrado!
    echo Baixe em: https://nodejs.org/
    pause
    exit /b 1
)
for /f "tokens=*" %%i in ('node -v') do echo [OK] Node.js %%i

:: Check if .env exists
if not exist "backend\.env" (
    echo.
    echo [AVISO] Arquivo backend\.env nao encontrado!
    echo Copiando .env.example para .env...
    copy backend\.env.example backend\.env >nul
    echo.
    echo IMPORTANTE: Edite backend\.env com suas configuracoes:
    echo   - DB_HOST, DB_USER, DB_PASS (PostgreSQL)
    echo   - JWT_SECRET (troque para uma senha forte)
    echo.
    echo Abrindo o arquivo para edicao...
    notepad backend\.env
    echo.
    pause
)

:: Install dependencies
echo.
echo [1/4] Instalando dependencias...
cd backend
call npm install --production
cd ..

:: Run migrations
echo.
echo [2/4] Criando tabelas no banco...
cd backend
node src/config/migrate.js
if %errorlevel% neq 0 (
    echo.
    echo [ERRO] Falha ao criar tabelas!
    echo Verifique se o PostgreSQL esta rodando e se backend\.env esta correto.
    echo.
    echo Dicas:
    echo   1. Abra o pgAdmin e crie o banco "planejamento_saas"
    echo   2. Verifique usuario e senha no backend\.env
    echo.
    cd ..
    pause
    exit /b 1
)
cd ..

:: Seed data
echo.
echo [3/4] Inserindo dados iniciais...
cd backend
node src/config/seed.js
cd ..

:: Start server
echo.
echo [4/4] Iniciando servidor...
echo.
echo ========================================
echo  Servidor rodando!
echo  Acesse: http://localhost:3001
echo.
echo  Admin: admin@planejamento.com
echo  Senha: admin123
echo ========================================
echo.
echo (Nao feche esta janela!)
echo.

cd backend
node src/server.js

pause
