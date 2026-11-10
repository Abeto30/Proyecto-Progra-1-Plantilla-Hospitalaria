#ifndef SERIALIZADOR_DEPARTAMENTOS_H
#define SERIALIZADOR_DEPARTAMENTOS_H

#include <string>

class GestorDepartamentos;

class SerializadorDepartamentos {
public:
    static std::string serializar(const GestorDepartamentos& gestor);

    static bool deserializar(const std::string& datos,
                             GestorDepartamentos& gestor);
};

#endif // SERIALIZADORDEPARTAMENTOS.h