
#ifndef GESTION_DEPARTAMENTO_H
#define GESTION_DEPARTAMENTO_H

#include "../Gestores/GestorDepartamentos.h"
#include "../Gestores/GestorEmpleados.h"
#include "../Gestores/GestorComprobantes.h"

void menuDepartamento(
    GestorDepartamentos& gestor,
    GestorEmpleados& gestorEmpleados,
    GestorComprobantes& gestorComprobantes
);

#endif
