#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;

struct registro {
    int id;
    string nombre, correo, edad;
};
struct registro reg;

FILE *alias;
long int dir_fisica;

int menu();
void Agregar();
void Mostrar_todo();
void Buscar();
void Modificar();
void Eliminar();
int Idx(string);

int main()
{
	int op;

	do {
	    op = menu();

	    switch (op)
        {

	        case 1: Agregar(); break;
	        case 2: Mostrar_todo(); break;
	        case 3: Buscar(); break;
            case 4: Modificar(); break;
            case 5: Eliminar(); break;
	        default: cout << "Opcion no valida "; break;

	    }

	} while (op != 6);

	return 0;
}

int menu()
{
    int op;
    system("cls");
    system("color 0E");
    cout<<"-----------------------------------------------"<<endl;
    cout << "                  .:MENU:.                  " << endl;
    cout<<"-----------------------------------------------"<<endl;
    cout << "\t[1]  Agregar nuevo registro" << endl;
    cout << "\t[2]. Mostrar todos los registros" << endl;
    cout << "\t[3]. Buscar registro" << endl;
    cout << "\t[4]. Modificar registro" << endl;
    cout << "\t[5]. Eliminar registro" << endl;
    cout << "\t[6]. Salir" << endl;
    cout << "\nopcion:  ";
    cin >> op;

    return op;
}


void Agregar()
{
    int ID = 0;
    string nombre;
    system("cls");
    system("cls");
    cout<<"-----------------------------------------------"<<endl;
    cout << "                  .Agregar.                  " << endl;
    cout<<"-----------------------------------------------"<<endl;

    alias = fopen("Users.txt", "rb+");

    if (alias == nullptr)
    {
        alias = fopen("Users.txt", "wb");
    }

    cout << "Nombre: ";
    fflush(stdin);
    getline(cin, nombre);

    ID = Idx(nombre);

    dir_fisica = ID*sizeof(reg);
    fseek(alias, dir_fisica, SEEK_SET); //posicionar
    fread(&reg, sizeof(reg), 1, alias);

    if (reg.id == ID)
    {
        cout << endl << " Registro duplicado, intente otro nombre o agregue " << endl;
        cout << " cualquier caracter alfanumerico al actual " <<endl;
        fclose(alias);
        system("pause");
        return;
    }

    cout << endl << " ID: " << ID;
    cout << endl << " Nombre: " << nombre;
    cout << endl << " Edad: ";
    fflush(stdin);
    getline(cin, reg.edad);
    cout << endl << " Correo electronico: ";
    fflush(stdin);
    getline(cin, reg.correo);
    reg.id = ID;
    reg.nombre = nombre;

    fseek(alias, dir_fisica, SEEK_SET);
    fwrite(&reg, sizeof(reg), 1, alias);
    fclose(alias);

    cout << endl << "Usuario registrado..." << endl;

    system("pause");
}

void Mostrar_todo()
{
    system("cls");

    cout<<"-----------------------------------------------"<<endl;
    cout << "             .Detalles de usuario.                " << endl;
    cout<<"-----------------------------------------------\n"<<endl;

    alias = fopen("Users.txt", "r");

    if (alias == NULL)
    {
        cout << "No existe el archivo/No se pudo abrir \n";

        system("pause");

        return;
    }

    fread(&reg, sizeof(reg), 1, alias);

    while (!feof(alias))
    {
        if (reg.id == 0)
        {
            fread(&reg, sizeof(reg), 1, alias);
        }
        else
        {
        cout << "\t    ID: " << reg.id << endl;
        cout << "\t    Nombre: " << reg.nombre << endl;
        cout << "\t    Edad: " << reg.edad << endl;
        cout << "\t    Correo: " << reg.correo << endl;
        cout << endl;
        fread(&reg, sizeof(reg), 1, alias);
        }
    }

    fclose(alias);

    system("pause");
}

