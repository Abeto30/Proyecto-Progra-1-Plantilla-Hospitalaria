
#include "SerializadorEmpleados.h"

#include "../Gestores/GestorEmpleados.h"
#include "../Gestores/GestorDepartamentos.h"

#include "../Clases/Empleado.h"
#include "../Clases/Medico.h"
#include "../Clases/Enfermero.h"
#include "../Clases/Administrativo.h"
#include "../Clases/Departamento.h"

#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <unordered_set>
#include <cmath>

// SERIALIZAR: convertir los empleados a texto
std::string SerializadorEmpleados::serializar(
    const GestorEmpleados& gestor) {

    std::ostringstream salida;

    salida << std::setprecision(17);
    salida << gestor.getCantidadEmpleados() << '\n';

    for (int i = 0; i < gestor.getCantidadEmpleados(); i++) {

        Empleado* empleado =
            gestor.obtenerEmpleadoEnPosicion(i);

        if (empleado == nullptr) {
            continue;
        }

        int idDepartamento = -1;

        if (empleado->getDepartamento() != nullptr) {
            idDepartamento = empleado->getDepartamento()->getId();
        }

        salida << empleado->getTipoEmpleado() << ' '
               << empleado->getId() << ' '
               << std::quoted(empleado->getNombre()) << ' '
               << std::quoted(empleado->getIdentificacion()) << ' '
               << std::quoted(empleado->getTelefono()) << ' '
               << std::quoted(empleado->getCorreo()) << ' '
               << empleado->getSalarioBase() << ' '
               << empleado->estaActivo() << ' '
               << idDepartamento;

        // Datos específicos de los médicos
        if (Medico* medico = dynamic_cast<Medico*>(empleado)) {

            salida << ' '
                   << std::quoted(medico->getEspecialidad()) << ' '
                   << medico->getHorasExtras() << ' '
                   << medico->getHorasGuardia() << ' '
                   << medico->getTarifaHoraExtra() << ' '
                   << medico->getTarifaHoraGuardia();
        }

        // Datos específicos de los enfermeros
        else if (Enfermero* enfermero =
                     dynamic_cast<Enfermero*>(empleado)) {

            salida << ' '
                   << std::quoted(enfermero->getTurno()) << ' '
                   << enfermero->getHorasExtras() << ' '
                   << enfermero->getHorasNocturnas() << ' '
                   << enfermero->getTarifaHoraExtra() << ' '
                   << enfermero->getTarifaHoraNocturna();
        }

        // Datos específicos de los administrativos
        else if (Administrativo* administrativo =
                     dynamic_cast<Administrativo*>(empleado)) {

            salida << ' '
                   << std::quoted(administrativo->getCargo()) << ' '
                   << administrativo->getHorasExtras() << ' '
                   << administrativo->getTarifaHoraExtra();
        }

        salida << '\n';
    }

    return salida.str();
}

