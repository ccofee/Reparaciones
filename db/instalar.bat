@echo off
REM ============================================================
REM Instala la base Reparaciones_G79 en la instancia indicada.
REM Uso:  instalar.bat            (usa .\SQLEXPRESS por defecto)
REM       instalar.bat MI\INSTANCIA
REM Requiere: sqlcmd + ODBC Driver para SQL Server + autenticacion Windows.
REM ============================================================
setlocal
set SERVIDOR=%1
if "%SERVIDOR%"=="" set SERVIDOR=.\SQLEXPRESS

echo Instalando en %SERVIDOR% ...
for %%F in (
    01_crear_base_y_tablas.sql
    02_vistas.sql
    03_funciones.sql
    04_procedimientos.sql
    05_triggers.sql
    06_datos_prueba.sql
) do (
    echo  -- Ejecutando %%F
    sqlcmd -S %SERVIDOR% -E -b -i "%~dp0%%F"
    if errorlevel 1 (
        echo  ^>^> ERROR ejecutando %%F
        exit /b 1
    )
)
echo.
echo Base Reparaciones_G79 instalada correctamente.
endlocal
