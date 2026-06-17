# ============================================================
# Habilita TCP/IP en SQL Server Express (instancia SQLEXPRESS)
# para poder conectarse desde Navicat / otras GUI por red.
# >>> EJECUTAR EN UNA POWERSHELL ABIERTA COMO ADMINISTRADOR <<<
# ============================================================

$instancia = "MSSQL16.SQLEXPRESS"   # SQL Server 2022 Express
$tcp = "HKLM:\SOFTWARE\Microsoft\Microsoft SQL Server\$instancia\MSSQLServer\SuperSocketNetLib\Tcp"

Write-Host "1) Habilitando protocolo TCP/IP..." -ForegroundColor Cyan
Set-ItemProperty -Path $tcp -Name Enabled -Value 1

Write-Host "2) Fijando puerto estatico 1433 en IPAll..." -ForegroundColor Cyan
Set-ItemProperty -Path "$tcp\IPAll" -Name TcpDynamicPorts -Value ""      # sin puerto dinamico
Set-ItemProperty -Path "$tcp\IPAll" -Name TcpPort        -Value "1433"   # puerto fijo

Write-Host "3) Habilitando y arrancando SQL Browser..." -ForegroundColor Cyan
Set-Service  -Name SQLBrowser -StartupType Automatic
Start-Service -Name SQLBrowser -ErrorAction SilentlyContinue

Write-Host "4) Reiniciando la instancia SQLEXPRESS..." -ForegroundColor Cyan
Restart-Service -Name 'MSSQL$SQLEXPRESS' -Force

Write-Host "`nListo. SQL Server escucha en localhost:1433" -ForegroundColor Green
Write-Host "Probando conexion por TCP..." -ForegroundColor Cyan
sqlcmd -S tcp:localhost,1433 -E -d Reparaciones_G79 -Q "SELECT TOP 1 'OK conexion TCP' AS Estado FROM Cliente"
