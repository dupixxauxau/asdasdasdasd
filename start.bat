@echo off
chcp 65001 >nul 2>nul
title Planejamento Semanal - SaaS

echo.
echo ========================================
echo   Planejamento Semanal - SaaS
echo ========================================
echo.

where node >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERRO] Node.js nao encontrado!
    echo Baixe em: https://nodejs.org/
    pause
    exit /b 1
)
for /f "tokens=*" %%i in ('node -v') do echo [OK] Node.js %%i

if not exist "backend\.env" (
    echo.
    echo [AVISO] Arquivo backend\.env nao encontrado!
    echo Copiando .env.example para .env...
    copy backend\.env.example backend\.env >nul
    echo.
    echo IMPORTANTE: Edite backend\.env com suas configuracoes:
    echo   - DB_PASS = senha do seu PostgreSQL
    echo   - JWT_SECRET = qualquer texto aleatorio
    echo.
    echo Abrindo o arquivo para edicao...
    notepad backend\.env
    echo.
    pause
)

echo.
echo [1/4] Instalando dependencias...
cd backend
call npm install --omit=dev
cd ..

echo.
echo [2/4] Criando tabelas no banco...
cd backend
node src/config/migrate.js
if %errorlevel% neq 0 (
    echo.
    echo [ERRO] Falha ao criar tabelas!
    echo Verifique se o PostgreSQL esta rodando e o backend\.env esta correto.
    cd ..
    pause
    exit /b 1
)
cd ..

echo.
echo [3/4] Inserindo dados iniciais...
cd backend
node src/config/seed.js
cd ..

echo.
echo [4/4] Iniciando servidor...
echo.
echo ========================================
echo   Servidor rodando!
echo   Acesse: http://localhost:3001
echo.
echo   Admin: admin@planejamento.com
echo   Senha: admin123
echo ========================================
echo.
echo   Nao feche esta janela!
echo.

cd backend
node src/server.js

pause
