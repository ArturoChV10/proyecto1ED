
#include <list>
#include <math.h>
#include <string>
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

#define anchoPantalla 550 // Define el ancho de la pantalla
#define altoPantalla 700 // Define el alto de la pantalla

typedef struct TVehiculo {
    ALLEGRO_BITMAP* vehiculo;
    int x;
    int y;
    float angulo;
    int espacio;
    string cedula;
    string placa;

    TVehiculo()
        : vehiculo(nullptr), x(0), y(0), angulo(0.0f), espacio(0), cedula(""), placa("") { // Constructor de inicialización, no se usa, pero si lo quito genera advertencias que me molestan
    }

}*PtrTVehiculo;

void configurarEstacionamiento(int& pisos, int& espacios_por_piso, int cantidad_vehiculos, int tipoDeEstacionamiento, float reservados, list<int>& espacios_disponibles, list<int>& espacios_reservados) {
    system("cls");

    int total_espacios = pisos * espacios_por_piso;
    int espacios_reservados_total = static_cast<int>(total_espacios * reservados); // 15% de los espacios totales

    if (cantidad_vehiculos > total_espacios - espacios_reservados_total) {
        cout << "La cantidad de vehiculos a ingresar es mayor que los espacios disponibles (hay espacios reservados). Por favor, ingrese una cantidad menor." << endl;
        return;
    }

    // Generar y agregar los espacios disponibles a la lista
    for (int i = 1; i <= total_espacios; i++) {
        espacios_disponibles.push_back(i);
    }

    // Generar y agregar los espacios reservados a la lista
    for (int i = 1; i <= espacios_reservados_total; i++) {
        espacios_reservados.push_back(i);
    }
}

void asignarEspacio(PtrTVehiculo& StructVehiculo, list<int>& espacios_disponibles) {
    srand(time(NULL));
    int espacio_aleatorio = rand() % espacios_disponibles.size(); // Error de división entre 0
    auto it = next(espacios_disponibles.begin(), espacio_aleatorio);
    StructVehiculo->espacio = *it;
    espacios_disponibles.erase(it);
}

int vehiculoRandom() {
    srand(time(NULL));
    int num = rand() % 5;
    return num;
}

int fondoRandom() {
    srand(time(NULL));
    int num = rand() % 5;
    return num;
}

string generarCedula() {
    string cedula = "";
    for (int i = 0; i < 9; i++) {
        cedula += to_string(rand() % 10);
    }
    return cedula;
}

int obtenerEspacio(int numeroEspacio) {
    if (numeroEspacio <= 0) {
        return 0;
    }
    float numeroFloat;
    int numeroInt;
    numeroInt = numeroEspacio * 0.1;
    numeroFloat = numeroEspacio * 0.1;
    numeroFloat = numeroFloat - numeroInt;
    numeroInt = numeroFloat * 10;
    return numeroInt;
}

int obtenerCiclosParqueo(int numeroEspacio) {
    return numeroEspacio / 10 / 10;
}

string generarPlaca() {
    string placa = "";
    char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 3; i++) {
        placa += letras[rand() % 26];
    }
    for (int i = 0; i < 3; i++) {
        placa += to_string(rand() % 10);
    }
    return placa;
}

void actualizarFondo(ALLEGRO_BITMAP* fondo1, ALLEGRO_BITMAP* fondo2, ALLEGRO_BITMAP* fondo3, ALLEGRO_BITMAP* fondo4, int numeroFondo, bool& puerta) { // Método que verifica cual fondo debe ser pintado en cada momento de ejecución
    switch (numeroFondo) {
    case 0:
        al_draw_bitmap(fondo1, 0, 0, NULL); // Se dibuja el fondo
        break;
    case 1:
        al_draw_bitmap(fondo2, 0, 0, NULL); // Se dibuja el fondo
        break;
    case 2:
        al_draw_bitmap(fondo3, 0, 0, NULL); // Se dibuja el fondo
        break;
    case 3:
        al_draw_bitmap(fondo4, 0, 0, NULL); // Se dibuja el fondo
        puerta = true;
        break;
    }
}

void mostrarTiposEstacionamientos(ALLEGRO_BITMAP* parqueo, ALLEGRO_BITMAP* parqueo1, ALLEGRO_BITMAP* parqueo2, ALLEGRO_BITMAP* parqueo3, ALLEGRO_BITMAP* parqueo4, ALLEGRO_BITMAP* parqueoIzquierda, ALLEGRO_BITMAP* parqueoDerecha, ALLEGRO_FONT* fuente1, int fondo, int numero, int tipoEstacionamiento, int espacio) {
    string text;
    const char* cadena;
    switch (tipoEstacionamiento)
    {
    case 0:
        switch (fondo)
        {
        case 0:
            al_draw_bitmap(parqueo, 0, 0, NULL);
            break;
        case 1:
            al_draw_bitmap(parqueo1, 0, 0, NULL);
            break;
        case 2:
            al_draw_bitmap(parqueo2, 0, 0, NULL);
            break;
        case 3:
            al_draw_bitmap(parqueo3, 0, 0, NULL);
            break;
        case 4:
            al_draw_bitmap(parqueo4, 0, 0, NULL);
            break;
        default:
            break;
        }
        text = to_string(numero);
        cadena = text.c_str();
        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, 75, ALLEGRO_ALIGN_CENTRE, cadena);
        break;
    case 1:
        switch (fondo)
        {
        case 0:
            al_draw_bitmap(parqueo, 0, 0, NULL);
            break;
        case 1:
            al_draw_bitmap(parqueo1, 0, 0, NULL);
            break;
        case 2:
            al_draw_bitmap(parqueo2, 0, 0, NULL);
            break;
        case 3:
            al_draw_bitmap(parqueo3, 0, 0, NULL);
            break;
        case 4:
            al_draw_bitmap(parqueo4, 0, 0, NULL);
            break;
        default:
            break;
        }
        text = to_string(numero);
        cadena = text.c_str();
        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, 75, ALLEGRO_ALIGN_CENTRE, cadena);
        break;
    case 2:
        if (espacio % 2) {
            al_draw_bitmap(parqueoDerecha, 0, 0, NULL);
        }
        else {
            al_draw_bitmap(parqueoIzquierda, 0, 0, NULL);
        }
    default:
        break;
    }
}

int obtenerVehiculo() {
    srand(time(NULL));
    int num = rand() % 2;
    if (num == 0) { // 50% de probabilidad de pintar un vehículo
        return vehiculoRandom();
    }
    else {
        return -1;
    }
}

ALLEGRO_BITMAP* obtenerBitMap(ALLEGRO_BITMAP* redPickup, ALLEGRO_BITMAP* yellowMotorcycle, ALLEGRO_BITMAP* brownTruck, ALLEGRO_BITMAP* redCar1, ALLEGRO_BITMAP* greenCar2, int seleccionador) {
    switch (seleccionador)
    {
    case 0:
        return redPickup;
        break;
    case 1:
        return yellowMotorcycle;
        break;
    case 2:
        return brownTruck;
        break;
    case 3:
        return redCar1;
        break;
    case 4:
        return greenCar2;
        break;
    default:
        break;
    }
}

