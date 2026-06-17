-- ============================================================
-- 02 - Vistas
-- ============================================================
USE Reparaciones_G79;
GO

IF OBJECT_ID('vista_reparacionesActivas','V')    IS NOT NULL DROP VIEW vista_reparacionesActivas;
IF OBJECT_ID('vista_topClientesFacturacion','V') IS NOT NULL DROP VIEW vista_topClientesFacturacion;
IF OBJECT_ID('vista_equiposPorCliente','V')      IS NOT NULL DROP VIEW vista_equiposPorCliente;
GO

-- ------------------------------------------------------------
-- Vista 1: reparaciones activas que NO estan finalizadas
-- (estados "Sin iniciar" o "En proceso"), con cliente y tecnico.
-- ------------------------------------------------------------
CREATE VIEW vista_reparacionesActivas AS
SELECT
    r.NroReparacion,
    c.CUIT,
    ISNULL(c.RazonSocial, c.Apellido + ', ' + c.Nombre) AS Cliente,
    e.Legajo,
    e.Apellido + ', ' + e.Nombre AS Empleado,
    r.FechaIngreso,
    r.FechaEntrega,
    ep.Descripcion AS Estado,
    r.TotalCalculado
FROM Reparacion r
INNER JOIN Cliente c           ON c.CUIT   = r.CUIT
INNER JOIN Empleado e          ON e.Legajo = r.Legajo
INNER JOIN EstadoReparacion ep ON ep.Id    = r.IdEstado
WHERE r.Activo = 1
  AND ep.Descripcion IN ('Sin iniciar', 'En proceso');
GO

-- ------------------------------------------------------------
-- Vista 2: top 100 clientes por facturacion acumulada
-- ------------------------------------------------------------
CREATE VIEW vista_topClientesFacturacion AS
SELECT TOP 100
    c.CUIT,
    ISNULL(c.RazonSocial, c.Apellido + ', ' + c.Nombre) AS Cliente,
    COUNT(DISTINCT r.NroReparacion) AS CantidadReparaciones,
    SUM(r.TotalCalculado)           AS TotalFacturado
FROM Cliente c
INNER JOIN Reparacion r ON r.CUIT = c.CUIT
WHERE c.Activo = 1 AND r.Activo = 1
GROUP BY c.CUIT,
         ISNULL(c.RazonSocial, c.Apellido + ', ' + c.Nombre)
ORDER BY TotalFacturado DESC;
GO

-- ------------------------------------------------------------
-- Vista 3: equipos activos agrupados por cliente, con su tipo
-- ------------------------------------------------------------
CREATE VIEW vista_equiposPorCliente AS
SELECT
    c.CUIT,
    ISNULL(c.RazonSocial, c.Apellido + ', ' + c.Nombre) AS Cliente,
    e.NroEquipo,
    te.Descripcion AS TipoEquipo,
    e.Marca,
    e.Descripcion AS DescripcionEquipo,
    e.FechaIngreso
FROM Cliente c
INNER JOIN Equipo e      ON e.CUIT = c.CUIT
INNER JOIN TipoEquipo te ON te.Id  = e.IdTipoEquipo
WHERE c.Activo = 1 AND e.Activo = 1;
GO

PRINT 'Vistas creadas correctamente.';
GO
