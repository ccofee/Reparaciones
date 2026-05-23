#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <direct.h>
#include "funciones.h"

using namespace std;

bool archivoExiste(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo);
    bool existe = archivo.good();
    archivo.close();
    return existe;
}

void crearArchivoSiNoExiste(const char* nombreArchivo) {
    if (!archivoExiste(nombreArchivo)) {
        ofstream archivo(nombreArchivo, ios::binary);
        archivo.close();
    }
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void mostrarFecha(const Fecha& fecha) {
    cout << fecha.dia << "/" << fecha.mes << "/" << fecha.anio;
}

bool guardarCliente(const Cliente& cliente) {
    ofstream archivo("clientes.dat", ios::binary | ios::app);
    if (!archivo) return false;

    archivo.write((const char*)&cliente, sizeof(Cliente));
    archivo.close();
    return true;
}

int contarClientes() {
    ifstream archivo("clientes.dat", ios::binary | ios::ate);
    if (!archivo.is_open()) return 0;

    streampos pos = archivo.tellg();
    archivo.close();
    if (pos <= 0) return 0;
    return (int)(pos / (streampos)sizeof(Cliente));
}

Cliente leerCliente(int posicion) {
    Cliente cliente;
    ifstream archivo("clientes.dat", ios::binary);
    archivo.seekg(posicion * sizeof(Cliente), ios::beg);
    archivo.read((char*)&cliente, sizeof(Cliente));
    archivo.close();
    return cliente;
}

bool actualizarCliente(int posicion, const Cliente& cliente) {
    fstream archivo("clientes.dat", ios::binary | ios::in | ios::out);
    if (!archivo) return false;

    archivo.seekp(posicion * sizeof(Cliente), ios::beg);
    archivo.write((const char*)&cliente, sizeof(Cliente));
    archivo.close();
    return true;
}

bool guardarEquipo(const Equipo& equipo) {
    ofstream archivo("equipos.dat", ios::binary | ios::app);
    if (!archivo) return false;

    archivo.write((const char*)&equipo, sizeof(Equipo));
    archivo.close();
    return true;
}

int contarEquipos() {
    ifstream archivo("equipos.dat", ios::binary | ios::ate);
    if (!archivo.is_open()) return 0;

    streampos pos = archivo.tellg();
    archivo.close();
    if (pos <= 0) return 0;
    return (int)(pos / (streampos)sizeof(Equipo));
}

Equipo leerEquipo(int posicion) {
    Equipo equipo;
    ifstream archivo("equipos.dat", ios::binary);
    archivo.seekg(posicion * sizeof(Equipo), ios::beg);
    archivo.read((char*)&equipo, sizeof(Equipo));
    archivo.close();
    return equipo;
}

bool actualizarEquipo(int posicion, const Equipo& equipo) {
    fstream archivo("equipos.dat", ios::binary | ios::in | ios::out);
    if (!archivo) return false;

    archivo.seekp(posicion * sizeof(Equipo), ios::beg);
    archivo.write((const char*)&equipo, sizeof(Equipo));
    archivo.close();
    return true;
}

bool guardarEmpleado(const Empleado& empleado) {
    ofstream archivo("empleados.dat", ios::binary | ios::app);
    if (!archivo) return false;

    archivo.write((const char*)&empleado, sizeof(Empleado));
    archivo.close();
    return true;
}

int contarEmpleados() {
    ifstream archivo("empleados.dat", ios::binary | ios::ate);
    if (!archivo.is_open()) return 0;

    streampos pos = archivo.tellg();
    archivo.close();
    if (pos <= 0) return 0;
    return (int)(pos / (streampos)sizeof(Empleado));
}

Empleado leerEmpleado(int posicion) {
    Empleado empleado;
    ifstream archivo("empleados.dat", ios::binary);
    archivo.seekg(posicion * sizeof(Empleado), ios::beg);
    archivo.read((char*)&empleado, sizeof(Empleado));
    archivo.close();
    return empleado;
}

bool actualizarEmpleado(int posicion, const Empleado& empleado) {
    fstream archivo("empleados.dat", ios::binary | ios::in | ios::out);
    if (!archivo) return false;

    archivo.seekp(posicion * sizeof(Empleado), ios::beg);
    archivo.write((const char*)&empleado, sizeof(Empleado));
    archivo.close();
    return true;
}

bool guardarReparacion(const Reparacion& reparacion) {
    ofstream archivo("reparaciones.dat", ios::binary | ios::app);
    if (!archivo) return false;

    archivo.write((const char*)&reparacion, sizeof(Reparacion));
    archivo.close();
    return true;
}

int contarReparaciones() {
    ifstream archivo("reparaciones.dat", ios::binary | ios::ate);
    if (!archivo.is_open()) return 0;

    streampos pos = archivo.tellg();
    archivo.close();
    if (pos <= 0) return 0;
    return (int)(pos / (streampos)sizeof(Reparacion));
}

Reparacion leerReparacion(int posicion) {
    Reparacion reparacion;
    ifstream archivo("reparaciones.dat", ios::binary);
    archivo.seekg(posicion * sizeof(Reparacion), ios::beg);
    archivo.read((char*)&reparacion, sizeof(Reparacion));
    archivo.close();
    return reparacion;
}

bool actualizarReparacion(int posicion, const Reparacion& reparacion) {
    fstream archivo("reparaciones.dat", ios::binary | ios::in | ios::out);
    if (!archivo) return false;

    archivo.seekp(posicion * sizeof(Reparacion), ios::beg);
    archivo.write((const char*)&reparacion, sizeof(Reparacion));
    archivo.close();
    return true;
}

bool guardarDetalleReparacion(const DetalleReparacion& detalle) {
    ofstream archivo("detalleReparaciones.dat", ios::binary | ios::app);
    if (!archivo) return false;

    archivo.write((const char*)&detalle, sizeof(DetalleReparacion));
    archivo.close();
    return true;
}

int contarDetallesReparacion() {
    ifstream archivo("detalleReparaciones.dat", ios::binary | ios::ate);
    if (!archivo.is_open()) return 0;

    streampos pos = archivo.tellg();
    archivo.close();
    if (pos <= 0) return 0;
    return (int)(pos / (streampos)sizeof(DetalleReparacion));
}

DetalleReparacion leerDetalleReparacion(int posicion) {
    DetalleReparacion detalle;
    ifstream archivo("detalleReparaciones.dat", ios::binary);
    archivo.seekg(posicion * sizeof(DetalleReparacion), ios::beg);
    archivo.read((char*)&detalle, sizeof(DetalleReparacion));
    archivo.close();
    return detalle;
}

bool actualizarDetalleReparacion(int posicion, const DetalleReparacion& detalle) {
    fstream archivo("detalleReparaciones.dat", ios::binary | ios::in | ios::out);
    if (!archivo) return false;

    archivo.seekp(posicion * sizeof(DetalleReparacion), ios::beg);
    archivo.write((const char*)&detalle, sizeof(DetalleReparacion));
    archivo.close();
    return true;
}

int buscarClientePorCUIT(const char* cuit) {
    int cantidad = contarClientes();

    for (int i = 0; i < cantidad; i++) {
        Cliente cliente = leerCliente(i);

        if (strcmp(cliente.cuit, cuit) == 0 && !cliente.eliminado) {
            return i;
        }
    }

    return -1;
}

bool existeClienteActivoPorCUIT(const char* cuit) {
    return buscarClientePorCUIT(cuit) != -1;
}

int buscarEquipoPorNumero(int nroEquipo) {
    int cantidad = contarEquipos();

    for (int i = 0; i < cantidad; i++) {
        Equipo equipo = leerEquipo(i);

        if (equipo.nroEquipo == nroEquipo && !equipo.eliminado) {
            return i;
        }
    }

    return -1;
}

bool existeEquipoActivoPorNumero(int nroEquipo) {
    return buscarEquipoPorNumero(nroEquipo) != -1;
}

bool equipoPerteneceACliente(int nroEquipo, const char* cuit) {
    int pos = buscarEquipoPorNumero(nroEquipo);
    if (pos == -1) return false;

    Equipo equipo = leerEquipo(pos);
    return strcmp(equipo.cuit, cuit) == 0;
}

int buscarEmpleadoPorLegajo(const char* legajo) {
    int cantidad = contarEmpleados();

    for (int i = 0; i < cantidad; i++) {
        Empleado empleado = leerEmpleado(i);

        if (strcmp(empleado.legajo, legajo) == 0 && !empleado.eliminado) {
            return i;
        }
    }

    return -1;
}

bool existeEmpleadoActivoPorLegajo(const char* legajo) {
    return buscarEmpleadoPorLegajo(legajo) != -1;
}

int buscarReparacionPorNumero(int nroReparacion) {
    int cantidad = contarReparaciones();

    for (int i = 0; i < cantidad; i++) {
        Reparacion rep = leerReparacion(i);

        if (rep.nroReparacion == nroReparacion && !rep.eliminado) {
            return i;
        }
    }

    return -1;
}

bool existeReparacionActivaPorNumero(int nroReparacion) {
    return buscarReparacionPorNumero(nroReparacion) != -1;
}

int siguienteNroReparacion() {
    int cantidad = contarReparaciones();
    int maxNro = 0;

    for (int i = 0; i < cantidad; i++) {
        Reparacion rep = leerReparacion(i);
        if (rep.nroReparacion > maxNro) {
            maxNro = rep.nroReparacion;
        }
    }

    return maxNro + 1;
}

bool detalleYaCargado(int nroReparacion, int nroEquipo) {
    int cantidad = contarDetallesReparacion();

    for (int i = 0; i < cantidad; i++) {
        DetalleReparacion det = leerDetalleReparacion(i);

        if (det.nroReparacion == nroReparacion &&
            det.nroEquipo == nroEquipo &&
            !det.eliminado) {
            return true;
        }
    }

    return false;
}

bool validarCadenaNoVacia(const char* cadena) {
    return strlen(cadena) > 0;
}

bool validarFecha(const Fecha& fecha) {
    return fecha.dia >= 1 && fecha.dia <= 31 &&
           fecha.mes >= 1 && fecha.mes <= 12 &&
           fecha.anio > 0;
}

bool validarCUITUnico(const char* cuit) {
    return !existeClienteActivoPorCUIT(cuit);
}

bool validarEmail(const char* email) {
    return strchr(email, '@') != NULL;
}

bool validarTipoCliente(int tipo) {
    return tipo == 1 || tipo == 2;
}

bool validarNroEquipo(int nro) {
    return nro > 0;
}

bool validarNroEquipoUnico(int nro) {
    return !existeEquipoActivoPorNumero(nro);
}

bool validarTipoEquipo(int tipo) {
    return tipo >= 1 && tipo <= 5;
}

bool validarLegajoUnico(const char* legajo) {
    return !existeEmpleadoActivoPorLegajo(legajo);
}

bool validarImporte(float importe) {
    return importe > 0;
}

bool validarEquipoExiste(int nroEquipo) {
    return existeEquipoActivoPorNumero(nroEquipo);
}

bool validarClienteExiste(const char* cuit) {
    return existeClienteActivoPorCUIT(cuit);
}

bool validarEmpleadoExiste(const char* legajo) {
    return existeEmpleadoActivoPorLegajo(legajo);
}

void ingresarFecha(Fecha& fecha) {
    do {
        cout << "Dia: ";
        cin >> fecha.dia;
        cout << "Mes: ";
        cin >> fecha.mes;
        cout << "Anio: ";
        cin >> fecha.anio;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Debe ingresar numeros validos. Reingrese." << endl;
        } else if (!validarFecha(fecha)) {
            cout << "Fecha invalida. Dia (1-31), Mes (1-12), Anio (>0). Reingrese." << endl;
        }
    } while (cin.fail() || !validarFecha(fecha));
}

