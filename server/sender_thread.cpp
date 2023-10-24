#include "sender_thread.h"

Sender::Sender(ServerProtocol &p, BlockingQueue &q) : protocol(p), queue(q), was_closed(false) {}

void Sender::run()
{
    Juego game("escenarios.txt");
    game.armar_escenario();
    std::vector<uint32_t> posiciones = game.posicionGusano();
    protocol.send_position(was_closed, posiciones);

    while (not was_closed)
    {
        Dto *dto = queue.pop();

        if (not dto->is_alive())
        {
            was_closed = true;
            delete dto;
        }

        if (dto->message() == "move")
        {
            game.mover();
        }
        else if (dto->message() == "dir")
        {
            game.invertirDireccion(dto->orientation());
        }
        else if (dto->message() == "jump")
        {
            game.saltar(dto->orientation());
        }

        game.imprimir();

        std::vector<uint32_t> pos = game.posicionGusano();
        protocol.send_position(was_closed, pos);

        delete dto;
    }
}
