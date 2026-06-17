-- ============================================================
-- 04 - Procedimientos almacenados
-- ============================================================
USE Reparaciones_G79;
GO

IF OBJECT_ID('sp_altaReparacionConDetalle','P') IS NOT NULL
    DROP PROCEDURE sp_altaReparacionConDetalle;
IF OBJECT_ID('sp_bajaLogicaReparacion','P') IS NOT NULL
    DROP PROCEDURE sp_bajaLogicaReparacion;
GO

-- ------------------------------------------------------------
-- SP 1: alta de una reparacion + sus detalles en una unica
-- transaccion (operacion atomica). Recibe los detalles via un
-- Table-Valued Parameter (dbo.TipoDetalleReparacion).
-- La cabecera nace en estado "Sin iniciar" (IdEstado = 1).
-- NroReparacion se asigna como MAX + 1 (la PK no es IDENTITY).
-- ------------------------------------------------------------
CREATE PROCEDURE sp_altaReparacionConDetalle
    @CUIT     VARCHAR(13),
    @Legajo   INT,
    @Detalles dbo.TipoDetalleReparacion READONLY
AS
BEGIN
    SET NOCOUNT ON;
    BEGIN TRY
        BEGIN TRANSACTION;

        IF NOT EXISTS (SELECT 1 FROM Cliente WHERE CUIT = @CUIT AND Activo = 1)
            THROW 50001, 'El cliente no existe o esta dado de baja.', 1;

        IF NOT EXISTS (SELECT 1 FROM Empleado WHERE Legajo = @Legajo AND Activo = 1)
            THROW 50002, 'El empleado no existe o esta dado de baja.', 1;

        DECLARE @NroRep INT =
            (SELECT ISNULL(MAX(NroReparacion), 0) + 1 FROM Reparacion);

        INSERT INTO Reparacion (NroReparacion, CUIT, Legajo, IdEstado)
        VALUES (@NroRep, @CUIT, @Legajo, 1);

        -- Solo se cargan equipos que pertenecen al cliente y estan activos
        INSERT INTO DetalleReparacion (NroReparacion, NroEquipo, Importe, Descripcion)
        SELECT @NroRep, d.NroEquipo, d.Importe, d.Descripcion
        FROM @Detalles d
        INNER JOIN Equipo e ON e.NroEquipo = d.NroEquipo
        WHERE e.CUIT = @CUIT AND e.Activo = 1;

        COMMIT TRANSACTION;
        PRINT 'Reparacion ' + CAST(@NroRep AS VARCHAR) + ' creada correctamente.';
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0 ROLLBACK TRANSACTION;
        PRINT 'Error: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;
GO

-- ------------------------------------------------------------
-- SP 2: baja logica de una reparacion (Activo = 0 + estado
-- "Cancelada"). La cascada al detalle la realiza el trigger
-- trg_cascadaBajaReparacion.
-- ------------------------------------------------------------
CREATE PROCEDURE sp_bajaLogicaReparacion
    @NroReparacion INT
AS
BEGIN
    SET NOCOUNT ON;
    BEGIN TRY
        BEGIN TRANSACTION;

        IF NOT EXISTS (SELECT 1 FROM Reparacion
                       WHERE NroReparacion = @NroReparacion AND Activo = 1)
        BEGIN
            PRINT 'La reparacion no existe o ya esta dada de baja.';
            ROLLBACK TRANSACTION;
            RETURN;
        END

        DECLARE @IdCancelada INT =
            (SELECT Id FROM EstadoReparacion WHERE Descripcion = 'Cancelada');

        UPDATE Reparacion
        SET Activo   = 0,
            IdEstado = @IdCancelada
        WHERE NroReparacion = @NroReparacion;

        COMMIT TRANSACTION;
        PRINT 'Reparacion dada de baja correctamente.';
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0 ROLLBACK TRANSACTION;
        PRINT 'Error: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;
GO

PRINT 'Procedimientos creados correctamente.';
GO
