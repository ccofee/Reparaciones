#include <string>
#include <cstdio>
#include <cstdlib>
#include "reparacionArchivo.h"
#include "conexionBD.h"
using namespace std;

static string fechaSql(const Fecha &f) {
   char buf[16];
   snprintf(buf, sizeof(buf), "'%04d-%02d-%02d'", f.getAnio(), f.getMes(), f.getDia());
   return string(buf);
}

static Fecha parseFecha(const string &s) {
   if (s.size() < 10) return Fecha();
   int anio = atoi(s.substr(0, 4).c_str());
   int mes  = atoi(s.substr(5, 2).c_str());
   int dia  = atoi(s.substr(8, 2).c_str());
   return Fecha(dia, mes, anio);
}

static const char *COLS =
   "NroReparacion, CUIT, Legajo, FechaIngreso, FechaEntrega, IdEstado, Activo";

static Reparacion leerFila(SQLHSTMT h) {
   Reparacion r;
   r.setNroReparacion(ConexionBD::colEntero(h, 1));
   r.setCuit(ConexionBD::colTexto(h, 2));
   r.setLegajo(to_string(ConexionBD::colEntero(h, 3)));
   r.setFechaIngreso(parseFecha(ConexionBD::colTexto(h, 4)));
   string fe = ConexionBD::colTexto(h, 5);
   if (!fe.empty()) r.setFechaEntrega(parseFecha(fe));
   r.setEstado(ConexionBD::colEntero(h, 6));   // setEstado ignora valores fuera de 1..3
   r.setEliminado(ConexionBD::colEntero(h, 7) == 0);
   return r;
}

ReparacionArchivo::ReparacionArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool ReparacionArchivo::crear(const Reparacion &reg) {
   string fechaEntrega = reg.getFechaEntrega().esValida()
                            ? fechaSql(reg.getFechaEntrega())
                            : string("NULL");
   string sql =
      "INSERT INTO Reparacion (NroReparacion, CUIT, Legajo, FechaIngreso, "
      "FechaEntrega, IdEstado, Activo) VALUES ("
      + to_string(reg.getNroReparacion()) + ", "
      + sqlTexto(reg.getCuit()) + ", "
      + to_string(atoi(reg.getLegajo().c_str())) + ", "
      + fechaSql(reg.getFechaIngreso()) + ", "
      + fechaEntrega + ", "
      + to_string(reg.getEstado()) + ", "
      + (reg.getEliminado() ? "0" : "1") + ")";
   return ConexionBD::getInstance().ejecutar(sql);
}

bool ReparacionArchivo::actualizar(int pos, const Reparacion &reg) {
   ConexionBD &bd = ConexionBD::getInstance();
   string sqlPos = "SELECT NroReparacion FROM Reparacion ORDER BY NroReparacion OFFSET "
                   + to_string(pos) + " ROWS FETCH NEXT 1 ROWS ONLY";
   int nro = -1;
   SQLHSTMT h = bd.consultar(sqlPos);
   if (h == SQL_NULL_HSTMT) return false;
   if (SQLFetch(h) == SQL_SUCCESS) nro = ConexionBD::colEntero(h, 1);
   ConexionBD::liberar(h);
   if (nro < 0) return false;

   string fechaEntrega = reg.getFechaEntrega().esValida()
                            ? fechaSql(reg.getFechaEntrega())
                            : string("NULL");
   string sql =
      "UPDATE Reparacion SET "
      "CUIT = "         + sqlTexto(reg.getCuit()) + ", "
      "Legajo = "       + to_string(atoi(reg.getLegajo().c_str())) + ", "
      "FechaIngreso = " + fechaSql(reg.getFechaIngreso()) + ", "
      "FechaEntrega = " + fechaEntrega + ", "
      "IdEstado = "     + to_string(reg.getEstado()) + ", "
      "Activo = "       + (reg.getEliminado() ? string("0") : string("1")) +
      " WHERE NroReparacion = " + to_string(nro);
   return bd.ejecutar(sql);
}

Reparacion ReparacionArchivo::leer(int pos) {
   Reparacion r;
   string sql = string("SELECT ") + COLS +
                " FROM Reparacion ORDER BY NroReparacion OFFSET " + to_string(pos) +
                " ROWS FETCH NEXT 1 ROWS ONLY";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return r;
   if (SQLFetch(h) == SQL_SUCCESS) r = leerFila(h);
   ConexionBD::liberar(h);
   return r;
}

int ReparacionArchivo::leerTodos(Reparacion vReparaciones[], int cantidad) {
   string sql = string("SELECT ") + COLS + " FROM Reparacion ORDER BY NroReparacion";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return 0;
   int i = 0;
   while (i < cantidad && SQLFetch(h) == SQL_SUCCESS) {
      vReparaciones[i++] = leerFila(h);
   }
   ConexionBD::liberar(h);
   return i;
}

int ReparacionArchivo::getCantidadRegistros() {
   return (int)ConexionBD::getInstance().escalar("SELECT COUNT(*) FROM Reparacion");
}

int ReparacionArchivo::getNuevoId() {
   return (int)ConexionBD::getInstance().escalar(
      "SELECT ISNULL(MAX(NroReparacion), 0) + 1 FROM Reparacion", 1);
}

int ReparacionArchivo::buscarPorNumero(int nroReparacion) {
   ConexionBD &bd = ConexionBD::getInstance();
   long existe = bd.escalar(
      "SELECT COUNT(*) FROM Reparacion WHERE NroReparacion = " + to_string(nroReparacion));
   if (existe == 0) return -1;
   return (int)bd.escalar(
      "SELECT COUNT(*) FROM Reparacion WHERE NroReparacion < " + to_string(nroReparacion));
}
