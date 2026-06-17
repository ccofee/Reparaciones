-- ============================================================
-- 06 - Datos de prueba
-- Los Id de las tablas parametricas son explicitos y coinciden
-- con los codigos que usa la aplicacion C++.
-- ============================================================
USE Reparaciones_G79;
GO

-- ---------- Tablas parametricas ----------
INSERT INTO TipoCliente (Id, Descripcion) VALUES
    (1, 'Particular'),
    (2, 'Empresa');

INSERT INTO TipoEquipo (Id, Descripcion) VALUES
    (1, 'PC escritorio'),
    (2, 'Notebook'),
    (3, 'Impresora'),
    (4, 'Periferico'),
    (5, 'Celular');

INSERT INTO EstadoReparacion (Id, Descripcion) VALUES
    (1, 'Sin iniciar'),
    (2, 'En proceso'),
    (3, 'Terminada'),
    (4, 'Cancelada');
GO

-- ---------- Empleados (mismos que precarga la app) ----------
INSERT INTO Empleado (Legajo, Nombre, Apellido, Email) VALUES
    (123,    'Agustin Nahuel', 'Parada',     'aparada@taller.com'),
    (1234,   'Luz',            'Campagnale', 'lcampagnale@taller.com'),
    (12345,  'Enzo Gabriel',   'Sander',     'esander@taller.com'),
    (123456, 'Claudio Andres', 'Arce',       'carce@taller.com');
GO

-- ---------- Clientes (particulares y empresas) ----------
-- (pasan por el trigger INSTEAD OF INSERT trg_validarUnicidadCUIT)
INSERT INTO Cliente (CUIT, Nombre, Apellido, RazonSocial, Email, Telefono, Direccion, IdTipoCliente) VALUES
    ('20-12345678-9', 'Juan',  'Perez', NULL,         'juan.perez@mail.com', '1145678901', 'Av. Siempreviva 742',  1),
    ('27-98765432-1', 'Maria', 'Gomez', NULL,         'maria.gomez@mail.com','1156789012', 'Calle Falsa 123',      1),
    ('20-30303030-3', 'Carlos','Lopez', NULL,         'clopez@mail.com',     '1167890123', 'Mitre 456',            1),
    ('30-11223344-5', NULL,    NULL,    'Tecno SRL',  'contacto@tecno.com',  '1148001122', 'Parque Industrial 10', 2),
    ('30-55667788-9', NULL,    NULL,    'Compu SA',   'ventas@compusa.com',  '1148003344', 'Ruta 8 Km 35',         2);
GO

-- ---------- Equipos ----------
INSERT INTO Equipo (NroEquipo, CUIT, Descripcion, Marca, IdTipoEquipo, FechaIngreso) VALUES
    (1, '20-12345678-9', 'Notebook 14 pulgadas',   'Lenovo',   2, '20260510'),
    (2, '20-12345678-9', 'Impresora multifuncion', 'HP',       3, '20260510'),
    (3, '27-98765432-1', 'PC de escritorio i5',     'Dell',     1, '20260512'),
    (4, '30-11223344-5', 'Notebook empresarial',    'Asus',     2, '20260514'),
    (5, '30-55667788-9', 'Celular gama media',      'Samsung',  5, '20260515'),
    (6, '20-30303030-3', 'Teclado mecanico',        'Logitech', 4, '20260516');
GO

-- ---------- Reparaciones (cabecera) ----------
INSERT INTO Reparacion (NroReparacion, CUIT, Legajo, FechaIngreso, FechaEntrega, IdEstado) VALUES
    (1, '20-12345678-9', 123,   '20260510', '20260513', 3),  -- Terminada
    (2, '27-98765432-1', 1234,  '20260512', NULL,       2),  -- En proceso
    (3, '30-11223344-5', 12345, '20260514', NULL,       1),  -- Sin iniciar
    (4, '30-55667788-9', 123,   '20260515', '20260518', 3);  -- Terminada
GO

-- ---------- Detalle de reparaciones ----------
-- (el trigger trg_actualizarTotalRep recalcula TotalCalculado)
INSERT INTO DetalleReparacion (NroReparacion, NroEquipo, Importe, Descripcion) VALUES
    (1, 1, 15000.00, 'Cambio de teclado y bateria'),
    (1, 2,  8000.00, 'Limpieza de cabezal de impresion'),
    (2, 3, 22000.00, 'Reemplazo de fuente de alimentacion'),
    (3, 4, 12000.00, 'Reinstalacion de sistema operativo'),
    (4, 5, 30000.00, 'Cambio de pantalla');
GO

PRINT 'Datos de prueba cargados correctamente.';
GO
