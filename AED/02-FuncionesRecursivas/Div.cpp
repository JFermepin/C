/*
 * Filename: Div.cpp
 * Description: Realizar una división de enteros naturales utilizando recursividad
 * Author: Grupo 6
 * Date: 2022-08-04
 */

#include <cassert>

/*
 * Div: NxN-{0} -> N / Div(dividendo, divisor) =    {
 *                                                      0                                           dividendo < divisor
 *                                                      1 + Div(dividendo - divisor, divisor)       e.o.c
 *                                                  }
 *
 */

unsigned Div(unsigned, unsigned);

int main()
{
    assert(Div(6, 8) == 0);
    assert(Div(11, 3) == 3);
    assert(Div(16, 4) == 4);
    assert(Div(10, 10) == 1);
    assert(Div(1000, 3) == 333);
    // assert(Div(1, 0) == infito); // no funciona la division por 0
}

unsigned Div(unsigned dividendo, unsigned divisor)
{
    return (dividendo < divisor) ? 0 : 1 + Div(dividendo - divisor, divisor);
}