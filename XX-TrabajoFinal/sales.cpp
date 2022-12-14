/***************
***	INCLUDES ***
****************/

#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

/******************
***	NAMESPACES ****
*******************/

using namespace std;

/******************
***	ESTRUCTURAS ***
*******************/

struct MejorVendedor{

	unsigned contador{};
	array<int, 12> lista{};

};

/*************
***	USINGS ***
**************/

using Data = array<array<array<int,12>,3>,4>;	//REGION - VENDEDOR - MES
using Ventas = vector<int>;
using MejoresVendedores = array<MejorVendedor,4>;

/*****************
***	PROTOTIPOS ***
******************/

void CargarDatosDesdeTXT (Data&, MejoresVendedores&, Ventas&);
void CargarDatosDesdeBIN (Data&, MejoresVendedores&, Ventas&);
void CrearBin (Data&, MejoresVendedores&, Ventas&);
void CrearTXT (const Data&, const MejoresVendedores&);
unsigned TotalDeVentas(const Data&, int, int);
int PromedioVentas (const Data&, int, int);
void GuardarMejoresVendedores (Data&, MejoresVendedores&);
void MostrarEstadisticas(const Data&, const MejoresVendedores&);
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
    Ventas ventasPrimerVendedor{};

    //CargarDatosDesdeTXT (data, mejoresVendedores, ventasPrimerVendedor);
    CargarDatosDesdeBIN (data, mejoresVendedores, ventasPrimerVendedor);
    MostrarEstadisticas(data, mejoresVendedores); 
    cout << ventasPrimerVendedor.size();

	return 0;
}

/******************************
***	FUNCIONES - DEFNICIONES ***
*******************************/

void CargarDatosDesdeTXT (Data& data, MejoresVendedores& mejoresVendedores, Ventas& ventasPrimerVendedor){

    for(int region{}, vendedor{}, mes{}, importe{}; cin >> region >> vendedor >> mes >> importe; ){

        data.at(region-1).at(vendedor-1).at(mes-1) += importe;

        if (region == 1 && vendedor == 1)
            ventasPrimerVendedor.push_back(importe);
    }

    GuardarMejoresVendedores(data, mejoresVendedores);
    CrearBin(data, mejoresVendedores, ventasPrimerVendedor);
}


void CargarDatosDesdeBIN (Data& data, MejoresVendedores& mejoresVendedores, Ventas& ventasPrimerVendedor){

    ifstream archivoBin;
    archivoBin.open("data.bin", ios::in | ios::binary);
    archivoBin.read(reinterpret_cast<char *>(&data), sizeof(data));
    archivoBin.read(reinterpret_cast<char *>(&mejoresVendedores), sizeof(mejoresVendedores));
    archivoBin.read(reinterpret_cast<char *>(&ventasPrimerVendedor), sizeof(ventasPrimerVendedor));
	archivoBin.close();

    CrearTXT(data, mejoresVendedores);

}

void CrearBin (Data& data, MejoresVendedores& mejoresVendedores, Ventas& ventasPrimerVendedor){

    ofstream archivoSalida;
    archivoSalida.open("out.bin", ios::out | ios::binary);
    archivoSalida.write(reinterpret_cast<char *>(&data), sizeof(data));
    archivoSalida.write(reinterpret_cast<char *>(&mejoresVendedores), sizeof(mejoresVendedores));
    archivoSalida.write(reinterpret_cast<char *>(&ventasPrimerVendedor), sizeof(ventasPrimerVendedor));
    archivoSalida.close();
}

