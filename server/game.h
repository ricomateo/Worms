#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <iostream>
#include <exception>
#include <list>
#include "box2d/box2d.h"
#include "world.h"
#include "server_protocol.h"
#include "thread.h"
#include "queue.h"
#include "broadcaster.h"
#include "dto.h"
#include "viga.h"
#include "gusano.h"

const uint8_t MOVER_A_DERECHA_CODE = 3;

class Game : public Thread
{
private:
    Queue<Dto *> &common_queue;
    Broadcaster &broadcaster;
    World world;

public:
    bool game_finished;
    Game(Queue<Dto *> &queue, Broadcaster &broadcaster);
    void update();
    void run() override;
    void stop() override;
    void sendMap(Queue<Dto *> &q);
    void sendWorms(Queue<Dto *> &q);
    void moveWormRight();
    void executeCommand(Dto *dto);
    void broadcast();
};
#endif
