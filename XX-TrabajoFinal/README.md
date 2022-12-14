# Trabajo Practico Final - Ventas

### Fecha: 16/11/2022

### Versión del compilador G++

```
# g++ --version
g++ (MinGW.org GCC Build-2) 9.2.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### Información del trabajo práctico

##### Objetivos

Diseñar un programa capaz de recibir un flujo de datos (y/o leer un archivo) para luego armar una matriz con todas las ventas realizadas entre distintas sedes, clientes y meses.

Mostrar en pantalla un reporte de las mismas, agrupadas por los distintos tipos de categorías.

Ademas debe poxer guardar en un archivo, los datos binarios de la matriz.

##### Temas

- Flujos
- Arrays
- Vectores
- Archivos

### Instrucciones

El programa es capaz de leer datos tanto desde un archivo .bin, como desde un archivo .txt, generando un archivo de salida (out.txt/out.bin) dependiendo el tipo de archivo que se haya leído.

Para ejecutar el programa correctamente, primero se especifica que tipo de archivo se va a leer (mediante las funciones CargarDatosDesdeTXT o CargarDatosDesdeBIN).

Una vez hecho esto, el código fuente debe ser previamente compilado para luego poder ser ejecutado a través de la consola.

Se debe correr el comando de compilación:

```
# g++ --std=c++2a sales.cpp -o sales.exe
```

Luego con el ejecutable ya compilado, correrlo y verificar su funcionamiento, conectando el flujo de entrada de datos de entrada con el archivo en cuestión (en este caso, data.txt):

```
# sales < data.txt
```

Este comando creará un archivo binario llamado "out.bin" que contendra toda la información necesaria para luego realizar todas las estadisticas.

Al mismo tiempo se ejecutara el resto del programa que mostrará en pantalla tablas de estadistica con la información recopilada.
