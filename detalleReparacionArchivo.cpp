#include <string>
#include <cstdio>
#include "detalleReparacionArchivo.h"
#include "conexionBD.h"
using namespace std;

// El detalle no tiene clave en el struct: la PK Id es IDENTITY en la
// base. La "posicion" se mapea al orden ascendente por Id.
static const char *COLS = "NroReparacion, NroEquipo, Importe, Descripcion, Activo";

static string importeSql(float v) {
   char buf[32];
   snprintf(buf, sizeof(buf), "%.2f", v);
   return string(buf);
}

static DetalleReparacion leerFila(SQLHSTMT h) {
   DetalleReparacion d;
   d.setNroReparacion(ConexionBD::colEntero(h, 1));
   d.setNroEquipo(ConexionBD::colEntero(h, 2));
   d.setImporte((float)ConexionBD::colReal(h, 3));
   string falla = ConexionBD::colTexto(h, 4);
   if (falla.size() > 99) falla = falla.substr(0, 99);   // _detalleFalla es char[100]
   d.setDetalleFalla(falla.c_str());
   d.setEliminado(ConexionBD::colEntero(h, 5) == 0);
   return d;
}

DetalleReparacionArchivo::DetalleReparacionArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool DetalleReparacionArchivo::crear(const DetalleReparacion &reg) {
   string sql =
      "INSERT INTO DetalleReparacion (NroReparacion, NroEquipo, Importe, "
      "Descripcion, Activo) VALUES ("
      + to_string(reg.getNroReparacion()) + ", "
      + to_string(reg.getNroEquipo()) + ", "
      + importeSql(reg.getImporte()) + ", "
      + sqlTextoONull(string(reg.getDetalleFalla())) + ", "
      + (reg.getEliminado() ? "0" : "1") + ")";
   return ConexionBD::getInstance().ejecutar(sql);
}

bool DetalleReparacionArchivo::actualizar(int pos, const DetalleReparacion &reg) {
   ConexionBD &bd = ConexionBD::getInstance();
   string sqlPos = "SELECT Id FROM DetalleReparacion ORDER BY Id OFFSET "
                   + to_string(pos) + " ROWS FETCH NEXT 1 ROWS ONLY";
   int id = -1;
   SQLHSTMT h = bd.consultar(sqlPos);
   if (h == SQL_NULL_HSTMT) return false;
   if (SQLFetch(h) == SQL_SUCCESS) id = ConexionBD::colEntero(h, 1);
   ConexionBD::liberar(h);
   if (id < 0) return false;

   string sql =
      "UPDATE DetalleReparacion SET "
      "NroReparacion = " + to_string(reg.getNroReparacion()) + ", "
      "NroEquipo = "     + to_string(reg.getNroEquipo()) + ", "
      "Importe = "       + importeSql(reg.getImporte()) + ", "
      "Descripcion = "   + sqlTextoONull(string(reg.getDetalleFalla())) + ", "
      "Activo = "        + (reg.getEliminado() ? string("0") : string("1")) +
      " WHERE Id = "     + to_string(id);
   return bd.ejecutar(sql);
}

DetalleReparacion DetalleReparacionArchivo::leer(int pos) {
   DetalleReparacion d;
   string sql = string("SELECT ") + COLS +
                " FROM DetalleReparacion ORDER BY Id OFFSET " + to_string(pos) +
                " ROWS FETCH NEXT 1 ROWS ONLY";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return d;
   if (SQLFetch(h) == SQL_SUCCESS) d = leerFila(h);
   ConexionBD::liberar(h);
   return d;
}

int DetalleReparacionArchivo::leerTodos(DetalleReparacion vDetalles[], int cantidad) {
   string sql = string("SELECT ") + COLS + " FROM DetalleReparacion ORDER BY Id";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return 0;
   int i = 0;
   while (i < cantidad && SQLFetch(h) == SQL_SUCCESS) {
      vDetalles[i++] = leerFila(h);
   }
   ConexionBD::liberar(h);
   return i;
}

int DetalleReparacionArchivo::getCantidadRegistros() {
   return (int)ConexionBD::getInstance().escalar(
      "SELECT COUNT(*) FROM DetalleReparacion");
}

int DetalleReparacionArchivo::buscarDetalle(int nroReparacion, int nroEquipo) {
   ConexionBD &bd = ConexionBD::getInstance();
   string filtro = "NroReparacion = " + to_string(nroReparacion) +
                   " AND NroEquipo = " + to_string(nroEquipo) + " AND Activo = 1";
   long minId = bd.escalar(
      "SELECT ISNULL(MIN(Id), -1) FROM DetalleReparacion WHERE " + filtro, -1);
   if (minId < 0) return -1;
   return (int)bd.escalar(
      "SELECT COUNT(*) FROM DetalleReparacion WHERE Id < " + to_string(minId));
}
