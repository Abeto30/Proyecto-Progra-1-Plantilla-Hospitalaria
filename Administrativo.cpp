#include "Administrativo.h"

Administrativo::Administrativo(int id,
                               const std::string& nombre,
                               const std::string& identificacion,
                               const std::string& telefono,
                               const std::string& correo,
                               double salarioBase,
                               const std::string& cargo)
    : Empleado(id, nombre, identificacion, telefono, correo, salarioBase),
      cargo(cargo),
      horasExtras(0),
      tarifaHoraExtra(0.0) {
}