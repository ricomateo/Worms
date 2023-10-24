#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <vector>

// ACLARACION: Los mover son confusos, porque cuando se aumenta X se mueve para arriba
// y cuando se aumenta Y para la derecha.
// esto se debe a que como la matriz es matriz[fila][columnas] es al reves de como tratamos a los
// ejes de coordenadas (x,y) ya que las filas hacen referencia a las Y, porque al incrementar o
// decrementar se mueve para arriba o para abajo

// Por algun motivo cppcheck dice que no uso las variables dentro de la estructura del escenario
struct Escenario
{
    // cppcheck-suppress unusedStructMember
    int filas; // cant de filas que tiene el escenario
    // cppcheck-suppress unusedStructMember
    int columnas;
    // cppcheck-suppress unusedStructMember
    int indice_i; // se usa para inicializar la matriz
    // cppcheck-suppress unusedStructMember
    int indice_j;
    std::vector<std::vector<char>> matriz;
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
    std::vector<int> posicionG;
    std::string nombre_archivo;
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
