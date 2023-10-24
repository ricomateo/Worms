#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <vector>

struct Escenario
{
    int filas; // cant de filas que tiene el escenario
    int columnas;
    int indice_i; // se usa para inicializar la matriz
    int indice_j;
    std::vector<std::vector<char>> matriz;
};

struct Worm
{
    uint32_t x;
    uint32_t y;
};

class Juego
{
public:
    explicit Juego(std::string nombre);
    bool cargarEscenarioDeseado(const std::string &nombreEscenario);
    void imprimir();
    std::vector<uint32_t> posicionGusano() const;
    void invertirDireccion(uint8_t orientacion);
    void mover();
    void saltar(uint8_t orientacion);
    void armar_escenario();

private:
    int direccion;
    // std::vector<int> posicionG;
    std::string nombre_archivo;
    Worm gusano;
    Escenario escenario;

    bool moverArriba(); // false si no se pudo mover
    void moverAbajo();  // es void orque la uso siempre hasta una pared
    bool moverDerecha();
    bool moverIzquierda();
    void saltarHaciaAdelante();
    void saltarHaciaAtras();
    void simularGravedad();
    void completarMatriz(const std::string &linea);
    void asignarValoresALaMatriz(std::string linea);
    bool leerArchivo(std::ifstream &archivo, const std::string &nombreEscenario);
};

#endif
