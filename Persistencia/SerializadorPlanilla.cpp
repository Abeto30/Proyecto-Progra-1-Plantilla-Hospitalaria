
#include "SerializadorPlanilla.h"

#include "../Gestores/GestorComprobantes.h"
#include "../Gestores/GestorEmpleados.h"
#include "../Gestores/GestorDepartamentos.h"

#include "../Clases/ComprobantePago.h"
#include "../Clases/Empleado.h"
#include "../Clases/Departamento.h"

#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <unordered_set>
#include <cmath>
#include <exception>

// SERIALIZAR: convertir los comprobantes a texto
std::string SerializadorPlanilla::serializar(
    const GestorComprobantes& gestor
) {
    std::ostringstream salida;

    salida << std::setprecision(17);
    salida << gestor.getCantidadComprobantes() << '\n';

    for (int i = 0; i < gestor.getCantidadComprobantes(); i++) {

        ComprobantePago* comprobante =
            gestor.obtenerComprobanteEnPosicion(i);

        if (comprobante == nullptr) {
            continue;
        }

        salida << comprobante->getId() << ' '
               << comprobante->getEmpleadoId() << ' '
               << std::quoted(comprobante->getNombreEmpleado()) << ' '
               << std::quoted(comprobante->getIdentificacion()) << ' '
               << std::quoted(comprobante->getTipoEmpleado()) << ' '
               << comprobante->getDepartamentoId() << ' '
               << std::quoted(comprobante->getNombreDepartamento()) << ' '
               << comprobante->getSalarioBruto() << ' '
               << comprobante->getDeducciones() << ' '
               << std::quoted(comprobante->getFecha())
               << '\n';
    }

    return salida.str();
}

// DESERIALIZAR: reconstruir comprobantes desde texto
bool SerializadorPlanilla::deserializar(
    const std::string& datos,
    GestorComprobantes& gestor,
    GestorEmpleados& gestorEmpleados,
    GestorDepartamentos& gestorDepartamentos
) {
    std::istringstream entrada(datos);

    int cantidadComprobantes;

    if (!(entrada >> cantidadComprobantes) ||
        cantidadComprobantes < 0 ||
        cantidadComprobantes > 1000000) {
        return false;
    }

    std::vector<std::unique_ptr<ComprobantePago>> temporales;
    std::unordered_set<int> idsComprobantes;

    for (int i = 0; i < cantidadComprobantes; i++) {

        int id;
        int empleadoId;
        std::string nombreEmpleado;
        std::string identificacion;
        std::string tipoEmpleado;
        int departamentoId;
        std::string nombreDepartamento;
        double salarioBruto;
        double deducciones;
        std::string fecha;

        if (!(entrada >> id
                     >> empleadoId
                     >> std::quoted(nombreEmpleado)
                     >> std::quoted(identificacion)
                     >> std::quoted(tipoEmpleado)
                     >> departamentoId
                     >> std::quoted(nombreDepartamento)
                     >> salarioBruto
                     >> deducciones
                     >> std::quoted(fecha))) {
            return false;
        }

        // Validar identificadores únicos
        if (id <= 0 ||
            !idsComprobantes.insert(id).second) {
            return false;
        }

        // Validar salarios
        if (!std::isfinite(salarioBruto) ||
            !std::isfinite(deducciones) ||
            salarioBruto < 0 ||
            deducciones < 0 ||
            deducciones > salarioBruto) {
            return false;
        }

        // Buscar las referencias originales
        Empleado* empleado =
            gestorEmpleados.buscarEmpleadoPorId(empleadoId);

        Departamento* departamento =
            gestorDepartamentos.buscarDepartamentoPorId(departamentoId);

        std::unique_ptr<ComprobantePago> comprobante;

        try {

            // Si existen ambas entidades, recuperar las referencias.
            if (empleado != nullptr && departamento != nullptr) {

                comprobante = std::make_unique<ComprobantePago>(
                    id,
                    empleado,
                    departamento,
                    salarioBruto,
                    deducciones,
                    fecha
                );

            } else {

                // Si alguna entidad ya no existe, conservar
                // los datos históricos del comprobante.
                comprobante = std::make_unique<ComprobantePago>(
                    id,
                    empleadoId,
                    nombreEmpleado,
                    identificacion,
                    tipoEmpleado,
                    departamentoId,
                    nombreDepartamento,
                    salarioBruto,
                    deducciones,
                    fecha
                );
            }

        } catch (const std::exception&) {
            return false;
        }

        temporales.push_back(std::move(comprobante));
    }

    // Rechazar información adicional inesperada
    entrada >> std::ws;

    if (!entrada.eof()) {
        return false;
    }
    // Reemplazar los comprobantes anteriores
    gestor.limpiarComprobantes();

    // Transferir la propiedad al gestor
    for (auto& temporal : temporales) {

        ComprobantePago* comprobante = temporal.get();

        if (!gestor.agregarComprobante(comprobante)) {
            gestor.limpiarComprobantes();
            return false;
        }

        temporal.release();
    }

    return true;
}
