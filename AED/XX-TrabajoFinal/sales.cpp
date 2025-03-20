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

struct Mejor{

	unsigned contador{};
	array<int, 12> lista{};

};

/*************
***	USINGS ***
**************/

using Data = array<array<array<int,12>,3>,4>;	//REGION - VENDEDOR - MES
using Ventas = vector<int>;
using MejoresVendedores = array<Mejor,4>;
using MejoresMeses = array<Mejor,4>;

/*****************
***	PROTOTIPOS ***
******************/

void CargarDatosDesdeTXT (Data&, MejoresVendedores&, MejoresMeses&, Ventas&);
void CargarDatosDesdeBIN (Data&, MejoresVendedores&, MejoresMeses&, Ventas&);

void CrearBin (Data&, MejoresVendedores&, MejoresMeses&, Ventas&);
void CrearTXT (const Data&, const MejoresVendedores&, const MejoresMeses&, const Ventas&);

unsigned TotalDeVentasRegionVendedor(const Data&, int, int);
unsigned TotalDeVentasRegionMes(const Data&, int, int);
int PromedioVentas (const Data&, int, int);

void GuardarMejoresVendedores (Data&, MejoresVendedores&);
void GuardarMejoresMeses (Data&, MejoresMeses&);

void MostrarEstadisticas(const Data&, const MejoresVendedores&, const MejoresMeses&);
void MostrarMejoresVendedores (const MejoresVendedores&, int);
void MostrarMejoresMeses (const MejoresMeses&, int);

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
    MejoresMeses mejoresMeses{};
    Ventas ventasPrimerVendedor{};

    //CargarDatosDesdeTXT (data, mejoresVendedores, mejoresMeses, ventasPrimerVendedor);
    CargarDatosDesdeBIN (data, mejoresVendedores, mejoresMeses, ventasPrimerVendedor);
    MostrarEstadisticas(data, mejoresVendedores, mejoresMeses); 

    /*
    cout << "El primer vendedor hizo " << ventasPrimerVendedor.size() << " ventas: [";
    for(int i{} ; i<ventasPrimerVendedor.size() ; i++)
        cout << (i > 0 ? ", " : "") << ventasPrimerVendedor.at(i);
    cout << "]";
    */

	return 0;
}

/******************************
***	FUNCIONES - DEFNICIONES ***
*******************************/

void CargarDatosDesdeTXT (Data& data, MejoresVendedores& mejoresVendedores, MejoresMeses& mejoresMeses, Ventas& ventasPrimerVendedor){

    for(int region{}, vendedor{}, mes{}, importe{}; cin >> region >> vendedor >> mes >> importe; ){

        data.at(region-1).at(vendedor-1).at(mes-1) += importe;

        if (region == 1 && vendedor == 1)
            ventasPrimerVendedor.push_back(importe);
    }

    GuardarMejoresVendedores(data, mejoresVendedores);
    GuardarMejoresMeses(data, mejoresMeses);
    CrearBin(data, mejoresVendedores, mejoresMeses, ventasPrimerVendedor);
}


void CargarDatosDesdeBIN (Data& data, MejoresVendedores& mejoresVendedores, MejoresMeses& mejoresMeses, Ventas& ventasPrimerVendedor){

    ifstream archivoBin;
    archivoBin.open("data.bin", ios::in | ios::binary);

    unsigned numVentasPrimerVendedor{};
    archivoBin.read(reinterpret_cast<char *>(&numVentasPrimerVendedor), sizeof(unsigned));

    for (unsigned i{}; i < numVentasPrimerVendedor; i++)
    {
        int importe{};
        archivoBin.read(reinterpret_cast<char *>(&importe), sizeof(int));
        ventasPrimerVendedor.push_back(importe);
    }

    archivoBin.read(reinterpret_cast<char *>(&data), sizeof(data));
    archivoBin.read(reinterpret_cast<char *>(&mejoresVendedores), sizeof(mejoresVendedores));
    archivoBin.read(reinterpret_cast<char *>(&mejoresMeses), sizeof(mejoresMeses));

	archivoBin.close();

    CrearTXT(data, mejoresVendedores, mejoresMeses, ventasPrimerVendedor);

}

void CrearBin (Data& data, MejoresVendedores& mejoresVendedores, MejoresMeses& mejoresMeses, Ventas& ventasPrimerVendedor){

    ofstream archivoSalida;
    archivoSalida.open("out.bin", ios::out | ios::binary);

    unsigned numVentasPrimerVendedor = ventasPrimerVendedor.size();
    archivoSalida.write(reinterpret_cast<char *>(&numVentasPrimerVendedor), sizeof(unsigned));

	for (auto importe : ventasPrimerVendedor)
		archivoSalida.write(reinterpret_cast<char *>(&importe), sizeof(int));

    archivoSalida.write(reinterpret_cast<char *>(&data), sizeof(data));
    archivoSalida.write(reinterpret_cast<char *>(&mejoresVendedores), sizeof(mejoresVendedores));
    archivoSalida.write(reinterpret_cast<char *>(&mejoresMeses), sizeof(mejoresMeses));

    archivoSalida.close();
}

