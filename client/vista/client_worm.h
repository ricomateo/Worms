#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "client_animacion.h"
#include "client_apuntado.h"
#include "constantes.h"
#include <map>

#include "vista_bate.h"
#include "vista_granada_verde.h"
#include "vista_bazooka.h"
#include "vista_banana.h"
#include "vista_granada_santa.h"
#include "vista_dinamita.h"
#include "vista_ataque_aereo.h"

const int BATE = 7;
const int GRANADA_VERDE = 2;
const int BAZOOKA = 0;
const int BANANA = 4;
const int GRANADA_SANTA = 5;
const int DINAMITA = 6;
const int TELETRANSPORTACION = 9;
const int ATAQUE_AEREO = 8;

#include "yaml-cpp/yaml.h"

class Worm
{

private:
    Animation animacion;

    std::shared_ptr<Arma> arma;

    int estado;

    int tipoDeArma;

    float x;
    float y;
    int vida;

    bool turno;
    bool mirandoIzquierda;

    SDL2pp::Color &color;
    YAML::Node configuraciones;

public:
    Worm(SDL2pp::Renderer &renderer, SDL2pp::Color &color, float x, float y, int vida);

    void update(int it, float nuevoX, float nuevoY, int vida); // Actualiza el Worm en funcion del tiempo transcurrido.
    void update_estado(SDL2pp::Renderer &renderer, int nuevoEstado, int arma = -1);

    void render(SDL2pp::Renderer &renderer, Camara &camara, float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior);
    void render_vida(SDL2pp::Renderer &renderer,float camaraCentroX, float camaraLimiteIzquierdo, float camaraLimiteSuperior);

    void desactivar_turno();
    void activar_turno();

    void mirar_derecha();
    void mirar_izquierda();

    int get_tipo_de_arma();

    void update_proyectil(int id, float nuevoX, float nuevoY, int nuevoAngulo, int nuevaDireccion, int nuevoFlag);
    void set_tiempo(int tiempo);
    int get_tiempo();

    void aumentar_angulo();
    void decrementar_angulo();
    int get_angulo();

    void aumentar_potencia();
    int get_potencia();

    float get_x();
    float get_y();
    int get_vida();
    int get_estado();
};

#endif // __WORM_H_
