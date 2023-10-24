#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include <cstring>
#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "blockingqueue.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"
#include "juego.h"

const uint8_t CODE_MOVE = 1;
const uint8_t CODE_DIR = 2;
const uint8_t CODE_JUMP = 3;

struct Sender : public Thread
{
private:
    ServerProtocol &protocol;
    BlockingQueue &queue;

public:
    bool was_closed;

    Sender(ServerProtocol &p, BlockingQueue &q);
    void run() override;
};

#endif
