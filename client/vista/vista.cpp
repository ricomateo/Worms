#include "client_vista.h"

#define ALTO_SPRITE 60
#define ANCHO_SPRITE 60

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

Vista::Vista() {}

int Vista::iniciar() {
    // cliente.conectarse();

    // Inicializamos la libreria SDL
	SDL sdl(SDL_INIT_VIDEO);

    // Inicializamos la libreria SDL_ttf
	SDLTTF ttf;

	// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    // Creamos la ventana main: Dimensiones de 640x480, Redimensionable, Titulo de la ventana "Worms 2D"
	Window window("Worms 2D",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			ANCHO_VENTANA, ALTO_VENTANA,
			SDL_WINDOW_RESIZABLE);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprites image as a new texture; since there's no alpha channel
	// but we need transparency, use helper surface for which set color key
	// to color index 0 -> black background on image will be transparent on our
	// texture
	Texture sprites(renderer, Surface(DATA_PATH "/gusano_caminando_derecha.png")
			.SetColorKey(true, 0));

	// Enable alpha blending for the sprites
	sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

	// Cargamos la imagen para una viga
	Texture viga(renderer, Surface(DATA_PATH "/viga_corta.png")
			.SetColorKey(true, 0xff));

	viga.SetBlendMode(SDL_BLENDMODE_BLEND);

	// Cargamos la imagen para el fondo
	Texture background(renderer, Surface(DATA_PATH "/background.png")
			.SetColorKey(true, 0xff));

	background.SetBlendMode(SDL_BLENDMODE_BLEND);

	// Cargamos la imagen para el agua
	Texture agua(renderer, Surface(DATA_PATH "/agua.png")
			.SetColorKey(true, 0xff));

	agua.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cargamos la fuente de la letra y le ajustamos un tamaño de 12 pt
	Font font(DATA_PATH "/Vera.ttf", 12);

	// Estado del juego
	Jugador jugador({"Alan", 100, 0.0, false, false, -1});

	unsigned int prev_ticks = SDL_GetTicks();
	// Main loop
	while (1) {
		// Timing: calculate difference between this and previous frame
		// in milliseconds
		unsigned int frame_ticks = SDL_GetTicks();
		unsigned int frame_delta = frame_ticks - prev_ticks;
		prev_ticks = frame_ticks;

        if (handleEvents(jugador)) {
			return 0;
		}

		actualizar(renderer, jugador, frame_ticks, frame_delta);
		renderizar(renderer, sprites, viga, background, agua, font, jugador);

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		SDL_Delay(1);
	}

    return 0;
}

bool Vista::handleEvents(Jugador &jugador) {
	// Procesamiento de evento
	SDL_Event event;

	// REvisamos si hay algun evento pendiente en la cola de eventos de SDL y, si lo hay, lo almacenamos en la estructura event.
	while (SDL_PollEvent(&event)) {

		// Si la ventana se cierra terminamos la ejecucion
		if (event.type == SDL_QUIT) {
			return true;

		// Si se presiona alguna tecla...
		} else if (event.type == SDL_KEYDOWN) {

			switch (event.key.keysym.sym) {

			// Si se presiona la tecla "Q" o "ESC" terminamos la ejecucion
			case SDLK_ESCAPE: case SDLK_q:
				return true;

			// Si se presiona la flecha hacia la derecha el gusano se mueve hacia la derecha
			case SDLK_RIGHT: 
				jugador.gusano_moviendose = true;
				break;
			
			// Si se presiona la flecha hacia la izquierda el gusano se mueve hacia la izquierda
			case SDLK_LEFT: 
				jugador.gusano_moviendose_izquierda = true; 
				break;

			// Si se presiona la flecha hacia ariba el gusano direcciona su arma
			case SDLK_UP: 
				// ...
				break;

			// Si se presiona la flecha hacia abajo el gusano direcciona su arma
			case SDLK_DOWN: 
				// ...
				break;
			
			// Si se presiona la tecla de enter el gusano salta hacia adelante
			case SDLK_RETURN: 
				// ...
				break;
			
			// Si se presiona la tecla de espacio disparamos o aumentamos la potencia del disparo
			case SDLK_SPACE: 
				// ...
				break;
			
			// Si se presiona la tecla de retroceso el gusano cambia su direccion (se da la vuelta)
			case SDLK_BACKSPACE: 
				// ...
				break;
			
			// Si se presiona la tecla del numero 0 se setea como tiempo de espera para un proyectil
			case SDLK_0: 
				// ... 
				break;
			}

		// Si se suelta alguna tecla...
		} else if (event.type == SDL_KEYUP) {

			switch (event.key.keysym.sym) {

			// Si se suelta la flecha hacia la derecha cambiamos el estado del gusano
			case SDLK_RIGHT: 
				jugador.gusano_moviendose = false; 
				break;
			
			// Si se suelta la flecha hacia la izquierda cambiamos el estado del gusano
			case SDLK_LEFT: 
				jugador.gusano_moviendose_izquierda = false; 
				break;

			// Si se suelta la flecha hacia ariba...
			case SDLK_UP: 
				// ...
				break;

			// Si se suelta la flecha hacia abajo...
			case SDLK_DOWN: 
				// ...
				break;
			
			// Si se suelta la tecla de enter...
			case SDLK_RETURN: 
				// ...
				break;
			
			// Si se suelta la tecla de espacio...
			case SDLK_SPACE: 
				// ...
				break;
			
			// Si se suelta la tecla de retroceso...
			case SDLK_BACKSPACE: 
				// ...
				break;
			
			// Si se suelta la tecla del numero 0...
			case SDLK_0: 
				// ... 
				break;
			}
		}
	}

	return false;
}