void CrearTXT (const Data& data, const MejoresVendedores& mejoresVendedores){

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
            archivoSalida << '\t' << '\t' << "Promedio de ventas: " << PromedioVentas(data, r, v) << '\n' << '\n';
        }

        if(mejoresVendedores.at(r).contador>1){ //si hay mas de uno

            archivoSalida << "Los mejores vendedores fueron: ";

            for(int v{} ; v < mejoresVendedores.at(r).contador ; ++v){

                if(v == mejoresVendedores.at(r).contador-1){
                    archivoSalida << NombreVendedor(mejoresVendedores.at(r).lista.at(v)) + '\n';
                }
                else{
                    archivoSalida << NombreVendedor(mejoresVendedores.at(r).lista.at(v)) + ", ";
                }

            }
        
        }

        else{
            archivoSalida << "El mejor vendedor fue: " << NombreVendedor(mejoresVendedores.at(r).lista.at(0)) << '\n';
        }

        archivoSalida << '\n' << '\n';

        archivoSalida  << "-----------------------------------" << '\n' << '\n';
    }


    archivoSalida.close();

}

string NombreRegion (int region)
{
	const array<string, 4> regiones{"Norte", "Este", "Sur", "Oeste"};
	return regiones.at(region);
}

string NombreMes (int mes)
{
	const array<string, 12> meses{"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
	return meses.at(mes);
}

string NombreVendedor(int vendedor)
{
	const array<string, 3> vendedores{"Nicolas Filippi", "Jeronimo Fermepin", "Enrique Marques"};
	return vendedores.at(vendedor);
}

unsigned TotalDeVentas(const Data& data, int region, int vendedor){

    int total{};
    for(int mes{} ; mes < 12 ; ++mes)
        total += data.at(region).at(vendedor).at(mes);
    return total;

}

void GuardarMejoresVendedores (Data& data, MejoresVendedores& mejoresVendedores){

    for(int r{} ; r < 4 ; ++r){

        unsigned max{};

        for(int v{}; v < 3 ; ++v){

            if(TotalDeVentas(data,r,v)>max)
            {
                max = TotalDeVentas(data,r,v);
                mejoresVendedores.at(r).contador = 0;
                mejoresVendedores.at(r).lista.fill(0);
            }
            if (TotalDeVentas(data,r,v)>=max)
            {
              	mejoresVendedores.at(r).lista.at(mejoresVendedores.at(r).contador) = v;
			    mejoresVendedores.at(r).contador++;
            }
        }
    }
}

void MostrarEstadisticas(const Data& data, const MejoresVendedores& mejoresVendedores){

    for(int r{}; r < 4 ; ++r){

        cout << "Region: " << NombreRegion(r) << '\n' << '\n';

        for(int v{}; v < 3 ; ++v){

            cout << '\t' << "Vendedor: " << NombreVendedor(v) << '\n' << '\n';

            for(int m{}; m < 12 ; ++m){

            cout << '\t' << '\t' << "Total de " << NombreMes(m) << ": " << data.at(r).at(v).at(m) << '\n';

            }

            cout << '\t' << '\t' << "Total de ventas en el ano: " << TotalDeVentas(data, r, v) << '\n';
            cout << '\t' << '\t' << "Promedio de ventas: " << PromedioVentas(data, r, v) << '\n' << '\n';
        }

        if(mejoresVendedores.at(r).contador>1){ //si hay mas de uno

            cout << "Los mejores vendedores fueron: ";

            for(int v{} ; v < mejoresVendedores.at(r).contador ; ++v){

                if(v == mejoresVendedores.at(r).contador-1){
                    cout << NombreVendedor(mejoresVendedores.at(r).lista.at(v)) + '\n';
                }
                else{
                    cout << NombreVendedor(mejoresVendedores.at(r).lista.at(v)) + ", ";
                }

            }
        
        }

        else{
            cout << "El mejor vendedor fue: " << NombreVendedor(mejoresVendedores.at(r).lista.at(0)) << '\n';
        }

        cout << '\n' << '\n';

        cout  << "-----------------------------------" << '\n' << '\n';
    }

}

int PromedioVentas (const Data& data, int region, int vendedor){

    return TotalDeVentas(data, region, vendedor)/12;

}