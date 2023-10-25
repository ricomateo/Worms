#include <iostream>
#include <list>
#include <thread>
#include <vector>

#include <netinet/in.h>

#include "broadcaster.h"
#include "socket.h"
#include "thread.h"
#include "server_client.h"
#include "server_protocol.h"

struct Aceptador : public Thread
{
private:
    std::list<ServerClient *> clients; // no es recurso compartido
    Socket &skt;
    Broadcaster broadcaster;

public:
    void run() override
    {
        Juego game("escenarios.txt");
        game.armar_escenario(); // armo el escenario 1 sola vez y se lo paso a los clientes
        while (_keep_running)
        {
            Socket peer = skt.accept();

            ServerClient *th = new ServerClient(std::move(peer), std::ref(broadcaster), std::ref(game));
            th->start();

            reap_dead();

            clients.push_back(th);
            broadcaster.addQueueToList(std::ref(th->queue));
            broadcastMap(std::ref(game), std::ref(th->queue));
        }
        kill_all();
    }

    void kill_all()
    {
        for (auto &c : clients)
        {
            c->kill();
            c->join();
            delete c;
        }
        broadcaster.deleteAllQueues();
        clients.clear();
    }

    void stop_running() { _keep_running = false; }

    void reap_dead()
    {
        bool was_removed = false;
        BlockingQueue *client_queue;

        clients.remove_if([&](ServerClient *c)
                          {
            if (c->is_dead()) {
                c->join();
                was_removed = true;
                client_queue = &c->queue;  // obtengo el puntero de la queue para eliminarlo despues
                delete c;
                return true;
            }
            return false; });
        if (was_removed)
            broadcaster.removeQueueFromList(client_queue);
    }

    void broadcastMap(Juego &g, BlockingQueue &q)
    {
        int cant_filas = g.filas();
        for (int fila = 0; fila < cant_filas; fila++)
        {
            std::string l = g.mapa_fila(fila);
            Dto *d = new MapLine(l);
            broadcaster.sendLineMap(d);
        }

        Dto *dead = new MapLine(std::string("fin"));
        broadcaster.sendLineMap(dead);

        Dto *pos = new Position(g.posicionGusano());
        broadcaster.addPositionToQueues(pos, g.posicionGusano());
    }

    explicit Aceptador(Socket &skt) : skt(skt) {}
};
