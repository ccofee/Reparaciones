#pragma once
#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

// ============================================================
// ConexionBD - Conexion unica (singleton) a SQL Server via ODBC.
// Reemplaza la persistencia en archivos .dat por acceso a la base
// Reparaciones_G79. La cadena de conexion se puede sobreescribir
// con la variable de entorno REP_DB_CONN.
// ============================================================
class ConexionBD {
public:
   static ConexionBD &getInstance();

   bool ok() const;

   // INSERT / UPDATE / DELETE (sin parametros de salida).
   bool ejecutar(const std::string &sql);

   // SELECT que devuelve un unico valor entero (COUNT, MAX, etc.).
   long escalar(const std::string &sql, long porDefecto = 0);

   // SELECT generico: devuelve un statement listo para iterar con
   // SQLFetch. El llamador debe liberarlo con liberar(). NULL si falla.
   SQLHSTMT consultar(const std::string &sql);

   // Lectura de columnas de la fila actual (1-based). NULL -> "" / 0.
   static std::string colTexto(SQLHSTMT h, int col);
   static int         colEntero(SQLHSTMT h, int col);
   static double      colReal(SQLHSTMT h, int col);
   static void        liberar(SQLHSTMT h);

   ~ConexionBD();

private:
   ConexionBD();
   ConexionBD(const ConexionBD &) = delete;
   ConexionBD &operator=(const ConexionBD &) = delete;

   void conectar();
   void reportarError(const std::string &contexto, SQLSMALLINT tipo, SQLHANDLE h);

   SQLHENV _env;
   SQLHDBC _dbc;
   bool    _conectado;
};

// --------- utilidades de formateo de literales SQL ---------
// Devuelve 'texto' con las comillas simples escapadas.
std::string sqlTexto(const std::string &v);
// Igual que sqlTexto pero devuelve NULL si la cadena esta vacia.
std::string sqlTextoONull(const std::string &v);
