# Ejercicio - Relevamiento de Cliente

### Fecha: 31/08/2022

### Versión del compilador G++

```
# g++ --version
g++.exe (Rev10, Built by MSYS2 project) 11.2.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### Información del trabajo práctico

##### Objetivos

Armar estructuras y funciones para poder realizar el relevamiento de clientes

##### Temas

- Estructuras.

##### Problema

Desarrollar un programa capaz de administrar clientes con minimo la siguiente estructura y sus auxiliares

```
Cliente
 |- Nombre y apellido
 |- DNI
 |- Dirección de envío
 |- Dirección de facturación
```

```
Dirección
 |- Mitre 586, Edificio, Vicente Lopez, Buenos Aires, 1636
```

_Enumeraciones_

```
Tipos de Inmueble
 |- Edificio
 |- Casa
 |- Local
 |- Departamento
 |- Baldío
 |- Otros
```

##### Productos

```
XX-RelevamientoClientes
|-- README.md
|-- RelevamientoClientes.cpp
```

### Instrucciones

El código fuente debe ser previamente compilado para luego poder ser ejecutado a través de la consola.

Primero se debe correr el comando de compilación:

```
# g++ --std=c++20 RelevamientoClientes.cpp -o RelevamientoClientes.exe
```

Luego con el ejecutable ya compilado, correrlo y verificar su funcionamiento

```
# .\RelevamientoClientes.exe
```
