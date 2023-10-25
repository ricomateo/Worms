#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket &skt) : skt(skt) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::sendPosition(Dto *dto, bool &was_closed)
{
    uint32_t x = htonl(dto->x_pos());
    uint32_t y = htonl(dto->y_pos());

    skt.sendall(&(x), sizeof(x), &was_closed);
    skt.sendall(&(y), sizeof(y), &was_closed);
}

void ServerProtocol::sendMap(Dto *dto, bool &was_closed)
{
    uint16_t sz = htons((dto->return_line()).size());
    skt.sendall(&(sz), sizeof(sz), &was_closed);
    skt.sendall((dto->return_line()).c_str(), (dto->return_line()).size(), &was_closed);
}

uint8_t ServerProtocol::recv_comand(bool &was_closed)
{
    uint8_t comando;

    skt.recvall(&comando, sizeof(comando), &was_closed);

    if (was_closed)
        return 0;

    return comando;
}

Dto *ServerProtocol::handle_dir(bool &was_closed, uint8_t code)
{

    if (was_closed)
        return new DeadDto();

    uint8_t mode;
    skt.recvall(&mode, sizeof(mode), &was_closed);

    if (was_closed)
        return new DeadDto();

    return new Dir(mode);
}

Dto *ServerProtocol::handle_jump(bool &was_closed, uint8_t code)
{

    if (was_closed)
        return new DeadDto();

    uint8_t mode;
    skt.recvall(&mode, sizeof(mode), &was_closed);

    if (was_closed)
        return new DeadDto();

    return new Jump(mode);
}

Dto *ServerProtocol::decode(bool &was_closed)
{
    if (was_closed)
        return new DeadDto();
    Dto *dto;
    uint8_t comando = recv_comand(was_closed);

    if (comando == 4)
        dto = new Move();
    else if (comando == 3)
        dto = handle_dir(was_closed, comando);
    else
        dto = handle_jump(was_closed, comando);

    return dto;
}

// void ServerProtocol::send_position(bool &was_closed, std::vector<uint32_t> pos)
// {
//     uint32_t x = htonl(pos[1]);
//     uint32_t y = htonl(pos[0]);

//     skt.sendall(&(x), sizeof(x), &was_closed);
//     skt.sendall(&(y), sizeof(y), &was_closed);
// }
