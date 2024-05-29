#include "empleado.h"

//Bibliotecas necesarias para que el codigo funcione
#include <fstream>
#include <iostream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>


//implementacion de bitacora

#include "Bitacora.h"

using namespace std;

//Definir la función principal del CRUD
void empleadoCrud::CrudAula()
{
 //implementacion de variables para bitacora
    string codigoPrograma= "5000";
    Bitacora Auditoria;
    string user ="admin";

    int opcion;
    do
    {

//Limpiamos pantalla
	system("cls");

	//Mostramos el menu principal
	cout<<"\t\t\t--------------------------------------------"<<endl;
	cout<<"\t\t\t|     SISTEMA DE GESTION UMG - empleado       |"<<endl;
	cout<<"\t\t\t--------------------------------------------"<<endl;
	cout<<"\t\t\t 1. Ingresar Aula"<<endl;
	cout<<"\t\t\t 2. Modificar Aula"<<endl;
	cout<<"\t\t\t 3. Borrar Aula"<<endl;
	cout<<"\t\t\t 4. Desplegar Aula"<<endl;
	cout<<"\t\t\t 5. Regresar Menu Anterior"<<endl;
    cout<<"\t\t\t --------------------------------------------"<<endl;
	cout<<"\t\t\t |   Opcion a escoger:[1|2|3|4|5|]           |"<<endl;
	cout<<"\t\t\t --------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa tu Opcion: ";
    cin>>opcion;

//Maneja las opciones del menu
     switch(opcion)
    {
	case 1:
        IngresarAula();
        //registro de bitacora ingreso
        Auditoria.ingresoBitacora(user,codigoPrograma,"CUA");//CAU = Create empleado

		break;
    case 2:
        ModificarAula();
		//registro de bitacora Modificar
        Auditoria.ingresoBitacora(user,codigoPrograma,"UAU");//UAU = Update empleado

		break;
    case 3:
        BorrarAula();
		//registro de bitacora borrar
        Auditoria.ingresoBitacora(user,codigoPrograma,"DAU");//DAU = Delete empleado

		break;
    case 4:

        DesplegarAula();
		//registro de bitacora despliegle
        Auditoria.ingresoBitacora(user,codigoPrograma,"RAU");//RCU = Read empleado
        break;
    case 5:
		break;
	default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
		cin.get();
	}
    }while(opcion!= 5);

}

// Función para agregar un aula
void empleadoCrud::IngresarAula() {
    // Limpiar la pantalla
    system("cls");
    // Mostrar mensaje de agregar aula
    cout<<"\n------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n-------------------------------------------------Agregar Aula--------------------------------------------"<<endl;
    // Declarar una variable para el aula
    empleado aula;
    // Solicitar al usuario ingresar los datos del aula
    cout << "Ingrese el codigo del aula: ";
    cin >> aula.codigo;
    cin.ignore();

    cout << "Ingrese el nombre del aula: ";
    cin.getline(aula.nombre, 50);

    cout << "Ingrese la estatus de la aula: ";
    cin.getline(aula.estatus, 50);

    // Abrir el archivo de empleado en modo binario para agregar el aula
    ofstream archivo("empleado.dat", ios::binary | ios::app);
    // Escribir el aula en el archivo
    archivo.write(reinterpret_cast<const char*>(&aula), sizeof(empleado));
    archivo.close(); // Cerrar el archivo

    cout << "aula agregada exitosamente!" << endl; // Mostrar mensaje de éxito
}

// Función para modificar un aula
void empleadoCrud::ModificarAula() {
    int codigo;
    // Solicitar al usuario ingresar el código del aula a modificar
    cout << "Ingrese el codigo de la aula a modificar: ";
    cin >> codigo;

    // Abrir el archivo de empleado en modo lectura y escritura binaria
    fstream archivo("empleado.dat", ios::binary | ios::in | ios::out);
    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        cout << "No hay empleado registradas." << endl;
        return;
    }

    // Declarar una variable para el aula
    empleado aula;
    bool encontrada = false;
    // Recorrer el archivo para encontrar el aula con el código ingresado
    while (archivo.read(reinterpret_cast<char*>(&aula), sizeof(empleado))) {
        if (aula.codigo == codigo) {
            // Solicitar al usuario ingresar los nuevos datos del aula
            cout << "Ingrese el nuevo nombre de la aula: ";
            cin.ignore();
            cin.getline(aula.nombre, 50);

            cout << "Ingrese el nuevo estatus de la aula: ";
            cin.getline(aula.estatus, 50);

            // Mover el puntero de escritura hacia atrás para sobreescribir el aula
            archivo.seekp(-static_cast<int>(sizeof(empleado)), ios::cur);
            // Escribir el aula modificada en el archivo
            archivo.write(reinterpret_cast<const char*>(&aula), sizeof(empleado));

            encontrada = true;
            break;
        }
    }

    archivo.close(); // Cerrar el archivo

    if (!encontrada) {
        cout << "No se encontró la aula con el codigo ingresado." << endl;
    } else {
        cout << "aula modificada exitosamente!" << endl;
    }

}

// Función para eliminar un aula
void empleadoCrud::BorrarAula() {
    int codigo;
    // Solicitar al usuario ingresar el código del aula a eliminar
    cout << "Ingrese el codigo de la aula a eliminar: ";
    cin >> codigo;

    // Abrir el archivo de empleado en modo lectura binaria
    ifstream archivo("empleado.dat", ios::binary);
    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        cout << "No hay empleado registradas." << endl;
        return;
    }

    // Abrir un archivo temporal para escribir las empleado que no se van a eliminar
    ofstream archivoTmp("empleado_tmp.dat", ios::binary);
    // Declarar una variable para el aula
    empleado aula;
    bool eliminada = false;
    // Recorrer el archivo para copiar las empleado que no se van a eliminar al archivo temporal
    while (archivo.read(reinterpret_cast<char*>(&aula), sizeof(empleado))) {
        if (aula.codigo != codigo) {
            archivoTmp.write(reinterpret_cast<const char*>(&aula), sizeof(empleado));
        } else {
            eliminada = true;
        }
    }

    archivo.close(); // Cerrar el archivo original
    archivoTmp.close(); // Cerrar el archivo temporal

    // Eliminar el archivo original y renombrar el archivo temporal
    remove("empleado.dat");
    rename("empleado_tmp.dat", "empleado.dat");

    if (eliminada) {
        cout << "aula eliminada exitosamente!" << endl;
    } else {
        cout << "No se encontró la aula con el codigo ingresado." << endl;
    }

}

// Función para desplegar todas las empleado registradas
void empleadoCrud::DesplegarAula() {
    // Limpiar la pantalla
    system("cls");
    // Mostrar mensaje de despliegue de empleado registradas
    cout<<"-----------------Despliegue de empleado registradas---------------------"<<endl;
    // Abrir el archivo de empleado en modo lectura binaria
    ifstream archivo("empleado.dat", ios::binary);
    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        cout << "No hay empleado registradas." << endl;
        return;
    }

    // Declarar una variable para el aula
    empleado aula;
    // Recorrer el archivo y mostrar los datos de cada aula
    while (archivo.read(reinterpret_cast<char*>(&aula), sizeof(empleado))) {
        cout << "Codigo: " << aula.codigo << endl;
        cout << "Nombre: " << aula.nombre << endl;
        cout << "Estatus: " << aula.estatus << endl;
        cout << "-----------------------------" << endl;
    }

    archivo.close(); // Cerrar el archivo

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}
