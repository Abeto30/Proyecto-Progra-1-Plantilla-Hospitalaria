#include "SerializadorDepartamentos.h"

#include "../Gestores/GestorDepartamentos.h"
#include "../Clases/Departamento.h"
#include "../Clases/Puesto.h"

#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <utility>

// SERIALIZAR: convertir departamentos y puestos a texto
std::string SerializadorDepartamentos::serializar(
    const GestorDepartamentos& gestor) {

    std::ostringstream salida;

    salida << gestor.getCantidadDepartamentos() << '\n';

    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++) {

        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        salida << departamento->getId() << ' '
               << std::quoted(departamento->getNombre()) << ' '
               << std::quoted(departamento->getDescripcion()) << ' '
               << departamento->getCantidadPuestos() << '\n';

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

// DESERIALIZAR: reconstruir departamentos y puestos desde texto
bool SerializadorDepartamentos::deserializar(
    const std::string& datos,
    GestorDepartamentos& gestor) {

    std::istringstream entrada(datos);

    int cantidadDepartamentos;

    if (!(entrada >> cantidadDepartamentos) ||
        cantidadDepartamentos < 0) {
        return false;
    }

    struct DatosPuesto {
        int id;
        std::string nombre;
        std::string descripcion;
    };

    struct DatosDepartamento {
        int id;
        std::string nombre;
        std::string descripcion;
        std::vector<DatosPuesto> puestos;
    };

    std::vector<DatosDepartamento> departamentosLeidos;

    // Leer los datos antes de modificar el gestor
    for (int i = 0; i < cantidadDepartamentos; i++) {

        DatosDepartamento departamento;
        int cantidadPuestos;

        if (!(entrada >> departamento.id
                     >> std::quoted(departamento.nombre)
                     >> std::quoted(departamento.descripcion)
                     >> cantidadPuestos) ||
            cantidadPuestos < 0) {
            return false;
        }

        for (int j = 0; j < cantidadPuestos; j++) {

            DatosPuesto puesto;

            if (!(entrada >> puesto.id
                         >> std::quoted(puesto.nombre)
                         >> std::quoted(puesto.descripcion))) {
                return false;
            }

            departamento.puestos.push_back(puesto);
        }

        departamentosLeidos.push_back(departamento);
    }

    // Reconstruir los departamentos temporalmente
    std::vector<std::unique_ptr<Departamento>> temporales;

    for (const DatosDepartamento& datosDepartamento : departamentosLeidos) {

        auto departamento = std::make_unique<Departamento>(
            datosDepartamento.id,
            datosDepartamento.nombre,
            datosDepartamento.descripcion
        );

        for (const DatosPuesto& datosPuesto : datosDepartamento.puestos) {

            Puesto puesto(
                datosPuesto.id,
                datosPuesto.nombre,
                datosPuesto.descripcion
            );

            if (!departamento->agregarPuesto(puesto)) {
                return false;
            }
        }

        temporales.push_back(std::move(departamento));
    }

    // Reemplazar los datos anteriores
    gestor.limpiarDepartamentos();

    for (auto& departamento : temporales) {

        if (!gestor.agregarDepartamento(departamento.get())) {
            gestor.limpiarDepartamentos();
            return false;
        }

        departamento.release();
    }

    return true;
}