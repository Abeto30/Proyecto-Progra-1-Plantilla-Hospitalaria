#ifndef SERIALIZADOR_EMPLEADOS_H
#define SERIALIZADOR_EMPLEADOS_H

#include <string>

class GestorEmpleados;
class GestorDepartamentos;

class SerializadorEmpleados {
public:
    static std::string serializar(const GestorEmpleados& gestor);

    static bool deserializar(
        const std::string& datos,
        GestorEmpleados& gestor,
        GestorDepartamentos& gestorDepartamentos
    );
};

#endif // SERIALIZADOR_EMPLEADOS_H
