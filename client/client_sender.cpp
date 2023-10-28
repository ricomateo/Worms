#include "client_sender.h"

SenderTH::SenderTH(ClientProtocol &p, Queue<Dto *> &q, Broadcaster &b) : protocol(p), queue(q), broadcaster(b), was_closed(false) {}

void SenderTH::run()
{
    std::string data;
    while (not was_closed)
    {
        Dto *dto = queue.pop();
        // std::cout << "send: " << dto->is_alive() << std::endl;

        if (dto->is_alive())
        {
            send(dto);
            protocol.send(was_closed);
        } // se lo mando al protocolo
        else
            was_closed = true;

        delete dto;
    }
}

void SenderTH::send(Dto *d)
{
    if (d->return_code() == MOVER_A_DERECHA)
        protocol.moverADerecha((MoverADerecha *)d, was_closed);
    else
        ;
}
