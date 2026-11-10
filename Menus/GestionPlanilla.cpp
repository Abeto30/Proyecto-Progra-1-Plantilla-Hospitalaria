
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

#include "GestionPlanilla.h"
#include "../Clases/Empleado.h"
#include "../Clases/Departamento.h"
#include "../Clases/ComprobantePago.h"
#include "../Validacion General/Entrada.h"

using namespace std;

const double PORCENTAJE_DEDUCCION = 0.08;

// Funciones del menu
void generarPlanilla(
    GestorEmpleados& gestorEmpleados,
    GestorComprobantes& gestorComprobantes
);

void mostrarResumenPlanilla(
    const GestorComprobantes& gestorComprobantes
);

// Menu de planilla
void menuPlanilla(
    GestorEmpleados& gestorEmpleados,
    GestorComprobantes& gestorComprobantes
) {
    int opcion;

    do {
        cout << "\n===================================" << endl;
        cout << "        GESTION DE PLANILLA" << endl;
        cout << "===================================" << endl;
        cout << "1. Generar planilla" << endl;
        cout << "2. Consultar resumen de planilla" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "===================================" << endl;

        opcion = leerEntero("Seleccione una opcion: ", 0, 2);

        switch (opcion) {
            case 1:
                generarPlanilla(gestorEmpleados, gestorComprobantes);
                break;

            case 2:
                mostrarResumenPlanilla(gestorComprobantes);
                break;

            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
        }

    } while (opcion != 0);
}

// Generar planilla
void generarPlanilla(
    GestorEmpleados& gestorEmpleados,
    GestorComprobantes& gestorComprobantes
) {
    if (gestorEmpleados.getCantidadEmpleados() == 0) {
        cout << "\nNo hay empleados registrados." << endl;
        return;
    }

    string fecha = leerLinea("\nIngrese la fecha de la planilla: ");

    int empleadosActivos = 0;
    int comprobantesGenerados = 0;

    double totalBruto = 0;
    double totalDeducciones = 0;
    double totalNeto = 0;

    int siguienteId = 1;

    while (gestorComprobantes.buscarComprobantePorId(siguienteId) != nullptr) {
        siguienteId++;
    }

    cout << "\n========== GENERANDO PLANILLA ==========" << endl;

    for (int i = 0; i < gestorEmpleados.getCantidadEmpleados(); i++) {
        Empleado* empleado =
            gestorEmpleados.obtenerEmpleadoEnPosicion(i);

        if (empleado == nullptr || !empleado->estaActivo()) {
            continue;
        }

        Departamento* departamento = empleado->getDepartamento();

        if (departamento == nullptr) {
            cout << "Empleado " << empleado->getId()
                 << " no tiene departamento asignado." << endl;
            continue;
        }

        double salarioBruto = empleado->calcularSalarioBruto();
        double deducciones = salarioBruto * PORCENTAJE_DEDUCCION;

        ComprobantePago* comprobante = nullptr;

        try {
            comprobante = new ComprobantePago(
                siguienteId,
                empleado->getId(),
                empleado->getNombre(),
                empleado->getIdentificacion(),
                empleado->getTipoEmpleado(),
                departamento->getId(),
                departamento->getNombre(),
                salarioBruto,
                deducciones,
                fecha
            );

            if (gestorComprobantes.agregarComprobante(comprobante)) {
                empleadosActivos++;
                comprobantesGenerados++;

                totalBruto += salarioBruto;
                totalDeducciones += deducciones;
                totalNeto += comprobante->getSalarioNeto();

                cout << "\nComprobante generado: "
                     << comprobante->getId() << endl;

                cout << "Empleado: "
                     << comprobante->getNombreEmpleado() << endl;

                cout << "Salario bruto: "
                     << fixed << setprecision(2)
                     << comprobante->getSalarioBruto() << endl;

                cout << "Deducciones (8%): "
                     << comprobante->getDeducciones() << endl;

                cout << "Salario neto: "
                     << comprobante->getSalarioNeto() << endl;

                siguienteId++;
            } else {
                delete comprobante;
            }

        } catch (const exception& e) {
            delete comprobante;

            cout << "Error al generar comprobante del empleado "
                 << empleado->getId() << ": "
                 << e.what() << endl;
        }
    }

    cout << "\n========== RESUMEN DE PLANILLA ==========" << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Empleados activos procesados: " << empleadosActivos << endl;
    cout << "Comprobantes generados: " << comprobantesGenerados << endl;

    cout << fixed << setprecision(2);

    cout << "Total salario bruto: " << totalBruto << endl;
    cout << "Total deducciones: " << totalDeducciones << endl;
    cout << "Total salario neto: " << totalNeto << endl;

    cout << "=========================================" << endl;

    if (comprobantesGenerados == 0) {
        cout << "No se genero ningun comprobante." << endl;
    }
}

