#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <netinet/in.h>

#include "blockingqueue.h"
#include "dto.h"
#include "socket.h"

const uint8_t PLAYER_CNT_CODE = 6;
const uint8_t CHAT_MSG_CODE = 9;

class ServerProtocol
{
public:
    explicit ServerProtocol(Socket &skt);
    ~ServerProtocol();
    Dto *decode(bool &was_closed);
    void send_position(bool &was_closed, std::vector<uint32_t> pos);

private:
    Socket &skt;
    uint8_t recv_comand(bool &was_closed);
    Dto *handle_dir(bool &was_closed, uint8_t code);
    Dto *handle_jump(bool &was_closed, uint8_t code);
};
#endif