void moverVehiculo(PtrTVehiculo& StructVehiculo, ALLEGRO_BITMAP* redPickup, ALLEGRO_BITMAP* yellowMotorcycle, ALLEGRO_BITMAP* brownTruck, ALLEGRO_BITMAP* redCar1, ALLEGRO_BITMAP* greenCar2, int CVelocidad, bool& PrimerPasoV, bool& AutoDetenido, bool& puerta, bool& cambio, int vehiculo, bool parqueando, int tipoEstacionamiento, ALLEGRO_BITMAP* parqueoDerecha, ALLEGRO_BITMAP* parqueoIzquierda, bool& cicloParqueo, ALLEGRO_BITMAP* parqueoEstandar, ALLEGRO_FONT* fuente1, int& corredorActual, ALLEGRO_BITMAP* parqueo1, ALLEGRO_BITMAP* parqueo2, ALLEGRO_BITMAP* parqueo3, ALLEGRO_BITMAP* parqueo4, int& fondo, int pisos) {
    if (!parqueando) { // Este if corresponde a cuando el vehículo está en el proceso de parqueo o no, en el else se está parqueando el vehículo
        if (PrimerPasoV) { // Este primer if define cual imagen tendrá el vehículo y el lugar donde debería aparecer, además le asigna una cédula y una placa
            StructVehiculo = new(TVehiculo);
            switch (vehiculo) {
            case 0:
                StructVehiculo->vehiculo = redPickup;
                break;
            case 1:
                StructVehiculo->vehiculo = yellowMotorcycle;
                break;
            case 2:
                StructVehiculo->vehiculo = brownTruck;
                break;
            case 3:
                StructVehiculo->vehiculo = redCar1;
                break;
            case 4:
                StructVehiculo->vehiculo = greenCar2;
                break;
            }
            StructVehiculo->x = 0;
            StructVehiculo->y = 590;
            StructVehiculo->angulo = 0;
            StructVehiculo->cedula = "";
            StructVehiculo->placa = "";
            StructVehiculo->cedula = generarCedula();
            StructVehiculo->placa = generarPlaca();
            PrimerPasoV = false;
        }

        if (StructVehiculo->x <= 263) { // If para avanzar hasta la vuelta que se encuentra enfrente del estacionamiento
            StructVehiculo->x = StructVehiculo->x + CVelocidad;
        }
        else { // Condición cuando se ha alcanzado la entrada del estacionamiento
            if (!puerta) { // puerta se mantiene en false cuando está cerrada
                if (StructVehiculo->y >= 572) {
                    StructVehiculo->y = StructVehiculo->y - CVelocidad;
                    StructVehiculo->angulo = 29.839;
                }
                else {
                    AutoDetenido = true; // Esto es enviado por referencia hacia el exterior de la función para abrir la puerta, cuando se habla la puerta la variable "puerta" tambien será modificada
                }
            }
            else { // Condición cuando la puerta se abre y el vehículo debe entrar al ascensor
                StructVehiculo->y = StructVehiculo->y - CVelocidad;
                if (StructVehiculo->y <= 475) {
                    cambio = true; // Cuando cambio se vuelve true significa que se debe presentar el ascensor
                }
            }

        }
        if (!cambio) { // cambio se refiere a la variable usada para saber cuando se está en el ascensor, el if es cuando no está en el ascensor, mientras que en el else es cuando se ingresa al ascensor
            if (vehiculo == 2) { // Revisa si el vehículo corresponde al camión, porque el tamaño de este es mayor
                if (StructVehiculo->angulo != 0) {
                    al_draw_rotated_bitmap(StructVehiculo->vehiculo, 0, 0, StructVehiculo->x, StructVehiculo->y + 75, StructVehiculo->angulo, NULL);
                }
                else {
                    al_draw_rotated_bitmap(StructVehiculo->vehiculo, 0, 0, StructVehiculo->x, StructVehiculo->y, StructVehiculo->angulo, NULL);
                }
            }
            else {
                al_draw_rotated_bitmap(StructVehiculo->vehiculo, 0, 0, StructVehiculo->x, StructVehiculo->y, StructVehiculo->angulo, NULL);
            }
        }
        else {
            float cx = al_get_bitmap_width(StructVehiculo->vehiculo) / 2;
            float cy = al_get_bitmap_height(StructVehiculo->vehiculo) / 2;
            // cx y cy determinan el centro sobre el que se rotará la imagen
            float dx = StructVehiculo->x;
            float dy;
            // dx y dy corresponde a la ubicación del vehículo
            if (StructVehiculo->y >= 430) { // El if se refiere a cuando el vehículo no ha avanzado lo suficiente dentro del ascensor
                dy = StructVehiculo->y;
            }
            else { // El else es cuando el vehiculo llega al punto deseado y se detiene
                StructVehiculo->y = StructVehiculo->y + CVelocidad;
                dy = StructVehiculo->y;
            }
            // dx y dy son la ubicación donde se dibujará la imagen
            al_draw_scaled_rotated_bitmap(StructVehiculo->vehiculo, cx, cy, dx + 18, dy, 3.5, 3.5, 29.839, 0);
        }
    }
    else {
        float cx = al_get_bitmap_width(StructVehiculo->vehiculo) / 2;
        float cy = al_get_bitmap_height(StructVehiculo->vehiculo) / 2;
        int cantidadCiclos = StructVehiculo->espacio / pisos / 10;
        bool corredorCorrecto = false;
        float angulo = ALLEGRO_PI;
        switch (tipoEstacionamiento) // Switch para ver que tipo de estacionamiento es
        {
        case 0: // Caso en el que son múltiples plantas con N espacios
            if (PrimerPasoV) {
                StructVehiculo->x = 650;
                StructVehiculo->y = 430;
                PrimerPasoV = false;
            }
            if (StructVehiculo->x <= -85) { // Aquí debería meter la función para que se realice una sola vez
                //mostrarVehiculos(redPickup, yellowMotorcycle, brownTruck, redCar1, greenCar2, corredorCorrecto);
                int aux = fondo;
                fondo = fondoRandom(); // Escoge un fondo
                if (aux == fondo) { // Revisa que el nuevo fondo no sea el mismo al anterior
                    if (fondo != 4) {
                        fondo++;
                    }
                    else {
                        fondo--;
                    }
                }
                StructVehiculo->x = 650;
                corredorActual++;
                //cout << "Pasó" << endl;
            }
            if (corredorActual == cantidadCiclos) { // Cuando se da este caso se debe enviar StructVehiculo->espacio a la función obtenerEspacio, debido a que es en este punto cuando el vehículo debe parquearse
                corredorCorrecto = true;
                fondo = 0;
                /*
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡LLEGO!!!!!!!!!!!!!!!!" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                */
                int espacioSeleccionado = obtenerEspacio(StructVehiculo->espacio);
                bool alineado = false;
                switch (espacioSeleccionado) // Casos de donde se parqueará el vehiculo
                {
                case 0:
                    if (StructVehiculo->x <= 50) {
                        alineado = true;
                    }
                    break;
                case 1:
                    if (StructVehiculo->x <= 50) {
                        alineado = true;
                    }
                    break;
                case 2:
                    if (StructVehiculo->x <= 160) {
                        alineado = true;
                    }
                    break;
                case 3:
                    if (StructVehiculo->x <= 160) {
                        alineado = true;
                    }
                    break;
                case 4:
                    if (StructVehiculo->x <= 275) {
                        alineado = true;
                    }
                    break;
                case 5:
                    if (StructVehiculo->x <= 275) {
                        alineado = true;
                    }
                    break;
                case 6:
                    if (StructVehiculo->x <= 390) {
                        alineado = true;
                    }
                    break;
                case 7:
                    if (StructVehiculo->x <= 390) {
                        alineado = true;
                    }
                    break;
                case 8:
                    if (StructVehiculo->x <= 500) {
                        alineado = true;
                    }
                    break;
                case 9:
                    if (StructVehiculo->x <= 500) {
                        alineado = true;
                    }
                    break;
                default:
                    break;
                }
                if (!alineado) {
                    StructVehiculo->x = StructVehiculo->x - CVelocidad;
                }
                else {
                    if (espacioSeleccionado % 2 == 0) {
                        StructVehiculo->y = StructVehiculo->y - CVelocidad;
                        angulo = 29.839;
                        if (StructVehiculo->y <= 300) {
                            //                            StructVehiculo->y = StructVehiculo->y + CVelocidad;
                            cicloParqueo = true;
                        }
                    }
                    else {
                        StructVehiculo->y = StructVehiculo->y + CVelocidad;
                        angulo = 29.839 + ALLEGRO_PI;
                        if (StructVehiculo->y >= 625) {
                            //                            StructVehiculo->y = StructVehiculo->y - CVelocidad;
                            cicloParqueo = true;
                        }
                    }
                }
            }
            else {
                StructVehiculo->x = StructVehiculo->x - CVelocidad;
                //cout << cantidadCiclos << endl;
            }
            /*al_draw_bitmap(parqueoEstandar, 0, 0, NULL);
            al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, 75, ALLEGRO_ALIGN_CENTRE, "58");*/
            mostrarTiposEstacionamientos(parqueoEstandar, parqueo1, parqueo2, parqueo3, parqueo4, parqueoIzquierda, parqueoDerecha, fuente1, fondo, corredorActual + 1, 0, StructVehiculo->espacio);

            al_draw_scaled_rotated_bitmap(StructVehiculo->vehiculo, cx, cy, StructVehiculo->x, StructVehiculo->y, 1.4, 1.4, angulo, NULL);
            //cout << StructVehiculo->x << endl; //264
            //cout << StructVehiculo->y << endl; //430
            break;
        case 1: // Caso en el que es una sola planta con N espacios
            if (PrimerPasoV) {
                StructVehiculo->x = 650;
                StructVehiculo->y = 430;
                PrimerPasoV = false;
            }
            if (StructVehiculo->x <= -85) { // Aquí debería meter la función para que se realice una sola vez
                //mostrarVehiculos(redPickup, yellowMotorcycle, brownTruck, redCar1, greenCar2, corredorCorrecto);
                int aux = fondo;
                fondo = fondoRandom(); // Escoge un fondo
                if (aux == fondo) { // Revisa que el nuevo fondo no sea el mismo al anterior
                    if (fondo != 4) {
                        fondo++;
                    }
                    else {
                        fondo--;
                    }
                }
                StructVehiculo->x = 650;
                corredorActual++;
                //cout << "Pasó" << endl;
            }
            if (corredorActual == cantidadCiclos) { // Cuando se da este caso se debe enviar StructVehiculo->espacio a la función obtenerEspacio, debido a que es en este punto cuando el vehículo debe parquearse
                corredorCorrecto = true;
                fondo = 0;
                /*
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡LLEGO!!!!!!!!!!!!!!!!" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                */
                int espacioSeleccionado = obtenerEspacio(StructVehiculo->espacio);
                bool alineado = false;
                switch (espacioSeleccionado) // Casos de donde se parqueará el vehiculo
                {
                case 0:
                    if (StructVehiculo->x <= 50) {
                        alineado = true;
                    }
                    break;
                case 1:
                    if (StructVehiculo->x <= 50) {
                        alineado = true;
                    }
                    break;
                case 2:
                    if (StructVehiculo->x <= 160) {
                        alineado = true;
                    }
                    break;
                case 3:
                    if (StructVehiculo->x <= 160) {
                        alineado = true;
                    }
                    break;
                case 4:
                    if (StructVehiculo->x <= 275) {
                        alineado = true;
                    }
                    break;
                case 5:
                    if (StructVehiculo->x <= 275) {
                        alineado = true;
                    }
                    break;
                case 6:
                    if (StructVehiculo->x <= 390) {
                        alineado = true;
                    }
                    break;
                case 7:
                    if (StructVehiculo->x <= 390) {
                        alineado = true;
                    }
                    break;
                case 8:
                    if (StructVehiculo->x <= 500) {
                        alineado = true;
                    }
                    break;
                case 9:
                    if (StructVehiculo->x <= 500) {
                        alineado = true;
                    }
                    break;
                default:
                    break;
                }
                if (!alineado) {
                    StructVehiculo->x = StructVehiculo->x - CVelocidad;
                }
                else {
                    if (espacioSeleccionado % 2 == 0) {
                        StructVehiculo->y = StructVehiculo->y - CVelocidad;
                        angulo = 29.839;
                        if (StructVehiculo->y <= 300) {
                            //                            StructVehiculo->y = StructVehiculo->y + CVelocidad;
                            cicloParqueo = true;
                        }
                    }
                    else {
                        StructVehiculo->y = StructVehiculo->y + CVelocidad;
                        angulo = 29.839 + ALLEGRO_PI;
                        if (StructVehiculo->y >= 625) {
                            //                            StructVehiculo->y = StructVehiculo->y - CVelocidad;
                            cicloParqueo = true;
                        }
                    }
                }
            }
            else {
                StructVehiculo->x = StructVehiculo->x - CVelocidad;
                //cout << cantidadCiclos << endl;
            }
            /*al_draw_bitmap(parqueoEstandar, 0, 0, NULL);
            al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, 75, ALLEGRO_ALIGN_CENTRE, "58");*/
            mostrarTiposEstacionamientos(parqueoEstandar, parqueo1, parqueo2, parqueo3, parqueo4, parqueoIzquierda, parqueoDerecha, fuente1, fondo, corredorActual + 1, 0, StructVehiculo->espacio);

            al_draw_scaled_rotated_bitmap(StructVehiculo->vehiculo, cx, cy, StructVehiculo->x, StructVehiculo->y, 1.4, 1.4, angulo, NULL);
            //cout << StructVehiculo->x << endl; //264
            //cout << StructVehiculo->y << endl; //430
            break;
        case 2: // Caso de torre izq y der
            if (PrimerPasoV) { // TOTALMENTE NECESARIO, si no se pone el vehículo se pinta una y otra vez en el mismo lugar
                if (StructVehiculo->espacio % 2) { // Verifica si el espacio que se le asigna es divisible entre 2, en caso de que sí se imprime el vehículo al lado izquierdo de la pantalla
                    StructVehiculo->x = 150;
                }
                else { // En caso de que el espacio no sea divisible entre 2 se imprime el vehículo al lado derecho
                    StructVehiculo->x = 450;
                }
                StructVehiculo->angulo = 29.839;
                PrimerPasoV = false;
            }
            StructVehiculo->y = 350;
            mostrarTiposEstacionamientos(parqueoEstandar, parqueo1, parqueo2, parqueo3, parqueo4, parqueoIzquierda, parqueoDerecha, fuente1, fondo, 1, 2, StructVehiculo->espacio);
            if (StructVehiculo->espacio % 2) { // Si el vehículo es pintado a la izquierda de la pantalla se aumenta el valor de x
                //                float cx = al_get_bitmap_width(StructVehiculo->vehiculo) / 2;
                //                float cy = al_get_bitmap_height(StructVehiculo->vehiculo) / 2;
                if (StructVehiculo->x >= 370) {
                    StructVehiculo->x = StructVehiculo->x + CVelocidad;
                    /*cout << "Aumenta ";
                    cout << StructVehiculo->x << endl;*/
                }
                else {
                    cicloParqueo = true;
                }
                //al_draw_bitmap(parqueoDerecha, 0, 0, NULL);
                al_draw_scaled_rotated_bitmap(StructVehiculo->vehiculo, cx, cy, StructVehiculo->x, StructVehiculo->y, 2.5, 2.5, StructVehiculo->angulo, 0);
            }
            else { // Si el vehículo es pintado a la derecha de la pantalla se disminuye el valor de x
                //               float cx = al_get_bitmap_width(StructVehiculo->vehiculo) / 2;
                //               float cy = al_get_bitmap_height(StructVehiculo->vehiculo) / 2;
                if (StructVehiculo->x <= 130) {
                    StructVehiculo->x = StructVehiculo->x - CVelocidad;
                    /*cout << "Disminuye ";
                    cout << StructVehiculo->x << endl;*/
                }
                else {
                    cicloParqueo = true;
                }
                //al_draw_bitmap(parqueoIzquierda, 0, 0, NULL);
                al_draw_scaled_rotated_bitmap(StructVehiculo->vehiculo, cx, cy, StructVehiculo->x, StructVehiculo->y, 2.5, 2.5, StructVehiculo->angulo, 0);
            }
            break;
        }
    }

}

