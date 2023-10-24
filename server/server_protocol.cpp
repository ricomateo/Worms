#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket &skt) : skt(skt) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::players_message(bool &was_closed, uint8_t number_of_clients)
{
    skt.sendall(&PLAYER_CNT_CODE, sizeof(PLAYER_CNT_CODE), &was_closed);

    if (was_closed)
        return;

    skt.sendall(&number_of_clients, sizeof(number_of_clients), &was_closed);

    if (was_closed)
        return;
}

void ServerProtocol::chat_message(bool &was_closed, const std::string &msj)
{
    uint16_t tam = htons(msj.size());

    skt.sendall(&CHAT_MSG_CODE, sizeof(CHAT_MSG_CODE), &was_closed);

    if (was_closed)
        return;

    skt.sendall(&tam, sizeof(tam), &was_closed);

    if (was_closed)
        return;

    skt.sendall(msj.c_str(), msj.size(), &was_closed);

    if (was_closed)
        return;
}

void ServerProtocol::send(bool &was_closed, Dto *msj)
{

    if (was_closed)
        return;

    if (msj->code() == CHAT_MSG_CODE)
        chat_message(was_closed, msj->message());
    else if (msj->code() == PLAYER_CNT_CODE)
        players_message(was_closed, msj->playersCount());
    else
        return;
}

uint8_t ServerProtocol::recv_comand(bool &was_closed)
{
    uint8_t comando;

    skt.recvall(&comando, sizeof(comando), &was_closed);

    if (was_closed)
        return 0;

    return comando;
}

uint16_t ServerProtocol::recv_size_of_message(bool &was_closed)
{
    if (was_closed)
        return 0;

    uint16_t sz;
    skt.recvall(&sz, sizeof(sz), &was_closed);

    if (was_closed)
        return 0;

    uint16_t sz_2 = ntohs(sz);
    return sz_2;
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

void ServerProtocol::send_position(bool &was_closed, std::vector<uint32_t> pos)
{
    uint32_t x = htonl(pos[1]);
    uint32_t y = htonl(pos[0]);

    skt.sendall(&(x), sizeof(x), &was_closed);
    skt.sendall(&(y), sizeof(y), &was_closed);
}
