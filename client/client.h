#ifndef CLIENT_CLASS_H
#define CLIENT_CLASS_H

#include <chrono>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

const char CHAT[] = "Chat";
const char READ[] = "Read";
const char EXIT[] = "Exit";

#include "client_protocol.h"
#include "dto.h"
#include "socket.h"

class Client
{
public:
    explicit Client(Socket &&socket);
    ~Client();
    void start();

private:
    Socket skt;
    ClientProtocol protocolo;
    bool was_closed;
    std::vector<std::vector<char>> matriz;
    uint32_t x;
    uint32_t y;
    int filas;
    int columnas;

    void encode(std::string data);
    void receiveNTimes(std::string data, size_t pos);
    void closeEverything();
    void chargeMap();
    void addLineToMap(Dto *dto, int fila);
    void imprimirMapa();
    void receivePosition();
};
#endif
