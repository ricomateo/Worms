#include "client_worm.h"

#define ANCHO_SPRITE 60
#define ALTO_SPRITE 60

#define OFFSET 30 // Definimos un offset ya que debemos hacer un corrimiento en 'x' e 'y' ya que las fisicas modeladas con Box2D
                  // tienen el (0,0) de los cuerpos en el centro

Worm::Worm(SDL2pp::Renderer &renderer, SDL2pp::Color &color, int numeroColor, float x, float y, int vida, int direccion): animacion(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/worm_walk.png").SetColorKey(true, 0))), 
                                                                                          estado(QUIETO),
                                                                                          x(x), 
                                                                                          y(y), 
                                                                                          vida(vida),
                                                                                          direccion(direccion),
                                                                                          angulo(0),
                                                                                          turno(false), 
                                                                                          numeroColor(numeroColor),
                                                                                          color(color),
                                                                                          camara(false) {}

// Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.

/******************** ACTUALIZACION Y RENDERIZADO ********************/

void Worm::update(int it, float nuevoX, float nuevoY, int nuevaVida, int nuevaDireccion, int nuevoAngulo)
{

    if (this->estado == EQUIPANDO_ARMA) {
        this->animacion.update(it);
    }

    // if (this->estado == MOVIENDOSE) {
    if ((nuevoX != this->x) || (nuevoY != this->y)) {

        if (this->estado != GOLPEADO) {
            this->animacion.update(it);
        }

        this->x = nuevoX;
        this->y = nuevoY;
        
    }

    this->vida = nuevaVida;
    this->direccion = nuevaDireccion;
    this->angulo = nuevoAngulo;
}

void Worm::update_estado(SDL2pp::Renderer &renderer, int nuevoEstado, int tipoDeArma) {
    this->estado = nuevoEstado;
    this->tipoDeArma = tipoDeArma;

    if (nuevoEstado == MOVIENDOSE) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/worm_walk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
    }

    else if (nuevoEstado == SALTANDO_ADELANTE) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wflylnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();
    }

    else if (nuevoEstado == SALTANDO_ATRAS) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbackflp.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();
    }

    else if (nuevoEstado == EQUIPANDO_ARMA) {
        equipar_arma(renderer, tipoDeArma);
    }

    else if (nuevoEstado == GOLPEADO) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wfly1.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
    }

    else if (nuevoEstado == MUERTO) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/grave1.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
    }
}

void Worm::equipar_arma(SDL2pp::Renderer &renderer, int tipoDeArma) {
    this->tipoDeArma = tipoDeArma;

    if (tipoDeArma == BATE) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbsblnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionBateDeBaseball>(renderer);
    }

    else if (tipoDeArma == GRANADA_VERDE) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wgrnlnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionGranadaVerde>(renderer);
    }

    else if (tipoDeArma == BAZOOKA) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbazlnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionBazooka>(renderer);
    }

    else if (tipoDeArma == BANANA) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbanlnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionBanana>(renderer);
    }

    else if (tipoDeArma == GRANADA_SANTA) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/whgrlnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionGranadaSanta>(renderer);
    }

    else if (tipoDeArma == DINAMITA) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wdynlnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionDinamita>(renderer);
    }

    else if (tipoDeArma == TELETRANSPORTACION) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wtellnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();
    }

    else if (tipoDeArma == ATAQUE_AEREO) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wairlnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionAtaqueAereo>(renderer);
    }

    else if (tipoDeArma == GRANADA_ROJA) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wclslnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionGranadaRoja>(renderer);
    }

    else if (tipoDeArma == MORTERO) {
        std::shared_ptr<SDL2pp::Texture> nuevaTextura = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "/wbazlnk.png").SetColorKey(true, 0));
        this->animacion.cambiar(nuevaTextura);
        this->animacion.no_repetir_animacion();

        this->arma = std::make_shared<AnimacionMortero>(renderer);
    }
}

void Worm::render(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior)
{
    SDL_RendererFlip flip = this->direccion ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    if (this->estado == MUERTO) {
        this->animacion.render(renderer, this->camara ? SDL2pp::Rect(camaraCentroX - OFFSET, y - 20 - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE) : SDL2pp::Rect(x - OFFSET - camaraLimiteIzquierdo, y - 20 - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE), flip);
    
    } else if (this->estado == APUNTANDO) {
        int posicionX = this->camara ? (camaraCentroX - OFFSET) : (x - OFFSET - camaraLimiteIzquierdo);
        int posicionY = this->camara ? (y - OFFSET - camaraLimiteSuperior) : (y - OFFSET - camaraLimiteSuperior);
        this->arma->render(renderer, this->color, posicionX, posicionY, this->direccion);

    } else {
        this->animacion.render(renderer, this->camara ? SDL2pp::Rect(camaraCentroX - OFFSET, y - OFFSET - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE) : SDL2pp::Rect(x - OFFSET - camaraLimiteIzquierdo, y - OFFSET - camaraLimiteSuperior, ANCHO_SPRITE, ALTO_SPRITE), flip, this->angulo);
    }

    if ((this->estado == EQUIPANDO_ARMA) && (this->animacion.completa())) {
        
        if ((this->tipoDeArma != DINAMITA) && (this->tipoDeArma != TELETRANSPORTACION) && (this->tipoDeArma != ATAQUE_AEREO)) {
            this->estado = APUNTANDO;
        }
    }

    if ((this->arma) && (this->estado != EQUIPANDO_ARMA) && (this->estado != APUNTANDO) && (this->arma->get_estado() == ARMA_MOVIENDOSE || this->arma->get_estado() == ARMA_EXPLOTAR)) {
        this->arma->render(renderer, this->color, camaraLimiteIzquierdo, camaraLimiteSuperior);
    }

    if (this->estado != MUERTO) {
        this->render_vida(renderer, camaraCentroX, camaraLimiteIzquierdo, camaraLimiteSuperior);
    }
}