// Mostrar resumen de todos los comprobantes
void mostrarResumenPlanilla(
    const GestorComprobantes& gestorComprobantes
) {
    int cantidad = gestorComprobantes.getCantidadComprobantes();

    if (cantidad == 0) {
        cout << "\nNo hay comprobantes registrados." << endl;
        return;
    }

    double totalBruto = 0;
    double totalDeducciones = 0;
    double totalNeto = 0;

    cout << "\n========== RESUMEN GENERAL ==========" << endl;

    for (int i = 0; i < cantidad; i++) {
        ComprobantePago* comprobante =
            gestorComprobantes.obtenerComprobanteEnPosicion(i);

        if (comprobante != nullptr) {
            totalBruto += comprobante->getSalarioBruto();
            totalDeducciones += comprobante->getDeducciones();
            totalNeto += comprobante->getSalarioNeto();
        }
    }

    cout << fixed << setprecision(2);
    cout << "Cantidad de comprobantes: " << cantidad << endl;
    cout << "Total bruto: " << totalBruto << endl;
    cout << "Total deducciones: " << totalDeducciones << endl;
    cout << "Total neto: " << totalNeto << endl;

    cout << "=====================================" << endl;
}

// Menu de consulta de comprobantes
void menuConsultaComprobantes(
    const GestorComprobantes& gestorComprobantes
) {
    int opcion;

    do {
        cout << "\n===================================" << endl;
        cout << "    CONSULTA DE COMPROBANTES" << endl;
        cout << "===================================" << endl;
        cout << "1. Mostrar todos los comprobantes" << endl;
        cout << "2. Buscar comprobante por ID" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "===================================" << endl;

        opcion = leerEntero("Seleccione una opcion: ", 0, 2);

        switch (opcion) {
            case 1: {
                int cantidad =
                    gestorComprobantes.getCantidadComprobantes();

                if (cantidad == 0) {
                    cout << "\nNo hay comprobantes registrados."
                         << endl;
                    break;
                }

                cout << "\n========== COMPROBANTES =========="
                     << endl;

                for (int i = 0; i < cantidad; i++) {
                    ComprobantePago* comprobante =
                        gestorComprobantes.obtenerComprobanteEnPosicion(i);

                    if (comprobante == nullptr) {
                        continue;
                    }

                    cout << "\nID comprobante: "
                         << comprobante->getId() << endl;
                    cout << "Fecha: "
                         << comprobante->getFecha() << endl;
                    cout << "Empleado: "
                         << comprobante->getNombreEmpleado() << endl;
                    cout << "Identificacion: "
                         << comprobante->getIdentificacion() << endl;
                    cout << "Tipo de empleado: "
                         << comprobante->getTipoEmpleado() << endl;
                    cout << "Departamento: "
                         << comprobante->getNombreDepartamento() << endl;

                    cout << fixed << setprecision(2);
                    cout << "Salario bruto: "
                         << comprobante->getSalarioBruto() << endl;
                    cout << "Deducciones: "
                         << comprobante->getDeducciones() << endl;
                    cout << "Salario neto: "
                         << comprobante->getSalarioNeto() << endl;

                    cout << "-----------------------------------"
                         << endl;
                }

                break;
            }

            case 2: {
                if (gestorComprobantes.getCantidadComprobantes() == 0) {
                    cout << "\nNo hay comprobantes registrados."
                         << endl;
                    break;
                }

                int id = leerEntero(
                    "\nIngrese el ID del comprobante: ",
                    1,
                    2147483647
                );

                ComprobantePago* comprobante =
                    gestorComprobantes.buscarComprobantePorId(id);

                if (comprobante == nullptr) {
                    cout << "\nNo se encontro un comprobante con ese ID."
                         << endl;
                    break;
                }

                cout << "\n========== COMPROBANTE =========="
                     << endl;
                cout << "ID: " << comprobante->getId() << endl;
                cout << "Fecha: " << comprobante->getFecha() << endl;
                cout << "Empleado: "
                     << comprobante->getNombreEmpleado() << endl;
                cout << "Identificacion: "
                     << comprobante->getIdentificacion() << endl;
                cout << "Tipo de empleado: "
                     << comprobante->getTipoEmpleado() << endl;
                cout << "Departamento: "
                     << comprobante->getNombreDepartamento() << endl;

                cout << fixed << setprecision(2);
                cout << "Salario bruto: "
                     << comprobante->getSalarioBruto() << endl;
                cout << "Deducciones: "
                     << comprobante->getDeducciones() << endl;
                cout << "Salario neto: "
                     << comprobante->getSalarioNeto() << endl;

                cout << "================================="
                     << endl;

                break;
            }

            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
        }

    } while (opcion != 0);
}

// GestionPlanilla.cpp