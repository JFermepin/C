# Trabajo Practico Final - Ventas

### Fecha: 16/11/2022

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

Diseñar un programa capaz de recibir un flujo de datos (y/o leer un archivo) para luego armar una matriz con todas ls ventas realizadas entre distintas sedes, clientes y meses.

Mostrar en pantalla un reporte de las mismas arupadas por los distintos tipos de categorías.

Ademas debe poxer gusrdar en un archivo, la dstos binarios de la matriz.

##### Temas

- Flujos
- Arrays
- Vectores
- Archivos

### Instrucciones

El código fuente debe ser previamente compilado para luego poder ser ejecutado a través de la consola.

Primero se debe correr el comando de compilación:

```
# g++ --std=c++20 sales.cpp -o sales.exe
```

Luego con el ejecutable ya compilado, correrlo y verificar su funcionamiento.

Como principal ejecucion se debe crear el archivo binario con la información de las ventas, para ello se debera utilizar el flujo de datos de entrada conectado a un archivo de texto.

```
# .\sales.exe --loadDataFile < data.txt
```

Este comando creará un archivo binario llamado "data.bin" que contendra toda la información necesaria para luego realizar todas las estadisticas.

Al mismo tiempo se ejecutara el resto del programa que mostrata en pantalla tablas de estadistica con la información recopilada.

Si lo que se quiere es unicamente mostrar las estadistincas, sin necesidad de recrear el archivo binario, solo basta con correr el ejecutable sin parametros ni flujos conectados.

```
# .\sales.exe
```
