Sistema de Planilla Hospitalaria

Universidad Nacional
Sección Regional Central Occidente**

Curso: EIF201 – Programación I  
**Profesor:** Adrián Ramírez Fernández

 Integrantes

- Maikel Novoa Murillo 208060985
- John Herrera Villalobos 209030525
- Erick Chaves Víquez 208970949


## Descripción del proyecto

El Sistema de Planilla Hospitalaria es una aplicación desarrollada en C++ que permite administrar empleados, departamentos, puestos y procesos de planilla de una institución hospitalaria.

El sistema facilita el registro y consulta de información, la generación de comprobantes de pago y el almacenamiento de los datos para conservarlos entre ejecuciones.

## Funcionalidades principales

- **Gestión de empleados:** registrar, mostrar, buscar, eliminar y cambiar el estado de los empleados.
- **Gestión de departamentos:** registrar, consultar y eliminar departamentos.
- **Gestión de puestos:** registrar, mostrar, buscar y eliminar puestos asociados a departamentos.
- **Gestión de planilla:** generar la planilla de los empleados activos.
- **Comprobantes de pago:** consultar los comprobantes generados.
- **Persistencia de datos:** guardar y cargar la información desde archivos de texto.

## Tecnologías utilizadas

- Lenguaje de programación: C++.
- Estándar: C++17.
- Compilador: G++.
- Programación orientada a objetos.
- Estructuras de datos mediante listas enlazadas.
- Archivos de texto para el almacenamiento de información.

## Estructura del proyecto

Proyecto-Progra-1-Plantilla-Hospitalaria/
│
├── Clases/
│   ├── Administrativo
│   ├── ComprobantePago
│   ├── Departamento
│   ├── Empleado
│   ├── Enfermero
│   ├── Medico
│   └── Puesto
│
├── Datos/
│   └── Archivos/
│       ├── departamentos.txt
│       ├── empleados.txt
│       └── planilla.txt
│
├── Gestores/
│   ├── GestorComprobantes
│   ├── GestorDepartamentos
│   └── GestorEmpleados
│
├── Listas/
│   ├── Lista
│   └── Nodo
│
├── Menus/
│   ├── GestionDepartamento
│   ├── GestionPlanilla
│   ├── GestionPuesto
│   └── MenuEmpleado
│
├── Persistencia/
│   ├── Almacenamiento
│   ├── SerializadorDepartamentos
│   ├── SerializadorEmpleados
│   └── SerializadorPlanilla
│
├── Pruebas/
│
├── Validacion General/
│
└── main.cpp

## Requisitos para ejecutar el proyecto

- Tener instalado un compilador compatible con C++17, como G++.
- Contar con Windows PowerShell o una terminal compatible.

## Compilación y ejecución

Desde la carpeta principal del proyecto, ejecutar los siguientes comandos en PowerShell:

powershell
$archivos = Get-ChildItem -Recurse -Filter *.cpp |
    Where-Object { $_.FullName -notmatch '\\Pruebas\\' } |
    ForEach-Object { $_.FullName }

g++ -std=c++17 $archivos -o Planilla.exe

.\Planilla.exe


## Almacenamiento de información

El sistema utiliza archivos de texto ubicados en `Datos/Archivos/` para conservar la información:

- `departamentos.txt`: información de los departamentos y sus puestos.
- `empleados.txt`: información de los empleados registrados.
- `planilla.txt`: comprobantes de pago generados.

Los datos pueden guardarse desde el menú principal y se cargan al iniciar el programa.

Universidad Nacional – Sección Regional Central Occidente**  
EIF201 – Programación I
