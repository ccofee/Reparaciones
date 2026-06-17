#include <string>
#include <cstdio>
#include "equipoArchivo.h"
#include "conexionBD.h"
using namespace std;

// 'YYYY-MM-DD' (literal SQL entre comillas) a partir de una Fecha.
static string fechaSql(const Fecha &f) {
   char buf[16];
   snprintf(buf, sizeof(buf), "'%04d-%02d-%02d'", f.getAnio(), f.getMes(), f.getDia());
   return string(buf);
}

// Convierte 'YYYY-MM-DD' (lo que devuelve SQL Server) a Fecha.
static Fecha parseFecha(const string &s) {
   if (s.size() < 10) return Fecha();
   int anio = atoi(s.substr(0, 4).c_str());
   int mes  = atoi(s.substr(5, 2).c_str());
   int dia  = atoi(s.substr(8, 2).c_str());
   return Fecha(dia, mes, anio);
}

static const char *COLS =
   "NroEquipo, CUIT, Descripcion, Marca, IdTipoEquipo, FechaIngreso, Activo";

static Equipo leerFila(SQLHSTMT h) {
   Equipo e;
   e.setNroEquipo(ConexionBD::colEntero(h, 1));
   e.setCuit(ConexionBD::colTexto(h, 2));
   e.setDescripcion(ConexionBD::colTexto(h, 3));
   e.setMarca(ConexionBD::colTexto(h, 4));
   e.setTipoEquipo(ConexionBD::colEntero(h, 5));
   e.setFechaIngreso(parseFecha(ConexionBD::colTexto(h, 6)));
   e.setEliminado(ConexionBD::colEntero(h, 7) == 0);
   return e;
}

EquipoArchivo::EquipoArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool EquipoArchivo::crear(const Equipo &reg) {
   string sql =
      "INSERT INTO Equipo (NroEquipo, CUIT, Descripcion, Marca, "
      "IdTipoEquipo, FechaIngreso, Activo) VALUES ("
      + to_string(reg.getNroEquipo()) + ", "
      + sqlTexto(reg.getCuit()) + ", "
      + sqlTexto(reg.getDescripcion()) + ", "
      + sqlTextoONull(reg.getMarca()) + ", "
      + to_string(reg.getTipoEquipo()) + ", "
      + fechaSql(reg.getFechaIngreso()) + ", "
      + (reg.getEliminado() ? "0" : "1") + ")";
   return ConexionBD::getInstance().ejecutar(sql);
}

bool EquipoArchivo::actualizar(int pos, const Equipo &reg) {
   ConexionBD &bd = ConexionBD::getInstance();
   string sqlPos = "SELECT NroEquipo FROM Equipo ORDER BY NroEquipo OFFSET "
                   + to_string(pos) + " ROWS FETCH NEXT 1 ROWS ONLY";
   int nro = -1;
   SQLHSTMT h = bd.consultar(sqlPos);
   if (h == SQL_NULL_HSTMT) return false;
   if (SQLFetch(h) == SQL_SUCCESS) nro = ConexionBD::colEntero(h, 1);
   ConexionBD::liberar(h);
   if (nro < 0) return false;

   string sql =
      "UPDATE Equipo SET "
      "CUIT = "         + sqlTexto(reg.getCuit()) + ", "
      "Descripcion = "  + sqlTexto(reg.getDescripcion()) + ", "
      "Marca = "        + sqlTextoONull(reg.getMarca()) + ", "
      "IdTipoEquipo = " + to_string(reg.getTipoEquipo()) + ", "
      "FechaIngreso = " + fechaSql(reg.getFechaIngreso()) + ", "
      "Activo = "       + (reg.getEliminado() ? string("0") : string("1")) +
      " WHERE NroEquipo = " + to_string(nro);
   return bd.ejecutar(sql);
}

Equipo EquipoArchivo::leer(int pos) {
   Equipo e;
   string sql = string("SELECT ") + COLS +
                " FROM Equipo ORDER BY NroEquipo OFFSET " + to_string(pos) +
                " ROWS FETCH NEXT 1 ROWS ONLY";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return e;
   if (SQLFetch(h) == SQL_SUCCESS) e = leerFila(h);
   ConexionBD::liberar(h);
   return e;
}

int EquipoArchivo::leerTodos(Equipo vEquipos[], int cantidad) {
   string sql = string("SELECT ") + COLS + " FROM Equipo ORDER BY NroEquipo";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return 0;
   int i = 0;
   while (i < cantidad && SQLFetch(h) == SQL_SUCCESS) {
      vEquipos[i++] = leerFila(h);
   }
   ConexionBD::liberar(h);
   return i;
}

int EquipoArchivo::getCantidadRegistros() {
   return (int)ConexionBD::getInstance().escalar("SELECT COUNT(*) FROM Equipo");
}

int EquipoArchivo::buscarPorNumero(int nroEquipo) {
   ConexionBD &bd = ConexionBD::getInstance();
   long existe = bd.escalar(
      "SELECT COUNT(*) FROM Equipo WHERE NroEquipo = " + to_string(nroEquipo));
   if (existe == 0) return -1;
   return (int)bd.escalar(
      "SELECT COUNT(*) FROM Equipo WHERE NroEquipo < " + to_string(nroEquipo));
}

int EquipoArchivo::getNuevoId() {
   return (int)ConexionBD::getInstance().escalar(
      "SELECT ISNULL(MAX(NroEquipo), 0) + 1 FROM Equipo", 1);
}
