#include <cassert>
#include <string>
using namespace std::literals;

int main()
{
    //prueba de tipo de dato int
	assert(2==1+1);
    assert(-4==-1-1-1-1);
    //prueba de tipo de dato unsigned (numeros naturales - solo positivos)
    assert(10000==5000+5000);
    assert(0==0);
	//prueba de tipo de dato bool
	assert(true);
    assert(false==false);
    assert(true!=false);
    assert(true==true);
    //prueba de tipo de dato double
    assert(2.0==1.0+1.0);
    assert(0.1==1.0/10.0);
    assert(1==1.0);
    assert(2.0==1+1.0);
    assert(2==1+1.0);
    //prueba de tipo de dato string
    assert("Jeronimo"s=="Je"s+"ro"s+"ni"s+"mo"s);
    assert("Jeronimo"s.length()==8);
    //prueba de tipo de dato char
    assert(65=='A');
    assert('A'+32=='a');
    assert('z'+'z'==244);

    //Tenemos tambien, entre otros, los tipos de dato Float (reales), Short y Long (naturales)

}