#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

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

#include "blockingqueue.h"
#include "broadcaster.h"
#include "receiver_thread.h"
#include "sender_thread.h"
#include "socket.h"
#include "thread.h"
#include "server_protocol.h"
#include "juego.h"

class ServerClient
{
public:
    ServerClient(Socket &&socket, Broadcaster &b, Juego &j);
    ~ServerClient();
    bool is_dead();
    void join();
    void kill();
    void start();

    BlockingQueue queue;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

private:
    Socket skt;
    Broadcaster &broadcaster;
    Juego &game;
    ServerProtocol serverproto;
    Receiver recv_th;
    Sender send_th;
};
#endif
