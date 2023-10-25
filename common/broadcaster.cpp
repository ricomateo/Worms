#include "broadcaster.h"

void Broadcaster::sendLineMap(Dto *dto)
{
    std::unique_lock<std::mutex> lock(mutex);
    BlockingQueue *q = queues.back(); // tomo la ultima queue insertada
    q->push(dto);
}

void Broadcaster::addPositionToQueues(Dto *dto, std::vector<uint32_t> pos)
{
    std::unique_lock<std::mutex> lock(mutex);
    for (auto q : queues)
    {
        Dto *d = new Position(pos);
        q->push(d);
    }
    delete dto;
}

void Broadcaster::addMoveToQueues(Dto *dto)
{
    std::unique_lock<std::mutex> lock(mutex);
    for (auto q : queues)
    {
        Dto *d = new Move();
        q->push(d);
    }
    delete dto;
}

void Broadcaster::addDirToQueues(Dto *dto)
{
    std::unique_lock<std::mutex> lock(mutex);
    for (auto q : queues)
    {
        Dto *d = new Dir(dto->orientation());
        q->push(d);
    }
    delete dto;
}

void Broadcaster::addJumpToQueues(Dto *dto)
{
    std::unique_lock<std::mutex> lock(mutex);
    for (auto q : queues)
    {
        Dto *d = new Jump(dto->orientation());
        q->push(d);
    }
    delete dto;
}

/*
 *  Agrega una cola a la lista de colas.
 */
void Broadcaster::addQueueToList(BlockingQueue &q)
{
    std::unique_lock<std::mutex> lock(mutex);
    queues.push_back(&q);
}

/*
 *  Le agrega un mensaje que indica el fin a la cola del cliente.
 *  Luego elimina una cola de la lista de colas.
 */
void Broadcaster::removeQueueFromList(BlockingQueue *q)
{
    std::unique_lock<std::mutex> lock(mutex);
    DeadDto *dto = new DeadDto();
    for (auto it = queues.begin(); it != queues.end();)
    {
        if (*it == q)
        {
            q->push(dto);
            it = queues.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

/*
 *  Vacia todas las colas que almacena la lista de colas.
 *  Luego vacia la lista de colas.
 */
void Broadcaster::deleteAllQueues()
{
    for (BlockingQueue *queue : queues)
    {
        queue->clear();
    }
    queues.clear();
}
