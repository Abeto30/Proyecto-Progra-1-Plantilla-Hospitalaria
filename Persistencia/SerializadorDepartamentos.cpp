#include "SerializadorDepartamentos.h"

#include "../Gestores/GestorDepartamentos.h"
#include "../Clases/Departamento.h"
#include "../Clases/Puesto.h"

#include <sstream>
#include <iomanip>

std::string SerializadorDepartamentos::serializar(
    const GestorDepartamentos& gestor) {

    std::ostringstream salida;

    // Guardar la cantidad de departamentos
    salida << gestor.getCantidadDepartamentos() << '\n';

    // Recorrer los departamentos
    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++) {

        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        // Guardar los datos del departamento
        salida << departamento->getId() << ' '
               << std::quoted(departamento->getNombre()) << ' '
               << std::quoted(departamento->getDescripcion()) << ' '
               << departamento->getCantidadPuestos() << '\n';

        // Guardar los puestos del departamento
        for (int j = 0; j < departamento->getCantidadPuestos(); j++) {

            Puesto puesto =
                departamento->obtenerPuestoEnPosicion(j);

            salida << puesto.getId() << ' '
                   << std::quoted(puesto.getNombre()) << ' '
                   << std::quoted(puesto.getDescripcion()) << '\n';
        }
    }

    return salida.str();
}