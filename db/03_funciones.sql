-- ============================================================
-- 03 - Funciones
-- ============================================================
USE Reparaciones_G79;
GO

IF OBJECT_ID('fn_calcularTotalReparacion','FN') IS NOT NULL
    DROP FUNCTION fn_calcularTotalReparacion;
GO

-- ------------------------------------------------------------
-- Devuelve la suma de los importes activos del detalle de una
-- reparacion. Util para reportes y validaciones bajo demanda.
-- ------------------------------------------------------------
CREATE FUNCTION fn_calcularTotalReparacion (@NroReparacion INT)
RETURNS DECIMAL(12,2)
AS
BEGIN
    DECLARE @Total DECIMAL(12,2);

    SELECT @Total = SUM(Importe)
    FROM DetalleReparacion
    WHERE NroReparacion = @NroReparacion
      AND Activo = 1;

    RETURN ISNULL(@Total, 0);
END;
GO

PRINT 'Funcion creada correctamente.';
GO
