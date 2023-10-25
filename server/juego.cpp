#include "juego.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

const char PARED = 'X';
const char GUSANO = 'G';
const char VACIO = ' ';
const int DIRECCION_IZQUIERDA = 0;
const int DIRECCION_DERECHA = 1;
const int SALTO_ADELANTE = 0;

Juego::Juego(std::string nombre) : direccion(0), nombre_archivo(std::string(nombre))
{
    escenario.filas = 0;
    escenario.columnas = 0;
    escenario.indice_i = 0;
    escenario.indice_j = 0;
    escenario.matriz.clear();
}

/*
 * Inicializa los valores del escenario segun la informacion dada en la linea
 * La linea es de la forma --> linea == "9 5 nombre_escenario"
 */
void Juego::asignarValoresALaMatriz(std::string linea)
{
    // cargo el valor de la fila y columnas que son las 2 primeras "letras" de la linea
    escenario.filas = linea[2] - '0';
    escenario.columnas = linea[0] - '0';

    escenario.matriz.clear();
    // ajusto la matriz al tamaño que voy a necesitar
    escenario.matriz.resize(escenario.filas, std::vector<char>(escenario.columnas));
}

/*
 * Se encarga de leer el archivo linea por linea
 * Si la linea comieza con el caracter que representa a una PARED, carga la linea a la matriz del
 * escenario si corresponde.
 * Si la linea no comienza con un caracter PARED entonces checkea si el escenario es el buscado
 * En caso de serlo, inicializa los valores del Escenario y setea la variable llenar_matriz como
 * true para notificar que las proximas lineas que comienzan con PARED pertenecen al escenario y las
 * cargue a la matriz. Una vez que encuentra el escenario y lo carga, deja de leer el archivo.
 * Al final retorna si encontro el escenario buscado o no.
 */
bool Juego::leerArchivo(std::ifstream &archivo, const std::string &nombreEscenario)
{
    std::string linea;
    bool llenar_matriz = false;
    bool escenario_encontrado = false;

    while (std::getline(archivo, linea))
    {
        if (linea.empty() || (escenario_encontrado && !llenar_matriz))
            break;

        if (linea[0] != PARED)
        {
            // Se que la tercer palabra de la primer linea es el escenario
            if (linea.substr(4) == nombreEscenario)
            {
                escenario_encontrado = true;
                llenar_matriz = true;
                asignarValoresALaMatriz(linea);
                continue;
            }
            llenar_matriz = false;
        }
        if (llenar_matriz)
            completarMatriz(linea);
    }

    return escenario_encontrado;
}

/*
 * Dado un nombre de escenario, lee un archivo asignado previamente y carga el escenario si este
 * existe.
 */
bool Juego::cargarEscenarioDeseado(const std::string &nombreEscenario)
{
    if (nombre_archivo.empty() || nombreEscenario.empty())
        return false;

    std::ifstream archivo(nombre_archivo);

    if (!archivo.is_open())
        throw std::runtime_error("No se pudo abrir el archivo. " + std::string(__FILE__) +
                                 std::to_string(__LINE__));

    bool escenario_encontrado = leerArchivo(archivo, nombreEscenario);

    archivo.close();
    return escenario_encontrado;
}

void Juego::armar_escenario()
{
    escenario.filas = 5;
    escenario.columnas = 9;
    gusano.y = 3;
    gusano.x = 2;
    escenario.matriz.resize(escenario.filas, std::vector<char>(escenario.columnas));
    std::string linea1("XXXXXXXXX");
    std::string linea2("X       X");
    std::string linea3("X       X");
    std::string linea4("X   X   X");
    std::string linea5("XXXXXXXXX");
    completarMatriz(linea1);
    completarMatriz(linea2);
    completarMatriz(linea3);
    completarMatriz(linea4);
    completarMatriz(linea5);
}

// Imprime el escenario
void Juego::imprimir()
{
    system("clear");
    for (int i = 0; i < escenario.filas; i++)
    {
        for (int j = 0; j < escenario.columnas; j++)
        {
            std::cout << escenario.matriz[i][j];
        }
        std::cout << std::endl;
    }
}

/*
 *   Dado una linea de texto
 *   ingresa los valores pertinentes en cada posicion de la matriz
 *   contruyendo el escenario
 */
void Juego::completarMatriz(const std::string &linea)
{
    int i = 0;
    while (i < escenario.columnas)
    {
        if (escenario.indice_j <= escenario.columnas - 1 && escenario.indice_i < escenario.filas)
        {
            escenario.matriz[escenario.indice_i][escenario.indice_j] = linea[i];
            if (linea[i] == GUSANO)
            {
                gusano.y = escenario.indice_i;
                gusano.x = escenario.indice_j;
            }
            escenario.indice_j++;
        }
        i++;
    }
    escenario.indice_j = 0;
    escenario.indice_i++;
}

/*
 * Devuelve la posicion actual del gusano siendo la posicion 0 la correspondiente al eje y de
 * coordenadas y la posicion 1 pertenece al eje x
 */
std::vector<uint32_t> Juego::posicionGusano() const
{
    std::vector<uint32_t> posicion;
    posicion.push_back(gusano.y);
    posicion.push_back(gusano.x);
    return posicion;
}

