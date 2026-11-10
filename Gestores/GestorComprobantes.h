
#ifndef GESTOR_COMPROBANTES_H
#define GESTOR_COMPROBANTES_H

#include "../Clases/ComprobantePago.h"
#include "../Listas/Lista.h"

class GestorComprobantes {
private:
    Lista<ComprobantePago*> comprobantes;

public:
    GestorComprobantes();
    ~GestorComprobantes();

    GestorComprobantes(const GestorComprobantes&) = delete;
    GestorComprobantes& operator=(const GestorComprobantes&) = delete;

    bool agregarComprobante(ComprobantePago* comprobante);
    ComprobantePago* buscarComprobantePorId(int id) const;

    int getCantidadComprobantes() const;

    ComprobantePago* obtenerComprobanteEnPosicion(int posicion) const;

    void limpiarComprobantes();
};

#endif
//ComprobantePago .h