void Vista::renderizar(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua, SDL2pp::Font &font, Jugador &jugador) {
	renderer.Clear();

	renderizar_mapa(renderer, viga, background, agua);

	renderizar_gusano(renderer, sprites, jugador);

	renderizar_nombre(renderer, font, jugador);
	renderizar_vida(renderer, font, jugador);

	renderizar_posicion(renderer, font, jugador);

	renderer.Present();
}

void Vista::renderizar_mapa(SDL2pp::Renderer &renderer, SDL2pp::Texture &viga, SDL2pp::Texture &background, SDL2pp::Texture &agua) {
	int vcenter = renderer.GetOutputHeight() / 2;

	renderer.Copy(background, NullOpt, NullOpt);
	renderer.Copy(agua, NullOpt, NullOpt);

	for (int i = 0; i < renderer.GetOutputWidth(); i += 50) {
		renderer.Copy(
				viga,
				Rect(0, 0, 50, 50),
				Rect(i, vcenter, 50, 50)
			);
	}
}

void Vista::renderizar_gusano(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, Jugador &jugador) {
	int vcenter = renderer.GetOutputHeight() / 2;

	int src_x = 0, src_y = 0;
	if (jugador.gusano_moviendose) {
		src_x = 0;
		src_y = ALTO_SPRITE * jugador.run_phase;
		sprites.Update(NullOpt, Surface(DATA_PATH "/gusano_caminando_derecha.png").SetColorKey(true, 0));

	} else if (jugador.gusano_moviendose_izquierda) {
		src_x = 0;
		src_y = ALTO_SPRITE * jugador.run_phase;
		sprites.Update(NullOpt, Surface(DATA_PATH "/gusano_caminando_izquierda.png").SetColorKey(true, 0));
	}

	sprites.SetAlphaMod(255);
	renderer.Copy(
			sprites,
			Rect(src_x, src_y, 50, 50),
			Rect((int)jugador.gusano_posicion, vcenter - 42, 50, 50)
		);
}

void Vista::renderizar_nombre(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Jugador &jugador) {
	int vcenter = renderer.GetOutputHeight() / 2;

	Rect borde((int)jugador.gusano_posicion + 6, vcenter - 77, 50, 21);
	Color blanco(255, 255, 255, 255);
	renderer.SetDrawColor(blanco);
	renderer.FillRect(borde);

	Rect contenedor((int)jugador.gusano_posicion + 8, vcenter - 75, 46, 17);
	Color negro(0,0,0,255);
	renderer.SetDrawColor(negro);
	renderer.FillRect(contenedor);

	Surface surface = font.RenderText_Solid(jugador.nombre, blanco);
	Texture texture(renderer, surface);

	Rect nombre((int)jugador.gusano_posicion + 18, vcenter - 75, surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, NullOpt, nombre);
}

void Vista::renderizar_vida(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Jugador &jugador) {
	int vcenter = renderer.GetOutputHeight() / 2;

	Rect borde((int)jugador.gusano_posicion + 16, vcenter - 52, 29, 21);
	Color blanco(255, 255, 255, 255); 
	renderer.SetDrawColor(blanco);
	renderer.FillRect(borde);

	Rect contenedor((int)jugador.gusano_posicion + 18, vcenter - 50, 25, 17);
	Color negro(0,0,0,255);
	renderer.SetDrawColor(negro); 
	renderer.FillRect(contenedor);

	Surface surface = font.RenderText_Solid(std::to_string(jugador.vida), blanco);
	Texture texture(renderer, surface);

	Rect vida((int)jugador.gusano_posicion + 18, vcenter - 50, surface.GetWidth(), surface.GetHeight());
	renderer.Copy(texture, NullOpt, vida);
}

void Vista::renderizar_posicion(SDL2pp::Renderer &renderer, SDL2pp::Font &font, Jugador &jugador) {
	std::string texto = obtener_texto(jugador);

	Texture text_sprite(
			renderer,
			font.RenderText_Blended(texto, SDL_Color{255, 255, 255, 255})
		);

	renderer.Copy(text_sprite, NullOpt, Rect(0, 0, text_sprite.GetWidth(), text_sprite.GetHeight()));
}

void Vista::actualizar(SDL2pp::Renderer &renderer, Jugador &jugador, unsigned int &frame_ticks, unsigned int &frame_delta) {

	if (jugador.gusano_moviendose) {
		jugador.gusano_posicion += frame_delta * 0.2;
		jugador.run_phase = (frame_ticks / 100) % 8;
	} else if (jugador.gusano_moviendose_izquierda) {
		jugador.gusano_posicion -= frame_delta * 0.2;
		jugador.run_phase = (frame_ticks / 100) % 8;
	} else {
		jugador.run_phase = 0;
	}

	if (jugador.gusano_posicion > renderer.GetOutputWidth()) {
		jugador.gusano_posicion = -ANCHO_SPRITE;
	}
	
	else if (jugador.gusano_posicion < -ANCHO_SPRITE) {
		jugador.gusano_posicion = renderer.GetOutputWidth();
	}
}

std::string Vista::obtener_texto(Jugador &jugador) {
	std::string text = "gusano_posicion: " + std::to_string((int)jugador.gusano_posicion) + ", running: " + (jugador.gusano_moviendose ? "true" : "false");
	return text;
}