void Buscar()
{
    int ID = 0;
    string nombre;
    system("cls");


    cout<<"-----------------------------------------------"<<endl;
    cout << "                   .Buscar.                  " << endl;
    cout<<"-----------------------------------------------\n"<<endl;

    alias = fopen("Users.txt", "r");

    if (alias == NULL)
    {
        cout << "No existe el archivo/No se pudo abrir \n";
        system("pause");
        return;
    }

    cout << " Dame el nombre a buscar: ";
    fflush(stdin);
    getline(cin, nombre);

    ID = Idx(nombre);

    dir_fisica = ID*sizeof(reg);
    fseek(alias, dir_fisica, SEEK_SET); //posicionar

    fread(&reg, sizeof(reg), 1, alias);

    if(reg.id == ID)
    {
        cout << "\n-----------------------------------------------";

        cout << "\n\n\t    ID: " << reg.id << endl;
        cout << "\t    Nombre: " << reg.nombre << endl;
        cout << "\t    Edad: " << reg.edad << endl;
        cout << "\t    Correo: " << reg.correo << endl << endl;
    }

    else
        cout << " El registro no existe!, inserte un ID valido ";

    fclose(alias);

    system("pause");
}


void Modificar(){
    int ID;
    string nombre;
    system("cls");


    cout<<"-----------------------------------------------"<<endl;
    cout << "             .Modificar registro.                  " << endl;
    cout<<"-----------------------------------------------"<<endl;

    alias = fopen("Users.txt", "rb+");

    if (alias == NULL)
    {
        cout << "No existe el archivo/No se pudo abrir \n";
        system("pause");
        return;
    }

    cout << " Dame el nombre del usuario a modificar: ";
    fflush(stdin);
    getline(cin, nombre);

    ID = Idx(nombre);


    dir_fisica = ID*sizeof(reg);
    fseek(alias, dir_fisica, SEEK_SET); //posicionar

    fread(&reg, sizeof(reg), 1, alias);

    if(reg.id == ID)
    {
        cout << "------------------------------------\n";

        cout << " ID: " << reg.id << endl;
        cout << " Nombre: " << reg.nombre << endl;
        cout << " Edad: " << reg.edad << endl;
        cout << " Correo: " << reg.correo << endl;

        cout << " Dame los datos a nuevos (El ID es irremplazable) " <<endl;
        cout << " Nombre: ";
        fflush(stdin);
        getline(cin, reg.nombre);
        cout << endl << " Edad: ";
        fflush(stdin);
        getline(cin, reg.edad);
        cout << " Correo electronico: ";
        fflush(stdin);
        getline(cin, reg.correo);

        fseek(alias, dir_fisica, SEEK_SET);
        fwrite(&reg, sizeof(reg), 1, alias);
    }

    else
        cout << " El registro no existe!, inserte un ID valido ";

    fclose(alias);

    system("pause");

}

void Eliminar(){
    int ID = 0, opc = 0;
    string nombre;

    system("cls");


    cout<<"-----------------------------------------------"<<endl;
    cout << "             .Eliminar Registro.                  " << endl;
    cout<<"-----------------------------------------------\n"<<endl;

    alias = fopen("Users.txt", "rb+");

    if (alias == NULL)
    {
        cout << "No existe el archivo/No se pudo abrir \n";
        system("pause");
        return;
    }

    cout << " Dame el ID del usuario a eliminar: ";
    cin >> ID;


    dir_fisica = ID*sizeof(reg);
    fseek(alias, dir_fisica, SEEK_SET); //posicionar

    fread(&reg, sizeof(reg), 1, alias);

    if(reg.id == ID)
    {
        cout << "ID: " << reg.id << endl;
        cout << "Nombre: " << reg.nombre << endl;
        cout << "Edad: " << reg.edad << endl;
        cout << "Correo: " << reg.correo << endl;


        cout << "\n\n�Estas seguro que deseas eliminarlo? 1)Si  |  2)No " << endl;
        cin >> opc;
        if(opc == 2)
            return;
        else

        reg.id = 0;

        reg.nombre = "";

        reg.edad = "";

        reg.correo = "";

        fseek(alias, dir_fisica, SEEK_SET);
        fwrite(&reg, sizeof(reg), 1, alias);
    }

    else
        cout << " El registro no existe!, inserte un ID valido ";

    fclose(alias);
    system("pause");

}

int Idx(string nombre){
    int ascii, cont, idx;
    ascii = 0, cont = 1, idx = 0;
    for(int i=0; i<nombre.length(); i++){
        ascii = nombre[i] * cont;
        idx = (idx + ascii) % 20;
        cont++;
    }

    return idx;
    }
