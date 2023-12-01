#include "client_explosion.h"

Explosion::Explosion(SDL2pp::Renderer &renderer, std::unique_ptr<SDL2pp::Texture> ex):  ex(std::move(ex), false),
                                                                                        circulo(std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/circle50.png").SetColorKey(true, 0)), false),
                                                                                        elipse(std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/elipse50.png").SetColorKey(true, 0)), false),
                                                                                        fuego(std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/flame1.png").SetColorKey(true, 0)), false),
                                                                                        movimientoFuego(0) {}

void Explosion::update() {
    this->fuego.update();
    this->circulo.update();
    this->elipse.update();
    this->ex.update();
}

void Explosion::render(SDL2pp::Renderer &renderer, float x, float y, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (not this->fuego.completa()) {
        this->fuego.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo - 2 - movimientoFuego, y - 30 - camaraLimiteSuperior - 20 + movimientoFuego, 60, 60), flip);
        this->fuego.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo + 2 + movimientoFuego, y - 30 - camaraLimiteSuperior - 20 + movimientoFuego, 60, 60), flip);

        this->fuego.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo - 20 - movimientoFuego, y - 30 - camaraLimiteSuperior + movimientoFuego, 60, 60), flip);
        this->fuego.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo + 20 + movimientoFuego, y - 30 - camaraLimiteSuperior + movimientoFuego, 60, 60), flip);
    }
 
    if (not this->circulo.completa()) {
        this->circulo.render(renderer, SDL2pp::Rect(x - 50 - camaraLimiteIzquierdo, y - 50 - camaraLimiteSuperior, 100, 100), flip);
    }

    if (not this->elipse.completa()) {
        this->elipse.render(renderer, SDL2pp::Rect(x - 75 - camaraLimiteIzquierdo, y - 75 - camaraLimiteSuperior, 150, 150), flip);
    }

    if (not this->ex.completa()) {
        this->ex.render(renderer, SDL2pp::Rect(x - 30 - camaraLimiteIzquierdo, y - 30 - camaraLimiteSuperior, 60, 60), flip);
    }
    
    movimientoFuego += 1;
}

bool Explosion::animacion_completa() {
    return (this->fuego.completa() && this->circulo.completa() && this->elipse.completa() && this->ex.completa());
}
