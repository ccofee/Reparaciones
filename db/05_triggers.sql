-- ============================================================
-- 05 - Triggers
-- ============================================================
USE Reparaciones_G79;
GO

IF OBJECT_ID('trg_cascadaBajaReparacion','TR') IS NOT NULL DROP TRIGGER trg_cascadaBajaReparacion;
IF OBJECT_ID('trg_validarUnicidadCUIT','TR')   IS NOT NULL DROP TRIGGER trg_validarUnicidadCUIT;
IF OBJECT_ID('trg_actualizarTotalRep','TR')    IS NOT NULL DROP TRIGGER trg_actualizarTotalRep;
GO

-- ------------------------------------------------------------
-- Trigger 1: baja en cascada logica. Cuando una reparacion
-- pasa Activo de 1 a 0, marca como inactivos sus detalles.
-- ------------------------------------------------------------
CREATE TRIGGER trg_cascadaBajaReparacion
ON Reparacion
AFTER UPDATE
AS
BEGIN
    SET NOCOUNT ON;

    IF UPDATE(Activo)
    BEGIN
        UPDATE d
        SET d.Activo = 0
        FROM DetalleReparacion d
        INNER JOIN inserted i ON i.NroReparacion = d.NroReparacion
        INNER JOIN deleted  e ON e.NroReparacion = d.NroReparacion
        WHERE i.Activo = 0 AND e.Activo = 1
          AND d.Activo = 1;
    END
END;
GO

-- ------------------------------------------------------------
-- Trigger 2: valida unicidad de CUIT entre clientes activos
-- (INSTEAD OF INSERT). Permite reutilizar un CUIT solo si el
-- cliente original fue dado de baja.
-- ------------------------------------------------------------
CREATE TRIGGER trg_validarUnicidadCUIT
ON Cliente
INSTEAD OF INSERT
AS
BEGIN
    SET NOCOUNT ON;

    IF EXISTS (
        SELECT 1
        FROM Cliente c
        INNER JOIN inserted i ON i.CUIT = c.CUIT
        WHERE c.Activo = 1
    )
    BEGIN
        RAISERROR ('Ya existe un cliente activo con ese CUIT.', 16, 1);
        RETURN;
    END

    INSERT INTO Cliente (CUIT, Nombre, Apellido, RazonSocial, Email,
                         Telefono, Direccion, IdTipoCliente, Activo,
                         FechaAlta, FechaBaja)
    SELECT CUIT, Nombre, Apellido, RazonSocial, Email,
           Telefono, Direccion, IdTipoCliente,
           ISNULL(Activo, 1), ISNULL(FechaAlta, GETDATE()), FechaBaja
    FROM inserted;
END;
GO

-- ------------------------------------------------------------
-- Trigger 3: mantiene Reparacion.TotalCalculado coherente ante
-- cualquier INSERT / UPDATE / DELETE sobre DetalleReparacion.
-- ------------------------------------------------------------
CREATE TRIGGER trg_actualizarTotalRep
ON DetalleReparacion
AFTER INSERT, UPDATE, DELETE
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @Repas TABLE (NroReparacion INT PRIMARY KEY);

    INSERT INTO @Repas (NroReparacion)
    SELECT NroReparacion FROM inserted
    UNION
    SELECT NroReparacion FROM deleted;

    UPDATE r
    SET r.TotalCalculado = ISNULL((
        SELECT SUM(d.Importe)
        FROM DetalleReparacion d
        WHERE d.NroReparacion = r.NroReparacion
          AND d.Activo = 1
    ), 0)
    FROM Reparacion r
    INNER JOIN @Repas a ON a.NroReparacion = r.NroReparacion;
END;
GO

PRINT 'Triggers creados correctamente.';
GO