void mostrarAscensor(ALLEGRO_BITMAP* ascensor0, ALLEGRO_BITMAP* ascensor1, ALLEGRO_BITMAP* ascensor2, ALLEGRO_BITMAP* ascensor3, ALLEGRO_BITMAP* ascensor4,
    ALLEGRO_BITMAP* ascensor5, ALLEGRO_BITMAP* ascensor6, ALLEGRO_BITMAP* ascensor7, ALLEGRO_BITMAP* ascensor8, double& comparador, int& piso, int& contAscensor, double ciclos, bool& parqueando, bool& primerPasoV)
{
    if (ciclos == 1.0) {
        parqueando = true;
        return;
    }
    if (contAscensor % 50 == 0) {
        piso++;
        if (piso >= 9) {
            piso = 0;
            comparador++;
        }
    }
    switch (piso)
    {
    case 0:
        al_draw_bitmap(ascensor0, 0, 0, NULL);
        break;
    case 1:
        al_draw_bitmap(ascensor1, 0, 0, NULL);
        break;
    case 2:
        al_draw_bitmap(ascensor2, 0, 0, NULL);
        break;
    case 3:
        al_draw_bitmap(ascensor3, 0, 0, NULL);
        break;
    case 4:
        al_draw_bitmap(ascensor4, 0, 0, NULL);
        break;
    case 5:
        al_draw_bitmap(ascensor5, 0, 0, NULL);
        break;
    case 6:
        al_draw_bitmap(ascensor6, 0, 0, NULL);
        break;
    case 7:
        al_draw_bitmap(ascensor7, 0, 0, NULL);
        break;
    case 8:
        al_draw_bitmap(ascensor8, 0, 0, NULL);
        break;
    }

    contAscensor++;
    if (comparador == ciclos) {
        parqueando = true;
        primerPasoV = true;
    }
}

