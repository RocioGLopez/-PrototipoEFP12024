#ifndef EMPLEADO_H
#define EMPLEADO_H


#include<stdlib.h>// Incluye funciones para el manejo de memoria dinamica, control de procesos y conversiones de cadena.
#include<cstdlib>// Incluye funciones para el control de procesos y conversiones de cadena.
#include<conio.h>// Incluye funciones para el manejo de la consola.
#include<iomanip>// Incluye funciones para formatear la salida.

using namespace std;// Se utiliza el espacio de nombres estandar.


//Definir la función principal del CRUD
struct empleado
{
    int codigo;// Código del aula.
    char nombre [45];// Nombre del aula.
    char estatus [1];// Estatus del aula.
     int sueldo;// Código del aula
       char depa [1];// Estatus del aula.

};
// Definición de la clase AulasCRUD que proporciona mótodos para realizar operaciones CRUD en aulas.
class empleadoCRUD
{
    public:// Mótodos para realizar operaciones CRUD.
        void IngresarAula();
        void ModificarAula();
        void BorrarAula();
        void DesplegarAula();
        void CrudAula();
        void visualizarBitacora();

};

#endif
