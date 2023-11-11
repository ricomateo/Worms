# Worms 

Taller de Programación I (75.42) - [2C 2023] - FIUBA 

Trabajo final que consiste en la remake del icónico Worms

## Grupo 2

* **Integrante 1** - [Alan Valdevenito](https://github.com/AlanValdevenito)
* **Integrante 2** - [Mateo Julián Rico](https://github.com/ricomateo)
* **Integrante 3** - [Federico Solari Vazquez](https://github.com/FedericoSolari)

**Corrector:** [Martin Di Paola](https://github.com/eldipa)

## Documentacion requerida

* Manual de usuario: ...
* Documentacion tecnica: Debe contener la información necesaria para que otro desarrollador puede entender la arquitectura e incluso continuar con el desarrollo del proyecto.
* Manual de proyecto: Documentación corta para indicar en que trabajó cada integrante del equipo, como se organizaron por semana y cuanto difirió del plan inicial.

## Dependencias

* cmake
* build-essential
* qt5-default
* libsdl2-dev
* libsdl2-image-dev
* libsdl2-ttf-dev
* libyaml-cpp-dev

## Instalacion

Nota: En un futuro se debe crear un .sh que automatice toda la instalacion descripta a continuacion.

### Instalacion de CMake

Instalar desde una terminal:

```
sudo apt-get -y install cmake
```

### Instalacion de SDL2pp

Instalar desde una terminal las dependencias:

```
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev
```

Bajar los fuentes de [libsdl2-image](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3), [libsdl2-mixer](https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3)  y [libsdl2-ttf](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2) en formato zip. Para cada uno se debe descomprimir, compilar e instalar de la siguiente forma:

```
cd carpeta_sdl_x
mkdir build
cd build
cmake ..
make -j4
sudo make install
```

Compilar e instalar la version 0.18.1 de libsdl2pp:

```
cd libSDL2pp-0.18.1
mkdir build
cd build
cmake ..
make -j4
sudo make install
```

[Repositorio oficial](https://github.com/libsdl-org/SDL_image/tree/release-2.6.3)

### Instalacion de QT

Instalar desde una terminal:

```
sudo apt install -y qtcreator qtbase5-dev qt5-qmake cmake
```

[Repositorio oficial](https://github.com/erincatto/box2d)

### Instalacion de YAML

Instalar desde una terminal:

```
sudo apt update
sudo apt install libyaml-cpp-dev
```

Verificar instalacion desde una terminal:

```
dpkg -l libyaml-cpp*
```

[Repositorio oficial](https://github.com/jbeder/yaml-cpp)

## Compilacion

Compilar:

```
mkdir build
cd build
sudo cmake ..
make
```

## Ejecucion

En una primer terminal:

```
./server 8080
```

En una segunda terminal:

```
./client 127.0.0.1 8080
```

## Licencia

Este repositorio se encuentra bajo la Licencia MIT.
