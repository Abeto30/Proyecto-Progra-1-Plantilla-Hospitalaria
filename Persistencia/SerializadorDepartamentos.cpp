#include "SerializadorDepartamentos.h"

#include "../Gestores/GestorDepartamentos.h"
#include "../Clases/Departamento.h"
#include "../Clases/Puesto.h"

#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_set>

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
    std::unordered_set<int> idsDepartamentos;

    // Leer y validar todos los departamentos
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

        if (!idsDepartamentos.insert(departamento.id).second) {
            return false;
        }

        std::unordered_set<int> idsPuestos;

        // Leer y validar los puestos
        for (int j = 0; j < cantidadPuestos; j++) {

            DatosPuesto puesto;

            if (!(entrada >> puesto.id
                         >> std::quoted(puesto.nombre)
                         >> std::quoted(puesto.descripcion))) {
                return false;
            }

            if (!idsPuestos.insert(puesto.id).second) {
                return false;
            }

            departamento.puestos.push_back(puesto);
        }

        departamentosLeidos.push_back(departamento);
    }

    // Rechazar contenido adicional inesperado
    entrada >> std::ws;

    if (!entrada.eof()) {
        return false;
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

    // Preparar los departamentos para transferirlos al gestor
    std::vector<Departamento*> punteros;

    for (const auto& departamento : temporales) {
        punteros.push_back(departamento.get());
    }

    // Reemplazar los datos anteriores
    gestor.limpiarDepartamentos();

    for (Departamento* departamento : punteros) {

        if (!gestor.agregarDepartamento(departamento)) {
            gestor.limpiarDepartamentos();
            return false;
        }

        // El gestor ahora es propietario del objeto
        for (auto& temporal : temporales) {
            if (temporal.get() == departamento) {
                temporal.release();
                break;
            }
        }
    }

    return true;
}