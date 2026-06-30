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
void cargarArchivo(Invitado invitados[], int &cantidad);
void agregarInvitado(Invitado invitados[], int &cantidad);
void modificarInvitado(Invitado invitados[], int cantidad);
void eliminarInvitado(Invitado invitados[], int &cantidad);
void listarAsistentes(Invitado invitados[], int cantidad);
void confirmarAsistencia(Invitado invitados[], int cantidad);
void cancelarAsistencia(Invitado invitados[], int cantidad);
void mostrarTodos(Invitado invitados[], int cantidad);
void guardarArchivo(Invitado invitados[], int cantidad);

//=========================
// MAIN
//=========================

int main()
{
    cargarArchivo(invitados, cantidad);

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
            eliminarInvitado(invitados, cantidad);
            break;

        case 4:
            listarAsistentes(invitados, cantidad);
            break;

        case 5:
            confirmarAsistencia(invitados, cantidad);
            break;

        case 6:
            cancelarAsistencia(invitados, cantidad);
            break;

        case 7:
            mostrarTodos(invitados, cantidad);
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
void cargarArchivo(Invitado invitados[], int &cantidad)
{
    ifstream archivo("invitados.dat", ios::binary);

    if (!archivo)
    {
        return;
    }

    cantidad = 0;

    while (archivo.read((char*)&invitados[cantidad], sizeof(Invitado)))
    {
        cantidad++;
    }

    archivo.close();
}

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

            guardarArchivo(invitados, cantidad);
            break;
        }
    }

    if (!encontrado)
    {
        cout << "\nNo existe un invitado con ese numero de Ticket.\n";
    }
}
 // Código para eliminar un invitado
void eliminarInvitado(Invitado invitados[], int &cantidad)
{
    int ticket;
    bool encontrado = false;

    cout << "\n----- ELIMINAR INVITADO -----\n";
    if (cantidad == 0) {
        cout << "La lista esta vacia. No hay a quien eliminar.\n";
        return;
    }

    cout << "Ingrese el numero de Ticket a eliminar: ";
    cin >> ticket;

    for (int i = 0; i < cantidad; i++)
    {
        if (invitados[i].ticket == ticket)
        {
            encontrado = true;
            // Desplazar todos los elementos siguientes un lugar hacia atrás
            for (int j = i; j < cantidad - 1; j++)
            {
                invitados[j] = invitados[j + 1];
            }
            cantidad--; // Reducimos la cantidad total
            guardarArchivo(invitados, cantidad); // Sobrescribimos el archivo con el nuevo tamaño
            cout << "\nInvitado eliminado correctamente.\n";
            break;
        }
    }

    if (!encontrado) cout << "\nNo existe un invitado con ese numero de Ticket.\n";
}
// Mostrar únicamente los invitados confirmados
void listarAsistentes(Invitado invitados[], int cantidad)
{
    cout << "\n----- ASISTENTES CONFIRMADOS -----\n";
    bool hayConfirmados = false;
    
    for(int i = 0; i < cantidad; i++)
    {
        if(invitados[i].confirmado) // Solo entra si es true
        {
            cout << "Ticket: " << invitados[i].ticket << "\n";
            cout << "Nombre: " << invitados[i].nombre << " " << invitados[i].apellido << "\n";
            cout << "Telefono: " << invitados[i].telefono << "\n\n";
            hayConfirmados = true;
        }
    }
    
    if(!hayConfirmados) cout << "Aun no hay asistentes confirmados.\n";
}
  // Buscar por número de ticket y confirmar
void confirmarAsistencia(Invitado invitados[], int cantidad)
{
    int ticket;
    bool encontrado = false;

    cout << "\n----- CONFIRMAR ASISTENCIA -----\n";
    cout << "Ingrese el numero de Ticket: ";
    cin >> ticket;

    for (int i = 0; i < cantidad; i++)
    {
        if (invitados[i].ticket == ticket)
        {
            invitados[i].confirmado = true; // Cambiamos el estado
            encontrado = true;
            guardarArchivo(invitados, cantidad); // Guardamos el cambio
            cout << "\nAsistencia confirmada exitosamente.\n";
            break;
        }
    }

    if (!encontrado) cout << "\nNo existe un invitado con ese numero de Ticket.\n";
}
  // Buscar por número de ticket y cancelar
void cancelarAsistencia(Invitado invitados[], int cantidad)
{
    int ticket;
    bool encontrado = false;

    cout << "\n----- CANCELAR ASISTENCIA -----\n";
    cout << "Ingrese el numero de Ticket: ";
    cin >> ticket;

    for (int i = 0; i < cantidad; i++)
    {
        if (invitados[i].ticket == ticket)
        {
            invitados[i].confirmado = false; // Cambiamos el estado
            encontrado = true;
            guardarArchivo(invitados, cantidad); // Guardamos el cambio
            cout << "\nAsistencia cancelada exitosamente.\n";
            break;
        }
    }

    if (!encontrado) cout << "\nNo existe un invitado con ese numero de Ticket.\n";
}
 // Mostrar todos los invitados
void mostrarTodos(Invitado invitados[], int cantidad)
{
    cout << "\n----- LISTA COMPLETA DE INVITADOS -----\n";
    if (cantidad == 0) cout << "La lista esta vacia.\n";
    
    for(int i = 0; i < cantidad; i++)
    {
        cout << "Ticket: " << invitados[i].ticket << "\n";
        cout << "Nombre: " << invitados[i].nombre << " " << invitados[i].apellido << "\n";
        cout << "Edad: " << invitados[i].edad << "\n";
        cout << "Telefono: " << invitados[i].telefono << "\n";
        cout << "Estado: " << (invitados[i].confirmado ? "Confirmado" : "No confirmado") << "\n";
        cout << "---------------------------\n";
    }
}
//guardar los datos en el archivo 
void guardarArchivo(Invitado invitados[], int cantidad)
{
    // Agregamos ios::trunc para que limpie el archivo antes de reescribir los datos actualizados
    ofstream archivo("invitados.dat", ios::binary | ios::trunc); 

    if (!archivo)
    {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++)
    {
        archivo.write((char*)&invitados[i], sizeof(Invitado));
    }

    archivo.close();
}