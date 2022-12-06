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

void CargarDatosDesdeTXT (Data&);
void CargarDatosDesdeBIN (Data&);
void CrearBin (Data); //No necesito pasarle la referencia - no va const (?)
void CrearTXT (Data); //No necesito pasarle la referencia - no va const(?)
string NombreRegion(int);
string NombreMes(int);
string NombreVendedor(int);


/***********
***	MAIN ***
************/

int main()
{
    Data data{};
    //CargarDatosDesdeTXT (data);
    CargarDatosDesdeBIN (data);
	return 0;
}

/******************************
***	FUNCIONES - DEFNICIONES ***
*******************************/

void CargarDatosDesdeTXT (Data& data){

    for(int region{}, vendedor{}, mes{}, importe{}; cin >> region >> vendedor >> mes >> importe; )
        data.at(region-1).at(vendedor-1).at(mes-1) += importe;

    CrearBin(data);
}


void CargarDatosDesdeBIN (Data& data){

    ifstream archivoBin;
    archivoBin.open("data.bin", ios::in | ios::binary);
    archivoBin.read(reinterpret_cast<char *>(&data), sizeof(data));
	for (int region{}, vendedor{}, mes{}, importe{}; cin >> region >> vendedor >> mes >> importe;)
	{
		data.at(region - 1).at(vendedor - 1).at(mes - 1) += importe;
	}
	archivoBin.close();

    CrearTXT(data);

}

void CrearBin (Data data){

    ofstream archivoSalida;
    archivoSalida.open("out.bin", ios::out | ios::binary);
    archivoSalida.write(reinterpret_cast<char *>(&data), sizeof(data));
    archivoSalida.close();
}

void CrearTXT (Data data){

    ofstream archivoSalida;
    archivoSalida.open("out.txt", ios::out);

    for(int r{}; r < 4; ++r){

        archivoSalida << "Region: " << NombreRegion(r) << '\n' << '\n';

        for(int v{}; v < 3 ; ++v){

            archivoSalida << '\t' << "Vendedor: " << NombreVendedor(v) << '\n' << '\n';

            for(int m{}; m < 12 ; ++m){

            archivoSalida << '\t' << '\t' << "Total de " << NombreMes(m) << ": " << data[r][v][m] << '\n';

            }

            archivoSalida << '\n';
        }

        archivoSalida  << "-----------------------------------" << '\n' << '\n';
    }

    archivoSalida.close();

}

string NombreRegion (int region)
{
	const array<string, 4> regiones{"Norte", "Este", "Sur", "Oeste"}; //Const por que es constante (hace falta static?) 
	return regiones.at(region);
}

string NombreMes (int mes)
{
	const array<string, 12> meses{"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"}; //Const por que es constante (hace falta static?) 
	return meses.at(mes);
}

string NombreVendedor(int vendedor)
{
	const array<string, 3> vendedores{"Nicolas Filippi", "Jeronimo Fermepin", "Enrique Marques"}; //Const por que es constante (hace falta static?) 
	return vendedores.at(vendedor);
}