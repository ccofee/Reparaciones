#include <iostream>
#include <cstdlib>
#include "conexionBD.h"
using namespace std;

// Cadena de conexion por defecto (instancia local SQL Server Express).
// Se puede sobreescribir exportando la variable de entorno REP_DB_CONN.
static const char *CONN_POR_DEFECTO =
   "Driver={ODBC Driver 17 for SQL Server};"
   "Server=.\\SQLEXPRESS;"
   "Database=Reparaciones_G79;"
   "Trusted_Connection=yes;";

ConexionBD &ConexionBD::getInstance() {
   static ConexionBD instancia;
   return instancia;
}

ConexionBD::ConexionBD() : _env(SQL_NULL_HENV), _dbc(SQL_NULL_HDBC), _conectado(false) {
   conectar();
}

ConexionBD::~ConexionBD() {
   if (_dbc != SQL_NULL_HDBC) {
      if (_conectado) SQLDisconnect(_dbc);
      SQLFreeHandle(SQL_HANDLE_DBC, _dbc);
   }
   if (_env != SQL_NULL_HENV) {
      SQLFreeHandle(SQL_HANDLE_ENV, _env);
   }
}

bool ConexionBD::ok() const { return _conectado; }

void ConexionBD::conectar() {
   if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_env) != SQL_SUCCESS) {
      cout << "\n[BD] ERROR: no se pudo crear el entorno ODBC." << endl;
      return;
   }
   SQLSetEnvAttr(_env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

   if (SQLAllocHandle(SQL_HANDLE_DBC, _env, &_dbc) != SQL_SUCCESS) {
      cout << "\n[BD] ERROR: no se pudo crear la conexion ODBC." << endl;
      return;
   }

   const char *envConn = getenv("REP_DB_CONN");
   string cadena = envConn ? string(envConn) : string(CONN_POR_DEFECTO);

   SQLCHAR salida[1024];
   SQLSMALLINT salidaLen = 0;
   SQLRETURN r = SQLDriverConnect(
      _dbc, NULL,
      (SQLCHAR *)cadena.c_str(), SQL_NTS,
      salida, sizeof(salida), &salidaLen,
      SQL_DRIVER_NOPROMPT);

   if (r == SQL_SUCCESS || r == SQL_SUCCESS_WITH_INFO) {
      _conectado = true;
   } else {
      _conectado = false;
      reportarError("Conexion a la base", SQL_HANDLE_DBC, _dbc);
      cout << "[BD] Verifique que SQL Server este corriendo y que la base "
              "Reparaciones_G79 exista (ver carpeta db/)." << endl;
   }
}

void ConexionBD::reportarError(const string &contexto, SQLSMALLINT tipo, SQLHANDLE h) {
   SQLCHAR estado[6], mensaje[SQL_MAX_MESSAGE_LENGTH];
   SQLINTEGER nativo;
   SQLSMALLINT largo;
   SQLSMALLINT i = 1;
   cout << "\n[BD] " << contexto << ":" << endl;
   while (SQLGetDiagRec(tipo, h, i, estado, &nativo, mensaje,
                        sizeof(mensaje), &largo) == SQL_SUCCESS) {
      cout << "     [" << estado << "] " << mensaje << endl;
      i++;
   }
}

bool ConexionBD::ejecutar(const string &sql) {
   if (!_conectado) return false;

   SQLHSTMT stmt = SQL_NULL_HSTMT;
   if (SQLAllocHandle(SQL_HANDLE_STMT, _dbc, &stmt) != SQL_SUCCESS) return false;

   SQLRETURN r = SQLExecDirect(stmt, (SQLCHAR *)sql.c_str(), SQL_NTS);
   bool exito = (r == SQL_SUCCESS || r == SQL_SUCCESS_WITH_INFO || r == SQL_NO_DATA);
   if (!exito) reportarError("Error al ejecutar comando", SQL_HANDLE_STMT, stmt);

   SQLFreeHandle(SQL_HANDLE_STMT, stmt);
   return exito;
}

long ConexionBD::escalar(const string &sql, long porDefecto) {
   SQLHSTMT stmt = consultar(sql);
   if (stmt == SQL_NULL_HSTMT) return porDefecto;

   long valor = porDefecto;
   if (SQLFetch(stmt) == SQL_SUCCESS) {
      valor = colEntero(stmt, 1);
   }
   liberar(stmt);
   return valor;
}

SQLHSTMT ConexionBD::consultar(const string &sql) {
   if (!_conectado) return SQL_NULL_HSTMT;

   SQLHSTMT stmt = SQL_NULL_HSTMT;
   if (SQLAllocHandle(SQL_HANDLE_STMT, _dbc, &stmt) != SQL_SUCCESS) return SQL_NULL_HSTMT;

   SQLRETURN r = SQLExecDirect(stmt, (SQLCHAR *)sql.c_str(), SQL_NTS);
   if (r != SQL_SUCCESS && r != SQL_SUCCESS_WITH_INFO) {
      reportarError("Error al consultar", SQL_HANDLE_STMT, stmt);
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      return SQL_NULL_HSTMT;
   }
   return stmt;
}

string ConexionBD::colTexto(SQLHSTMT h, int col) {
   char buffer[4096];
   SQLLEN ind = 0;
   SQLRETURN r = SQLGetData(h, (SQLUSMALLINT)col, SQL_C_CHAR,
                            buffer, sizeof(buffer), &ind);
   if (r != SQL_SUCCESS && r != SQL_SUCCESS_WITH_INFO) return "";
   if (ind == SQL_NULL_DATA) return "";
   return string(buffer);
}

int ConexionBD::colEntero(SQLHSTMT h, int col) {
   SQLINTEGER valor = 0;
   SQLLEN ind = 0;
   SQLRETURN r = SQLGetData(h, (SQLUSMALLINT)col, SQL_C_SLONG, &valor, 0, &ind);
   if (r != SQL_SUCCESS && r != SQL_SUCCESS_WITH_INFO) return 0;
   if (ind == SQL_NULL_DATA) return 0;
   return (int)valor;
}

double ConexionBD::colReal(SQLHSTMT h, int col) {
   double valor = 0.0;
   SQLLEN ind = 0;
   SQLRETURN r = SQLGetData(h, (SQLUSMALLINT)col, SQL_C_DOUBLE, &valor, 0, &ind);
   if (r != SQL_SUCCESS && r != SQL_SUCCESS_WITH_INFO) return 0.0;
   if (ind == SQL_NULL_DATA) return 0.0;
   return valor;
}

void ConexionBD::liberar(SQLHSTMT h) {
   if (h != SQL_NULL_HSTMT) SQLFreeHandle(SQL_HANDLE_STMT, h);
}

// ------------------------------------------------------------
std::string sqlTexto(const std::string &v) {
   string esc;
   esc.reserve(v.size() + 2);
   esc += '\'';
   for (char c : v) {
      if (c == '\'') esc += '\'';   // escapar comilla simple
      esc += c;
   }
   esc += '\'';
   return esc;
}

std::string sqlTextoONull(const std::string &v) {
   if (v.empty()) return "NULL";
   return sqlTexto(v);
}
