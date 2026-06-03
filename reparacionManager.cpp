#include <iostream>
#include "reparacionManager.h"
#include "utils.h"
using namespace std;

ReparacionManager::ReparacionManager()
   : _repo(), _repoDetalle(), _repoCliente(), _repoEmpleado(), _repoEquipo() {}

float ReparacionManager::calcularTotal(int nroReparacion) {
   int cant = _repoDetalle.getCantidadRegistros();
   float total = 0;
   for (int i = 0; i < cant; i++) {
      DetalleReparacion d = _repoDetalle.leer(i);
      if (d.getNroReparacion() == nroReparacion && !d.getEliminado()) {
         total += d.getImporte();
      }
   }
   return total;
}

int ReparacionManager::contarEquiposDeReparacion(int nroReparacion) {
   int cant = _repoDetalle.getCantidadRegistros();
   int cantidad = 0;
   for (int i = 0; i < cant; i++) {
      DetalleReparacion d = _repoDetalle.leer(i);
      if (d.getNroReparacion() == nroReparacion && !d.getEliminado()) {
         cantidad++;
      }
   }
   return cantidad;
}

void ReparacionManager::mostrarEquiposDeCliente(const string &cuit) {
   int cant = _repoEquipo.getCantidadRegistros();
   bool hay = false;

   cout << "\nEquipos del cliente " << cuit << ":" << endl;
   for (int i = 0; i < cant; i++) {
      Equipo e = _repoEquipo.leer(i);
      if (!e.getEliminado() && e.getCuit() == cuit) {
         cout << "  #" << e.getNroEquipo() << " - " << e.getTipoEquipoString()
              << " - " << e.getMarca() << " - " << e.getDescripcion() << endl;
         hay = true;
      }
   }
   if (!hay) cout << "  (sin equipos cargados)" << endl;
}

float ReparacionManager::pedirImporte() {
   float importe;
   do {
      importe = cargarFloat("Importe: ");
      if (importe <= 0) cout << " > El importe debe ser mayor a 0." << endl;
   } while (importe <= 0);
   return importe;
}

void ReparacionManager::agregarDetalle(int nroReparacion, int nroEquipo, float importe) {
   DetalleReparacion d(nroReparacion, nroEquipo, importe);
   _repoDetalle.crear(d);
}

bool ReparacionManager::detalleYaCargado(int nroReparacion, int nroEquipo) {
   return _repoDetalle.buscarDetalle(nroReparacion, nroEquipo) != -1;
}

bool ReparacionManager::equipoPerteneceACliente(int nroEquipo, const string &cuit) {
   int pos = _repoEquipo.buscarPorNumero(nroEquipo);
   if (pos == -1) return false;
   Equipo e = _repoEquipo.leer(pos);
   return e.getCuit() == cuit;
}

void ReparacionManager::mostrar(const Reparacion &r) {
   cout << "Reparacion #" << r.getNroReparacion() << endl;

   int posC = _repoCliente.buscarPorCuit(r.getCuit());
   if (posC != -1) {
      Cliente c = _repoCliente.leer(posC);
      cout << "Cliente: " << r.getCuit() << " - " << c.getNombre() << " " << c.getApellido() << endl;
   } else {
      cout << "Cliente: " << r.getCuit() << " (no encontrado)" << endl;
   }

   int posE = _repoEmpleado.buscarPorLegajo(r.getLegajo());
   if (posE != -1) {
      Empleado e = _repoEmpleado.leer(posE);
      cout << "Atendio: " << r.getLegajo() << " - " << e.getNombre() << " " << e.getApellido() << endl;
   } else {
      cout << "Atendio: " << r.getLegajo() << " (no encontrado)" << endl;
   }

   cout << "Fecha de entrega: " << r.getFechaEntrega().toString() << endl;

   cout << "Equipos reparados:" << endl;
   int cantD = _repoDetalle.getCantidadRegistros();
   float total = 0;
   bool hay = false;
   for (int i = 0; i < cantD; i++) {
      DetalleReparacion d = _repoDetalle.leer(i);
      if (d.getNroReparacion() == r.getNroReparacion() && !d.getEliminado()) {
         cout << "  - Equipo #" << d.getNroEquipo();
         int posEq = _repoEquipo.buscarPorNumero(d.getNroEquipo());
         if (posEq != -1) {
            Equipo eq = _repoEquipo.leer(posEq);
            cout << " (" << eq.getTipoEquipoString() << " - " << eq.getDescripcion() << ")";
         }
         cout << " - Importe: $" << d.getImporte() << endl;
         total += d.getImporte();
         hay = true;
      }
   }
   if (!hay) cout << "  (sin equipos cargados)" << endl;
   cout << "TOTAL: $" << total << endl;
   cout << "-----------------------------------" << endl;
}

