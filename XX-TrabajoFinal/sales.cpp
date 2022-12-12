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

using MejoresVendedores = array<vector<int>,4>; //Mejores vendedores para cada region

/*****************
***	PROTOTIPOS ***
******************/

void CargarDatosDesdeTXT (Data&, MejoresVendedores&);
void CargarDatosDesdeBIN (Data&, MejoresVendedores&);
void CrearBin (Data, MejoresVendedores); //No necesito pasarle la referencia - no va const (?)
void CrearTXT (Data, MejoresVendedores); //No necesito pasarle la referencia - no va const(?)
unsigned TotalDeVentas(Data, int, int); //Para una region y un vendedor especifico - no necesito pasarle la referencia - no va const(?)
void GuardarMejoresVendedores (Data, MejoresVendedores&);
string NombreRegion(int);
string NombreMes(int);
string NombreVendedor(int);


/***********
***	MAIN ***
************/

int main()
{
    Data data{};
    MejoresVendedores mejoresVendedores{};

    //CargarDatosDesdeTXT (data, mejoresVendedores);
    CargarDatosDesdeBIN (data, mejoresVendedores);

	return 0;
}

/******************************
***	FUNCIONES - DEFNICIONES ***
*******************************/

void CargarDatosDesdeTXT (Data& data, MejoresVendedores& mejoresVendedores){

    for(int region{}, vendedor{}, mes{}, importe{}; cin >> region >> vendedor >> mes >> importe; )
        data.at(region-1).at(vendedor-1).at(mes-1) += importe;

    GuardarMejoresVendedores(data, mejoresVendedores);
    CrearBin(data, mejoresVendedores);
}


void CargarDatosDesdeBIN (Data& data, MejoresVendedores& mejoresVendedores){

    ifstream archivoBin;
    archivoBin.open("data.bin", ios::in | ios::binary);
    archivoBin.read(reinterpret_cast<char *>(&data), sizeof(data));
	for (int region{}, vendedor{}, mes{}, importe{}; cin >> region >> vendedor >> mes >> importe;)
	{
		data.at(region - 1).at(vendedor - 1).at(mes - 1) += importe;
	}
	archivoBin.close();

    GuardarMejoresVendedores(data, mejoresVendedores);
    CrearTXT(data, mejoresVendedores);

}

void CrearBin (Data data, MejoresVendedores mejoresVendedores){

    ofstream archivoSalida;
    archivoSalida.open("out.bin", ios::out | ios::binary);
    archivoSalida.write(reinterpret_cast<char *>(&data), sizeof(data));
    archivoSalida.close();
}

void CrearTXT (Data data, MejoresVendedores mejoresVendedores){

    ofstream archivoSalida;
    archivoSalida.open("out.txt", ios::out);

    for(int r{}; r < 4 ; ++r){

        archivoSalida << "Region: " << NombreRegion(r) << '\n' << '\n';

        for(int v{}; v < 3 ; ++v){

            archivoSalida << '\t' << "Vendedor: " << NombreVendedor(v) << '\n' << '\n';

            for(int m{}; m < 12 ; ++m){

            archivoSalida << '\t' << '\t' << "Total de " << NombreMes(m) << ": " << data.at(r).at(v).at(m) << '\n';

            }

            archivoSalida << '\t' << '\t' << "Total de ventas en el año: " << TotalDeVentas(data, r, v) << '\n';

            archivoSalida << '\n';
        }

        archivoSalida  << "-----------------------------------" << '\n' << '\n';
    }

    for(int r{}; r < 4 ; ++r){

        if(mejoresVendedores.at(r).size()>1){ //si hay mas de uno
        
        archivoSalida << "Los mejores vendedores de la region " << NombreRegion(r) << " fueron: " << '\n';
            for(int v{} ; v < mejoresVendedores.at(r).size() ; ++v)
                archivoSalida << NombreVendedor(mejoresVendedores.at(r).at(v)) << '\n';
        }

        else{

        archivoSalida << "El mejor vendedor de la region " << NombreRegion(r) << " fue: " << '\n';
            for(int v{} ; v < mejoresVendedores.at(r).size() ; ++v)
                archivoSalida << NombreVendedor(mejoresVendedores.at(r).at(v)) << '\n';
        }

        archivoSalida << '\n' << '\n';

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

unsigned TotalDeVentas(Data data, int region, int vendedor){

    int total{};
    for(int mes{} ; mes < 12 ; ++mes)
        total += data.at(region).at(vendedor).at(mes);
    return total;

}

void GuardarMejoresVendedores (Data data, MejoresVendedores& mejoresVendedores){

    for(int r{} ; r < 4 ; ++r){

        unsigned max{};

        for(int v{}; v < 3 ; ++v){

            if(TotalDeVentas(data,r,v)>max)
            {
                max = TotalDeVentas(data,r,v);
                mejoresVendedores.at(r).clear();
            }
            if (TotalDeVentas(data,r,v)>=max)
            {
               mejoresVendedores.at(r).push_back(v); 
            }
        }
    }
}