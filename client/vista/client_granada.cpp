#include "client_granada.h"

Granada::Granada(SDL2pp::Renderer &renderer): texture(SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "/grenade.1.png").SetColorKey(true, 0))), 
                                                                          size(this->texture.GetWidth()),
                                                                          x(0),
                                                                          y(0),
                                                                          angulo(0),
                                                                          direccion(1),
                                                                          seLanzo(false),
                                                                          exploto(0),
                                                                          currentFrame(12),
                                                                          tiempo(5) {}

void Granada::render(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    renderer.Copy(
        this->texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->x - 8 - camaraLimiteIzquierdo, this->y - 8 - camaraLimiteSuperior, this->size, this->size), this->angulo - 45,
        SDL2pp::NullOpt,    // rotation center - not needed
        this->direccion ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE
    );
}

void Granada::update(float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion) {
    this->x = nuevoX;
    this->y = nuevoY;
    this->angulo = nuevoAngulo;
    this->direccion = nuevaDireccion;
}

void Granada::cambiar(std::string &ruta) {
    SDL2pp::Surface surface(DATA_PATH + ruta);

    this->size = surface.GetWidth();
    this->texture.Update(SDL2pp::NullOpt, surface.SetColorKey(true, 0));
}

void Granada::explotar(SDL2pp::Renderer &renderer, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL2pp::Texture explosion(renderer, SDL2pp::Surface(DATA_PATH "/exbiff.png").SetColorKey(true, 0));

    int tamaño = 60;

    if (this->currentFrame < 12) {
        renderer.Copy(
            explosion,
            SDL2pp::Rect(0, (tamaño) * currentFrame, tamaño, tamaño),
            SDL2pp::Rect(this->x - 16 - camaraLimiteIzquierdo, this->y - 16 - camaraLimiteSuperior, tamaño, tamaño)
        );
    }

    this->currentFrame++;
}

void Granada::lanzarGranada() {
    this->seLanzo = true;
}

bool Granada::seLanzoGranada() {
    return this->seLanzo;
}

void Granada::set_flag(int flag) {
    this->exploto = flag;

    // Si el flag es igual a 1 quiere decir que tiramos la bomba y debemos reiniciar el frame actual de la explosion
    if (flag == 1) {
        this->currentFrame = 0;
    }
}

int Granada::get_flag() {
    return this->exploto;
}

float Granada::get_x() {
    return this->x;
}

float Granada::get_y() {
    return this->y;
}

void Granada::set_tiempo(int tiempoElegido) {
    this->tiempo = tiempoElegido;
}

int Granada::get_tiempo() {
    return this->tiempo;
}
