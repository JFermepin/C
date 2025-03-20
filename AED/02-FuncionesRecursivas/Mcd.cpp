/*
 * Filename: Mcd.cpp
 * Description: Obtener el maximo comun divisor entre dos enteros naturales utilizando recursividad
 * Author: Grupo 6
 * Date: 2022-08-04
 */

/*
 * NOTAS:
 * Optamos por utilizar el algoritmo de Euclides, por lo tanto, la funcion
 * Mcd es una referencia de la funcion de Euclides
 */

#include <cassert>

/*
 * Euclides: NxN -> N / Euclides(a, b) =    {
 *                                              a                       si b == 0
 *                                              Euclides(b, a % b)      e.o.c.
 *                                          }
 */
unsigned int Euclides(unsigned int a, unsigned int);

/*
 * Mcd: NxN -> N / Mcd(a, b) = Euclides(a, b)
 */
unsigned int Mcd(unsigned int, unsigned int);

unsigned int Euclides(unsigned int a, unsigned int b)
{
    return b == 0 ? a : Euclides(b, a % b);
}

unsigned int Mcd(unsigned int a, unsigned int b)
{
    return Euclides(a, b);
}

int main()
{
    assert(Mcd(0, 1) == 1);
    assert(Mcd(1, 0) == 1);

    assert(Mcd(50, 100) == 50);
    assert(Mcd(100, 50) == 50);

    assert(Mcd(45, 46) == 1);
    assert(Mcd(46, 45) == 1);

    assert(Mcd(3, 5) == 1);
    assert(Mcd(5, 3) == 1);

    assert(Mcd(10, 55) == 5);
    assert(Mcd(55, 10) == 5);
}