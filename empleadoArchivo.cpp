#include <string>
#include <cstdlib>
#include "empleadoArchivo.h"
#include "conexionBD.h"
using namespace std;

// El Legajo es INT en la base; la app lo maneja como cadena numerica.
static const char *COLS = "Legajo, Nombre, Apellido, Activo";

static Empleado leerFila(SQLHSTMT h) {
   Empleado e;
   e.setLegajo(to_string(ConexionBD::colEntero(h, 1)));
   e.setNombre(ConexionBD::colTexto(h, 2));
   e.setApellido(ConexionBD::colTexto(h, 3));
   e.setEliminado(ConexionBD::colEntero(h, 4) == 0);
   return e;
}

EmpleadoArchivo::EmpleadoArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool EmpleadoArchivo::crear(const Empleado &reg) {
   string sql =
      "INSERT INTO Empleado (Legajo, Nombre, Apellido, Activo) VALUES ("
      + to_string(atoi(reg.getLegajo().c_str())) + ", "
      + sqlTexto(reg.getNombre()) + ", "
      + sqlTexto(reg.getApellido()) + ", "
      + (reg.getEliminado() ? "0" : "1") + ")";
   return ConexionBD::getInstance().ejecutar(sql);
}

bool EmpleadoArchivo::actualizar(int pos, const Empleado &reg) {
   ConexionBD &bd = ConexionBD::getInstance();
   string sqlPos = "SELECT Legajo FROM Empleado ORDER BY Legajo OFFSET "
                   + to_string(pos) + " ROWS FETCH NEXT 1 ROWS ONLY";
   long legajo = -1;
   SQLHSTMT h = bd.consultar(sqlPos);
   if (h == SQL_NULL_HSTMT) return false;
   if (SQLFetch(h) == SQL_SUCCESS) legajo = ConexionBD::colEntero(h, 1);
   ConexionBD::liberar(h);
   if (legajo < 0) return false;

   string sql =
      "UPDATE Empleado SET "
      "Nombre = "   + sqlTexto(reg.getNombre()) + ", "
      "Apellido = " + sqlTexto(reg.getApellido()) + ", "
      "Activo = "   + (reg.getEliminado() ? string("0") : string("1")) +
      " WHERE Legajo = " + to_string(legajo);
   return bd.ejecutar(sql);
}

Empleado EmpleadoArchivo::leer(int pos) {
   Empleado e;
   string sql = string("SELECT ") + COLS +
                " FROM Empleado ORDER BY Legajo OFFSET " + to_string(pos) +
                " ROWS FETCH NEXT 1 ROWS ONLY";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return e;
   if (SQLFetch(h) == SQL_SUCCESS) e = leerFila(h);
   ConexionBD::liberar(h);
   return e;
}

int EmpleadoArchivo::leerTodos(Empleado vEmpleados[], int cantidad) {
   string sql = string("SELECT ") + COLS + " FROM Empleado ORDER BY Legajo";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return 0;
   int i = 0;
   while (i < cantidad && SQLFetch(h) == SQL_SUCCESS) {
      vEmpleados[i++] = leerFila(h);
   }
   ConexionBD::liberar(h);
   return i;
}

int EmpleadoArchivo::getCantidadRegistros() {
   return (int)ConexionBD::getInstance().escalar("SELECT COUNT(*) FROM Empleado");
}

int EmpleadoArchivo::buscarPorLegajo(const string &legajo) {
   ConexionBD &bd = ConexionBD::getInstance();
   int leg = atoi(legajo.c_str());
   long existe = bd.escalar(
      "SELECT COUNT(*) FROM Empleado WHERE Legajo = " + to_string(leg));
   if (existe == 0) return -1;
   return (int)bd.escalar(
      "SELECT COUNT(*) FROM Empleado WHERE Legajo < " + to_string(leg));
}
