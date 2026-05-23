#include <iostream>
#include <cstring>
#include <fstream>
#include "funciones.h"

using namespace std;

void cargarEmpleadosIniciales() {

    if (contarEmpleados() == 0) {
        Empleado emp1, emp2, emp3, emp4;

        strcpy(emp1.legajo, "23971");
        strcpy(emp1.nombre, "Agustin Nahuel");
        strcpy(emp1.apellido, "Parada");
        emp1.eliminado = false;
        guardarEmpleado(emp1);

        strcpy(emp2.legajo, "28047");
        strcpy(emp2.nombre, "Luz");
        strcpy(emp2.apellido, "Campagnale");
        emp2.eliminado = false;
        guardarEmpleado(emp2);

        strcpy(emp3.legajo, "32335");
        strcpy(emp3.nombre, "Enzo Gabriel");
        strcpy(emp3.apellido, "Sander");
        emp3.eliminado = false;
        guardarEmpleado(emp3);

        strcpy(emp4.legajo, "31950");
        strcpy(emp4.nombre, "Claudio Andres");
        strcpy(emp4.apellido, "Arce");
        emp4.eliminado = false;
        guardarEmpleado(emp4);

        cout << "Empleados iniciales cargados exitosamente." << endl;
    }
}

int main() {

    crearArchivoSiNoExiste("clientes.dat");
    crearArchivoSiNoExiste("equipos.dat");
    crearArchivoSiNoExiste("empleados.dat");
    crearArchivoSiNoExiste("reparaciones.dat");
    crearArchivoSiNoExiste("detalleReparaciones.dat");

    cargarEmpleadosIniciales();

    int opcion;

    do {
        cout << "\n=== REPARALO TODO MENU PRINCIPAL ===" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Equipos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Reparaciones" << endl;
        cout << "5. Consultas y Listados" << endl;
        cout << "6. Informes" << endl;
        cout << "7. Configuracion (Backup / CSV)" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                menuClientes();
                break;
            case 2:
                menuEquipos();
                break;
            case 3:
                menuEmpleados();
                break;
            case 4:
                menuReparaciones();
                break;
            case 5:
                menuConsultas();
                break;
            case 6:
                menuInformes();
                break;
            case 7:
                menuConfiguracion();
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}