void CrearTXT (const Data& data, const MejoresVendedores& mejoresVendedores, const MejoresMeses& mejoresMeses, const Ventas& ventasPrimerVendedor){

    ofstream archivoSalida;
    archivoSalida.open("out.txt", ios::out);

    for(int r{}; r < 4 ; ++r){

        archivoSalida << "Region: " << NombreRegion(r) << "\n\n";

        for(int v{}; v < 3 ; ++v){

            archivoSalida << "\tVendedor: " << NombreVendedor(v) << "\n\n";

            for(int m{}; m < 12 ; ++m){

            archivoSalida << "\t\tTotal de " << NombreMes(m) << ": " << data.at(r).at(v).at(m) << '\n';

            }

            archivoSalida << "\n\t\tTotal de ventas en el año: " << TotalDeVentasRegionVendedor(data, r, v) << '\n';
            archivoSalida << "\t\tPromedio de ventas: " << PromedioVentas(data, r, v) << "\n\n";
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

        if(mejoresMeses.at(r).contador>1){ //si hay mas de uno

            archivoSalida << "Los mejores meses fueron: ";

            for(int m{} ; m < mejoresMeses.at(r).contador ; ++m){

                if(m == mejoresMeses.at(r).contador-1){
                    archivoSalida << NombreMes(mejoresMeses.at(r).lista.at(m)) + '\n';
                }
                else{
                    archivoSalida << NombreMes(mejoresMeses.at(r).lista.at(m)) + ", ";
                }
            }
        }

        else{
            archivoSalida << "El mejor mes fue: " << NombreMes(mejoresMeses.at(r).lista.at(0)) << '\n';
        }

            archivoSalida << "\n\n-----------------------------------\n\n";
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

unsigned TotalDeVentasRegionVendedor(const Data& data, int region, int vendedor){

    int total{};
    for(int m{} ; m < 12 ; ++m)
        total += data.at(region).at(vendedor).at(m);
    return total;

}

unsigned TotalDeVentasRegionMes(const Data& data, int region, int mes){

    unsigned total{};
    for(int v{} ; v < 3 ; ++v)
        total += data.at(region).at(v).at(mes);
    return total;
}

void GuardarMejoresVendedores(Data& data, MejoresVendedores& mejoresVendedores){

    for(int r{} ; r < 4 ; ++r){

        unsigned max{};

        for(int v{}; v < 3 ; ++v){

            if(TotalDeVentasRegionVendedor(data,r,v)>max)
            {
                max = TotalDeVentasRegionVendedor(data,r,v);
                mejoresVendedores.at(r).contador = 0;
                mejoresVendedores.at(r).lista.fill(0);
            }
            if (TotalDeVentasRegionVendedor(data,r,v)>=max)
            {
              	mejoresVendedores.at(r).lista.at(mejoresVendedores.at(r).contador) = v;
			    mejoresVendedores.at(r).contador++;
            }
        }
    }
}

void GuardarMejoresMeses (Data& data, MejoresVendedores& mejoresMeses){

    for(int r{} ; r < 4 ; ++r){

        unsigned max{};

        for(int m{}; m < 12 ; ++m){

            if(TotalDeVentasRegionMes(data,r,m)>max)
            {
                max = TotalDeVentasRegionMes(data,r,m);
                mejoresMeses.at(r).contador = 0;
                mejoresMeses.at(r).lista.fill(0);
            }
            if (TotalDeVentasRegionMes(data,r,m)>=max)
            {
              	mejoresMeses.at(r).lista.at(mejoresMeses.at(r).contador) = m;
			    mejoresMeses.at(r).contador++;
            }
        }
    }
}

void MostrarEstadisticas(const Data& data, const MejoresVendedores& mejoresVendedores, const MejoresMeses& mejoresMeses){

    for(int r{}; r < 4 ; ++r){

        cout << "Region: " << NombreRegion(r) << "\n\n";

        for(int v{}; v < 3 ; ++v){

            cout << "\tVendedor: " << NombreVendedor(v) << "\n\n";

            for(int m{}; m < 12 ; ++m){

            cout << "\t\tTotal de " << NombreMes(m) << ": " << data.at(r).at(v).at(m) << '\n';

            }

            cout << "\n\t\tTotal de ventas en el ano: " << TotalDeVentasRegionVendedor(data, r, v) << '\n';
            cout << "\t\tPromedio de ventas: " << PromedioVentas(data, r, v) << "\n\n";
        }

        MostrarMejoresVendedores(mejoresVendedores, r);
        MostrarMejoresMeses(mejoresMeses, r);

        cout << "\n\n-----------------------------------\n\n";
    }

}

int PromedioVentas (const Data& data, int region, int vendedor){

    return TotalDeVentasRegionVendedor(data, region, vendedor)/12;

}

void MostrarMejoresVendedores (const MejoresVendedores& mejoresVendedores, int region){

    if(mejoresVendedores.at(region).contador>1){ //si hay mas de uno

        cout << "Los mejores vendedores fueron: ";

        for(int v{} ; v < mejoresVendedores.at(region).contador ; ++v){

            if(v == mejoresVendedores.at(region).contador-1){
                cout << NombreVendedor(mejoresVendedores.at(region).lista.at(v)) + '\n';
            }
            else{
                cout << NombreVendedor(mejoresVendedores.at(region).lista.at(v)) + ", ";
            }

        }

    }

    else{
        cout << "El mejor vendedor fue: " << NombreVendedor(mejoresVendedores.at(region).lista.at(0)) << '\n';
    }

}

void MostrarMejoresMeses (const MejoresVendedores& mejoresMeses, int region){

    if(mejoresMeses.at(region).contador>1){ //si hay mas de uno

        cout << "Los mejores meses fueron: ";

        for(int m{} ; m < mejoresMeses.at(region).contador ; ++m){

            if(m == mejoresMeses.at(region).contador-1){
                cout << NombreMes(mejoresMeses.at(region).lista.at(m)) + '\n';
            }
            else{
                cout << NombreMes(mejoresMeses.at(region).lista.at(m)) + ", ";
            }

        }

    }

    else{
        cout << "El mejor mes fue: " << NombreMes(mejoresMeses.at(region).lista.at(0)) << '\n';
    }

}