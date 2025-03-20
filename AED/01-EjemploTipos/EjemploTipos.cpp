#include <cassert>
#include <string>
using namespace std::literals;

int main()
{
    //Prueba de tipo de dato int
	assert(2==1+1);
    assert(-4==-1-1-1-1);
    assert(4294967295-4294967295==0);
    assert(2*2==4);
    assert(5/5==1);
    assert(10%2!=1);
    assert(10<15);
    assert(-50<=-48);
    //Prueba de tipo de dato unsigned (numeros naturales - solo positivos)
    assert(10000u==5000u+5000u);
    assert(0u==0u);
    assert(8589934592u>0u);
    assert(8589934592u*1==8589934592u);
	//Prueba de tipo de dato bool
	assert(true);
    assert(false==false);
    assert(true!=false);
    assert(true==true);
    assert(true||false);
    assert(true&true);
    assert((true&false)||(true&true));
    //Prueba de tipo de dato double
    assert(2.0==1.0+1.0);
    assert(0.1==1.0/10.0);
    assert(1==1.0);
    assert(2.0==1+1.0);
    assert(2==1+1.0);
    assert(49.9<=50.0);
    assert(127.0*127.0<=16129.0);
    //Prueba de tipo de dato string
    assert("Jeronimo"s=="Je"s+"ro"s+"ni"s+"mo"s);
    assert("Jeronimo"s.length()==8);
    assert("J"s<"K"s);
    //Prueba de tipo de dato char
    assert(65=='A');
    assert('A'+32=='a');
    assert('z'+'z'==244);
    assert('A'<'a');
    assert('A'+32=='a');

    //Tenemos tambien, entre otros, los tipos de dato Float (reales), Short y Long (naturales)

}