/*
 * Filename: Fibonacci.cpp
 * Description: Realizar el factorial de un entero natural utilizando recursividad
 * Author: Grupo 6
 * Date: 2022-08-04
 */

/*
 * NOTAS:
 * Debido a que utilizamos un tipo de variable entera no signada, el valor maximo que podemos obtener es el
 * de 93 en la serie de Fibonacci (12200160415121876738).
 * A partir de este valor, todos los resultados generan overflow y el numero retornado es invalido.
 */

#include <iostream>
#include <cassert>

/*
 * Fib: N -> N / Fib(n) = FibAuxiliar(n, 0, 1);
 */

// Fib: N -> N / Fib(x) = Fib(x-1) + Fib(x-2)     e.o.c
//                                 x              si x=1 v x=0
long long unsigned int Fib(long long unsigned int);

int main()
{
    assert(Fib(0) == 0);
    assert(Fib(1) == 1);
    assert(Fib(6) == 8);
    assert(Fib(15) == 610);
    assert(Fib(60) == 1548008755920);
    assert(Fib(93) == 12200160415121876738);
    assert(Fib(93) >= 12200160415121876737 && Fib(93) <= 12200160415121876739); // El numero es exacto hasta el valor 93
    assert(Fib(94) < 12200160415121876738);                                     // Deberia ser mayor
}

/*
 * FibAuxiliar: N³ -> N / FibAuxiliar(posicion, a0, a1) =   {
 *                                                              FibAuxiliar(posicion - 1, a1, a0 + a1)      posicion >= 2
 *                                                              a1                                  posicion >= 1
 *                                                              a0                                  posicion < 1
 *                                                          }
 */
long long unsigned int FibAuxiliar(long long unsigned int, long long unsigned int, long long unsigned int);

long long unsigned int Fib(long long unsigned int n)
{
    return FibAuxiliar(n, 0, 1);
}

long long unsigned int FibAuxiliar(long long unsigned int posicion, long long unsigned int a0 = 0, long long unsigned int a1 = 1)
{
    return posicion >= 2 ? FibAuxiliar(posicion - 1, a1, a0 + a1) : (posicion >= 1 ? a1 : a0);
}