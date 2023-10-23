#ifndef VISTA_H
#define VISTA_H

#include <iostream>
#include <exception>
#include <algorithm>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

struct Jugador {
    std::string nombre;
    int vida;

	float gusano_posicion;
	bool gusano_moviendose;
    bool gusano_moviendose_izquierda;
	int run_phase;
};

class Vista {
private:

public:
    Vista();

    int iniciar();

    bool handleEvents(Jugador &jugador);

    void renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, Jugador &jugador);
    void renderizar_gusano(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, Jugador &jugador);
    void renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua);
    void renderizar_nombre(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Jugador &jugador);
    void renderizar_vida(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Jugador &jugador);
    void renderizar_posicion(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Jugador &jugador);

    void actualizar(SDL2pp::Renderer &renderer, Jugador &jugador, unsigned int &frame_ticks, unsigned int &frame_delta);

    std::string obtener_texto(Jugador &jugador);
};

#endif
