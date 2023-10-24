#include "receiver_thread.h"

void Receiver::broadcastDto(Dto *dto)
{
    if (dto->return_code() == MOVE__CODE)
        broadcaster.addMoveToQueues(dto);
    else if (dto->return_code() == DIR__CODE)
        broadcaster.addDirToQueues(dto);
    else
        broadcaster.addJumpToQueues(dto);
}
void Receiver::run()
{
    while (not was_closed)
    {
        Dto *dto = protocol.decode(was_closed);

        if (dto->is_alive())
        {
            broadcastDto(dto);
        }
        else
        {
            was_closed = true;
            delete dto;
        }
    }
    broadcaster.removeQueueFromList(&queue);
}

Receiver::Receiver(ServerProtocol &p, BlockingQueue &q, Broadcaster &b) : protocol(p), queue(q), broadcaster(b), was_closed(false) {}
