#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Cliente {
    char cuit[15];
    char nombre[20];
    char apellido[20];
    char telefono[20];
    char email[40];
    char direccion[50];
    int tipoCliente;
    bool eliminado;
};

struct Equipo {
    int nroEquipo;
    char cuit[15];
    char descripcion[50];
    char marca[30];
    int tipoEquipo;
    Fecha fechaIngreso;
    bool eliminado;
};

struct Empleado {
    char legajo[10];
    char nombre[20];
    char apellido[20];
    bool eliminado;
};

struct Reparacion {
    int nroReparacion;
    char cuit[15];
    char legajo[10];
    Fecha fechaEntrega;
    bool eliminado;
};

struct DetalleReparacion {
    int nroReparacion;
    int nroEquipo;
    float importe;
    bool eliminado;
};

bool archivoExiste(const char* nombreArchivo);
void crearArchivoSiNoExiste(const char* nombreArchivo);
void limpiarBuffer();
void mostrarFecha(const Fecha& fecha);

bool guardarCliente(const Cliente& cliente);
int contarClientes();
Cliente leerCliente(int posicion);
bool actualizarCliente(int posicion, const Cliente& cliente);

bool guardarEquipo(const Equipo& equipo);
int contarEquipos();
Equipo leerEquipo(int posicion);
bool actualizarEquipo(int posicion, const Equipo& equipo);

bool guardarEmpleado(const Empleado& empleado);
int contarEmpleados();
Empleado leerEmpleado(int posicion);
bool actualizarEmpleado(int posicion, const Empleado& empleado);

bool guardarReparacion(const Reparacion& reparacion);
int contarReparaciones();
Reparacion leerReparacion(int posicion);
bool actualizarReparacion(int posicion, const Reparacion& reparacion);

bool guardarDetalleReparacion(const DetalleReparacion& detalle);
int contarDetallesReparacion();
DetalleReparacion leerDetalleReparacion(int posicion);
bool actualizarDetalleReparacion(int posicion, const DetalleReparacion& detalle);

int buscarClientePorCUIT(const char* cuit);
bool existeClienteActivoPorCUIT(const char* cuit);

int buscarEquipoPorNumero(int nroEquipo);
bool existeEquipoActivoPorNumero(int nroEquipo);
bool equipoPerteneceACliente(int nroEquipo, const char* cuit);

int buscarEmpleadoPorLegajo(const char* legajo);
bool existeEmpleadoActivoPorLegajo(const char* legajo);

int buscarReparacionPorNumero(int nroReparacion);
bool existeReparacionActivaPorNumero(int nroReparacion);
int siguienteNroReparacion();

bool detalleYaCargado(int nroReparacion, int nroEquipo);

bool validarCadenaNoVacia(const char* cadena);
bool validarFecha(const Fecha& fecha);

bool validarCUITUnico(const char* cuit);
bool validarEmail(const char* email);
bool validarTipoCliente(int tipo);

bool validarNroEquipo(int nro);
bool validarNroEquipoUnico(int nro);
bool validarTipoEquipo(int tipo);

bool validarLegajoUnico(const char* legajo);

bool validarImporte(float importe);
bool validarEquipoExiste(int nroEquipo);
bool validarClienteExiste(const char* cuit);
bool validarEmpleadoExiste(const char* legajo);

void ingresarFecha(Fecha& fecha);
void ingresarCliente(Cliente& cliente);
void ingresarEquipo(Equipo& equipo);
void ingresarEmpleado(Empleado& empleado);

void mostrarCliente(const Cliente& cliente);
void mostrarEquipo(const Equipo& equipo);
void mostrarEmpleado(const Empleado& empleado);
void mostrarReparacion(const Reparacion& reparacion);
void mostrarEquiposDeCliente(const char* cuit);

void altaCliente();
void bajaCliente();
void modificacionCliente();
void listadoClientes();

void altaEquipo();
void bajaEquipo();
void modificacionEquipo();
void listadoEquipos();

void altaEmpleado();
void bajaEmpleado();
void modificacionEmpleado();
void listadoEmpleados();

void altaReparacion();
void bajaReparacion();
void modificacionReparacion();
void listadoReparaciones();

float calcularTotalReparacion(int nroReparacion);
int contarEquiposDeReparacion(int nroReparacion);
bool fechaEnRango(const Fecha& f, const Fecha& desde, const Fecha& hasta);
const char* nombreMes(int mes);
const char* nombreTipoEquipo(int tipo);

void listadoClientesPorApellido();
void listadoEquiposPorFechaIngreso();
void listadoReparacionesPorFechaEntrega();
void listadoEmpleadosPorApellido();

void consultaClientePorCUIT();
void consultaReparacionesPorCliente();
void consultaReparacionesPorRangoFechas();
void consultaEquiposPorCliente();

void informeRecaudacionAnual();
void informeRecaudacionPorCliente();
void informeReparacionesPorTipoEquipo();
void informeProductividadEmpleados();

bool copiarArchivo(const char* origen, const char* destino);
void asegurarCarpeta(const char* nombreCarpeta);

void backupArchivo(const char* nombreDat);
void backupTodos();
void restaurarArchivo(const char* nombreDat);
void restaurarTodos();

void exportarClientesCSV();
void exportarEquiposCSV();
void exportarEmpleadosCSV();
void exportarReparacionesCSV();
void exportarDetalleReparacionesCSV();
void exportarTodosCSV();

void menuClientes();
void menuEquipos();
void menuEmpleados();
void menuReparaciones();
void menuConsultas();
void menuInformes();
void menuConfiguracion();
void menuBackup();
void menuRestaurar();
void menuExportarCSV();

#endif
