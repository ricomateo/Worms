#ifndef VISTA_H
#define VISTA_H

#include <iostream>
#include <exception>
#include <algorithm>

#include <SDL2pp/SDL2pp.hh>

#include "client_mock_cliente.cpp"

using namespace SDL2pp;

struct Animacion {
    Gusano gusano;
	bool gusano_moviendose;
    bool gusano_moviendose_izquierda;
	int run_phase;
};

class Vista {
private:
    MockClient &cliente;

public:
    Vista(MockClient &cliente);

    int iniciar();

    bool handleEvents(Animacion &animacion, SDL2pp::Texture &sprites);

    void renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, Animacion &animacion, unsigned int tiempoRestante);
    void renderizar_temporizador(SDL2pp::Renderer &renderer, SDL2pp::Font &font, unsigned int tiempoRestante);
    void renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua);
    void renderizar_gusano(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, Animacion &animacion);
    void renderizar_nombre(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion);
    void renderizar_vida(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion);
    void renderizar_informacion(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Animacion &animacion);

    void actualizar(SDL2pp::Renderer &renderer, Animacion &animacion, unsigned int &frame_ticks, unsigned int &frame_delta);

    std::string obtener_texto(Animacion &animacion);

    float convertidor(float valor);
};

#endif
