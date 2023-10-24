#include "receiver_thread.h"

void Receiver::run()
{
    while (not was_closed)
    {
        Dto *dto = protocol.decode(was_closed);

        if (dto->is_alive())
        {
            if (dto->message() == "move")
                broadcaster.addMoveToQueues(dto);
            else if (dto->message() == "dir")
                broadcaster.addDirToQueues(dto);
            else
                broadcaster.addJumpToQueues(dto);
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
