-- ============================================================
-- TPI Base de Datos II - Grupo 79 - Sistema de Reparaciones
-- 01 - Creacion de base de datos, tipos y tablas (DER v2)
-- Motor: Microsoft SQL Server (probado en SQL Server Express)
-- ============================================================

IF DB_ID('Reparaciones_G79') IS NULL
    CREATE DATABASE Reparaciones_G79;
GO
USE Reparaciones_G79;
GO

-- ------------------------------------------------------------
-- Limpieza (orden inverso de dependencias) para reejecutar
-- ------------------------------------------------------------
IF OBJECT_ID('DetalleReparacion','U') IS NOT NULL DROP TABLE DetalleReparacion;
IF OBJECT_ID('Reparacion','U')        IS NOT NULL DROP TABLE Reparacion;
IF OBJECT_ID('Equipo','U')            IS NOT NULL DROP TABLE Equipo;
IF OBJECT_ID('Cliente','U')           IS NOT NULL DROP TABLE Cliente;
IF OBJECT_ID('Empleado','U')          IS NOT NULL DROP TABLE Empleado;
IF OBJECT_ID('EstadoReparacion','U')  IS NOT NULL DROP TABLE EstadoReparacion;
IF OBJECT_ID('TipoEquipo','U')        IS NOT NULL DROP TABLE TipoEquipo;
IF OBJECT_ID('TipoCliente','U')       IS NOT NULL DROP TABLE TipoCliente;
IF TYPE_ID('dbo.TipoDetalleReparacion') IS NOT NULL DROP TYPE dbo.TipoDetalleReparacion;
GO

-- ------------------------------------------------------------
-- Tablas parametricas (lookup).
-- El Id NO es IDENTITY: se cargan con valores explicitos que
-- coinciden con los codigos usados por la aplicacion C++.
-- ------------------------------------------------------------
CREATE TABLE TipoCliente (
    Id          INT          NOT NULL PRIMARY KEY,
    Descripcion VARCHAR(50)  NOT NULL UNIQUE
);

CREATE TABLE TipoEquipo (
    Id          INT          NOT NULL PRIMARY KEY,
    Descripcion VARCHAR(50)  NOT NULL UNIQUE
);

CREATE TABLE EstadoReparacion (
    Id          INT          NOT NULL PRIMARY KEY,
    Descripcion VARCHAR(50)  NOT NULL UNIQUE
);

-- ------------------------------------------------------------
-- Empleado (tecnico del taller)
-- ------------------------------------------------------------
CREATE TABLE Empleado (
    Legajo    INT          NOT NULL PRIMARY KEY,
    Nombre    VARCHAR(50)  NOT NULL,
    Apellido  VARCHAR(50)  NOT NULL,
    Email     VARCHAR(100) NULL,
    Activo    BIT          NOT NULL DEFAULT 1,
    FechaAlta DATETIME     NOT NULL DEFAULT GETDATE()
);

-- ------------------------------------------------------------
-- Cliente (particular o empresa). Nombre/Apellido nulos para
-- empresas; RazonSocial nula para particulares.
-- ------------------------------------------------------------
CREATE TABLE Cliente (
    CUIT          VARCHAR(13)  NOT NULL PRIMARY KEY,
    Nombre        VARCHAR(50)  NULL,
    Apellido      VARCHAR(50)  NULL,
    RazonSocial   VARCHAR(100) NULL,
    Email         VARCHAR(100) NULL,
    Telefono      VARCHAR(30)  NULL,
    Direccion     VARCHAR(150) NULL,
    IdTipoCliente INT          NOT NULL,
    Activo        BIT          NOT NULL DEFAULT 1,
    FechaAlta     DATETIME     NOT NULL DEFAULT GETDATE(),
    FechaBaja     DATETIME     NULL,
    CONSTRAINT FK_Cliente_TipoCliente FOREIGN KEY (IdTipoCliente)
        REFERENCES TipoCliente(Id)
);

-- ------------------------------------------------------------
-- Equipo (pertenece a un cliente). NroEquipo lo asigna la app.
-- ------------------------------------------------------------
CREATE TABLE Equipo (
    NroEquipo    INT          NOT NULL PRIMARY KEY,
    CUIT         VARCHAR(13)  NOT NULL,
    Descripcion  VARCHAR(150) NOT NULL,
    Marca        VARCHAR(50)  NULL,
    IdTipoEquipo INT          NOT NULL,
    FechaIngreso DATE         NOT NULL DEFAULT CAST(GETDATE() AS DATE),
    Activo       BIT          NOT NULL DEFAULT 1,
    CONSTRAINT FK_Equipo_Cliente FOREIGN KEY (CUIT)
        REFERENCES Cliente(CUIT),
    CONSTRAINT FK_Equipo_TipoEquipo FOREIGN KEY (IdTipoEquipo)
        REFERENCES TipoEquipo(Id)
);

-- ------------------------------------------------------------
-- Reparacion (cabecera). NroReparacion lo asigna la app.
-- TotalCalculado lo mantiene el trigger trg_actualizarTotalRep.
-- Estado normalizado via IdEstado (FK a EstadoReparacion) - DER v2.
-- ------------------------------------------------------------
CREATE TABLE Reparacion (
    NroReparacion  INT           NOT NULL PRIMARY KEY,
    CUIT           VARCHAR(13)   NOT NULL,
    Legajo         INT           NOT NULL,
    FechaIngreso   DATE          NOT NULL DEFAULT CAST(GETDATE() AS DATE),
    FechaEntrega   DATE          NULL,
    IdEstado       INT           NOT NULL DEFAULT 1,
    TotalCalculado DECIMAL(12,2) NOT NULL DEFAULT 0,
    Activo         BIT           NOT NULL DEFAULT 1,
    CONSTRAINT FK_Reparacion_Cliente FOREIGN KEY (CUIT)
        REFERENCES Cliente(CUIT),
    CONSTRAINT FK_Reparacion_Empleado FOREIGN KEY (Legajo)
        REFERENCES Empleado(Legajo),
    CONSTRAINT FK_Reparacion_Estado FOREIGN KEY (IdEstado)
        REFERENCES EstadoReparacion(Id)
);

-- ------------------------------------------------------------
-- DetalleReparacion (lineas de la orden). Id IDENTITY.
-- ------------------------------------------------------------
CREATE TABLE DetalleReparacion (
    Id            INT           IDENTITY(1,1) PRIMARY KEY,
    NroReparacion INT           NOT NULL,
    NroEquipo     INT           NOT NULL,
    Importe       DECIMAL(12,2) NOT NULL CHECK (Importe >= 0),
    Descripcion   VARCHAR(255)  NULL,
    Activo        BIT           NOT NULL DEFAULT 1,
    CONSTRAINT FK_Detalle_Reparacion FOREIGN KEY (NroReparacion)
        REFERENCES Reparacion(NroReparacion),
    CONSTRAINT FK_Detalle_Equipo FOREIGN KEY (NroEquipo)
        REFERENCES Equipo(NroEquipo)
);
GO

-- ------------------------------------------------------------
-- Tipo tabla (TVP) usado por sp_altaReparacionConDetalle
-- ------------------------------------------------------------
CREATE TYPE dbo.TipoDetalleReparacion AS TABLE (
    NroEquipo   INT           NOT NULL,
    Importe     DECIMAL(12,2) NOT NULL,
    Descripcion VARCHAR(255)  NULL
);
GO

PRINT 'Esquema creado correctamente.';
GO
