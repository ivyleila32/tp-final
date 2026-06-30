#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX = 100;

//=========================
// ESTRUCTURA
//=========================

struct Invitado
{
    int ticket;
    char nombre[30];
    char apellido[30];
    int edad;
    char telefono[20];
    bool confirmado;
};


Invitado invitados[MAX];
int cantidad = 0;


//=========================
// PROTOTIPOS
//=========================

//void agregarInvitado(invitados, cantidad);
void agregarInvitado(Invitado invitados[], int &cantidad);
void modificarInvitado(Invitado invitados[], int cantidad);
void eliminarInvitado();
void listarAsistentes();
void confirmarAsistencia();
void cancelarAsistencia();
void mostrarTodos();

//=========================
// MAIN
//=========================

int main()
{
    int opcion;

    do
    {
        cout << "\n==============================";
        cout << "\n STUDIO 54 - ACCESS PASS";
        cout << "\n==============================";
        cout << "\n1. Agregar invitado";
        cout << "\n2. Modificar datos";
        cout << "\n3. Eliminar invitado";
        cout << "\n4. Listar asistentes";
        cout << "\n5. Confirmar asistencia";
        cout << "\n6. Cancelar asistencia";
        cout << "\n7. Mostrar todos";
        cout << "\n8. Salir";
        cout << "\n\nOpcion: ";
        cin >> opcion;

        switch(opcion)
        {
        case 1:
            agregarInvitado(invitados, cantidad);
            break;

        case 2:
            modificarInvitado(invitados, cantidad);
            break;

        case 3:
            eliminarInvitado();
            break;

        case 4:
            listarAsistentes();
            break;

        case 5:
            confirmarAsistencia();
            break;

        case 6:
            cancelarAsistencia();
            break;

        case 7:
            mostrarTodos();
            break;

        case 8:
            cout << "\nGracias por utilizar el sistema.\n";
            break;

        default:
            cout << "\nOpcion incorrecta.\n";
        }

    } while(opcion != 8);

    return 0;
}

//=========================
// FUNCIONES
//=========================
   // Código para agregar un invitado
void agregarInvitado(Invitado invitados[], int &cantidad)
{
    ofstream archivo("invitados.dat", ios::binary | ios::app);

    if (!archivo)
    {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    char seguir;

    do
    {
        if (cantidad >= MAX)
        {
            cout << "No hay mas lugar para invitados." << endl;
            archivo.close();
            return;
        }

        cout << "\n----- NUEVO INVITADO -----\n";

        cout << "Numero de Ticket: ";
        cin >> invitados[cantidad].ticket;
        cin.ignore();

        cout << "Nombre: ";
        cin.getline(invitados[cantidad].nombre, 30);

        cout << "Apellido: ";
        cin.getline(invitados[cantidad].apellido, 30);

        cout << "Edad: ";
        cin >> invitados[cantidad].edad;
        cin.ignore();

        cout << "Telefono: ";
        cin.getline(invitados[cantidad].telefono, 20);

        invitados[cantidad].confirmado = false;

        // Guarda el invitado en el archivo
        archivo.write((char*)&invitados[cantidad], sizeof(Invitado));

        cantidad++;

        cout << "\nInvitado agregado correctamente." << endl;

        cout << "\n¿Desea agregar otro invitado? (S/N): ";
        cin >> seguir;
        seguir = toupper(seguir);
        cin.ignore();

    } while (seguir == 'S');

    archivo.close();
}
 // Código para modificar los datos de un invitado
void modificarInvitado(Invitado invitados[], int cantidad)
{
    int ticket;
    bool encontrado = false;

    cout << "\n----- MODIFICAR INVITADO -----\n";
    cout << "Ingrese el numero de Ticket: ";
    cin >> ticket;
    cin.ignore();

    for (int i = 0; i < cantidad; i++)
    {
        if (invitados[i].ticket == ticket)
        {
            encontrado = true;

            cout << "\nInvitado encontrado.\n";

            cout << "Nuevo nombre: ";
            cin.getline(invitados[i].nombre, 30);

            cout << "Nuevo apellido: ";
            cin.getline(invitados[i].apellido, 30);

            cout << "Nueva edad: ";
            cin >> invitados[i].edad;
            cin.ignore();

            cout << "Nuevo telefono: ";
            cin.getline(invitados[i].telefono, 20);

            cout << "\nDatos modificados correctamente.\n";

            break;
        }
    }

    if (!encontrado)
    {
        cout << "\nNo existe un invitado con ese numero de Ticket.\n";
    }
}
 // Código para eliminar un invitado
void eliminarInvitado()
{
   
}

void listarAsistentes()
{
    // Mostrar únicamente los invitados confirmados
}

void confirmarAsistencia()
{
    // Buscar por número de ticket y confirmar
}

void cancelarAsistencia()
{
    // Buscar por número de ticket y cancelar
}

void mostrarTodos()
{
    // Mostrar todos los invitados
}