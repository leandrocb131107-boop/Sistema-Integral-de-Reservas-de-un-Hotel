
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

// Estructura que representa una habitacion.
struct Habitacion {
    int numero;
    string tipo;
    int capacidad;
    double precioPorNoche;
    bool activa;
};

// Funcion para leer numeros enteros.
int leerEntero(string mensaje) {
    int valor;

    while (true) {
        cout << mensaje;

        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "Error: debes introducir un numero entero.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Funcion para leer numeros decimales.
double leerDecimal(string mensaje) {
    double valor;

    while (true) {
        cout << mensaje;

        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "Error: debes introducir un numero valido.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Muestra el menu de gestion de habitaciones.
void mostrarMenuHabitaciones() {
    cout << "\n";
    cout << "GESTION DE HABITACIONES\n";
    cout << "1. Registrar una habitacion\n";
    cout << "2. Listar habitaciones\n";
    cout << "3. Modificar una habitacion\n";
    cout << "0. Salir del programa\n";
}

// Registra una habitacion nueva.
void registrarHabitacion(vector<Habitacion>& habitaciones) {
    Habitacion nuevaHabitacion;

    // Solicitar un numero valido y no repetido.
    while (true) {
        nuevaHabitacion.numero = leerEntero(
            "Introduce el numero de habitacion: "
        );

        if (nuevaHabitacion.numero <= 0) {
            cout << "Error: el numero debe ser mayor que cero.\n";
            continue;
        }

        bool existe = false;

        for (const Habitacion& habitacion : habitaciones) {
            if (habitacion.numero == nuevaHabitacion.numero) {
                existe = true;
                break;
            }
        }

        if (existe) {
            cout << "Error: ya existe una habitacion con ese numero.\n";
        } else {
            break;
        }
    }

    // Seleccionar el tipo de habitacion.
    int opcionTipo;
    int capacidadMaxima;
    int capacidadMinima;

    while (true) {
        cout << "\nTipos de habitacion:\n";
        cout << "1. Sencilla\n";
        cout << "2. Doble\n";
        cout << "3. Familiar\n";

        opcionTipo = leerEntero("Selecciona el tipo: ");

        if (opcionTipo == 1) {
            nuevaHabitacion.tipo = "Sencilla";
            capacidadMinima = 1;
            capacidadMaxima = 2;
            break;
        } else if (opcionTipo == 2) {
            nuevaHabitacion.tipo = "Doble";
            capacidadMinima = 2;
            capacidadMaxima = 6;
            break;
        } else if (opcionTipo == 3) {
            nuevaHabitacion.tipo = "Familiar";
            capacidadMinima = 6;
            capacidadMaxima = 10;
            break;
        } else {
            cout << "Error: selecciona una opcion entre 1 y 3.\n";
        }
    }

    // Solicitar y validar la capacidad.
    while (true) {
        nuevaHabitacion.capacidad = leerEntero(
            "Introduce la capacidad: "
        );

        if (nuevaHabitacion.capacidad < capacidadMinima) {
            cout << "Error: la capacidad minima es de: "
                 << capacidadMinima << "\n";

        } else if (nuevaHabitacion.capacidad > capacidadMaxima) {
            cout << "Error: la capacidad supera el limite permitido.\n";
            cout << "Capacidad maxima: " << capacidadMaxima << "\n";

        } else {
            break;
        }
    }

    // Solicitar y validar el precio por noche.
    while (true) {
        nuevaHabitacion.precioPorNoche = leerDecimal(
            "Introduce el precio por noche: "
        );

        if (nuevaHabitacion.precioPorNoche <= 0) {
            cout << "Error: el precio debe ser mayor que cero.\n";
        } else {
            break;
        }
    }

    // La habitacion comienza activa.
    nuevaHabitacion.activa = true;

    // Guardar la habitacion en el vector.
    habitaciones.push_back(nuevaHabitacion);

    cout << "Habitacion registrada correctamente.\n";
}

// Muestra solamente la informacion de las habitaciones.
void listarHabitaciones(const vector<Habitacion>& habitaciones) {
    cout << "\nHabitaciones:\n";

    // Ordenar una copia por numero de habitacion.
    vector<Habitacion> habitacionesOrdenadas = habitaciones;

    sort(
        habitacionesOrdenadas.begin(),
        habitacionesOrdenadas.end(),
        [](const Habitacion& a, const Habitacion& b) {
            return a.numero < b.numero;
        }
    );

    // Mostrar los datos de cada habitacion.
    for (const Habitacion& habitacion : habitacionesOrdenadas) {
        cout << "Numero: " << habitacion.numero
             << " | Tipo: " << habitacion.tipo
             << " | Capacidad: " << habitacion.capacidad
             << " | Precio por noche: "
             << fixed << setprecision(2) << habitacion.precioPorNoche
             << " | Estado: "
             << (habitacion.activa ? "Activa" : "Deshabilitada")
             << "\n";
    }
}

// Modifica los datos de una habitacion existente.
void modificarHabitacion(vector<Habitacion>& habitaciones) {

    // No se puede modificar una habitacion si no hay ninguna registrada.
    if (habitaciones.empty()) {
        cout << "No hay habitaciones registradas para modificar.\n";
        return;
    }

    // Solicitar el numero de la habitacion que se desea modificar.
    int numeroBuscado = leerEntero(
        "Introduce el numero de habitacion que deseas modificar: "
    );

    // Buscar la habitacion dentro del vector.
    Habitacion* habitacionEncontrada = nullptr;

    for (Habitacion& habitacion : habitaciones) {
        if (habitacion.numero == numeroBuscado) {
            habitacionEncontrada = &habitacion;
            break;
        }
    }

    // Comprobar si se encontro la habitacion.
    if (habitacionEncontrada == nullptr) {
        cout << "Error: no existe una habitacion con ese numero.\n";
        return;
    }

    cout << "\nHabitacion encontrada.\n";
    cout << "Numero: " << habitacionEncontrada->numero << "\n";
    cout << "Tipo: " << habitacionEncontrada->tipo << "\n";
    cout << "Capacidad: " << habitacionEncontrada->capacidad << "\n";
    cout << "Precio por noche: "
         << fixed << setprecision(2)
         << habitacionEncontrada->precioPorNoche << "\n";
    cout << "Estado: "
         << (habitacionEncontrada->activa ? "Activa" : "Deshabilitada")
         << "\n";

    int opcion;

    // Permitir modificar diferentes atributos.
    do {
        cout << "\nMODIFICAR HABITACION "
             << habitacionEncontrada->numero << "\n";

        cout << "1. Modificar tipo y capacidad\n";
        cout << "2. Modificar capacidad\n";
        cout << "3. Modificar precio por noche\n";
        cout << "4. Cambiar estado\n";
        cout << "0. Finalizar modificacion\n";

        opcion = leerEntero("Selecciona una opcion: ");

        switch (opcion) {

            case 1: {
                int opcionTipo;
                int capacidadMinima;
                int capacidadMaxima;
                string nuevoTipo;

                // Seleccionar el nuevo tipo.
                while (true) {
                    cout << "\nTipos de habitacion:\n";
                    cout << "1. Sencilla\n";
                    cout << "2. Doble\n";
                    cout << "3. Familiar\n";

                    opcionTipo = leerEntero("Selecciona el nuevo tipo: ");

                    if (opcionTipo == 1) {
                        nuevoTipo = "Sencilla";
                        capacidadMinima = 1;
                        capacidadMaxima = 2;
                        break;

                    } else if (opcionTipo == 2) {
                        nuevoTipo = "Doble";
                        capacidadMinima = 2;
                        capacidadMaxima = 6;
                        break;

                    } else if (opcionTipo == 3) {
                        nuevoTipo = "Familiar";
                        capacidadMinima = 6;
                        capacidadMaxima = 10;
                        break;

                    } else {
                        cout << "Error: selecciona una opcion entre 1 y 3.\n";
                    }
                }

                int nuevaCapacidad;

                // Validar la capacidad correspondiente al nuevo tipo.
                while (true) {
                    nuevaCapacidad = leerEntero(
                        "Introduce la nueva capacidad: "
                    );

                    if (nuevaCapacidad < capacidadMinima) {
                        cout << "Error: la capacidad minima es "
                             << capacidadMinima << ".\n";

                    } else if (nuevaCapacidad > capacidadMaxima) {
                        cout << "Error: la capacidad maxima es "
                             << capacidadMaxima << ".\n";

                    } else {
                        break;
                    }
                }

                // Aplicar los cambios.
                habitacionEncontrada->tipo = nuevoTipo;
                habitacionEncontrada->capacidad = nuevaCapacidad;

                cout << "Tipo y capacidad modificados correctamente.\n";
                break;
            }

            case 2: {
                int capacidadMinima;
                int capacidadMaxima;

                // Determinar los limites segun el tipo actual.
                if (habitacionEncontrada->tipo == "Sencilla") {
                    capacidadMinima = 1;
                    capacidadMaxima = 2;

                } else if (habitacionEncontrada->tipo == "Doble") {
                    capacidadMinima = 2;
                    capacidadMaxima = 6;

                } else {
                    capacidadMinima = 6;
                    capacidadMaxima = 10;
                }

                int nuevaCapacidad;

                // Solicitar y validar la nueva capacidad.
                while (true) {
                    nuevaCapacidad = leerEntero(
                        "Introduce la nueva capacidad: "
                    );

                    if (nuevaCapacidad < capacidadMinima) {
                        cout << "Error: la capacidad minima es "
                             << capacidadMinima << ".\n";

                    } else if (nuevaCapacidad > capacidadMaxima) {
                        cout << "Error: la capacidad maxima es "
                             << capacidadMaxima << ".\n";

                    } else {
                        break;
                    }
                }

                habitacionEncontrada->capacidad = nuevaCapacidad;

                cout << "Capacidad modificada correctamente.\n";
                break;
            }

            case 3: {
                double nuevoPrecio;

                // Solicitar y validar el nuevo precio.
                while (true) {
                    nuevoPrecio = leerDecimal(
                        "Introduce el nuevo precio por noche: "
                    );

                    if (nuevoPrecio <= 0) {
                        cout << "Error: el precio debe ser mayor que cero.\n";
                    } else {
                        break;
                    }
                }

                habitacionEncontrada->precioPorNoche = nuevoPrecio;

                cout << "Precio modificado correctamente.\n";
                break;
            }

            case 4: {
                // Invertir el estado actual de la habitacion.
                habitacionEncontrada->activa = !habitacionEncontrada->activa;

                cout << "Nuevo estado: "
                     << (habitacionEncontrada->activa
                             ? "Activa"
                             : "Deshabilitada")
                     << "\n";

                break;
            }

            case 0:
                cout << "Modificacion finalizada.\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);
}

// Funcion principal.
int main() {
    vector<Habitacion> habitaciones;

    int opcion;

    do {
        mostrarMenuHabitaciones();

        opcion = leerEntero("Selecciona una opcion: ");

        switch (opcion) {

            case 1:
                registrarHabitacion(habitaciones);
                break;

            case 2:
                listarHabitaciones(habitaciones);
                break;

            case 3:
                modificarHabitacion(habitaciones);
                break;

            case 0:
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);

    return 0;
}