int main()
{
    int pisos = 5; // Cantidad de pisos del estacionamiento
    int espaciosXPiso = 12; // Cantidad de espacios por piso
    int cantidadDeVehiculos = 2; // Cantidad de vehículos que entrarán al estacionamiento
    int tipoEstacionamiento = 0; // Valor int para el tipo de estacionamiento (0 estacionamiento de múltiples pisos, 1 estacionamiento de un piso, 2 estacionamiento izquierda derecha)
    list<int> espacios_disponibles; // Lista para los espacios disponibles
    list<int> espacios_reservados; // Lista para los espacios reservados

    const float FPS = 60.0; // Constante usada para definir la cantidad de imágenes mostradas por segundo
    const float reservados = 0.15; // Constante para definir la cantidad de espacios reservados

    configurarEstacionamiento(pisos, espaciosXPiso, cantidadDeVehiculos, tipoEstacionamiento, reservados, espacios_disponibles, espacios_reservados); // Esto se realiza por si alguien quiere ejecutar directamente sin ingresar valores

    ALLEGRO_DISPLAY* Display; // Crea la pantalla inicial

    if (!al_init()) // Verifica que allegro haya inicializado correctamente
    {
        cout << "Allegro couldn´t initialize" << endl;
        return 0;
    }

    al_set_new_display_flags(ALLEGRO_WINDOWED); // Establece "banderas" para la pantalla, las banderas básicamente son características
    Display = al_create_display(anchoPantalla, altoPantalla); // Crea la pantalla según el ancho y alto especificados
    al_set_window_title(Display, "Background Testing"); // Le da un título a la pantalla inicial

    if (!Display) // Verifica si la pantalla inicial fue creada de manera correcta
    {
        cout << "Window 'Display' didn't initialize" << endl;
        return 0;
    }

    al_init_image_addon(); // Inicializa los métodos sobre imágenes de allegro
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(1);

    ALLEGRO_FONT* fuente1 = al_load_font("Orbitron_Black.ttf", 36, NULL); // Para utilizar esta línea se debe descargar la fuente de internet, con formato "Archivo de fuente TrueType", 
    ALLEGRO_FONT* fuente2 = al_load_font("Orbitron_Black.ttf", 90, NULL);
    ALLEGRO_FONT* fuente3 = al_load_font("Orbitron_Black.ttf", 24, NULL);

    ALLEGRO_BITMAP* imagenMenu = al_load_bitmap("menu.png"); // Se carga la imagen del menú inicial
    ALLEGRO_BITMAP* imagenConfig = al_load_bitmap("fondoConfig.png"); // Se carga la imagen de fondo de configuraciones
    ALLEGRO_BITMAP* Background1 = al_load_bitmap("Parkeo1.png"); // Carga una imagen del fondo
    ALLEGRO_BITMAP* Background2 = al_load_bitmap("Parkeo2.png"); // Carga una imagen del fondo
    ALLEGRO_BITMAP* Background3 = al_load_bitmap("Parkeo3.png"); // Carga una imagen del fondo
    ALLEGRO_BITMAP* Background4 = al_load_bitmap("Parkeo4.png"); // Carga una imagen del fondo
    ALLEGRO_BITMAP* elevator0 = al_load_bitmap("ascensor/ascensor01.png"); // Carga el primer frame del ascensor
    ALLEGRO_BITMAP* elevator1 = al_load_bitmap("ascensor/ascensor1.png"); // Carga el segundo frame del ascensor
    ALLEGRO_BITMAP* elevator2 = al_load_bitmap("ascensor/ascensor2.png"); // Carga el tercer frame del ascensor
    ALLEGRO_BITMAP* elevator3 = al_load_bitmap("ascensor/ascensor3.png"); // Carga el cuarto frame del ascensor
    ALLEGRO_BITMAP* elevator4 = al_load_bitmap("ascensor/ascensor4.png"); // Carga el quinto frame del ascensor
    ALLEGRO_BITMAP* elevator5 = al_load_bitmap("ascensor/ascensor5.png"); // Carga el sexto frame del ascensor
    ALLEGRO_BITMAP* elevator6 = al_load_bitmap("ascensor/ascensor6.png"); // Carga el séptimo frame del ascensor
    ALLEGRO_BITMAP* elevator7 = al_load_bitmap("ascensor/ascensor7.png"); // Carga el octavo frame del ascensor
    ALLEGRO_BITMAP* elevator8 = al_load_bitmap("ascensor/ascensor8.png"); // Carga el noveno frame del ascensor
    ALLEGRO_BITMAP* espacioDerecha = al_load_bitmap("izquierda_derecha/espacioDerecha.png"); // Se carga la imagen del espacio del parqueo a la derecha
    ALLEGRO_BITMAP* espacioIzquierda = al_load_bitmap("izquierda_derecha/espacioIzquierda.png"); // Se carga la imagen del espacio del parqueo a la izquierda
    ALLEGRO_BITMAP* parqueoEstandar = al_load_bitmap("izquierda_derecha/parqueoEstandar.png"); // Se carga la imagen del parqueo con múltiples espacios, necesario para el parqueo de un piso o el de múltiples pisos
    ALLEGRO_BITMAP* parqueoEstandar1 = al_load_bitmap("izquierda_derecha/parqueoEstandar1.png");
    ALLEGRO_BITMAP* parqueoEstandar2 = al_load_bitmap("izquierda_derecha/parqueoEstandar2.png");
    ALLEGRO_BITMAP* parqueoEstandar3 = al_load_bitmap("izquierda_derecha/parqueoEstandar3.png");
    ALLEGRO_BITMAP* parqueoEstandar4 = al_load_bitmap("izquierda_derecha/parqueoEstandar4.png");
    ALLEGRO_BITMAP* redPickup = al_load_bitmap("redPickup.png"); // Carga la imagen de la camioneta roja
    ALLEGRO_BITMAP* yellowMotorcycle = al_load_bitmap("yellowMotorcycle.png"); // Carga la imagen de una motocicleta amarilla
    ALLEGRO_BITMAP* brownTruck = al_load_bitmap("ligthBrownTruck.png"); // Carga la imagen de un camion café
    ALLEGRO_BITMAP* redCar1 = al_load_bitmap("redCar1.png"); // Carga la imagen de un automovil rojo
    ALLEGRO_BITMAP* greenCar2 = al_load_bitmap("greenCar2.png"); // Carga la imagen de un automovil verde
    ALLEGRO_SAMPLE* musica = al_load_sample("backgroundMusic.wav");

    ALLEGRO_TIMER* TimerMenu = al_create_timer(1.0 / FPS); // Timer usado en el menú inicial
    ALLEGRO_TIMER* PrimerTimer = al_create_timer(1.0 / FPS); // Timer encargado de manejar el caso en el que el vehículo esté fuera del estacionamiento
    ALLEGRO_TIMER* SegundoTimer = al_create_timer(1.0 / FPS); // Timer que maneja el caso en el que el vehículo se encuentra en el ascensor

    ALLEGRO_SAMPLE_INSTANCE* instanciaMusica = al_create_sample_instance(musica);

    al_set_sample_instance_playmode(instanciaMusica, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(instanciaMusica, al_get_default_mixer());

    bool done = false; // Crea una variable booleana que se usará para un ciclo infinito
    bool menu = true; // Variable booleana para saber cuando se debe estar en el menú
    bool vehiculoActivo = false; // Variable booleana usada para saber si hay un vehículo pintado
    bool primerPaso = true; // Variable booleana usada para saber si el vehículo acaba de ser pintado
    bool autoDetenido = false; // Variable booleana que se activará cuando el vehículo se haya detenido
    bool puerta = false; // Variable que verificará si la puerta está cerrada
    bool change = false; // Variable que define cuando se necesita realizar un cambio de escena
    bool parking = false; // Variable que se activa cuando se está en el proceso de parquear
    bool cicloParqueo = false; // Variable que cuando sea true va a devolver todos los valores a los datos iniciales ** DE SUMA IMPORTANCIA **
    bool contadorUnico = true; // Contador único para que solo se llame el método asignarEspacio una sola vez
    bool configuraciones = false; // Variable booleana que se activa cuando se está en el menú de configuracioes
    bool tipoSeleccionado = false; // Variable booleana que se activa cuando ya se ha seleccionado el tipo de estacionamiento
    bool pisosSeleccionado = false; // Variable booleana que se activa cuando ya se ha seleccionado la cantidad de pisos del estacionamiento
    bool espaciosXPisoSeleccionado = false; // Variable booleana que se activa cuando ya se ha seleccionado la cantidad de espacios por piso del estacionamiento
    bool cantidadVehiculosSeleccionada = false; // Variable booleana que se activa cuando ya se ha seleccionado la cantidad de vehiculos por ingresar
    bool informacion = false; // Variable booleana para saber cuando se debe mostrar la pantalla de información
    int vehiculo; // Variable de tipo int usada para saber cual vehículo pintar
    int velocidad = 2; // Velocidad con la que los autos avanzan
    int fondo = 0; // Variable de tipo int para saber cual animación realizar
    int contador = 0; // Variable que será usada para determinar la cantidad de frames que han pasado
    int contadorAscensor = 0; // Variable para contar los frames del ascensor
    int mouse_x = 0; // Variable que determina la posición del mouse en el eje x
    int mouse_y = 0; // Variable que determina la posición del mouse en el eje y
    int pisoActual = 0; // Variable para identificar en que piso se encuentra el ascensor
    int corredorActual = 0; // Variable que hace referencia al parqueo, sirve para saber cuantas veces el vehículo debe andar por el estacionamiento
    int fondoParqueo = 0; // Variable para pintar un fondo u otro
    int numericValue = 0; // Variable para almacenar el texto ingresado como número
    int vehiculosParqueados = 0; // Variable que lleva la cuenta de cuantos vehículos han ingresado
    string inputTexto; // Variable para almacenar el texto ingresado como string (cantidad de pisos)
    string inputTexto2; // Variable para almacenar el texto ingresado como string (cantidad de espacios por piso)
    string inputTexto3; // Variable para almacenar el texto ingresado como string (vehiculos por ingresar)
    double comparador = 0; // Variable que permitirá comparar si el ciclo del ascensor ha terminado
    PtrTVehiculo StrVehiculo = new(TVehiculo); // Struct de tipo TVehiculo que permitirá guardar al vehículo actual

    ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue(); // Crea una cola de eventos que guardará los timers

    al_register_event_source(colaEventos, al_get_timer_event_source(TimerMenu)); // Se registra el timer del menu en la cola, este timer será el encargado de manejar el menu
    al_register_event_source(colaEventos, al_get_timer_event_source(PrimerTimer)); // Se registra el primer timer en la cola, este timer será el encargado de actualizar la pantalla
    al_register_event_source(colaEventos, al_get_timer_event_source(SegundoTimer)); // Se registra el segundo timer en la cola, este timer será el encargado de actualizar el ascensor
    al_register_event_source(colaEventos, al_get_mouse_event_source()); // Registra el movimiento del mouse como un evento en colaEventos
    al_register_event_source(colaEventos, al_get_keyboard_event_source()); // Registra las acciones del teclado como un evento en colaEventos

    al_play_sample_instance(instanciaMusica);

    al_start_timer(TimerMenu); // Inicializa el timer antes del ciclo
    al_start_timer(PrimerTimer); // Inicializa un timer antes del ciclo
    al_start_timer(SegundoTimer); // Inicializa un segundo timer antes del ciclo

    while (!done) // Se crea el ciclo principal del simulador
    {
        ALLEGRO_EVENT eventos; // Se crea una variable dr tipo ALLEGRO_EVENT para poder analizar el evento ocurrido

        al_wait_for_event(colaEventos, &eventos); // Se utiliza la función al_wait_for_event() para que la misma mande una señal cuando algo ha cambiado en la cola de eventos (colaEventos), lo que se haya realizado estará en eventos
        if (menu) {
            if (!informacion) {
                if (!configuraciones) {
                    if (eventos.type == ALLEGRO_EVENT_MOUSE_AXES) {
                        mouse_x = eventos.mouse.x;
                        mouse_y = eventos.mouse.y;
                    }

                    if (eventos.timer.source == TimerMenu) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(imagenMenu, 0, 0, anchoPantalla, altoPantalla, 0, 0, anchoPantalla, altoPantalla, 0);
                        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (250.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SIMULAR");
                        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (320.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CONFIGURAR");
                        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (390.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "ACERCA DE");
                        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (460.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SALIR");
                    }

                    if ((mouse_x >= anchoPantalla / 2 - 102 && mouse_x <= anchoPantalla / 2 + 102) && (mouse_y >= (altoPantalla * 250.0 / 768.0) && mouse_y <= (altoPantalla * 280.0 / 768.0))) {
                        al_draw_text(fuente1, al_map_rgb(250, 250, 20), anchoPantalla / 2, (altoPantalla * (250.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SIMULAR");
                        if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                            menu = false;
                        }
                    }

                    if ((mouse_x >= anchoPantalla / 2 - 135 && mouse_x <= anchoPantalla / 2 + 135) && (mouse_y >= (altoPantalla * 320.0 / 768.0) && mouse_y <= (altoPantalla * 350.0 / 768.0))) {
                        al_draw_text(fuente1, al_map_rgb(250, 250, 20), anchoPantalla / 2, (altoPantalla * (320.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CONFIGURAR");
                        if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                            configuraciones = true;
                        }
                    }

                    if ((mouse_x >= anchoPantalla / 2 - 120 && mouse_x <= anchoPantalla / 2 + 120) && (mouse_y >= (altoPantalla * (390.0 / 768.0)) && mouse_y <= (altoPantalla * (420.0 / 768.0)))) {
                        al_draw_text(fuente1, al_map_rgb(250, 250, 20), anchoPantalla / 2, (altoPantalla * (390.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "ACERCA DE");
                        if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                            informacion = true;
                        }
                    }

                    if ((mouse_x >= anchoPantalla / 2 - 65 && mouse_x <= anchoPantalla / 2 + 65) && (mouse_y >= (altoPantalla * (460.0 / 768.0)) && mouse_y <= (altoPantalla * (490.0 / 768.0)))) {
                        al_draw_text(fuente1, al_map_rgb(250, 250, 20), anchoPantalla / 2, (altoPantalla * (460.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SALIR");
                        if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                            done = true;
                        }
                    }

                    al_flip_display();
                }
                else {
                    if (eventos.type == ALLEGRO_EVENT_MOUSE_AXES) {
                        mouse_x = eventos.mouse.x;
                        mouse_y = eventos.mouse.y;
                    }
                    if (eventos.timer.source == TimerMenu) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_scaled_bitmap(imagenConfig, 0, 0, anchoPantalla, altoPantalla, 0, 0, anchoPantalla, altoPantalla, 0);
                        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (150.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "TIPO DE PARQUEO");
                        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (320.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "VARIOS PISOS");
                        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (390.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "UN SOLO PISO");
                        al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (460.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "IZQUIERDA - DERECHA");
                    }
                    if (!tipoSeleccionado) { // Si el tipo de estacionamiento no ha sido seleccionado
                        if ((mouse_x >= anchoPantalla / 2 - 155 && mouse_x <= anchoPantalla / 2 + 155) && (mouse_y >= (altoPantalla * 320.0 / 768.0) && mouse_y <= (altoPantalla * 350.0 / 768.0))) {
                            al_draw_text(fuente1, al_map_rgb(250, 250, 20), anchoPantalla / 2, (altoPantalla * (320.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "VARIOS PISOS");
                            if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                                tipoEstacionamiento = 0;
                                tipoSeleccionado = true;
                                //cout << "a" << endl;
                            }
                        }

                        if ((mouse_x >= anchoPantalla / 2 - 145 && mouse_x <= anchoPantalla / 2 + 145) && (mouse_y >= (altoPantalla * (390.0 / 768.0)) && mouse_y <= (altoPantalla * (420.0 / 768.0)))) {
                            al_draw_text(fuente1, al_map_rgb(250, 250, 20), anchoPantalla / 2, (altoPantalla * (390.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "UN SOLO PISO");
                            if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                                tipoEstacionamiento = 1;
                                pisos = 1;
                                tipoSeleccionado = true;
                                pisosSeleccionado = true; // Se pone en true debido a que al ser el estacionamiento de un solo piso, la cantidad de pisos será 1
                                //cout << "b" << endl;
                            }
                        }

                        if ((mouse_x >= anchoPantalla / 2 - 235 && mouse_x <= anchoPantalla / 2 + 235) && (mouse_y >= (altoPantalla * (460.0 / 768.0)) && mouse_y <= (altoPantalla * (490.0 / 768.0)))) {
                            al_draw_text(fuente1, al_map_rgb(250, 250, 20), anchoPantalla / 2, (altoPantalla * (460.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "IZQUIERDA - DERECHA");
                            if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                                tipoEstacionamiento = 2;
                                tipoSeleccionado = true;
                                //cout << "c" << endl;
                            }
                        }
                    }
                    else {
                        if (eventos.timer.source == TimerMenu) {
                            al_clear_to_color(al_map_rgb(0, 0, 0));
                            al_draw_scaled_bitmap(imagenConfig, 0, 0, anchoPantalla, altoPantalla, 0, 0, anchoPantalla, altoPantalla, 0);
                            al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (150.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CANTIDAD DE PISOS");
                            al_draw_textf(fuente1, al_map_rgb(255, 255, 255), anchoPantalla / 2, altoPantalla / 2, ALLEGRO_ALIGN_CENTER, "Pisos: %s", inputTexto.c_str());
                            al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (500.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "PRESIONE ENTER");
                            al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (550.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CUANDO HAYA");
                            al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (600.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SELECCIONADO");
                        }
                        if (!pisosSeleccionado) { // Si la catidad de pisos no ha sido seleccionada
                            if (eventos.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (eventos.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                    // Si se presiona la tecla de retroceso (backspace), eliminar el último dígito
                                    if (!inputTexto.empty()) {
                                        inputTexto.pop_back();
                                    }
                                }
                                else if (eventos.keyboard.keycode >= ALLEGRO_KEY_0 && eventos.keyboard.keycode <= ALLEGRO_KEY_9) {
                                    // Si se presiona una tecla numérica, agregar el dígito a la cadena de entrada
                                    inputTexto += to_string(eventos.keyboard.keycode - ALLEGRO_KEY_0);
                                }
                                if (eventos.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                    if (!inputTexto.empty()) {
                                        pisos = stoi(inputTexto); // Actualizar el valor numérico usando la función stoi (string to integer)
                                        if (pisos > 0) {
                                            pisosSeleccionado = true;
                                            /*if (tipoEstacionamiento == 2) {
                                                espaciosXPiso =
                                            }*/
                                        }
                                        else {
                                            cout << "La cantidad de pisos debe ser mayor a 0" << endl;
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            if (eventos.timer.source == TimerMenu) {
                                al_clear_to_color(al_map_rgb(0, 0, 0));
                                al_draw_scaled_bitmap(imagenConfig, 0, 0, anchoPantalla, altoPantalla, 0, 0, anchoPantalla, altoPantalla, 0);
                                al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (150.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CANTIDAD DE ESPACIOS");
                                al_draw_textf(fuente1, al_map_rgb(255, 255, 255), anchoPantalla / 2, altoPantalla / 2, ALLEGRO_ALIGN_CENTER, "Espacios: %s", inputTexto2.c_str());
                                al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (500.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "PRESIONE ENTER");
                                al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (550.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CUANDO HAYA");
                                al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (600.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SELECCIONADO");
                            }
                            if (!espaciosXPisoSeleccionado) {
                                if (tipoEstacionamiento == 2) {
                                    espaciosXPiso = pisos * 2;
                                    espaciosXPisoSeleccionado = true;
                                    /*
                                    printf("Tipo estacionamiento: %d\n", tipoEstacionamiento);
                                    printf("Pisos: %i\n", pisos);
                                    printf("Espacios: %d\n", espaciosXPiso);
                                    */
                                }
                                if (eventos.type == ALLEGRO_EVENT_KEY_DOWN) {
                                    if (eventos.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                        // Si se presiona la tecla de retroceso (backspace), eliminar el último dígito
                                        if (!inputTexto2.empty()) {
                                            inputTexto2.pop_back();
                                        }
                                    }
                                    else if (eventos.keyboard.keycode >= ALLEGRO_KEY_0 && eventos.keyboard.keycode <= ALLEGRO_KEY_9) {
                                        // Si se presiona una tecla numérica, agregar el dígito a la cadena de entrada
                                        inputTexto2 += to_string(eventos.keyboard.keycode - ALLEGRO_KEY_0);
                                    }
                                    if (eventos.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                        if (!inputTexto2.empty()) {
                                            espaciosXPiso = stoi(inputTexto2); // Actualizar el valor numérico usando la función stoi (string to integer)
                                            if (espaciosXPiso > 0) {
                                                espaciosXPisoSeleccionado = true;
                                                /*configuraciones = false;
                                                tipoSeleccionado = false;
                                                pisosSeleccionado = false;
                                                espaciosXPisoSeleccionado = false;
                                                printf("Tipo estacionamiento: %d\n", tipoEstacionamiento);
                                                printf("Pisos: %i\n", pisos);
                                                printf("Espacios: %d\n", espaciosXPiso);*/
                                            }
                                            else {
                                                cout << "La cantidad de espacios por pisos debe ser mayor a 0" << endl;
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                if (eventos.timer.source == TimerMenu) {
                                    al_clear_to_color(al_map_rgb(0, 0, 0));
                                    al_draw_scaled_bitmap(imagenConfig, 0, 0, anchoPantalla, altoPantalla, 0, 0, anchoPantalla, altoPantalla, 0);
                                    al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (150.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CANTIDAD DE VEHICULOS");
                                    al_draw_textf(fuente1, al_map_rgb(255, 255, 255), anchoPantalla / 2, altoPantalla / 2, ALLEGRO_ALIGN_CENTER, "Vehiculos: %s", inputTexto3.c_str());
                                    al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (500.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "PRESIONE ENTER");
                                    al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (550.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CUANDO HAYA");
                                    al_draw_text(fuente1, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (600.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SELECCIONADO");
                                }
                                if (!cantidadVehiculosSeleccionada) { // Si la catidad de vehiculos no ha sido seleccionada
                                    if (eventos.type == ALLEGRO_EVENT_KEY_DOWN) {
                                        if (eventos.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                            // Si se presiona la tecla de retroceso (backspace), eliminar el último dígito
                                            if (!inputTexto3.empty()) {
                                                inputTexto3.pop_back();
                                            }
                                        }
                                        else if (eventos.keyboard.keycode >= ALLEGRO_KEY_0 && eventos.keyboard.keycode <= ALLEGRO_KEY_9) {
                                            // Si se presiona una tecla numérica, agregar el dígito a la cadena de entrada
                                            inputTexto3 += to_string(eventos.keyboard.keycode - ALLEGRO_KEY_0);
                                        }
                                        if (eventos.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                            if (!inputTexto3.empty()) {
                                                cantidadDeVehiculos = stoi(inputTexto3); // Actualizar el valor numérico usando la función stoi (string to integer)
                                                if (cantidadDeVehiculos > 0) {
                                                    int total_espacios = pisos * espaciosXPiso;
                                                    int espacios_reservados_total = static_cast<int>(total_espacios * reservados); // 15% de los espacios totales
                                                    if (cantidadDeVehiculos > total_espacios - espacios_reservados_total) {
                                                        cout << "La cantidad de vehiculos a ingresar es mayor que los espacios disponibles (hay espacios reservados). Por favor, ingrese una cantidad menor." << endl;
                                                    }
                                                    else {
                                                        configuraciones = false;
                                                        tipoSeleccionado = false;
                                                        pisosSeleccionado = false;
                                                        espaciosXPisoSeleccionado = false;
                                                        cantidadVehiculosSeleccionada = false;
                                                        printf("Tipo estacionamiento: %d\n", tipoEstacionamiento);
                                                        printf("Pisos: %i\n", pisos);
                                                        printf("Espacios: %d\n", espaciosXPiso);
                                                        printf("Vehiculos: %d\n", cantidadDeVehiculos);
                                                        configurarEstacionamiento(pisos, espaciosXPiso, cantidadDeVehiculos, tipoEstacionamiento, reservados, espacios_disponibles, espacios_reservados);
                                                    }
                                                }
                                                else {
                                                    cout << "La cantidad de espacios por pisos debe ser mayor a 0" << endl;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    al_flip_display();
                }
            }
            else {
                if (eventos.type == ALLEGRO_EVENT_MOUSE_AXES) {
                    mouse_x = eventos.mouse.x;
                    mouse_y = eventos.mouse.y;
                }
                if (eventos.timer.source == TimerMenu) {
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_scaled_bitmap(imagenConfig, 0, 0, anchoPantalla, altoPantalla, 0, 0, anchoPantalla, altoPantalla, 0);
                    al_draw_text(fuente3, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (150.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "ACERCA DE");
                    al_draw_text(fuente3, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (250.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "ESTE PROYECTO FUE REALIZADO POR");
                    al_draw_text(fuente3, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (290.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "LOS ESTUDIANTES JOSEPH ARRIETA");
                    al_draw_text(fuente3, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (330.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "Y ARTURO CHAVARRIA PARA EL");
                    al_draw_text(fuente3, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (370.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "CURSO ESTRUCTURAS DE DATOS");
                    al_draw_text(fuente3, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (450.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "ULTIMA ACTUALIZACION");
                    al_draw_text(fuente3, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (480.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "13/05/2024");
                    al_draw_text(fuente3, al_map_rgb(250, 250, 250), anchoPantalla / 2, (altoPantalla * (570.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "ATRAS");
                }

                if ((mouse_x >= anchoPantalla / 2 - 55 && mouse_x <= anchoPantalla / 2 + 55) && (mouse_y >= (altoPantalla * (570.0 / 768.0)) && mouse_y <= (altoPantalla * (600.0 / 768.0)))) {
                    al_draw_text(fuente3, al_map_rgb(250, 250, 20), anchoPantalla / 2, (altoPantalla * (570.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "ATRAS");
                    if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                        informacion = false;
                    }
                }

                al_flip_display();
            }


        }

        if (eventos.type == ALLEGRO_EVENT_TIMER) {
            if (!menu) {
                if (eventos.timer.source == PrimerTimer) { // Revisa si la fuente (source) que produce la señal de cambio es el primer timer (PrimerTimer)
                    if (!change) { // Variable que cubre todo el ciclo de cuando se está fuera del estacionamiento, cuando esta cambia es porque se cambia de escena
                        if (autoDetenido) { // Verfica si el auto está detenido enfrente del estacionamiento
                            if (contador % 60 == 0) { // Contador para que la animación de abrir la puerta sea menos rápida
                                if (fondo == 3) { // Verifica si la imagen que se muestra en el fondo corresponde al tercer y último frame de la animación

                                }
                                else {
                                    fondo++; // Aumenta el valor de fondo, cambiando el fondo para el proximo ciclo
                                }
                            }
                            contador++; // Aumenta el contador que ajusta el tiempo de la animación
                        }
                        actualizarFondo(Background1, Background2, Background3, Background4, fondo, puerta); // Actualiza el fondo del estacionamiento
                        if (!vehiculoActivo) { // Se verifica si hay un vehiculo en el momento, en caso de que no genera un random y lo asigna a vehículo, este número permitirá saber cual es el elemento que debe ser pintado, luego asigna a vehiculoActivo como true para que no se generen más vehículos
                            vehiculo = vehiculoRandom(); // Obtiene un núnero asociado a un vehículo random
                            vehiculoActivo = true; // Actualiza la variable vehículoActivo para afirmar que un vehículo ha sido seleccionado
                        }

                        moverVehiculo(StrVehiculo, redPickup, yellowMotorcycle, brownTruck, redCar1, greenCar2, velocidad, primerPaso, autoDetenido, puerta, change, vehiculo, parking, tipoEstacionamiento, espacioDerecha, espacioIzquierda, cicloParqueo, parqueoEstandar, fuente2, corredorActual, parqueoEstandar1, parqueoEstandar2, parqueoEstandar3, parqueoEstandar4, fondoParqueo, pisos); // Se mueve el vehículo por la pantalla, tiene diversos parámetros debido a las condiciones de parada o verificaciones que debe realizar

                        if (puerta) { // Revisa si la puerta está abierta, ya que en caso de que lo esté hay que pintar un cuadro para generar el efecto de que el vehículo desaparece
                            al_draw_filled_rectangle(266, 358, 386, 472, al_map_rgb(0, 0, 0)); // Dibuja el cuadro negro en donde está la puerta, de esta manera se genera el efecto de que el vehículo desaparece
                            if (contadorUnico) {
                                asignarEspacio(StrVehiculo, espacios_disponibles);
                                contadorUnico = false;
                            }

                        }
                        al_flip_display(); // Se actualiza la pantalla para que todo lo que se modificó salga en pantalla
                        //                al_clear_to_color(al_map_rgb(0, 0, 0));
                    }
                    else {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_flip_display();
                    }
                }
                if (eventos.timer.source == SegundoTimer) {
                    if (change) {

                        //                        al_draw_bitmap(elevator1, 0, 0, NULL);
                        if (!parking) {
                            double ciclosAscensor = ceil(StrVehiculo->espacio * pisos / (espaciosXPiso * pisos)); // Utilizando la función ceil que redondea hacia arriba, se obtiene la cantidad de ciclos que debe cumplir el ascensor
                            //                        cout << StrVehiculo->espacio << endl;
                            //al_clear_to_color(al_map_rgb(0, 0, 0));y
                            //cout << "Ciclos a alcanzar: ";
                            //cout << ciclosAscensor << endl;
                            //cout << "Ciclos actuales: ";
                            //cout << comparador << endl;
                            mostrarAscensor(elevator0, elevator1, elevator2, elevator3, elevator4, elevator5, elevator6, elevator7, elevator8, comparador, pisoActual, contadorAscensor, ciclosAscensor, parking, primerPaso);
                        }
                        else { // Para cuando se desea mostrar el parqueo
                            //                            mostrarTiposEstacionamientos();
                        }

                        al_draw_filled_rectangle(450, 0, 550, 100, al_map_rgb(255, 255, 255));
                        string numero = to_string(static_cast<int>(comparador));
                        /*
                        cout << "Hola ";
                        cout << numero << endl;
                        */
                        al_draw_textf(fuente3, al_map_rgb(0, 0, 0), 455, 40, NULL, "Piso %s", numero.c_str());

                        moverVehiculo(StrVehiculo, redPickup, yellowMotorcycle, brownTruck, redCar1, greenCar2, velocidad, primerPaso, autoDetenido, puerta, change, vehiculo, parking, tipoEstacionamiento, espacioDerecha, espacioIzquierda, cicloParqueo, parqueoEstandar, fuente2, corredorActual, parqueoEstandar1, parqueoEstandar2, parqueoEstandar3, parqueoEstandar4, fondoParqueo, pisos);
                        al_flip_display();
                    }
                }
            }

        }
        if (cicloParqueo) {
            vehiculosParqueados++;
            vehiculoActivo = false; // Variable booleana usada para saber si hay un vehículo pintado
            primerPaso = true; // Variable booleana usada para saber si el vehículo acaba de ser pintado
            autoDetenido = false; // Variable booleana que se activará cuando el vehículo se haya detenido
            puerta = false; // Variable que verificará si la puerta está cerrada
            change = false; // Variable que define cuando se necesita realizar un cambio de escena
            parking = false; // Variable que se activa cuando se está en el proceso de parquear
            vehiculo; // Variable de tipo int usada para saber cual vehículo pintar
            fondo = 0; // Variable de tipo int para saber cual animación realizar
            contador = 0; // Variable que será usada para determinar la cantidad de frames que han pasado
            contadorAscensor = 0; // Variable para contar los frames del ascensor
            pisoActual = 0; // Variable para identificar en que piso se encuentra el ascensor
            corredorActual = 0; // Variable que hace referencia al parqueo, sirve para saber cuantas veces el vehículo debe andar por el estacionamiento
            comparador = 0; // Variable que permitirá comparar si el ciclo del ascensor ha terminado
            contadorUnico = true; // Contador único para que solo se llame el método asignarEspacio una sola vez

            cicloParqueo = false; // Variable que cuando sea true va a devolver todos los valores a los datos iniciales ** DE SUMA IMPORTANCIA **
        }
        //        al_flip_display(); // Se utiliza la función al_flip_display() para hacer que todo aparezca en pantalla
        if (vehiculosParqueados == cantidadDeVehiculos) {
            done = true;
        }

    }

    al_destroy_bitmap(imagenMenu);
    al_destroy_bitmap(imagenConfig);
    al_destroy_bitmap(redCar1);
    al_destroy_bitmap(redPickup);
    al_destroy_bitmap(brownTruck);
    al_destroy_bitmap(yellowMotorcycle);
    al_destroy_bitmap(greenCar2);
    al_destroy_bitmap(Background1);
    al_destroy_bitmap(Background2);
    al_destroy_bitmap(Background3);
    al_destroy_bitmap(Background4);
    al_destroy_bitmap(elevator0);
    al_destroy_bitmap(elevator1);
    al_destroy_bitmap(elevator2);
    al_destroy_bitmap(elevator3);
    al_destroy_bitmap(elevator4);
    al_destroy_bitmap(elevator5);
    al_destroy_bitmap(elevator6);
    al_destroy_bitmap(elevator7);
    al_destroy_bitmap(elevator8);
    al_destroy_bitmap(espacioDerecha);
    al_destroy_bitmap(espacioIzquierda);
    al_destroy_bitmap(parqueoEstandar);
    al_destroy_bitmap(parqueoEstandar1);
    al_destroy_bitmap(parqueoEstandar2);
    al_destroy_bitmap(parqueoEstandar3);
    al_destroy_bitmap(parqueoEstandar4);
    al_destroy_display(Display);
    al_destroy_event_queue(colaEventos);
    al_destroy_timer(TimerMenu);
    al_destroy_timer(PrimerTimer);
    al_destroy_timer(SegundoTimer);
    al_destroy_font(fuente1);
    al_destroy_font(fuente2);
    al_destroy_font(fuente3);
    al_destroy_sample(musica);
    al_destroy_sample_instance(instanciaMusica);

    std::cout << "Hello World!\n";
}