#include "SerializadorDepartamentos.h"

#include "../Gestores/GestorDepartamentos.h"
#include "../Clases/Departamento.h"
#include "../Clases/Puesto.h"

#include <sstream>
#include <iomanip>
#include <vector>

bool SerializadorDepartamentos::deserializar(
    const std::string& datos,
    GestorDepartamentos& gestor) {

    std::istringstream entrada(datos);

    int cantidadDepartamentos;

    // Leer la cantidad de departamentos
    if (!(entrada >> cantidadDepartamentos) || cantidadDepartamentos < 0) {
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

    // Leer todos los departamentos y sus puestos
    for (int i = 0; i < cantidadDepartamentos; i++) {
        DatosDepartamento departamento;
        int cantidadPuestos;

        if (!(entrada >> departamento.id
                      >> std::quoted(departamento.nombre)
                      >> std::quoted(departamento.descripcion)
                      >> cantidadPuestos)
            || cantidadPuestos < 0) {
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

    // Reconstruir los departamentos
    gestor.limpiarDepartamentos();

    for (const DatosDepartamento& datosDepartamento : departamentosLeidos) {

        Departamento* departamento = new Departamento(
            datosDepartamento.id,
            datosDepartamento.nombre,
            datosDepartamento.descripcion
        );

        // Reconstruir los puestos del departamento
        for (const DatosPuesto& datosPuesto : datosDepartamento.puestos) {

            Puesto puesto(
                datosPuesto.id,
                datosPuesto.nombre,
                datosPuesto.descripcion
            );

            if (!departamento->agregarPuesto(puesto)) {
                delete departamento;
                gestor.limpiarDepartamentos();
                return false;
            }
        }

        // Agregar el departamento al gestor
        if (!gestor.agregarDepartamento(departamento)) {
            delete departamento;
            gestor.limpiarDepartamentos();
            return false;
        }
    }

    return true;
}