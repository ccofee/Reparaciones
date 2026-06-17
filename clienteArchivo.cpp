#include <string>
#include "clienteArchivo.h"
#include "conexionBD.h"
using namespace std;

// Columnas en el orden en que se leen las filas.
static const char *COLS =
   "CUIT, Nombre, Apellido, Email, Telefono, Direccion, IdTipoCliente, Activo";

static Cliente leerFila(SQLHSTMT h) {
   Cliente c;
   c.setCuit(ConexionBD::colTexto(h, 1));
   c.setNombre(ConexionBD::colTexto(h, 2));
   c.setApellido(ConexionBD::colTexto(h, 3));
   c.setEmail(ConexionBD::colTexto(h, 4));
   c.setTelefono(ConexionBD::colTexto(h, 5));
   c.setDireccion(ConexionBD::colTexto(h, 6));
   c.setTipoCliente(ConexionBD::colEntero(h, 7));
   c.setEliminado(ConexionBD::colEntero(h, 8) == 0);
   return c;
}

ClienteArchivo::ClienteArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool ClienteArchivo::crear(const Cliente &reg) {
   string sql =
      "INSERT INTO Cliente (CUIT, Nombre, Apellido, Email, Telefono, "
      "Direccion, IdTipoCliente, Activo) VALUES ("
      + sqlTexto(reg.getCuit()) + ", "
      + sqlTextoONull(reg.getNombre()) + ", "
      + sqlTextoONull(reg.getApellido()) + ", "
      + sqlTextoONull(reg.getEmail()) + ", "
      + sqlTextoONull(reg.getTelefono()) + ", "
      + sqlTextoONull(reg.getDireccion()) + ", "
      + to_string(reg.getTipoCliente()) + ", "
      + (reg.getEliminado() ? "0" : "1") + ")";
   return ConexionBD::getInstance().ejecutar(sql);
}

bool ClienteArchivo::actualizar(int pos, const Cliente &reg) {
   // Resolver el CUIT que ocupa la posicion 'pos' (orden por CUIT).
   ConexionBD &bd = ConexionBD::getInstance();
   string sqlPos = "SELECT CUIT FROM Cliente ORDER BY CUIT OFFSET "
                   + to_string(pos) + " ROWS FETCH NEXT 1 ROWS ONLY";
   SQLHSTMT h = bd.consultar(sqlPos);
   if (h == SQL_NULL_HSTMT) return false;
   string cuit;
   if (SQLFetch(h) == SQL_SUCCESS) cuit = ConexionBD::colTexto(h, 1);
   ConexionBD::liberar(h);
   if (cuit.empty()) return false;

   bool baja = reg.getEliminado();
   string sql =
      "UPDATE Cliente SET "
      "Nombre = "        + sqlTextoONull(reg.getNombre()) + ", "
      "Apellido = "      + sqlTextoONull(reg.getApellido()) + ", "
      "Email = "         + sqlTextoONull(reg.getEmail()) + ", "
      "Telefono = "      + sqlTextoONull(reg.getTelefono()) + ", "
      "Direccion = "     + sqlTextoONull(reg.getDireccion()) + ", "
      "IdTipoCliente = " + to_string(reg.getTipoCliente()) + ", "
      "Activo = "        + (baja ? string("0") : string("1")) + ", "
      "FechaBaja = "     + (baja ? string("GETDATE()") : string("NULL")) +
      " WHERE CUIT = "   + sqlTexto(cuit);
   return bd.ejecutar(sql);
}

Cliente ClienteArchivo::leer(int pos) {
   Cliente c;
   string sql = string("SELECT ") + COLS +
                " FROM Cliente ORDER BY CUIT OFFSET " + to_string(pos) +
                " ROWS FETCH NEXT 1 ROWS ONLY";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return c;
   if (SQLFetch(h) == SQL_SUCCESS) c = leerFila(h);
   ConexionBD::liberar(h);
   return c;
}

int ClienteArchivo::leerTodos(Cliente vClientes[], int cantidad) {
   string sql = string("SELECT ") + COLS + " FROM Cliente ORDER BY CUIT";
   SQLHSTMT h = ConexionBD::getInstance().consultar(sql);
   if (h == SQL_NULL_HSTMT) return 0;
   int i = 0;
   while (i < cantidad && SQLFetch(h) == SQL_SUCCESS) {
      vClientes[i++] = leerFila(h);
   }
   ConexionBD::liberar(h);
   return i;
}

int ClienteArchivo::getCantidadRegistros() {
   return (int)ConexionBD::getInstance().escalar("SELECT COUNT(*) FROM Cliente");
}

int ClienteArchivo::buscarPorCuit(const string &cuit) {
   ConexionBD &bd = ConexionBD::getInstance();
   long existe = bd.escalar(
      "SELECT COUNT(*) FROM Cliente WHERE CUIT = " + sqlTexto(cuit));
   if (existe == 0) return -1;
   // posicion 0-based = cantidad de CUIT anteriores en el mismo orden
   return (int)bd.escalar(
      "SELECT COUNT(*) FROM Cliente WHERE CUIT < " + sqlTexto(cuit));
}