int ReparacionManager::cargarDetalles(int nroReparacion, const string &cuit) {
   int cargados = 0;

   cout << "\n=== CARGA DE EQUIPOS A REPARAR ===" << endl;
   cout << "(Ingrese 0 como numero de equipo para finalizar)" << endl;

   while (true) {
      mostrarEquiposDeCliente(cuit);
      int nroEquipo = cargarEntero("\nNumero de equipo a reparar (0 para finalizar): ");

      if (nroEquipo == 0) {
         if (cargados == 0) {
            cout << "Debe cargar al menos un equipo para la reparacion." << endl;
            continue;
         }
         break;
      }
      if (_repoEquipo.buscarPorNumero(nroEquipo) == -1) {
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

void ReparacionManager::alta() {
   cout << "\n=== ALTA DE REPARACION ===" << endl;

   if (_repoCliente.getCantidadRegistros() == 0) {
      cout << "No hay clientes registrados. Cargue clientes primero." << endl;
      return;
   }
   if (_repoEquipo.getCantidadRegistros() == 0) {
      cout << "No hay equipos registrados. Cargue equipos primero." << endl;
      return;
   }

   int nro = _repo.getNuevoId();
   cout << "Numero de reparacion asignado: " << nro << endl;

   string cuit, legajo;
   do {
      cuit = cargarTexto("CUIT del cliente: ", 14);
      if (_repoCliente.buscarPorCuit(cuit) == -1) cout << " > El cliente no existe o esta eliminado." << endl;
   } while (_repoCliente.buscarPorCuit(cuit) == -1);

   do {
      legajo = cargarTexto("Legajo del empleado: ", 9);
      if (_repoEmpleado.buscarPorLegajo(legajo) == -1) cout << " > El empleado no existe o esta eliminado." << endl;
   } while (_repoEmpleado.buscarPorLegajo(legajo) == -1);

   Fecha fe = cargarFecha("Fecha de entrega:");

   Reparacion r(nro, cuit, legajo, fe);
   if (!_repo.crear(r)) {
      cout << "\nError al guardar la reparacion." << endl;
      return;
   }

   int cargados = cargarDetalles(nro, cuit);
   cout << "\nReparacion #" << nro << " guardada exitosamente con "
        << cargados << " equipo(s)." << endl;
}

void ReparacionManager::baja() {
   cout << "\n=== BAJA DE REPARACION ===" << endl;
   int nro = cargarEntero("Ingrese numero de reparacion: ");

   int pos = _repo.buscarPorNumero(nro);
   if (pos == -1) {
      cout << "\nReparacion no encontrada o ya esta eliminada." << endl;
      return;
   }

   Reparacion r = _repo.leer(pos);
   r.setEliminado(true);
   if (!_repo.actualizar(pos, r)) {
      cout << "\nError al dar de baja la reparacion." << endl;
      return;
   }

   int cantD = _repoDetalle.getCantidadRegistros();
   for (int i = 0; i < cantD; i++) {
      DetalleReparacion d = _repoDetalle.leer(i);
      if (d.getNroReparacion() == nro && !d.getEliminado()) {
         d.setEliminado(true);
         _repoDetalle.actualizar(i, d);
      }
   }

   cout << "\nReparacion dada de baja exitosamente (incluye sus detalles)." << endl;
}

void ReparacionManager::modificarDetalles(const Reparacion &r) {
   int opcion;

   do {
      cout << "\n=== DETALLES DE LA REPARACION #" << r.getNroReparacion() << " ===" << endl;
      cout << "1. Agregar equipo al detalle" << endl;
      cout << "2. Modificar importe de un equipo" << endl;
      cout << "3. Quitar equipo del detalle" << endl;
      cout << "4. Ver detalles actuales" << endl;
      cout << "0. Terminar modificacion de detalles" << endl;
      opcion = cargarEntero("Seleccione una opcion: ");

      if (opcion == 1) {
         mostrarEquiposDeCliente(r.getCuit());
         int nroEquipo = cargarEntero("\nNumero de equipo a agregar (0 para cancelar): ");
         if (nroEquipo == 0) continue;
         if (_repoEquipo.buscarPorNumero(nroEquipo) == -1) {
            cout << "El equipo no existe o esta eliminado." << endl;
            continue;
         }
         if (!equipoPerteneceACliente(nroEquipo, r.getCuit())) {
            cout << "El equipo no pertenece al cliente de la reparacion." << endl;
            continue;
         }
         if (detalleYaCargado(r.getNroReparacion(), nroEquipo)) {
            cout << "Ese equipo ya esta en el detalle." << endl;
            continue;
         }
         float importe = pedirImporte();
         agregarDetalle(r.getNroReparacion(), nroEquipo, importe);
         cout << "Equipo agregado." << endl;
      } else if (opcion == 2) {
         int nroEquipo = cargarEntero("Numero de equipo cuyo importe desea modificar: ");
         int posDetalle = _repoDetalle.buscarDetalle(r.getNroReparacion(), nroEquipo);
         if (posDetalle == -1) {
            cout << "Ese equipo no esta en el detalle." << endl;
            continue;
         }
         DetalleReparacion d = _repoDetalle.leer(posDetalle);
         cout << "Importe actual: $" << d.getImporte() << endl;
         d.setImporte(pedirImporte());
         _repoDetalle.actualizar(posDetalle, d);
         cout << "Importe modificado." << endl;
      } else if (opcion == 3) {
         int nroEquipo = cargarEntero("Numero de equipo a quitar del detalle: ");
         int posDetalle = _repoDetalle.buscarDetalle(r.getNroReparacion(), nroEquipo);
         if (posDetalle == -1) {
            cout << "Ese equipo no esta en el detalle." << endl;
            continue;
         }
         if (contarEquiposDeReparacion(r.getNroReparacion()) <= 1) {
            cout << "No se puede quitar: la reparacion debe tener al menos un equipo." << endl;
            continue;
         }
         DetalleReparacion d = _repoDetalle.leer(posDetalle);
         d.setEliminado(true);
         _repoDetalle.actualizar(posDetalle, d);
         cout << "Equipo quitado del detalle." << endl;
      } else if (opcion == 4) {
         mostrar(r);
      }
   } while (opcion != 0);
}

void ReparacionManager::modificacion() {
   cout << "\n=== MODIFICACION DE REPARACION ===" << endl;
   int nro = cargarEntero("Ingrese numero de reparacion: ");

   int pos = _repo.buscarPorNumero(nro);
   if (pos == -1) {
      cout << "\nReparacion no encontrada o esta eliminada." << endl;
      return;
   }

   Reparacion r = _repo.leer(pos);
   cout << "\nReparacion actual:" << endl;
   mostrar(r);

   string legajo;
   do {
      legajo = cargarTexto("Legajo del empleado: ", 9);
      if (_repoEmpleado.buscarPorLegajo(legajo) == -1) cout << " > El empleado no existe o esta eliminado." << endl;
   } while (_repoEmpleado.buscarPorLegajo(legajo) == -1);
   r.setLegajo(legajo);

   r.setFechaEntrega(cargarFecha("Fecha de entrega:"));

   if (!_repo.actualizar(pos, r)) {
      cout << "\nError al modificar la reparacion." << endl;
      return;
   }
   cout << "\nDatos de cabecera modificados." << endl;

   int modifica = cargarEntero("\nDesea modificar los equipos del detalle? (1=Si, 0=No): ");
   if (modifica == 1) {
      modificarDetalles(r);
   }

   cout << "\nReparacion modificada exitosamente." << endl;
}

void ReparacionManager::listado() {
   cout << "\n=== LISTADO DE REPARACIONES ===" << endl;
   int cantidad = _repo.getCantidadRegistros();
   if (cantidad == 0) {
      cout << "No hay reparaciones registradas." << endl;
      return;
   }

   bool hay = false;
   for (int i = 0; i < cantidad; i++) {
      Reparacion r = _repo.leer(i);
      if (!r.getEliminado()) {
         mostrar(r);
         hay = true;
      }
   }
   if (!hay) cout << "No hay reparaciones activas." << endl;
}

void ReparacionManager::listadoPorFechaEntrega() {
   cout << "\n=== LISTADO DE REPARACIONES (ORDENADO POR FECHA DE ENTREGA) ===" << endl;
   int cantidad = _repo.getCantidadRegistros();
   if (cantidad == 0) {
      cout << "No hay reparaciones registradas." << endl;
      return;
   }

   Reparacion *v = new Reparacion[cantidad];
   _repo.leerTodos(v, cantidad);

   for (int i = 0; i < cantidad - 1; i++) {
      int min = i;
      for (int j = i + 1; j < cantidad; j++) {
         if (v[j].getFechaEntrega().aNumero() < v[min].getFechaEntrega().aNumero()) min = j;
      }
      if (min != i) {
         Reparacion tmp = v[i];
         v[i] = v[min];
         v[min] = tmp;
      }
   }

   bool hay = false;
   for (int i = 0; i < cantidad; i++) {
      if (!v[i].getEliminado()) {
         mostrar(v[i]);
         hay = true;
      }
   }
   if (!hay) cout << "No hay reparaciones activas." << endl;

   delete[] v;
}
