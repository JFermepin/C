/***************
***	INCLUDES ***
****************/

#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

/*************
***	USINGS ***
**************/

using namespace std;

using Data = array<array<array<int,12>,3>,4>;	//REGION - VENDEDOR - MES

/*****************
***	PROTOTIPOS ***
******************/

Data LeerDatosTXT ();
void CargarDatosBIN (Data& data);


/***********
***	MAIN ***
************/

int main()
{
    Data data{};
    CargarDatosBIN (data);
	return 0;
}

/******************************
***	FUNCIONES - DEFNICIONES ***
*******************************/

Data LeerDatosTXT (){

    Data data{};
    for(int region{}, vendedor{}, mes{}, importe{}; cin >> region >> vendedor >> mes >> importe; )
        data.at(region-1).at(vendedor-1).at(mes-1) += importe;

    return data;
}


void CargarDatosBIN (Data& data){

    data = LeerDatosTXT();

    ofstream file;
    file.open("data.bin", ios::out | ios::binary);
    file.write(reinterpret_cast<char *>(&data), sizeof(data));
	file.close();

}