void Worm::render_vida(SDL2pp::Renderer &renderer, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior) {
    SDL2pp::Font font(DATA_PATH "/Vera.ttf", 18);
    SDL2pp::Color blanco(255, 255, 255, 255); 

    /********** BORDE **********/

    SDL2pp::Texture borde(renderer, SDL2pp::Surface(DATA_PATH "/borde.png").SetColorKey(true, 0));

    renderer.Copy(
        borde,
        SDL2pp::NullOpt,
        SDL2pp::Rect(this->camara ? (camaraCentroX + 10 - OFFSET) : (this->x - 19 - camaraLimiteIzquierdo),
                     this->camara ? (this->y - 45 - camaraLimiteSuperior) : (this->y - 45 - camaraLimiteSuperior), 
                     41, 29)
    );

    /********** CONTENEDOR **********/

    SDL2pp::Rect contenedor(this->camara ? (camaraCentroX + 13 - OFFSET) : (this->x - 16 - camaraLimiteIzquierdo),
                            this->camara ? (this->y - 42 - camaraLimiteSuperior) : (this->y - 42 - camaraLimiteSuperior), 
                            34, 22);
	renderer.SetDrawColor(this->color); 
	renderer.FillRect(contenedor);

    /********** VIDA **********/

	SDL2pp::Surface surface = font.RenderText_Solid(std::to_string(this->vida), blanco);
	SDL2pp::Texture texture(renderer, surface);

    if (this->vida == 100) {
        SDL2pp::Rect mensaje(this->camara ? (camaraCentroX + 12 - OFFSET) : (this->x - 16 - camaraLimiteIzquierdo),
                            this->camara ? (this->y - 42 - camaraLimiteSuperior) : (this->y - 42 - camaraLimiteSuperior), 
                            surface.GetWidth(), surface.GetHeight());

        renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
    
    } else if ((this->vida < 100) && (this->vida >= 10)) {
        SDL2pp::Rect mensaje(this->camara ? (camaraCentroX + 17 - OFFSET) : (this->x - 11 - camaraLimiteIzquierdo),
                            this->camara ? (this->y - 42 - camaraLimiteSuperior) : (this->y - 42 - camaraLimiteSuperior), 
                            surface.GetWidth(), surface.GetHeight());

        renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
    
    } else if (this->vida < 10) {
        SDL2pp::Rect mensaje(this->camara ? (camaraCentroX + 23 - OFFSET) : (this->x - 5 - camaraLimiteIzquierdo),
                            this->camara ? (this->y - 42 - camaraLimiteSuperior) : (this->y - 42 - camaraLimiteSuperior), 
                            surface.GetWidth(), surface.GetHeight());

        renderer.Copy(texture, SDL2pp::NullOpt, mensaje);
    }

}

/******************** TURNO ********************/

void Worm::set_turno(bool nuevoTurno) {
    this->turno = nuevoTurno;
}

void Worm::set_camara(bool nuevaCamara) {
    this->camara = nuevaCamara;
}

/******************** ARMA ********************/

int Worm::get_tipo_de_arma() {
    return this->tipoDeArma;
}

/******************** PROYECTIL ********************/

void Worm::update_proyectil(SDL2pp::Renderer &renderer, int id, float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion, int nuevoEstado, int nuevoTiempo) {
    this->arma->update(nuevoX, nuevoY, nuevoEstado, nuevoAngulo, nuevaDireccion, nuevoTiempo, id);
}

void Worm::set_tiempo(int tiempo) {
    this->arma->set_tiempo(tiempo);
}

int Worm::get_tiempo() {
    return this->arma->get_tiempo();
}

/******************** ANGULO ********************/

void Worm::aumentar_angulo() {
    if (this->estado == APUNTANDO) {
        this->arma->aumentar_angulo();
    }
}

void Worm::decrementar_angulo() {
    if (this->estado == APUNTANDO) {
        this->arma->decrementar_angulo();
    }
}

int Worm::get_angulo() {
    return this->arma->get_angulo();
}

/******************** POTENCIA ********************/

void Worm::aumentar_potencia() {
    if (this->estado == APUNTANDO) {
        this->arma->aumentar_potencia();
    }
}

int Worm::get_potencia() {
    if (this->estado == APUNTANDO) {
        return this->arma->get_potencia();
    } 

    return 0;
}

/******************** GETTERS GENERALES ********************/

int Worm::get_vida() {
    return this->vida;
}

float Worm::get_x() {
    return this->x;
}

float Worm::get_y() {
    return this->y;
}

int Worm::get_estado() {
    return this->estado;
}

int Worm::get_color() {
    return this->numeroColor;
}

bool Worm::get_turno() {
    return this->turno;
}
