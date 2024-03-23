//Ivan Alonso Hernandez Hernandez
//Oscar Andres Mosquera Hinestroza

#include <iostream>

using namespace std;

struct Cliente {
    int numeroCuenta;
    int tipoCuenta;
    struct Cliente* siguiente;
};

struct Fila {
    Cliente* frente;
    Cliente* final;
    int turnos; 
};

Fila* crearFila() {
    Fila* nuevaFila = new Fila;
    nuevaFila->frente = NULL;
    nuevaFila->final = NULL;
    nuevaFila->turnos = 1; 
    return nuevaFila;
}

void encolar(Fila* fila, int numeroCuenta, int tipoCuenta) {
    Cliente* nuevoCliente = new Cliente;
    nuevoCliente->numeroCuenta = numeroCuenta;
    nuevoCliente->tipoCuenta = tipoCuenta;
    nuevoCliente->siguiente = NULL;
    if(fila->final == NULL) {
        fila->frente = nuevoCliente;
    } else {
        fila->final->siguiente = nuevoCliente;
    }
    fila->final = nuevoCliente;
    cout << "Cliente " << numeroCuenta << " agregado a la fila. Turno asignado: " << fila->turnos << endl;
    fila->turnos++; 
}

void desencolar(Fila* fila) {
    if(fila->frente != NULL) {
        Cliente* clienteEliminado = fila->frente;
        fila->frente = fila->frente->siguiente;
        if(fila->frente == NULL) {
            fila->final = NULL;
        }
        cout << "Cliente " << clienteEliminado->numeroCuenta << " atendido y removido de la fila." << endl;
        delete clienteEliminado;
    }
}

void transferirCliente(Fila* filaTradicional, Fila* filaPreferencial) {
    if(filaTradicional->frente != NULL && filaTradicional->frente->siguiente != NULL && filaTradicional->frente->siguiente->siguiente != NULL) {
        Cliente* clienteTransferido = filaTradicional->frente->siguiente->siguiente;
        filaTradicional->frente->siguiente->siguiente = clienteTransferido->siguiente;
        clienteTransferido->siguiente = NULL;
        if(filaPreferencial->final == NULL) {
            filaPreferencial->frente = clienteTransferido;
        } else {
            filaPreferencial->final->siguiente = clienteTransferido;
        }
        filaPreferencial->final = clienteTransferido;
        cout << "Cliente " << clienteTransferido->numeroCuenta << " transferido a la fila preferencial. Turno asignado: " << filaPreferencial->turnos << endl;
        filaPreferencial->turnos++;
    }
}

void visualizarFila(Fila* fila) {
    Cliente* clienteActual = fila->frente;
    int i = 1;
    while(clienteActual != NULL) {
        cout << "Cliente " << i << ": " << clienteActual->numeroCuenta << " (Turno: " << fila->turnos - (i - 1) << ")" << endl;
        clienteActual = clienteActual->siguiente;
        i++;
    }
}

int main() {
    Fila* filaTradicional = crearFila();
    Fila* filaPreferencial = crearFila();

    char opcion;
    do {
        cout <<endl<< "--- Menu ---"<<endl;
        cout << "1. Registrar cliente en cola tradicional"<<endl;
        cout << "2. Registrar cliente en cola preferencial"<<endl;
        cout << "3. Transferir cliente de cola tradicional a preferencial"<<endl;
        cout << "4. Visualizar cola tradicional"<<endl;
        cout << "5. Visualizar cola preferencial"<<endl;
        cout << "6. Salir"<<endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch(opcion) {
            case '1': {
                int numeroCuenta, tipoCuenta;
                cout << "Ingrese el numero de cuenta del cliente: ";
                cin >> numeroCuenta;
                cout << "Ingrese el tipo de cuenta (1 - Tradicional, 2 - Preferencial): ";
                cin >> tipoCuenta;
                encolar(filaTradicional, numeroCuenta, tipoCuenta);
                break;
            }
            case '2': {
                int numeroCuenta, tipoCuenta;
                cout << "Ingrese el numero de cuenta del cliente: ";
                cin >> numeroCuenta;
                cout << "Ingrese el tipo de cuenta (1 - Tradicional, 2 - Preferencial): ";
                cin >> tipoCuenta;
                encolar(filaPreferencial, numeroCuenta, tipoCuenta);
                break;
            }
            case '3':
                transferirCliente(filaTradicional, filaPreferencial);
                break;
            case '4':
                cout <<endl<< "--- Cola Tradicional ---"<<endl;
                visualizarFila(filaTradicional);
                break;
            case '5':
                cout <<endl<< "--- Cola Preferencial ---"<<endl;
                visualizarFila(filaPreferencial);
                break;
            case '6':
                cout << "Saliendo del programa..."<<endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, ingrese una opcion valida."<<endl;
        }
    } while(opcion != '6');

    while(filaTradicional->frente != NULL) {
        desencolar(filaTradicional);
    }
    while(filaPreferencial->frente != NULL) {
        desencolar(filaPreferencial);
    }

    free(filaTradicional);
    free(filaPreferencial);

    return 0;
}