// DESERIALIZAR: reconstruir empleados desde texto
bool SerializadorEmpleados::deserializar(
    const std::string& datos,
    GestorEmpleados& gestor,
    GestorDepartamentos& gestorDepartamentos) {

    std::istringstream entrada(datos);

    int cantidadEmpleados;

    if (!(entrada >> cantidadEmpleados) ||
        cantidadEmpleados < 0) {
        return false;
    }

    std::vector<std::unique_ptr<Empleado>> temporales;
    std::unordered_set<int> idsEmpleados;

    for (int i = 0; i < cantidadEmpleados; i++) {

        std::string tipo;
        int id;
        std::string nombre;
        std::string identificacion;
        std::string telefono;
        std::string correo;
        double salarioBase;
        bool activo;
        int idDepartamento;

        if (!(entrada >> tipo
                     >> id
                     >> std::quoted(nombre)
                     >> std::quoted(identificacion)
                     >> std::quoted(telefono)
                     >> std::quoted(correo)
                     >> salarioBase
                     >> activo
                     >> idDepartamento)) {
            return false;
        }

        // Validar datos generales
        if (id <= 0 ||
            !idsEmpleados.insert(id).second ||
            !std::isfinite(salarioBase) ||
            salarioBase < 0) {
            return false;
        }

        // Recuperar el departamento correspondiente
        Departamento* departamento = nullptr;

        if (idDepartamento != -1) {

            departamento =
                gestorDepartamentos.buscarDepartamentoPorId(
                    idDepartamento
                );

            if (departamento == nullptr) {
                return false;
            }
        }

        std::unique_ptr<Empleado> empleado;

        // Reconstruir médicos
        if (tipo == "Medico") {

            std::string especialidad;
            int horasExtras;
            int horasGuardia;
            double tarifaHoraExtra;
            double tarifaHoraGuardia;

            if (!(entrada >> std::quoted(especialidad)
                         >> horasExtras
                         >> horasGuardia
                         >> tarifaHoraExtra
                         >> tarifaHoraGuardia)) {
                return false;
            }

            if (horasExtras < 0 ||
                horasGuardia < 0 ||
                horasExtras > 1000000 ||
                horasGuardia > 1000000 ||
                !std::isfinite(tarifaHoraExtra) ||
                !std::isfinite(tarifaHoraGuardia) ||
                tarifaHoraExtra < 0 ||
                tarifaHoraGuardia < 0) {
                return false;
            }

            auto medico = std::make_unique<Medico>(
                id,
                nombre,
                identificacion,
                telefono,
                correo,
                salarioBase,
                especialidad
            );

            if (horasExtras > 0) {
                medico->registrarHorasExtras(horasExtras);
            }

            if (horasGuardia > 0) {
                medico->registrarHorasGuardia(horasGuardia);
            }

            medico->setTarifaHoraExtra(tarifaHoraExtra);
            medico->setTarifaHoraGuardia(tarifaHoraGuardia);

            empleado = std::move(medico);
        }

        // Reconstruir enfermeros
        else if (tipo == "Enfermero") {

            std::string turno;
            int horasExtras;
            int horasNocturnas;
            double tarifaHoraExtra;
            double tarifaHoraNocturna;

            if (!(entrada >> std::quoted(turno)
                         >> horasExtras
                         >> horasNocturnas
                         >> tarifaHoraExtra
                         >> tarifaHoraNocturna)) {
                return false;
            }

            if (horasExtras < 0 ||
                horasNocturnas < 0 ||
                horasExtras > 1000000 ||
                horasNocturnas > 1000000 ||
                !std::isfinite(tarifaHoraExtra) ||
                !std::isfinite(tarifaHoraNocturna) ||
                tarifaHoraExtra < 0 ||
                tarifaHoraNocturna < 0) {
                return false;
            }

            auto enfermero = std::make_unique<Enfermero>(
                id,
                nombre,
                identificacion,
                telefono,
                correo,
                salarioBase,
                turno
            );

            if (horasExtras > 0) {
                enfermero->registrarHorasExtras(horasExtras);
            }

            if (horasNocturnas > 0) {
                enfermero->registrarHorasNocturnas(horasNocturnas);
            }

            enfermero->setTarifaHoraExtra(tarifaHoraExtra);
            enfermero->setTarifaHoraNocturna(tarifaHoraNocturna);

            empleado = std::move(enfermero);
        }

        // Reconstruir administrativos
        else if (tipo == "Administrativo") {

            std::string cargo;
            int horasExtras;
            double tarifaHoraExtra;

            if (!(entrada >> std::quoted(cargo)
                         >> horasExtras
                         >> tarifaHoraExtra)) {
                return false;
            }

            if (horasExtras < 0 ||
                horasExtras > 1000000 ||
                !std::isfinite(tarifaHoraExtra) ||
                tarifaHoraExtra < 0) {
                return false;
            }

            auto administrativo =
                std::make_unique<Administrativo>(
                    id,
                    nombre,
                    identificacion,
                    telefono,
                    correo,
                    salarioBase,
                    cargo
                );

            if (horasExtras > 0) {
                administrativo->registrarHorasExtras(horasExtras);
            }

            administrativo->setTarifaHoraExtra(tarifaHoraExtra);

            empleado = std::move(administrativo);
        }

        else {
            return false;
        }

        // Restaurar datos generales
        empleado->setActivo(activo);
        empleado->setDepartamento(departamento);

        temporales.push_back(std::move(empleado));
    }

    // Rechazar información adicional inesperada
    entrada >> std::ws;

    if (!entrada.eof()) {
        return false;
    }

    // Preparar los punteros para transferirlos al gestor
    std::vector<Empleado*> punteros;

    for (const auto& empleado : temporales) {
        punteros.push_back(empleado.get());
    }

    // Reemplazar los empleados anteriores
    gestor.limpiarEmpleados();

    for (Empleado* empleado : punteros) {

        if (!gestor.agregarEmpleado(empleado)) {
            gestor.limpiarEmpleados();
            return false;
        }

        // El gestor ahora es propietario del empleado
        for (auto& temporal : temporales) {

            if (temporal.get() == empleado) {
                temporal.release();
                break;
            }
        }
    }

    return true;
}
