#include "client_protocol.h"

ClientProtocol::ClientProtocol(Socket &skt) : skt(skt) {}

ClientProtocol::~ClientProtocol() {}

// int findNextWord(std::string str, int pos)
// {
//     while (str[pos] == ESPACIO)
//         (pos)++;

//     return pos;
// }

// void ClientProtocol::sendChatMsj(std::string str, bool &was_closed)
// {
//     if (was_closed)
//         return;

//     int pos = strlen(CHAT_ESPACIO);
//     int position = findNextWord(str, pos);
//     std::string msg = str.substr(position);

//     uint16_t lenght = htons(msg.size());

//     skt.sendall(&CHAT_CODE, sizeof(CHAT_CODE), &was_closed);
//     if (was_closed)
//         return;

//     skt.sendall(&lenght, sizeof(lenght), &was_closed);
//     if (was_closed)
//         return;

//     skt.sendall(msg.c_str(), msg.size(), &was_closed);
//     if (was_closed)
//         return;
// }

// Dto *ClientProtocol::receiveChatMessage(bool &was_closed)
// {
//     if (was_closed)
//         return new DeadDto();

//     uint16_t sz;
//     skt.recvall(&sz, sizeof(sz), &was_closed);
//     if (was_closed)
//         return new DeadDto();

//     uint16_t lenght = ntohs(sz);

//     std::vector<char> msg(lenght);
//     skt.recvall(msg.data(), msg.size(), &was_closed);
//     if (was_closed)
//         return new DeadDto();

//     std::string message(msg.begin(), msg.end());

//     return new ChatMessage(message);
// }

// Dto *ClientProtocol::receiveNumberOfPlayers(bool &was_closed)
// {
//     uint8_t number_of_players;
//     skt.recvall(&number_of_players, sizeof(number_of_players), &was_closed);

//     if (was_closed)
//         return new DeadDto();

//     return new PlayersMessage(number_of_players);
// }

// Dto *ClientProtocol::receive(bool &was_closed)
// {

//     uint8_t code;
//     skt.recvall(&code, sizeof(code), &was_closed);
//     if (was_closed)
//         return new DeadDto();

//     if (code == CHAT_MSG_CODE)
//         return receiveChatMessage(was_closed);
//     else
//         return receiveNumberOfPlayers(was_closed);
// }

void ClientProtocol::handle_move(bool &was_closed)
{
    uint8_t cmd = 4;
    skt.sendall(&cmd, sizeof(cmd), &was_closed);
}

void ClientProtocol::handle_jump(uint8_t orientacion, bool &was_closed)
{
    uint8_t cmd = 5;
    skt.sendall(&cmd, sizeof(cmd), &was_closed);
    skt.sendall(&orientacion, sizeof(orientacion), &was_closed);
}

void ClientProtocol::handle_dir(uint8_t orientacion, bool &was_closed)
{
    uint8_t cmd = 3;
    skt.sendall(&cmd, sizeof(cmd), &was_closed);
    skt.sendall(&orientacion, sizeof(orientacion), &was_closed);
}

void ClientProtocol::recibir_posicion(bool &was_closed)
{
    uint32_t pos_x;
    uint32_t pos_y;

    skt.recvall(&pos_x, sizeof(pos_x), &was_closed);
    skt.recvall(&pos_y, sizeof(pos_y), &was_closed);

    uint32_t x = ntohl(pos_x);
    uint32_t y = ntohl(pos_y);

    printf("%u %u\n", x, y);
}
