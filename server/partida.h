#ifndef PARTIDA_H
#define PARTIDA_H

#include <atomic>
#include <chrono>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <memory>

#include "queue.h"
#include "broadcaster.h"
#include "receiver_thread.h"
#include "sender_thread.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"
#include "server_client.h"
#include "game.h"
#include "dto.h"

class Partida
{
public:
    Partida(uint8_t id, int cant);
    ~Partida();
    void start();
    void sendMapTo(ServerClient *c);
    void finish();
    void forceFinish();
    uint8_t getId();
    bool is_dead();
    void join();

private:
    Queue<std::shared_ptr<Dto>> common_queue;
    Broadcaster broadcaster;
    Game game;
    uint8_t id;
    int jugadores;
    int conectados;
    std::list<ServerClient *> clients;
};
#endif
