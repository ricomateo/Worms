#include "sender_thread.h"

Sender::Sender(ServerProtocol &p, BlockingQueue &q, Juego &game, Broadcaster &b) : protocol(p), queue(q), game(game), broadcaster(b), was_closed(false) {}

void Sender::makeMove(Dto *dto)
{

    if (dto->return_code() == CODE_MOVE)
        game.mover();
    else if (dto->return_code() == CODE_DIR)
        game.invertirDireccion(dto->orientation());
    else if (dto->return_code() == CODE_JUMP)
        game.saltar(dto->orientation());

    Position *pos = new Position(game.posicionGusano());
    broadcaster.addPositionToQueues(pos, game.posicionGusano());
}
void Sender::run()
{
    while (not was_closed)
    {
        Dto *dto = queue.pop();

        if (not dto->is_alive())
        {
            was_closed = true;
            delete dto;
        }

        if (dto->return_code() == 4)
            protocol.sendMap(dto, was_closed);
        else if (dto->return_code() == 5)
            protocol.sendPosition(dto, was_closed);
        else
            makeMove(dto);

        // game.imprimir();

        delete dto;
    }
}
