#ifndef SERIALIZADOR_PLANILLA_H
#define SERIALIZADOR_PLANILLA_H

#include <string>

class GestorComprobantes;

class SerializadorPlanilla {
public:
    static std::string serializar(
        const GestorComprobantes& gestor
    );

    static bool deserializar(
        const std::string& datos,
        GestorComprobantes& gestor
    );
};

#endif // SERIALIZADOR_PLANILLA_H
