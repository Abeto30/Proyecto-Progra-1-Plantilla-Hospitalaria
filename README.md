# Sistema de Planilla Hospitalaria

**Universidad Nacional**  
**Sección Regional Central Occidente**

**Curso:** EIF201 – Programación I  
**Profesor:** Adrián Ramírez Fernández

## Integrantes

- Maikel Novoa Murillo – 208060985
- John Herrera Villalobos – 209030525
- Erick Chaves Víquez – 208970949

---

## Descripción del proyecto

El Sistema de Planilla Hospitalaria es una aplicación desarrollada en C++ que permite administrar empleados, departamentos, puestos y procesos de planilla de una institución hospitalaria.

El sistema facilita el registro, consulta y administración de información, la generación de comprobantes de pago y el almacenamiento de los datos para conservarlos entre ejecuciones.

## Funcionalidades principales

- **Gestión de empleados:** registrar, mostrar, buscar, eliminar y cambiar el estado de los empleados.
- **Gestión de departamentos:** registrar, consultar, buscar y eliminar departamentos.
- **Gestión de puestos:** registrar, mostrar, buscar y eliminar puestos asociados a departamentos.
- **Gestión de planilla:** generar la planilla de los empleados activos que cumplen las condiciones correspondientes.
- **Comprobantes de pago:** consultar los comprobantes generados.
- **Persistencia de datos:** guardar y cargar información mediante archivos de texto.
- **Validación de entradas:** controlar los datos ingresados por el usuario.

## Tecnologías utilizadas

- Lenguaje de programación: C++.
- Estándar: C++17.
- Compilador: G++.
- Programación orientada a objetos.
- Listas enlazadas para el manejo de colecciones dinámicas.
- Archivos de texto para el almacenamiento de información.

## Estructura del proyecto

```text
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
│   ├── Entrada.h
│   └── Entrada.cpp
│
├── main.cpp
└── README.md
```

## Requisitos para ejecutar el proyecto

- Tener instalado un compilador compatible con C++17, como G++.
- Contar con Windows PowerShell o una terminal compatible.
- Tener acceso a la carpeta del proyecto.

## Compilación y ejecución

Desde la carpeta principal del proyecto, ejecutar los siguientes comandos en PowerShell:

```powershell
$archivos = Get-ChildItem -Recurse -Filter *.cpp |
    Where-Object { $_.FullName -notmatch '\\Pruebas\\' } |
    ForEach-Object { $_.FullName }

g++ -std=c++17 $archivos -o Planilla.exe

.\Planilla.exe
```

## Guía básica de uso

1. Ejecutar el programa mediante el comando de compilación y ejecución.
2. En el menú principal, seleccionar el módulo que se desea utilizar.
3. Ingresar la opción correspondiente a la operación que se desea realizar.
4. Seguir las indicaciones del sistema para registrar, consultar o modificar información.
5. Utilizar la opción de guardar información cuando corresponda.
6. Seleccionar la opción de salida para finalizar el programa.

## Almacenamiento de información

El sistema utiliza archivos de texto ubicados en `Datos/Archivos/` para conservar la información:

- `departamentos.txt`: información de los departamentos y sus puestos.
- `empleados.txt`: información de los empleados registrados.
- `planilla.txt`: comprobantes de pago generados.

Los datos se cargan al iniciar el programa y pueden guardarse desde el menú principal. De esta manera, la información se conserva entre ejecuciones.

---

**Universidad Nacional – Sección Regional Central Occidente**  
**EIF201 – Programación I**