/*
 *  Si es posible, ubica al Gusano ('G') un posicion hacia arriba
 *  Devuelve TRUE si la siguiente posicion no es pared, dado que si no es pared realizo el
 *  movimiento
 */
bool Juego::moverArriba()
{
    int y = gusano.y;
    int x = gusano.x;

    bool la_siguiente_no_es_pared = (escenario.matriz[y - 1][x] != PARED);

    if (y > 0 && la_siguiente_no_es_pared)
    {
        escenario.matriz[gusano.y][gusano.x] = VACIO;
        gusano.y -= 1;
        escenario.matriz[gusano.y][gusano.x] = GUSANO;
    }
    return la_siguiente_no_es_pared;
}

/*
 *  Si es posible, ubica al Gusano ('G') un posicion hacia abajo
 */
void Juego::moverAbajo()
{
    int y = gusano.y;
    int x = gusano.x;

    if (y + 1 < escenario.filas && escenario.matriz[y + 1][x] != PARED)
    {
        escenario.matriz[gusano.y][gusano.x] = VACIO;
        gusano.y += 1;
        escenario.matriz[gusano.y][gusano.x] = GUSANO;
    }
}

/*
 *  Si es posible, ubica al Gusano ('G') un posicion hacia la derecha
 *  Devuelve TRUE si la siguiente posicion no es pared, dado que si no es pared realizo el
 *  movimiento
 */
bool Juego::moverDerecha()
{
    int y = gusano.y;
    int x = gusano.x;

    bool la_siguiente_no_es_pared = (escenario.matriz[y][x + 1] != PARED);

    if (x + 1 < escenario.columnas && la_siguiente_no_es_pared)
    {
        escenario.matriz[gusano.y][gusano.x] = VACIO;
        gusano.x += 1;
        escenario.matriz[gusano.y][gusano.x] = GUSANO;
    }
    return la_siguiente_no_es_pared;
}

/*
 *  Si es posible, ubica al Gusano ('G') un posicion hacia la izquierda
 *  Devuelve TRUE si la siguiente posicion no es pared, dado que si no es pared realizo el
 *  movimiento
 */
bool Juego::moverIzquierda()
{
    int y = gusano.y;
    int x = gusano.x;

    bool la_siguiente_no_es_pared = (escenario.matriz[y][x - 1] != PARED);

    if (x > 0 && la_siguiente_no_es_pared)
    {
        escenario.matriz[gusano.y][gusano.x] = VACIO;
        gusano.x -= 1;
        escenario.matriz[gusano.y][gusano.x] = GUSANO;
    }
    return la_siguiente_no_es_pared;
}

/*
 * Desplaza al gusano haca abajo hasta encontrar que la posiicon siguiente es una PARED
 * de forma que el gusano siempre termina por encima de una pared
 */
void Juego::simularGravedad()
{
    while (escenario.matriz[gusano.y + 1][gusano.x] != PARED)
    {
        moverAbajo();
    }
}

/* Mueve el gusano 1 posicion arriba y 2 hacia donde apunta*/
void Juego::saltarHaciaAdelante()
{
    bool se_movio = moverArriba();
    if (se_movio && direccion == DIRECCION_DERECHA)
    {
        moverDerecha();
        moverDerecha();
    }
    if (se_movio && direccion == DIRECCION_IZQUIERDA)
    {
        moverIzquierda();
        moverIzquierda();
    }
}
/* Mueve el gusano 2 posiciones para arriba y 1 a la direceccion contraria a la que apunta*/
void Juego::saltarHaciaAtras()
{
    moverArriba();
    bool se_movio = moverArriba(); // si no se mueve la de arriba, esta tampoco, pero no al reves

    if (se_movio && direccion == DIRECCION_IZQUIERDA) // 1 paso hacia la direccion contraria
        moverDerecha();
    if (se_movio && direccion == DIRECCION_DERECHA)
        moverIzquierda();
}

/* Mueve el gusano 1 paso hacia donde mira*/
void Juego::mover()
{
    std::cout << "direccion = " << direccion << std::endl;
    if (direccion == DIRECCION_DERECHA)
        moverDerecha();
    if (direccion == DIRECCION_IZQUIERDA)
        moverIzquierda();

    simularGravedad();
}

/*
 * Ejecuta el comando saltar segun indique la orientacion
 * Si orientacion es 1 ---> Salta hacia atras
 * Si orientacion es 0 ---> Salta hacia adelante
 */
void Juego::saltar(uint8_t orientacion)
{

    if (orientacion > 0)
        saltarHaciaAtras();
    else
        saltarHaciaAdelante();

    simularGravedad();
}
/*
 * Invierte la direccion del gusano dado una orientacion
 * Si orientacion es 1 ---> Direccion se modifica a Derecha
 * Si orientacion es 0 ---> Direccion se modifica a Izquierda
 */
void Juego::invertirDireccion(uint8_t orientacion)
{
    if (orientacion < 1)
        direccion = DIRECCION_IZQUIERDA;
    else
        direccion = DIRECCION_DERECHA;
}

std::string Juego::mapa_fila(int fila)
{
    std::string linea;
    for (int i = 0; i < escenario.columnas; i++)
    {
        linea = linea + escenario.matriz[fila][i];
    }
    return linea;
}

int Juego::filas() { return escenario.filas; }
