#ifndef _GRANADA_H
#define _GRANADA_H

#include <SDL2pp/SDL2pp.hh>

class Granada
{

private:
    SDL2pp::Texture texture; // Atributo que almacena la textura de la animacion

    int size; // Entero que almacena el tamaño de cada frame (altura y ancho).

    float x;
    float y;
    int angulo;
    int direccion;

    bool seLanzo;
    int exploto;
    int currentFrame;

    int tiempo;

public:
    Granada(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void update(float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion);
    void cambiar(std::string &ruta);

    void explotar(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void lanzarGranada();
    bool seLanzoGranada();

    void set_flag(int flag);
    int get_flag();

    float get_x();
    float get_y();

    void set_tiempo(int tiempoElegido);
    int get_tiempo();
};

#endif // _GRANADA_H
