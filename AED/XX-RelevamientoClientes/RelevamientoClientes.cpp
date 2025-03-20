/*
 * Filename: RelevamientoClientes.cpp
 * Description: Armar estructuras y funciones para poder realizar el relevamiento de clientes
 * Author: Grupo 6
 * Date: 2022-08-29
 */

// ################
// ### INCLUDES ###
// ################

#include <string>
#include <iostream>
#include <ctime>
#include <cassert>

// #####################
// ### ENUMERACIONES ###
// #####################

enum struct TiposDocumentos
{
    DNI,
    LC,
    LE,
    Pasaporte
};

enum struct TiposInmbuebles
{
    Edificio,
    Casa,
    PH,
    Local,
    Departamento,
    Baldio,
    Otros
};

// ###################
// ### ESTRUCTURAS ###
// ###################

struct Fecha
{
    short unsigned dia;
    short unsigned mes;
    short unsigned año;

    std::string toString()
    {
        return (dia < 10 ? "0" : "") + std::to_string(dia) + "/" + (mes < 10 ? "0" : "") + std::to_string(mes) + "/" + std::to_string(año);
    }
};

struct Documeto
{
    TiposDocumentos tipoDocumento;
    std::string numero;
};

struct Direccion
{
    std::string calle;
    short unsigned altura;
    TiposInmbuebles tipoInmueble;
    short unsigned piso;
    std::string departamento;
    std::string localidad;
    std::string provincia;
    std::string codigoPostal;

    std::string toString()
    {
        return calle + " " + std::to_string(altura) + (piso > 0 ? " [Piso " + std::to_string(piso) + "]" : "") + (departamento != "" ? " [Depto " + departamento + "]" : "") + " (" + localidad + ", " + provincia + ") | C.P.: " + codigoPostal;
    }
};

struct Cliente
{
    std::string nombre;
    std::string apellido;
    Documeto documento;
    Fecha fechaNacimiento;
    Direccion direccionEnvio;
    Direccion direccionFacturacion;
};

// ####################
// ### DEFINICIONES ###
// ####################

std::ostream &operator<<(std::ostream &, Cliente &);
std::string TipoDocumentoToString(TiposDocumentos);
short unsigned CalcularEdad(Fecha);

// ###################
// ### SOBRECARGAS ###
// ###################

std::ostream &operator<<(std::ostream &o, Cliente &c)
{
    o << "Cliente:\t\t\t" << c.apellido << ", " << c.nombre << "\r\n";
    o << "Documento:\t\t\t" << TipoDocumentoToString(c.documento.tipoDocumento) << " " << c.documento.numero << "\r\n";
    o << "Fecha de Nacimiento:\t\t" << c.fechaNacimiento.toString() << " (" << std::to_string(CalcularEdad(c.fechaNacimiento)) << " anos)\r\n";
    o << "Direccion de envio:\t\t" << c.direccionEnvio.toString() << "\r\n";
    o << "Direccion de facturacion:\t" << c.direccionFacturacion.toString() << "\r\n";
    return o;
}

// #################
// ### FUNCIONES ###
// #################

std::string TipoDocumentoToString(TiposDocumentos td) // Sirve para mostrar por pantalla el tipo de documento
{
    switch (td)
    {
    case TiposDocumentos::DNI:
        return "DNI";
    case TiposDocumentos::LC:
        return "LC";
    case TiposDocumentos::LE:
        return "LE";
    case TiposDocumentos::Pasaporte:
        return "Pasaporte";
    default:
        return "";
    }
}

short unsigned CalcularEdad(Fecha f) // Calcula la edad en base a la fecha proporcionada
{
    std::time_t t = std::time(0);
    std::tm *hoy = std::localtime(&t);

    short unsigned edad = (1900 + hoy->tm_year) - f.año;
    if (f.mes > (hoy->tm_mon + 1) || (f.mes == (hoy->tm_mon + 1) && f.dia > hoy->tm_mday))
    {
        edad -= 1;
    }

    return edad;
}

// ##########################
// ### PROGRAMA PRINCIPAL ###
// ##########################

int main()
{
    Cliente cliente1 = Cliente{
        "Juan",
        "Perez",
        Documeto{TiposDocumentos::DNI, "12345678"},
        Fecha{14, 12, 1992},
        Direccion{"Mitre", 586, TiposInmbuebles::Edificio, 5, "C", "Vicente Lopez", "Buenos Aires", "1636"},
        Direccion{"Av. Siempre Viva", 1234, TiposInmbuebles::Casa, 0, "", "Villa del Parque", "Capital Federal", "1416"}};

    assert(cliente1.nombre == "Juan");
    assert(cliente1.documento.numero == "12345678");
    assert(CalcularEdad(cliente1.fechaNacimiento) == 29);
    assert(cliente1.direccionEnvio.toString() == "Mitre 586 [Piso 5] [Depto C] (Vicente Lopez, Buenos Aires) | C.P.: 1636");
    assert(cliente1.direccionFacturacion.altura == 1234);

    Cliente cliente2 = Cliente{
        "Miguel",
        "Martinez",
        Documeto{TiposDocumentos::DNI, "51238459"},
        Fecha{5, 9, 1946},
        Direccion{"Av. Marconi", 2975, TiposInmbuebles::Casa, 0, "", "El Palomar", "Buenos Aires", "1755"},
        Direccion{"Belgrano", 1589, TiposInmbuebles::Casa, 0, "", "Ramos Mejia", "Buenos Aires", "1425"}};

    assert(cliente2.apellido == "Martinez");
    assert(TipoDocumentoToString(cliente2.documento.tipoDocumento) == "DNI");
    assert(CalcularEdad(cliente2.fechaNacimiento) == 75);
    assert(cliente2.direccionEnvio.provincia == "Buenos Aires");

    std::cout << cliente1 << "\r\n\r\n";
    std::cout << cliente2;
}