void ingresarCliente(Cliente& cliente) {
    limpiarBuffer();

    do {
        cout << "CUIT: ";
        cin.getline(cliente.cuit, 15);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El CUIT es demasiado largo (maximo 14 caracteres). Reingrese." << endl;
            cliente.cuit[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.cuit)) {
            cout << "El CUIT no puede estar vacio. Reingrese." << endl;
        } else if (!validarCUITUnico(cliente.cuit)) {
            cout << "El CUIT ya existe. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.cuit) || !validarCUITUnico(cliente.cuit));

    do {
        cout << "Nombre: ";
        cin.getline(cliente.nombre, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El nombre es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            cliente.nombre[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.nombre)) {
            cout << "El nombre no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.nombre));

    do {
        cout << "Apellido: ";
        cin.getline(cliente.apellido, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El apellido es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            cliente.apellido[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.apellido)) {
            cout << "El apellido no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.apellido));

    do {
        cout << "Telefono: ";
        cin.getline(cliente.telefono, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El telefono es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            cliente.telefono[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.telefono)) {
            cout << "El telefono no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.telefono));

    do {
        cout << "Email: ";
        cin.getline(cliente.email, 40);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El email es demasiado largo (maximo 39 caracteres). Reingrese." << endl;
            cliente.email[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.email)) {
            cout << "El email no puede estar vacio. Reingrese." << endl;
        } else if (!validarEmail(cliente.email)) {
            cout << "El email debe contener @. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.email) || !validarEmail(cliente.email));

    do {
        cout << "Direccion: ";
        cin.getline(cliente.direccion, 50);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "La direccion es demasiado larga (maximo 49 caracteres). Reingrese." << endl;
            cliente.direccion[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.direccion)) {
            cout << "La direccion no puede estar vacia. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.direccion));

    do {
        cout << "Tipo de cliente (1=Particular, 2=Empresa): ";
        cin >> cliente.tipoCliente;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Debe ingresar un numero valido. Reingrese." << endl;
        } else if (!validarTipoCliente(cliente.tipoCliente)) {
            cout << "Tipo invalido. Solo 1 o 2. Reingrese." << endl;
        }
    } while (cin.fail() || !validarTipoCliente(cliente.tipoCliente));

    cliente.eliminado = false;
}

void ingresarEquipo(Equipo& equipo) {

    do {
        cout << "Numero de equipo: ";
        cin >> equipo.nroEquipo;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Debe ingresar un numero valido. Reingrese." << endl;
        } else if (!validarNroEquipo(equipo.nroEquipo)) {
            cout << "El numero debe ser mayor a 0. Reingrese." << endl;
        } else if (!validarNroEquipoUnico(equipo.nroEquipo)) {
            cout << "El numero de equipo ya existe. Reingrese." << endl;
        }
    } while (cin.fail() || !validarNroEquipo(equipo.nroEquipo) || !validarNroEquipoUnico(equipo.nroEquipo));

    limpiarBuffer();

    do {
        cout << "CUIT del cliente propietario: ";
        cin.getline(equipo.cuit, 15);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El CUIT es demasiado largo (maximo 14 caracteres). Reingrese." << endl;
            equipo.cuit[0] = '\0';
        } else if (!validarCadenaNoVacia(equipo.cuit)) {
            cout << "El CUIT no puede estar vacio. Reingrese." << endl;
        } else if (!validarClienteExiste(equipo.cuit)) {
            cout << "El cliente no existe o esta eliminado. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(equipo.cuit) || !validarClienteExiste(equipo.cuit));

    do {
        cout << "Descripcion: ";
        cin.getline(equipo.descripcion, 50);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "La descripcion es demasiado larga (maximo 49 caracteres). Reingrese." << endl;
            equipo.descripcion[0] = '\0';
        } else if (!validarCadenaNoVacia(equipo.descripcion)) {
            cout << "La descripcion no puede estar vacia. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(equipo.descripcion));

    do {
        cout << "Marca: ";
        cin.getline(equipo.marca, 30);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "La marca es demasiado larga (maximo 29 caracteres). Reingrese." << endl;
            equipo.marca[0] = '\0';
        } else if (!validarCadenaNoVacia(equipo.marca)) {
            cout << "La marca no puede estar vacia. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(equipo.marca));

    do {
        cout << "Tipo de equipo (1=PC escritorio, 2=Notebook, 3=Impresora, 4=Periferico, 5=Celular): ";
        cin >> equipo.tipoEquipo;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Debe ingresar un numero valido. Reingrese." << endl;
        } else if (!validarTipoEquipo(equipo.tipoEquipo)) {
            cout << "Tipo invalido. Solo 1, 2, 3, 4 o 5. Reingrese." << endl;
        }
    } while (cin.fail() || !validarTipoEquipo(equipo.tipoEquipo));

    cout << "Fecha de ingreso:" << endl;
    ingresarFecha(equipo.fechaIngreso);

    equipo.eliminado = false;
}

void ingresarEmpleado(Empleado& empleado) {
    limpiarBuffer();

    do {
        cout << "Legajo: ";
        cin.getline(empleado.legajo, 10);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El legajo es demasiado largo (maximo 9 caracteres). Reingrese." << endl;
            empleado.legajo[0] = '\0';
        } else if (!validarCadenaNoVacia(empleado.legajo)) {
            cout << "El legajo no puede estar vacio. Reingrese." << endl;
        } else if (!validarLegajoUnico(empleado.legajo)) {
            cout << "El legajo ya existe. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(empleado.legajo) || !validarLegajoUnico(empleado.legajo));

    do {
        cout << "Nombre: ";
        cin.getline(empleado.nombre, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El nombre es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            empleado.nombre[0] = '\0';
        } else if (!validarCadenaNoVacia(empleado.nombre)) {
            cout << "El nombre no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(empleado.nombre));

    do {
        cout << "Apellido: ";
        cin.getline(empleado.apellido, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El apellido es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            empleado.apellido[0] = '\0';
        } else if (!validarCadenaNoVacia(empleado.apellido)) {
            cout << "El apellido no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(empleado.apellido));

    empleado.eliminado = false;
}

void mostrarCliente(const Cliente& cliente) {
    cout << "CUIT: " << cliente.cuit << endl;
    cout << "Nombre: " << cliente.nombre << " " << cliente.apellido << endl;
    cout << "Telefono: " << cliente.telefono << endl;
    cout << "Email: " << cliente.email << endl;
    cout << "Direccion: " << cliente.direccion << endl;
    cout << "Tipo: " << (cliente.tipoCliente == 1 ? "Particular" : "Empresa") << endl;
    cout << "-----------------------------------" << endl;
}

void mostrarEquipo(const Equipo& equipo) {
    cout << "Numero: " << equipo.nroEquipo << endl;

    int posCliente = buscarClientePorCUIT(equipo.cuit);
    if (posCliente != -1) {
        Cliente cliente = leerCliente(posCliente);
        cout << "Cliente: " << equipo.cuit << " - " << cliente.nombre << " " << cliente.apellido << endl;
    } else {
        cout << "Cliente: " << equipo.cuit << " (no encontrado)" << endl;
    }

    cout << "Descripcion: " << equipo.descripcion << endl;
    cout << "Marca: " << equipo.marca << endl;
    cout << "Tipo: ";
    switch (equipo.tipoEquipo) {
        case 1: cout << "PC escritorio"; break;
        case 2: cout << "Notebook"; break;
        case 3: cout << "Impresora"; break;
        case 4: cout << "Periferico"; break;
        case 5: cout << "Celular"; break;
    }
    cout << endl;
    cout << "Fecha de ingreso: ";
    mostrarFecha(equipo.fechaIngreso);
    cout << endl;
    cout << "-----------------------------------" << endl;
}

void mostrarEmpleado(const Empleado& empleado) {
    cout << "Legajo: " << empleado.legajo << endl;
    cout << "Nombre: " << empleado.nombre << " " << empleado.apellido << endl;
    cout << "-----------------------------------" << endl;
}

void mostrarEquiposDeCliente(const char* cuit) {
    int cantidad = contarEquipos();
    bool hayEquipos = false;

    cout << "\nEquipos del cliente " << cuit << ":" << endl;

    for (int i = 0; i < cantidad; i++) {
        Equipo equipo = leerEquipo(i);

        if (!equipo.eliminado && strcmp(equipo.cuit, cuit) == 0) {
            cout << "  #" << equipo.nroEquipo << " - ";
            switch (equipo.tipoEquipo) {
                case 1: cout << "PC escritorio"; break;
                case 2: cout << "Notebook"; break;
                case 3: cout << "Impresora"; break;
                case 4: cout << "Periferico"; break;
                case 5: cout << "Celular"; break;
            }
            cout << " - " << equipo.marca << " - " << equipo.descripcion << endl;
            hayEquipos = true;
        }
    }

    if (!hayEquipos) {
        cout << "  (sin equipos cargados)" << endl;
    }
}

void mostrarReparacion(const Reparacion& reparacion) {
    cout << "Reparacion #" << reparacion.nroReparacion << endl;

    int posCliente = buscarClientePorCUIT(reparacion.cuit);
    if (posCliente != -1) {
        Cliente cliente = leerCliente(posCliente);
        cout << "Cliente: " << reparacion.cuit << " - " << cliente.nombre << " " << cliente.apellido << endl;
    } else {
        cout << "Cliente: " << reparacion.cuit << " (no encontrado)" << endl;
    }

    int posEmpleado = buscarEmpleadoPorLegajo(reparacion.legajo);
    if (posEmpleado != -1) {
        Empleado empleado = leerEmpleado(posEmpleado);
        cout << "Atendio: " << reparacion.legajo << " - " << empleado.nombre << " " << empleado.apellido << endl;
    } else {
        cout << "Atendio: " << reparacion.legajo << " (no encontrado)" << endl;
    }

    cout << "Fecha de entrega: ";
    mostrarFecha(reparacion.fechaEntrega);
    cout << endl;

    cout << "Equipos reparados:" << endl;
    int cantDetalles = contarDetallesReparacion();
    float total = 0;
    bool hayDetalles = false;

    for (int i = 0; i < cantDetalles; i++) {
        DetalleReparacion det = leerDetalleReparacion(i);

        if (det.nroReparacion == reparacion.nroReparacion && !det.eliminado) {
            cout << "  - Equipo #" << det.nroEquipo;

            int posEquipo = buscarEquipoPorNumero(det.nroEquipo);
            if (posEquipo != -1) {
                Equipo equipo = leerEquipo(posEquipo);
                cout << " (";
                switch (equipo.tipoEquipo) {
                    case 1: cout << "PC escritorio"; break;
                    case 2: cout << "Notebook"; break;
                    case 3: cout << "Impresora"; break;
                    case 4: cout << "Periferico"; break;
                    case 5: cout << "Celular"; break;
                }
                cout << " - " << equipo.descripcion << ")";
            }

            cout << " - Importe: $" << det.importe << endl;
            total += det.importe;
            hayDetalles = true;
        }
    }

    if (!hayDetalles) {
        cout << "  (sin equipos cargados)" << endl;
    }

    cout << "TOTAL: $" << total << endl;
    cout << "-----------------------------------" << endl;
}

void altaCliente() {
    Cliente cliente;

    cout << "\n=== ALTA DE CLIENTE ===" << endl;
    ingresarCliente(cliente);

    if (guardarCliente(cliente)) {
        cout << "\nCliente guardado exitosamente." << endl;
    } else {
        cout << "\nError al guardar el cliente." << endl;
    }
}

void bajaCliente() {
    char cuit[15];

    cout << "\n=== BAJA DE CLIENTE ===" << endl;
    limpiarBuffer();
    cout << "Ingrese CUIT del cliente a dar de baja: ";
    cin.getline(cuit, 15);

    int posicion = buscarClientePorCUIT(cuit);

    if (posicion == -1) {
        cout << "\nCliente no encontrado o ya esta eliminado." << endl;
        return;
    }

    Cliente cliente = leerCliente(posicion);
    cliente.eliminado = true;

    if (actualizarCliente(posicion, cliente)) {
        cout << "\nCliente dado de baja exitosamente." << endl;
    } else {
        cout << "\nError al dar de baja el cliente." << endl;
    }
}

void modificacionCliente() {
    char cuit[15];

    cout << "\n=== MODIFICACION DE CLIENTE ===" << endl;
    limpiarBuffer();
    cout << "Ingrese CUIT del cliente a modificar: ";
    cin.getline(cuit, 15);

    int posicion = buscarClientePorCUIT(cuit);

    if (posicion == -1) {
        cout << "\nCliente no encontrado o esta eliminado." << endl;
        return;
    }

    Cliente cliente = leerCliente(posicion);

    cout << "\nCliente actual:" << endl;
    mostrarCliente(cliente);

    cout << "\nIngrese los nuevos datos:" << endl;

    do {
        cout << "Nombre: ";
        cin.getline(cliente.nombre, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El nombre es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            cliente.nombre[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.nombre)) {
            cout << "El nombre no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.nombre));

    do {
        cout << "Apellido: ";
        cin.getline(cliente.apellido, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El apellido es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            cliente.apellido[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.apellido)) {
            cout << "El apellido no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.apellido));

    do {
        cout << "Telefono: ";
        cin.getline(cliente.telefono, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El telefono es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            cliente.telefono[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.telefono)) {
            cout << "El telefono no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.telefono));

    do {
        cout << "Email: ";
        cin.getline(cliente.email, 40);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El email es demasiado largo (maximo 39 caracteres). Reingrese." << endl;
            cliente.email[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.email)) {
            cout << "El email no puede estar vacio. Reingrese." << endl;
        } else if (!validarEmail(cliente.email)) {
            cout << "El email debe contener @. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.email) || !validarEmail(cliente.email));

    do {
        cout << "Direccion: ";
        cin.getline(cliente.direccion, 50);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "La direccion es demasiado larga (maximo 49 caracteres). Reingrese." << endl;
            cliente.direccion[0] = '\0';
        } else if (!validarCadenaNoVacia(cliente.direccion)) {
            cout << "La direccion no puede estar vacia. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(cliente.direccion));

    do {
        cout << "Tipo de cliente (1=Particular, 2=Empresa): ";
        cin >> cliente.tipoCliente;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Debe ingresar un numero valido. Reingrese." << endl;
        } else if (!validarTipoCliente(cliente.tipoCliente)) {
            cout << "Tipo invalido. Solo 1 o 2. Reingrese." << endl;
        }
    } while (cin.fail() || !validarTipoCliente(cliente.tipoCliente));

    if (actualizarCliente(posicion, cliente)) {
        cout << "\nCliente modificado exitosamente." << endl;
    } else {
        cout << "\nError al modificar el cliente." << endl;
    }
}

void listadoClientes() {
    cout << "\n=== LISTADO DE CLIENTES ===" << endl;

    int cantidad = contarClientes();

    if (cantidad == 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Cliente cliente = leerCliente(i);

        if (!cliente.eliminado) {
            mostrarCliente(cliente);
            hayActivos = true;
        }
    }

    if (!hayActivos) {
        cout << "No hay clientes activos." << endl;
    }
}

void altaEquipo() {
    Equipo equipo;

    cout << "\n=== ALTA DE EQUIPO ===" << endl;
    ingresarEquipo(equipo);

    if (guardarEquipo(equipo)) {
        cout << "\nEquipo guardado exitosamente." << endl;
    } else {
        cout << "\nError al guardar el equipo." << endl;
    }
}

void bajaEquipo() {
    int nroEquipo;

    cout << "\n=== BAJA DE EQUIPO ===" << endl;
    cout << "Ingrese numero de equipo a dar de baja: ";
    cin >> nroEquipo;

    int posicion = buscarEquipoPorNumero(nroEquipo);

    if (posicion == -1) {
        cout << "\nEquipo no encontrado o ya esta eliminado." << endl;
        return;
    }

    Equipo equipo = leerEquipo(posicion);
    equipo.eliminado = true;

    if (actualizarEquipo(posicion, equipo)) {
        cout << "\nEquipo dado de baja exitosamente." << endl;
    } else {
        cout << "\nError al dar de baja el equipo." << endl;
    }
}

void modificacionEquipo() {
    int nroEquipo;

    cout << "\n=== MODIFICACION DE EQUIPO ===" << endl;
    cout << "Ingrese numero de equipo a modificar: ";
    cin >> nroEquipo;

    int posicion = buscarEquipoPorNumero(nroEquipo);

    if (posicion == -1) {
        cout << "\nEquipo no encontrado o esta eliminado." << endl;
        return;
    }

    Equipo equipo = leerEquipo(posicion);

    cout << "\nEquipo actual:" << endl;
    mostrarEquipo(equipo);

    cout << "\nIngrese los nuevos datos:" << endl;

    limpiarBuffer();

    do {
        cout << "CUIT del cliente propietario: ";
        cin.getline(equipo.cuit, 15);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El CUIT es demasiado largo (maximo 14 caracteres). Reingrese." << endl;
            equipo.cuit[0] = '\0';
        } else if (!validarCadenaNoVacia(equipo.cuit)) {
            cout << "El CUIT no puede estar vacio. Reingrese." << endl;
        } else if (!validarClienteExiste(equipo.cuit)) {
            cout << "El cliente no existe o esta eliminado. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(equipo.cuit) || !validarClienteExiste(equipo.cuit));

    do {
        cout << "Descripcion: ";
        cin.getline(equipo.descripcion, 50);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "La descripcion es demasiado larga (maximo 49 caracteres). Reingrese." << endl;
            equipo.descripcion[0] = '\0';
        } else if (!validarCadenaNoVacia(equipo.descripcion)) {
            cout << "La descripcion no puede estar vacia. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(equipo.descripcion));

    do {
        cout << "Marca: ";
        cin.getline(equipo.marca, 30);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "La marca es demasiado larga (maximo 29 caracteres). Reingrese." << endl;
            equipo.marca[0] = '\0';
        } else if (!validarCadenaNoVacia(equipo.marca)) {
            cout << "La marca no puede estar vacia. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(equipo.marca));

    do {
        cout << "Tipo de equipo (1=PC escritorio, 2=Notebook, 3=Impresora, 4=Periferico, 5=Celular): ";
        cin >> equipo.tipoEquipo;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Debe ingresar un numero valido. Reingrese." << endl;
        } else if (!validarTipoEquipo(equipo.tipoEquipo)) {
            cout << "Tipo invalido. Solo 1, 2, 3, 4 o 5. Reingrese." << endl;
        }
    } while (cin.fail() || !validarTipoEquipo(equipo.tipoEquipo));

    cout << "Fecha de ingreso:" << endl;
    ingresarFecha(equipo.fechaIngreso);

    if (actualizarEquipo(posicion, equipo)) {
        cout << "\nEquipo modificado exitosamente." << endl;
    } else {
        cout << "\nError al modificar el equipo." << endl;
    }
}

void listadoEquipos() {
    cout << "\n=== LISTADO DE EQUIPOS ===" << endl;

    int cantidad = contarEquipos();

    if (cantidad == 0) {
        cout << "No hay equipos registrados." << endl;
        return;
    }

    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Equipo equipo = leerEquipo(i);

        if (!equipo.eliminado) {
            mostrarEquipo(equipo);
            hayActivos = true;
        }
    }

    if (!hayActivos) {
        cout << "No hay equipos activos." << endl;
    }
}

void altaEmpleado() {
    Empleado empleado;

    cout << "\n=== ALTA DE EMPLEADO ===" << endl;
    ingresarEmpleado(empleado);

    if (guardarEmpleado(empleado)) {
        cout << "\nEmpleado guardado exitosamente." << endl;
    } else {
        cout << "\nError al guardar el empleado." << endl;
    }
}

void bajaEmpleado() {
    char legajo[10];

    cout << "\n=== BAJA DE EMPLEADO ===" << endl;
    limpiarBuffer();
    cout << "Ingrese legajo del empleado a dar de baja: ";
    cin.getline(legajo, 10);

    int posicion = buscarEmpleadoPorLegajo(legajo);

    if (posicion == -1) {
        cout << "\nEmpleado no encontrado o ya esta eliminado." << endl;
        return;
    }

    Empleado empleado = leerEmpleado(posicion);
    empleado.eliminado = true;

    if (actualizarEmpleado(posicion, empleado)) {
        cout << "\nEmpleado dado de baja exitosamente." << endl;
    } else {
        cout << "\nError al dar de baja el empleado." << endl;
    }
}

void modificacionEmpleado() {
    char legajo[10];

    cout << "\n=== MODIFICACION DE EMPLEADO ===" << endl;
    limpiarBuffer();
    cout << "Ingrese legajo del empleado a modificar: ";
    cin.getline(legajo, 10);

    int posicion = buscarEmpleadoPorLegajo(legajo);

    if (posicion == -1) {
        cout << "\nEmpleado no encontrado o esta eliminado." << endl;
        return;
    }

    Empleado empleado = leerEmpleado(posicion);

    cout << "\nEmpleado actual:" << endl;
    mostrarEmpleado(empleado);

    cout << "\nIngrese los nuevos datos:" << endl;

    do {
        cout << "Nombre: ";
        cin.getline(empleado.nombre, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El nombre es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            empleado.nombre[0] = '\0';
        } else if (!validarCadenaNoVacia(empleado.nombre)) {
            cout << "El nombre no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(empleado.nombre));

    do {
        cout << "Apellido: ";
        cin.getline(empleado.apellido, 20);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El apellido es demasiado largo (maximo 19 caracteres). Reingrese." << endl;
            empleado.apellido[0] = '\0';
        } else if (!validarCadenaNoVacia(empleado.apellido)) {
            cout << "El apellido no puede estar vacio. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(empleado.apellido));

    if (actualizarEmpleado(posicion, empleado)) {
        cout << "\nEmpleado modificado exitosamente." << endl;
    } else {
        cout << "\nError al modificar el empleado." << endl;
    }
}

void listadoEmpleados() {
    cout << "\n=== LISTADO DE EMPLEADOS ===" << endl;

    int cantidad = contarEmpleados();

    if (cantidad == 0) {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++) {
        Empleado empleado = leerEmpleado(i);

        if (!empleado.eliminado) {
            mostrarEmpleado(empleado);
            hayActivos = true;
        }
    }

    if (!hayActivos) {
        cout << "No hay empleados activos." << endl;
    }
}

static float pedirImporte() {
    float importe;
    do {
        cout << "Importe: ";
        cin >> importe;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Debe ingresar un numero valido. Reingrese." << endl;
        } else if (!validarImporte(importe)) {
            cout << "El importe debe ser mayor a 0. Reingrese." << endl;
        }
    } while (cin.fail() || !validarImporte(importe));
    return importe;
}

static void agregarDetalle(int nroReparacion, int nroEquipo, float importe) {
    DetalleReparacion det;
    det.nroReparacion = nroReparacion;
    det.nroEquipo = nroEquipo;
    det.importe = importe;
    det.eliminado = false;
    guardarDetalleReparacion(det);
}

static int cargarDetallesReparacion(int nroReparacion, const char* cuit) {
    int cargados = 0;

    cout << "\n=== CARGA DE EQUIPOS A REPARAR ===" << endl;
    cout << "(Ingrese 0 como numero de equipo para finalizar)" << endl;

    while (true) {
        mostrarEquiposDeCliente(cuit);

        int nroEquipo;
        cout << "\nNumero de equipo a reparar (0 para finalizar): ";
        cin >> nroEquipo;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Debe ingresar un numero valido." << endl;
            continue;
        }

        if (nroEquipo == 0) {
            if (cargados == 0) {
                cout << "Debe cargar al menos un equipo para la reparacion." << endl;
                continue;
            }
            break;
        }

        if (!existeEquipoActivoPorNumero(nroEquipo)) {
            cout << "El equipo no existe o esta eliminado." << endl;
            continue;
        }

        if (!equipoPerteneceACliente(nroEquipo, cuit)) {
            cout << "El equipo no pertenece al cliente seleccionado." << endl;
            continue;
        }

        if (detalleYaCargado(nroReparacion, nroEquipo)) {
            cout << "Ese equipo ya fue cargado en esta reparacion." << endl;
            continue;
        }

        float importe = pedirImporte();
        agregarDetalle(nroReparacion, nroEquipo, importe);
        cargados++;
        cout << "Equipo agregado al detalle." << endl;
    }

    return cargados;
}

void altaReparacion() {
    cout << "\n=== ALTA DE REPARACION ===" << endl;

    if (contarClientes() == 0) {
        cout << "No hay clientes registrados. Cargue clientes antes de crear una reparacion." << endl;
        return;
    }
    if (contarEquipos() == 0) {
        cout << "No hay equipos registrados. Cargue equipos antes de crear una reparacion." << endl;
        return;
    }

    Reparacion reparacion;
    reparacion.nroReparacion = siguienteNroReparacion();
    cout << "Numero de reparacion asignado: " << reparacion.nroReparacion << endl;

    limpiarBuffer();

    do {
        cout << "CUIT del cliente: ";
        cin.getline(reparacion.cuit, 15);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El CUIT es demasiado largo (maximo 14 caracteres). Reingrese." << endl;
            reparacion.cuit[0] = '\0';
        } else if (!validarCadenaNoVacia(reparacion.cuit)) {
            cout << "El CUIT no puede estar vacio. Reingrese." << endl;
        } else if (!validarClienteExiste(reparacion.cuit)) {
            cout << "El cliente no existe o esta eliminado. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(reparacion.cuit) || !validarClienteExiste(reparacion.cuit));

    do {
        cout << "Legajo del empleado: ";
        cin.getline(reparacion.legajo, 10);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El legajo es demasiado largo (maximo 9 caracteres). Reingrese." << endl;
            reparacion.legajo[0] = '\0';
        } else if (!validarCadenaNoVacia(reparacion.legajo)) {
            cout << "El legajo no puede estar vacio. Reingrese." << endl;
        } else if (!validarEmpleadoExiste(reparacion.legajo)) {
            cout << "El empleado no existe o esta eliminado. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(reparacion.legajo) || !validarEmpleadoExiste(reparacion.legajo));

    cout << "Fecha de entrega:" << endl;
    ingresarFecha(reparacion.fechaEntrega);

    reparacion.eliminado = false;

    if (!guardarReparacion(reparacion)) {
        cout << "\nError al guardar la reparacion." << endl;
        return;
    }

    int cargados = cargarDetallesReparacion(reparacion.nroReparacion, reparacion.cuit);

    cout << "\nReparacion #" << reparacion.nroReparacion
         << " guardada exitosamente con " << cargados << " equipo(s)." << endl;
}

void bajaReparacion() {
    int nroReparacion;

    cout << "\n=== BAJA DE REPARACION ===" << endl;
    cout << "Ingrese numero de reparacion: ";
    cin >> nroReparacion;

    int posicion = buscarReparacionPorNumero(nroReparacion);

    if (posicion == -1) {
        cout << "\nReparacion no encontrada o ya esta eliminada." << endl;
        return;
    }

    Reparacion reparacion = leerReparacion(posicion);
    reparacion.eliminado = true;

    if (!actualizarReparacion(posicion, reparacion)) {
        cout << "\nError al dar de baja la reparacion." << endl;
        return;
    }

    int cantDetalles = contarDetallesReparacion();
    for (int i = 0; i < cantDetalles; i++) {
        DetalleReparacion det = leerDetalleReparacion(i);

        if (det.nroReparacion == nroReparacion && !det.eliminado) {
            det.eliminado = true;
            actualizarDetalleReparacion(i, det);
        }
    }

    cout << "\nReparacion dada de baja exitosamente (incluye sus detalles)." << endl;
}

static void modificarDetalles(const Reparacion& reparacion) {
    int opcion;

    do {
        cout << "\n=== DETALLES DE LA REPARACION #" << reparacion.nroReparacion << " ===" << endl;
        cout << "1. Agregar equipo al detalle" << endl;
        cout << "2. Modificar importe de un equipo" << endl;
        cout << "3. Quitar equipo del detalle" << endl;
        cout << "4. Ver detalles actuales" << endl;
        cout << "0. Terminar modificacion de detalles" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1: {
                mostrarEquiposDeCliente(reparacion.cuit);
                int nroEquipo;
                cout << "\nNumero de equipo a agregar (0 para cancelar): ";
                cin >> nroEquipo;

                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); break; }
                if (nroEquipo == 0) break;

                if (!existeEquipoActivoPorNumero(nroEquipo)) {
                    cout << "El equipo no existe o esta eliminado." << endl;
                    break;
                }
                if (!equipoPerteneceACliente(nroEquipo, reparacion.cuit)) {
                    cout << "El equipo no pertenece al cliente de la reparacion." << endl;
                    break;
                }
                if (detalleYaCargado(reparacion.nroReparacion, nroEquipo)) {
                    cout << "Ese equipo ya esta en el detalle." << endl;
                    break;
                }

                float importe = pedirImporte();
                agregarDetalle(reparacion.nroReparacion, nroEquipo, importe);
                cout << "Equipo agregado." << endl;
                break;
            }
            case 2: {
                int nroEquipo;
                cout << "Numero de equipo cuyo importe desea modificar: ";
                cin >> nroEquipo;

                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); break; }

                int cantDetalles = contarDetallesReparacion();
                int posDetalle = -1;
                for (int i = 0; i < cantDetalles; i++) {
                    DetalleReparacion det = leerDetalleReparacion(i);
                    if (det.nroReparacion == reparacion.nroReparacion &&
                        det.nroEquipo == nroEquipo &&
                        !det.eliminado) {
                        posDetalle = i;
                        break;
                    }
                }

                if (posDetalle == -1) {
                    cout << "Ese equipo no esta en el detalle de la reparacion." << endl;
                    break;
                }

                DetalleReparacion det = leerDetalleReparacion(posDetalle);
                cout << "Importe actual: $" << det.importe << endl;
                det.importe = pedirImporte();
                actualizarDetalleReparacion(posDetalle, det);
                cout << "Importe modificado." << endl;
                break;
            }
            case 3: {
                int nroEquipo;
                cout << "Numero de equipo a quitar del detalle: ";
                cin >> nroEquipo;

                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); break; }

                int cantDetalles = contarDetallesReparacion();
                int posDetalle = -1;
                int cantActivos = 0;

                for (int i = 0; i < cantDetalles; i++) {
                    DetalleReparacion det = leerDetalleReparacion(i);
                    if (det.nroReparacion == reparacion.nroReparacion && !det.eliminado) {
                        cantActivos++;
                        if (det.nroEquipo == nroEquipo) {
                            posDetalle = i;
                        }
                    }
                }

                if (posDetalle == -1) {
                    cout << "Ese equipo no esta en el detalle de la reparacion." << endl;
                    break;
                }

                if (cantActivos <= 1) {
                    cout << "No se puede quitar: la reparacion debe tener al menos un equipo." << endl;
                    break;
                }

                DetalleReparacion det = leerDetalleReparacion(posDetalle);
                det.eliminado = true;
                actualizarDetalleReparacion(posDetalle, det);
                cout << "Equipo quitado del detalle." << endl;
                break;
            }
            case 4:
                mostrarReparacion(reparacion);
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
}

void modificacionReparacion() {
    int nroReparacion;

    cout << "\n=== MODIFICACION DE REPARACION ===" << endl;
    cout << "Ingrese numero de reparacion: ";
    cin >> nroReparacion;

    int posicion = buscarReparacionPorNumero(nroReparacion);

    if (posicion == -1) {
        cout << "\nReparacion no encontrada o esta eliminada." << endl;
        return;
    }

    Reparacion reparacion = leerReparacion(posicion);

    cout << "\nReparacion actual:" << endl;
    mostrarReparacion(reparacion);

    limpiarBuffer();

    do {
        cout << "Legajo del empleado: ";
        cin.getline(reparacion.legajo, 10);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "El legajo es demasiado largo (maximo 9 caracteres). Reingrese." << endl;
            reparacion.legajo[0] = '\0';
        } else if (!validarCadenaNoVacia(reparacion.legajo)) {
            cout << "El legajo no puede estar vacio. Reingrese." << endl;
        } else if (!validarEmpleadoExiste(reparacion.legajo)) {
            cout << "El empleado no existe o esta eliminado. Reingrese." << endl;
        }
    } while (!validarCadenaNoVacia(reparacion.legajo) || !validarEmpleadoExiste(reparacion.legajo));

    cout << "Fecha de entrega:" << endl;
    ingresarFecha(reparacion.fechaEntrega);

    if (!actualizarReparacion(posicion, reparacion)) {
        cout << "\nError al modificar la reparacion." << endl;
        return;
    }

    cout << "\nDatos de cabecera modificados." << endl;

    cout << "\nDesea modificar los equipos del detalle? (1=Si, 0=No): ";
    int opcion;
    cin >> opcion;
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); opcion = 0; }

    if (opcion == 1) {
        modificarDetalles(reparacion);
    }

    cout << "\nReparacion modificada exitosamente." << endl;
}

void listadoReparaciones() {
    cout << "\n=== LISTADO DE REPARACIONES ===" << endl;

    int cantidad = contarReparaciones();

    if (cantidad == 0) {
        cout << "No hay reparaciones registradas." << endl;
        return;
    }

    bool hayActivas = false;

    for (int i = 0; i < cantidad; i++) {
        Reparacion reparacion = leerReparacion(i);

        if (!reparacion.eliminado) {
            mostrarReparacion(reparacion);
            hayActivas = true;
        }
    }

    if (!hayActivas) {
        cout << "No hay reparaciones activas." << endl;
    }
}

void menuClientes() {
    int opcion;

    do {
        cout << "\n=== MENU CLIENTES ===" << endl;
        cout << "1. Alta de cliente" << endl;
        cout << "2. Baja de cliente" << endl;
        cout << "3. Modificacion de cliente" << endl;
        cout << "4. Listado de clientes" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                altaCliente();
                break;
            case 2:
                bajaCliente();
                break;
            case 3:
                modificacionCliente();
                break;
            case 4:
                listadoClientes();
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    } while (opcion != 0);
}

void menuEquipos() {
    int opcion;

    do {
        cout << "\n=== MENU EQUIPOS ===" << endl;
        cout << "1. Alta de equipo" << endl;
        cout << "2. Baja de equipo" << endl;
        cout << "3. Modificacion de equipo" << endl;
        cout << "4. Listado de equipos" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                altaEquipo();
                break;
            case 2:
                bajaEquipo();
                break;
            case 3:
                modificacionEquipo();
                break;
            case 4:
                listadoEquipos();
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    } while (opcion != 0);
}

void menuEmpleados() {
    int opcion;

    do {
        cout << "\n=== MENU EMPLEADOS ===" << endl;
        cout << "1. Alta de empleado" << endl;
        cout << "2. Baja de empleado" << endl;
        cout << "3. Modificacion de empleado" << endl;
        cout << "4. Listado de empleados" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                altaEmpleado();
                break;
            case 2:
                bajaEmpleado();
                break;
            case 3:
                modificacionEmpleado();
                break;
            case 4:
                listadoEmpleados();
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    } while (opcion != 0);
}

void menuReparaciones() {
    int opcion;

    do {
        cout << "\n=== MENU REPARACIONES ===" << endl;
        cout << "1. Alta de reparacion" << endl;
        cout << "2. Baja de reparacion" << endl;
        cout << "3. Modificacion de reparacion" << endl;
        cout << "4. Listado de reparaciones" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                altaReparacion();
                break;
            case 2:
                bajaReparacion();
                break;
            case 3:
                modificacionReparacion();
                break;
            case 4:
                listadoReparaciones();
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    } while (opcion != 0);
}

float calcularTotalReparacion(int nroReparacion) {
    int cantDetalles = contarDetallesReparacion();
    float total = 0;

    for (int i = 0; i < cantDetalles; i++) {
        DetalleReparacion det = leerDetalleReparacion(i);
        if (det.nroReparacion == nroReparacion && !det.eliminado) {
            total += det.importe;
        }
    }
    return total;
}

int contarEquiposDeReparacion(int nroReparacion) {
    int cantDetalles = contarDetallesReparacion();
    int cantidad = 0;

    for (int i = 0; i < cantDetalles; i++) {
        DetalleReparacion det = leerDetalleReparacion(i);
        if (det.nroReparacion == nroReparacion && !det.eliminado) {
            cantidad++;
        }
    }
    return cantidad;
}

static long fechaANumero(const Fecha& f) {
    return (long)f.anio * 10000L + (long)f.mes * 100L + (long)f.dia;
}

bool fechaEnRango(const Fecha& f, const Fecha& desde, const Fecha& hasta) {
    long n = fechaANumero(f);
    return n >= fechaANumero(desde) && n <= fechaANumero(hasta);
}

const char* nombreMes(int mes) {
    switch (mes) {
        case 1:  return "ENERO";
        case 2:  return "FEBRERO";
        case 3:  return "MARZO";
        case 4:  return "ABRIL";
        case 5:  return "MAYO";
        case 6:  return "JUNIO";
        case 7:  return "JULIO";
        case 8:  return "AGOSTO";
        case 9:  return "SEPTIEMBRE";
        case 10: return "OCTUBRE";
        case 11: return "NOVIEMBRE";
        case 12: return "DICIEMBRE";
        default: return "----";
    }
}

const char* nombreTipoEquipo(int tipo) {
    switch (tipo) {
        case 1: return "PC ESCRITORIO";
        case 2: return "NOTEBOOK";
        case 3: return "IMPRESORA";
        case 4: return "PERIFERICO";
        case 5: return "CELULAR";
        default: return "----";
    }
}

void listadoClientesPorApellido() {
    cout << "\n=== LISTADO DE CLIENTES (ORDENADO POR APELLIDO) ===" << endl;

    int cantidad = contarClientes();
    if (cantidad == 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    int* indices = new int[cantidad];
    int activos = 0;
    for (int i = 0; i < cantidad; i++) {
        Cliente c = leerCliente(i);
        if (!c.eliminado) {
            indices[activos++] = i;
        }
    }

    if (activos == 0) {
        cout << "No hay clientes activos." << endl;
        delete[] indices;
        return;
    }

    for (int i = 0; i < activos - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < activos; j++) {
            Cliente a = leerCliente(indices[idxMin]);
            Cliente b = leerCliente(indices[j]);
            if (strcmp(b.apellido, a.apellido) < 0) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            int tmp = indices[i];
            indices[i] = indices[idxMin];
            indices[idxMin] = tmp;
        }
    }

    for (int i = 0; i < activos; i++) {
        Cliente c = leerCliente(indices[i]);
        mostrarCliente(c);
    }

    delete[] indices;
}

void listadoEmpleadosPorApellido() {
    cout << "\n=== LISTADO DE EMPLEADOS (ORDENADO POR APELLIDO) ===" << endl;

    int cantidad = contarEmpleados();
    if (cantidad == 0) {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    int* indices = new int[cantidad];
    int activos = 0;
    for (int i = 0; i < cantidad; i++) {
        Empleado e = leerEmpleado(i);
        if (!e.eliminado) {
            indices[activos++] = i;
        }
    }

    if (activos == 0) {
        cout << "No hay empleados activos." << endl;
        delete[] indices;
        return;
    }

    for (int i = 0; i < activos - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < activos; j++) {
            Empleado a = leerEmpleado(indices[idxMin]);
            Empleado b = leerEmpleado(indices[j]);
            if (strcmp(b.apellido, a.apellido) < 0) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            int tmp = indices[i];
            indices[i] = indices[idxMin];
            indices[idxMin] = tmp;
        }
    }

    for (int i = 0; i < activos; i++) {
        Empleado e = leerEmpleado(indices[i]);
        mostrarEmpleado(e);
    }

    delete[] indices;
}

void listadoEquiposPorFechaIngreso() {
    cout << "\n=== LISTADO DE EQUIPOS (ORDENADO POR FECHA DE INGRESO) ===" << endl;

    int cantidad = contarEquipos();
    if (cantidad == 0) {
        cout << "No hay equipos registrados." << endl;
        return;
    }

    int* indices = new int[cantidad];
    int activos = 0;
    for (int i = 0; i < cantidad; i++) {
        Equipo e = leerEquipo(i);
        if (!e.eliminado) {
            indices[activos++] = i;
        }
    }

    if (activos == 0) {
        cout << "No hay equipos activos." << endl;
        delete[] indices;
        return;
    }

    for (int i = 0; i < activos - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < activos; j++) {
            Equipo a = leerEquipo(indices[idxMin]);
            Equipo b = leerEquipo(indices[j]);
            if (fechaANumero(b.fechaIngreso) < fechaANumero(a.fechaIngreso)) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            int tmp = indices[i];
            indices[i] = indices[idxMin];
            indices[idxMin] = tmp;
        }
    }

    for (int i = 0; i < activos; i++) {
        Equipo e = leerEquipo(indices[i]);
        mostrarEquipo(e);
    }

    delete[] indices;
}

void listadoReparacionesPorFechaEntrega() {
    cout << "\n=== LISTADO DE REPARACIONES (ORDENADO POR FECHA DE ENTREGA) ===" << endl;

    int cantidad = contarReparaciones();
    if (cantidad == 0) {
        cout << "No hay reparaciones registradas." << endl;
        return;
    }

    int* indices = new int[cantidad];
    int activas = 0;
    for (int i = 0; i < cantidad; i++) {
        Reparacion r = leerReparacion(i);
        if (!r.eliminado) {
            indices[activas++] = i;
        }
    }

    if (activas == 0) {
        cout << "No hay reparaciones activas." << endl;
        delete[] indices;
        return;
    }

    for (int i = 0; i < activas - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < activas; j++) {
            Reparacion a = leerReparacion(indices[idxMin]);
            Reparacion b = leerReparacion(indices[j]);
            if (fechaANumero(b.fechaEntrega) < fechaANumero(a.fechaEntrega)) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            int tmp = indices[i];
            indices[i] = indices[idxMin];
            indices[idxMin] = tmp;
        }
    }

    for (int i = 0; i < activas; i++) {
        Reparacion r = leerReparacion(indices[i]);
        mostrarReparacion(r);
    }

    delete[] indices;
}

void consultaClientePorCUIT() {
    char cuit[15];

    cout << "\n=== CONSULTA DE CLIENTE POR CUIT ===" << endl;
    limpiarBuffer();
    cout << "Ingrese CUIT: ";
    cin.getline(cuit, 15);

    int pos = buscarClientePorCUIT(cuit);

    if (pos == -1) {
        cout << "\nNo se encontro un cliente activo con ese CUIT." << endl;
        return;
    }

    Cliente c = leerCliente(pos);
    mostrarCliente(c);
    mostrarEquiposDeCliente(c.cuit);
}

void consultaEquiposPorCliente() {
    char cuit[15];

    cout << "\n=== CONSULTA DE EQUIPOS POR CLIENTE ===" << endl;
    limpiarBuffer();
    cout << "Ingrese CUIT del cliente: ";
    cin.getline(cuit, 15);

    if (!existeClienteActivoPorCUIT(cuit)) {
        cout << "\nNo existe un cliente activo con ese CUIT." << endl;
        return;
    }

    int pos = buscarClientePorCUIT(cuit);
    Cliente c = leerCliente(pos);
    cout << "\nCliente: " << c.cuit << " - " << c.nombre << " " << c.apellido << endl;

    int cantidad = contarEquipos();
    bool hay = false;
    for (int i = 0; i < cantidad; i++) {
        Equipo e = leerEquipo(i);
        if (!e.eliminado && strcmp(e.cuit, cuit) == 0) {
            mostrarEquipo(e);
            hay = true;
        }
    }

    if (!hay) {
        cout << "El cliente no tiene equipos activos." << endl;
    }
}

void consultaReparacionesPorCliente() {
    char cuit[15];

    cout << "\n=== CONSULTA DE REPARACIONES POR CLIENTE ===" << endl;
    limpiarBuffer();
    cout << "Ingrese CUIT del cliente: ";
    cin.getline(cuit, 15);

    if (!existeClienteActivoPorCUIT(cuit)) {
        cout << "\nNo existe un cliente activo con ese CUIT." << endl;
        return;
    }

    int cantidad = contarReparaciones();
    bool hay = false;
    float totalGeneral = 0;

    for (int i = 0; i < cantidad; i++) {
        Reparacion r = leerReparacion(i);
        if (!r.eliminado && strcmp(r.cuit, cuit) == 0) {
            mostrarReparacion(r);
            totalGeneral += calcularTotalReparacion(r.nroReparacion);
            hay = true;
        }
    }

    if (!hay) {
        cout << "El cliente no tiene reparaciones activas." << endl;
    } else {
        cout << "\n>>> TOTAL ACUMULADO DEL CLIENTE: $" << fixed << setprecision(2)
             << totalGeneral << endl;
    }
}

void consultaReparacionesPorRangoFechas() {
    Fecha desde, hasta;

    cout << "\n=== CONSULTA DE REPARACIONES POR RANGO DE FECHAS ===" << endl;
    cout << "Fecha desde:" << endl;
    ingresarFecha(desde);
    cout << "Fecha hasta:" << endl;
    ingresarFecha(hasta);

    if (fechaANumero(hasta) < fechaANumero(desde)) {
        cout << "El rango es invalido (la fecha hasta es anterior a desde)." << endl;
        return;
    }

    int cantidad = contarReparaciones();
    bool hay = false;
    float totalGeneral = 0;

    for (int i = 0; i < cantidad; i++) {
        Reparacion r = leerReparacion(i);
        if (!r.eliminado && fechaEnRango(r.fechaEntrega, desde, hasta)) {
            mostrarReparacion(r);
            totalGeneral += calcularTotalReparacion(r.nroReparacion);
            hay = true;
        }
    }

    if (!hay) {
        cout << "No hay reparaciones en el rango indicado." << endl;
    } else {
        cout << "\n>>> TOTAL DEL PERIODO: $" << fixed << setprecision(2)
             << totalGeneral << endl;
    }
}

void informeRecaudacionAnual() {
    int anio;

    cout << "\n=== INFORME: RECAUDACION ANUAL ===" << endl;
    cout << "Ingrese anio: ";
    cin >> anio;

    if (cin.fail() || anio <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Anio invalido." << endl;
        return;
    }

    float recaudacion[13] = {0};

    int cantidad = contarReparaciones();
    for (int i = 0; i < cantidad; i++) {
        Reparacion r = leerReparacion(i);
        if (!r.eliminado && r.fechaEntrega.anio == anio) {
            int mes = r.fechaEntrega.mes;
            if (mes >= 1 && mes <= 12) {
                recaudacion[mes] += calcularTotalReparacion(r.nroReparacion);
            }
        }
    }

    cout << "\nFACTURACION DEL ANIO " << anio << endl;
    cout << "==========================" << endl;
    cout << left << setw(15) << "MES" << "RECAUDACION" << endl;
    cout << "==========================" << endl;

    float total = 0;
    for (int m = 1; m <= 12; m++) {
        cout << left << setw(15) << nombreMes(m)
             << "$ " << fixed << setprecision(2) << recaudacion[m] << endl;
        total += recaudacion[m];
    }
    cout << "==========================" << endl;
    cout << left << setw(15) << "TOTAL"
         << "$ " << fixed << setprecision(2) << total << endl;
}

void informeRecaudacionPorCliente() {
    Fecha desde, hasta;

    cout << "\n=== INFORME: RECAUDACION POR CLIENTE ===" << endl;
    cout << "Fecha desde:" << endl;
    ingresarFecha(desde);
    cout << "Fecha hasta:" << endl;
    ingresarFecha(hasta);

    if (fechaANumero(hasta) < fechaANumero(desde)) {
        cout << "Rango invalido." << endl;
        return;
    }

    int cantClientes = contarClientes();
    if (cantClientes == 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    cout << "\nRECAUDACION POR CLIENTE ENTRE ";
    mostrarFecha(desde); cout << " Y "; mostrarFecha(hasta);
    cout << endl;
    cout << "================================================================" << endl;
    cout << left << setw(15) << "CUIT" << setw(20) << "APELLIDO"
         << setw(20) << "NOMBRE" << setw(15) << "TOTAL"
         << "REPARACIONES" << endl;
    cout << "================================================================" << endl;

    bool hayDatos = false;
    float totalGeneral = 0;

    for (int i = 0; i < cantClientes; i++) {
        Cliente c = leerCliente(i);
        if (c.eliminado) continue;

        float totalCliente = 0;
        int cantRep = 0;

        int cantRepArchivo = contarReparaciones();
        for (int j = 0; j < cantRepArchivo; j++) {
            Reparacion r = leerReparacion(j);
            if (!r.eliminado && strcmp(r.cuit, c.cuit) == 0
                && fechaEnRango(r.fechaEntrega, desde, hasta)) {
                totalCliente += calcularTotalReparacion(r.nroReparacion);
                cantRep++;
            }
        }

        if (cantRep > 0) {
            cout << left << setw(15) << c.cuit
                 << setw(20) << c.apellido
                 << setw(20) << c.nombre
                 << "$ " << left << setw(13) << fixed << setprecision(2) << totalCliente
                 << cantRep << endl;
            totalGeneral += totalCliente;
            hayDatos = true;
        }
    }

    if (!hayDatos) {
        cout << "No hubo recaudacion en el periodo." << endl;
        return;
    }

    cout << "================================================================" << endl;
    cout << ">>> TOTAL GENERAL: $" << fixed << setprecision(2) << totalGeneral << endl;
}

void informeReparacionesPorTipoEquipo() {
    Fecha desde, hasta;

    cout << "\n=== INFORME: REPARACIONES POR TIPO DE EQUIPO ===" << endl;
    cout << "Fecha desde:" << endl;
    ingresarFecha(desde);
    cout << "Fecha hasta:" << endl;
    ingresarFecha(hasta);

    if (fechaANumero(hasta) < fechaANumero(desde)) {
        cout << "Rango invalido." << endl;
        return;
    }

    int cantidades[6] = {0};
    float recaudaciones[6] = {0};

    int cantDetalles = contarDetallesReparacion();
    for (int i = 0; i < cantDetalles; i++) {
        DetalleReparacion det = leerDetalleReparacion(i);
        if (det.eliminado) continue;

        int posRep = buscarReparacionPorNumero(det.nroReparacion);
        if (posRep == -1) continue;

        Reparacion r = leerReparacion(posRep);
        if (r.eliminado) continue;
        if (!fechaEnRango(r.fechaEntrega, desde, hasta)) continue;

        int posEq = buscarEquipoPorNumero(det.nroEquipo);
        if (posEq == -1) continue;

        Equipo e = leerEquipo(posEq);
        if (e.tipoEquipo >= 1 && e.tipoEquipo <= 5) {
            cantidades[e.tipoEquipo]++;
            recaudaciones[e.tipoEquipo] += det.importe;
        }
    }

    cout << "\nREPARACIONES POR TIPO DE EQUIPO ENTRE ";
    mostrarFecha(desde); cout << " Y "; mostrarFecha(hasta);
    cout << endl;
    cout << "==========================================" << endl;
    cout << left << setw(20) << "TIPO"
         << setw(12) << "CANTIDAD" << "RECAUDACION" << endl;
    cout << "==========================================" << endl;

    int totalCant = 0;
    float totalRec = 0;
    for (int t = 1; t <= 5; t++) {
        cout << left << setw(20) << nombreTipoEquipo(t)
             << setw(12) << cantidades[t]
             << "$ " << fixed << setprecision(2) << recaudaciones[t] << endl;
        totalCant += cantidades[t];
        totalRec += recaudaciones[t];
    }
    cout << "==========================================" << endl;
    cout << left << setw(20) << "TOTAL"
         << setw(12) << totalCant
         << "$ " << fixed << setprecision(2) << totalRec << endl;
}

void informeProductividadEmpleados() {
    cout << "\n=== INFORME: PRODUCTIVIDAD POR EMPLEADO ===" << endl;

    int cantEmp = contarEmpleados();
    if (cantEmp == 0) {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    cout << "================================================================" << endl;
    cout << left << setw(10) << "LEGAJO"
         << setw(20) << "APELLIDO" << setw(20) << "NOMBRE"
         << setw(8) << "REPS" << "FACTURADO" << endl;
    cout << "================================================================" << endl;

    int cantRep = contarReparaciones();

    for (int i = 0; i < cantEmp; i++) {
        Empleado e = leerEmpleado(i);
        if (e.eliminado) continue;

        int reps = 0;
        float facturado = 0;

        for (int j = 0; j < cantRep; j++) {
            Reparacion r = leerReparacion(j);
            if (!r.eliminado && strcmp(r.legajo, e.legajo) == 0) {
                reps++;
                facturado += calcularTotalReparacion(r.nroReparacion);
            }
        }

        cout << left << setw(10) << e.legajo
             << setw(20) << e.apellido
             << setw(20) << e.nombre
             << setw(8) << reps
             << "$ " << fixed << setprecision(2) << facturado << endl;
    }
    cout << "================================================================" << endl;
}

void asegurarCarpeta(const char* nombreCarpeta) {
    _mkdir(nombreCarpeta);
}

bool copiarArchivo(const char* origen, const char* destino) {
    ifstream src(origen, ios::binary);
    if (!src) return false;

    ofstream dst(destino, ios::binary | ios::trunc);
    if (!dst) {
        src.close();
        return false;
    }

    dst << src.rdbuf();

    bool ok = src.good() && dst.good();
    src.close();
    dst.close();
    return ok;
}

void backupArchivo(const char* nombreDat) {
    asegurarCarpeta("backups");

    char destino[200];

    strcpy(destino, "backups/");
    strcat(destino, nombreDat);

    int len = strlen(destino);
    if (len >= 4 && strcmp(destino + len - 4, ".dat") == 0) {
        strcpy(destino + len - 4, ".bkp");
    } else {
        strcat(destino, ".bkp");
    }

    if (copiarArchivo(nombreDat, destino)) {
        cout << "Backup OK: " << nombreDat << " -> " << destino << endl;
    } else {
        cout << "ERROR al hacer backup de: " << nombreDat << endl;
    }
}

void backupTodos() {
    cout << "\nRealizando backup de todos los archivos..." << endl;
    backupArchivo("clientes.dat");
    backupArchivo("equipos.dat");
    backupArchivo("empleados.dat");
    backupArchivo("reparaciones.dat");
    backupArchivo("detalleReparaciones.dat");
    cout << "Backup completo." << endl;
}

static int generarCodigoConfirmacion(const char* nombre) {
    int codigo = 10000;
    for (int i = 0; nombre[i] != '\0'; i++) {
        codigo += (int)nombre[i] * (i + 1);
    }
    return codigo % 90000 + 10000;
}

void restaurarArchivo(const char* nombreDat) {
    char origen[200];
    strcpy(origen, "backups/");
    strcat(origen, nombreDat);
    int len = strlen(origen);
    if (len >= 4 && strcmp(origen + len - 4, ".dat") == 0) {
        strcpy(origen + len - 4, ".bkp");
    } else {
        strcat(origen, ".bkp");
    }

    if (!archivoExiste(origen)) {
        cout << "No existe backup para: " << nombreDat << " (" << origen << ")" << endl;
        return;
    }

    int codigoEsperado = generarCodigoConfirmacion(nombreDat);
    int codigoIngresado;

    cout << "\nATENCION: Restaurar SOBREESCRIBIRA " << nombreDat << "." << endl;
    cout << "Para continuar ingrese el siguiente codigo: " << codigoEsperado << endl;
    cout << "Codigo de confirmacion: ";
    cin >> codigoIngresado;

    if (cin.fail() || codigoIngresado != codigoEsperado) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Codigo incorrecto. Restauracion cancelada." << endl;
        return;
    }

    if (copiarArchivo(origen, nombreDat)) {
        cout << "Restauracion OK: " << origen << " -> " << nombreDat << endl;
    } else {
        cout << "ERROR al restaurar." << endl;
    }
}

void restaurarTodos() {
    int codigoEsperado = generarCodigoConfirmacion("TODOS");
    int codigoIngresado;

    cout << "\nATENCION: Restaurar TODO sobreescribira los archivos .dat actuales." << endl;
    cout << "Para continuar ingrese el siguiente codigo: " << codigoEsperado << endl;
    cout << "Codigo de confirmacion: ";
    cin >> codigoIngresado;

    if (cin.fail() || codigoIngresado != codigoEsperado) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Codigo incorrecto. Restauracion cancelada." << endl;
        return;
    }

    const char* archivos[] = {
        "clientes.dat", "equipos.dat", "empleados.dat",
        "reparaciones.dat", "detalleReparaciones.dat"
    };

    for (int i = 0; i < 5; i++) {
        char origen[200];
        strcpy(origen, "backups/");
        strcat(origen, archivos[i]);
        int len = strlen(origen);
        strcpy(origen + len - 4, ".bkp");

        if (!archivoExiste(origen)) {
            cout << "(omitido) No existe backup para: " << archivos[i] << endl;
            continue;
        }
        if (copiarArchivo(origen, archivos[i])) {
            cout << "Restauracion OK: " << archivos[i] << endl;
        } else {
            cout << "ERROR al restaurar: " << archivos[i] << endl;
        }
    }
    cout << "Restauracion completa." << endl;
}

void exportarClientesCSV() {
    asegurarCarpeta("exports");

    ofstream csv("exports/clientes.csv");
    if (!csv) {
        cout << "ERROR al crear exports/clientes.csv" << endl;
        return;
    }

    csv << "cuit,nombre,apellido,telefono,email,direccion,tipoCliente" << endl;

    int cantidad = contarClientes();
    int exportados = 0;

    for (int i = 0; i < cantidad; i++) {
        Cliente c = leerCliente(i);
        if (c.eliminado) continue;

        csv << c.cuit << ","
            << c.nombre << ","
            << c.apellido << ","
            << c.telefono << ","
            << c.email << ","
            << c.direccion << ","
            << (c.tipoCliente == 1 ? "Particular" : "Empresa")
            << endl;
        exportados++;
    }

    csv.close();
    cout << "Exportados " << exportados << " clientes a exports/clientes.csv" << endl;
}

void exportarEquiposCSV() {
    asegurarCarpeta("exports");

    ofstream csv("exports/equipos.csv");
    if (!csv) {
        cout << "ERROR al crear exports/equipos.csv" << endl;
        return;
    }

    csv << "nroEquipo,cuitCliente,descripcion,marca,tipoEquipo,fechaIngreso" << endl;

    int cantidad = contarEquipos();
    int exportados = 0;

    for (int i = 0; i < cantidad; i++) {
        Equipo e = leerEquipo(i);
        if (e.eliminado) continue;

        csv << e.nroEquipo << ","
            << e.cuit << ","
            << e.descripcion << ","
            << e.marca << ","
            << nombreTipoEquipo(e.tipoEquipo) << ","
            << e.fechaIngreso.dia << "/" << e.fechaIngreso.mes << "/" << e.fechaIngreso.anio
            << endl;
        exportados++;
    }

    csv.close();
    cout << "Exportados " << exportados << " equipos a exports/equipos.csv" << endl;
}

void exportarEmpleadosCSV() {
    asegurarCarpeta("exports");

    ofstream csv("exports/empleados.csv");
    if (!csv) {
        cout << "ERROR al crear exports/empleados.csv" << endl;
        return;
    }

    csv << "legajo,nombre,apellido" << endl;

    int cantidad = contarEmpleados();
    int exportados = 0;

    for (int i = 0; i < cantidad; i++) {
        Empleado e = leerEmpleado(i);
        if (e.eliminado) continue;

        csv << e.legajo << "," << e.nombre << "," << e.apellido << endl;
        exportados++;
    }

    csv.close();
    cout << "Exportados " << exportados << " empleados a exports/empleados.csv" << endl;
}

void exportarReparacionesCSV() {
    asegurarCarpeta("exports");

    ofstream csv("exports/reparaciones.csv");
    if (!csv) {
        cout << "ERROR al crear exports/reparaciones.csv" << endl;
        return;
    }

    csv << "nroReparacion,cuitCliente,legajoEmpleado,fechaEntrega,cantidadEquipos,importeTotal" << endl;

    int cantidad = contarReparaciones();
    int exportados = 0;

    for (int i = 0; i < cantidad; i++) {
        Reparacion r = leerReparacion(i);
        if (r.eliminado) continue;

        csv << r.nroReparacion << ","
            << r.cuit << ","
            << r.legajo << ","
            << r.fechaEntrega.dia << "/" << r.fechaEntrega.mes << "/" << r.fechaEntrega.anio << ","
            << contarEquiposDeReparacion(r.nroReparacion) << ","
            << fixed << setprecision(2) << calcularTotalReparacion(r.nroReparacion)
            << endl;
        exportados++;
    }

    csv.close();
    cout << "Exportadas " << exportados << " reparaciones a exports/reparaciones.csv" << endl;
}

void exportarDetalleReparacionesCSV() {
    asegurarCarpeta("exports");

    ofstream csv("exports/detalleReparaciones.csv");
    if (!csv) {
        cout << "ERROR al crear exports/detalleReparaciones.csv" << endl;
        return;
    }

    csv << "nroReparacion,nroEquipo,importe" << endl;

    int cantidad = contarDetallesReparacion();
    int exportados = 0;

    for (int i = 0; i < cantidad; i++) {
        DetalleReparacion d = leerDetalleReparacion(i);
        if (d.eliminado) continue;

        csv << d.nroReparacion << ","
            << d.nroEquipo << ","
            << fixed << setprecision(2) << d.importe
            << endl;
        exportados++;
    }

    csv.close();
    cout << "Exportados " << exportados << " detalles a exports/detalleReparaciones.csv" << endl;
}

void exportarTodosCSV() {
    cout << "\nExportando todos los archivos a CSV..." << endl;
    exportarClientesCSV();
    exportarEquiposCSV();
    exportarEmpleadosCSV();
    exportarReparacionesCSV();
    exportarDetalleReparacionesCSV();
    cout << "Exportacion completa." << endl;
}

void menuConsultas() {
    int opcion;

    do {
        cout << "\n=== MENU CONSULTAS Y LISTADOS ===" << endl;
        cout << "1. Listado de clientes (por apellido)" << endl;
        cout << "2. Listado de empleados (por apellido)" << endl;
        cout << "3. Listado de equipos (por fecha de ingreso)" << endl;
        cout << "4. Listado de reparaciones (por fecha de entrega)" << endl;
        cout << "5. Consulta de cliente por CUIT" << endl;
        cout << "6. Consulta de equipos por cliente" << endl;
        cout << "7. Consulta de reparaciones por cliente" << endl;
        cout << "8. Consulta de reparaciones por rango de fechas" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1: listadoClientesPorApellido(); break;
            case 2: listadoEmpleadosPorApellido(); break;
            case 3: listadoEquiposPorFechaIngreso(); break;
            case 4: listadoReparacionesPorFechaEntrega(); break;
            case 5: consultaClientePorCUIT(); break;
            case 6: consultaEquiposPorCliente(); break;
            case 7: consultaReparacionesPorCliente(); break;
            case 8: consultaReparacionesPorRangoFechas(); break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}

void menuInformes() {
    int opcion;

    do {
        cout << "\n=== MENU INFORMES ===" << endl;
        cout << "1. Recaudacion anual" << endl;
        cout << "2. Recaudacion por cliente" << endl;
        cout << "3. Reparaciones por tipo de equipo" << endl;
        cout << "4. Productividad por empleado" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1: informeRecaudacionAnual(); break;
            case 2: informeRecaudacionPorCliente(); break;
            case 3: informeReparacionesPorTipoEquipo(); break;
            case 4: informeProductividadEmpleados(); break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}

void menuBackup() {
    int opcion;

    do {
        cout << "\n=== REALIZAR COPIA DE SEGURIDAD ===" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Equipos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Reparaciones" << endl;
        cout << "5. Detalle de reparaciones" << endl;
        cout << "6. TODOS los archivos" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1: backupArchivo("clientes.dat"); break;
            case 2: backupArchivo("equipos.dat"); break;
            case 3: backupArchivo("empleados.dat"); break;
            case 4: backupArchivo("reparaciones.dat"); break;
            case 5: backupArchivo("detalleReparaciones.dat"); break;
            case 6: backupTodos(); break;
            case 0: break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}

void menuRestaurar() {
    int opcion;

    do {
        cout << "\n=== RESTAURAR COPIA DE SEGURIDAD ===" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Equipos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Reparaciones" << endl;
        cout << "5. Detalle de reparaciones" << endl;
        cout << "6. TODOS los archivos" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1: restaurarArchivo("clientes.dat"); break;
            case 2: restaurarArchivo("equipos.dat"); break;
            case 3: restaurarArchivo("empleados.dat"); break;
            case 4: restaurarArchivo("reparaciones.dat"); break;
            case 5: restaurarArchivo("detalleReparaciones.dat"); break;
            case 6: restaurarTodos(); break;
            case 0: break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}

void menuExportarCSV() {
    int opcion;

    do {
        cout << "\n=== EXPORTAR ARCHIVOS CSV ===" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Equipos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Reparaciones" << endl;
        cout << "5. Detalle de reparaciones" << endl;
        cout << "6. TODOS los archivos" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1: exportarClientesCSV(); break;
            case 2: exportarEquiposCSV(); break;
            case 3: exportarEmpleadosCSV(); break;
            case 4: exportarReparacionesCSV(); break;
            case 5: exportarDetalleReparacionesCSV(); break;
            case 6: exportarTodosCSV(); break;
            case 0: break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}

void menuConfiguracion() {
    int opcion;

    do {
        cout << "\n=== MENU CONFIGURACION ===" << endl;
        cout << "1. Realizar copia de seguridad" << endl;
        cout << "2. Restaurar copia de seguridad" << endl;
        cout << "3. Exportar datos a CSV" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1: menuBackup(); break;
            case 2: menuRestaurar(); break;
            case 3: menuExportarCSV(); break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);
}
