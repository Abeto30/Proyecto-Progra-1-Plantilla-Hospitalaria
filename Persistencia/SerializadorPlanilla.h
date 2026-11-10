
#ifndef SERIALIZADOR_PLANILLA_H
#define SERIALIZADOR_PLANILLA_H

#include <string>

class GestorComprobantes;
class GestorEmpleados;
class GestorDepartamentos;

class SerializadorPlanilla {
public:
    static std::string serializar(
        const GestorComprobantes& gestor
    );

    static bool deserializar(
        const std::string& datos,
        GestorComprobantes& gestor,
        GestorEmpleados& gestorEmpleados,
        GestorDepartamentos& gestorDepartamentos
    );
};

#endif // SERIALIZADOR_PLANILLA_H
