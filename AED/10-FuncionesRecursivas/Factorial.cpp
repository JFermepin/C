/*
 * Filename: Factorial.cpp
 * Description: Realizar el factorial de un entero natural utilizando recursividad
 * Author: Grupo 6
 * Date: 2022-08-04
 */

#include <cassert>

/*
 * Fact: N -> N / Fact (x)  { x * Fact (x-1)    si x>1
 *                          { 1                 e.o.c
 */

unsigned Fact(unsigned);

int main()
{
    assert(Fact(4) == 24);
    assert(Fact(0) == 1);
    assert(Fact(10) == 3628800);
    assert(Fact(1) == 1);
}

unsigned Fact(unsigned numero)
{
    return numero > 1 ? numero * Fact(numero - 1) : 1;
}