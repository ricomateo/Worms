#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <string>

const char VACIO[] = "";
const char JUGADORES_N[] = "Jugadores ";
const char COMPLETAR_MESAJE[] = ", esperando al resto de tus amigos...";
const char FIN[] = "mensaje de fin";
const uint8_t CLIENT_CHAT_CODE = 5;
const uint8_t CODE_PLAYER_CNT = 6;
const uint8_t CODE_CHAT_MESSAGE = 9;

class Dto
{
private:
    std::string msg;
    uint8_t mode;

public:
    Dto();
    explicit Dto(const std::string &message);
    virtual ~Dto();

    virtual uint8_t playersCount();
    virtual std::string message();
    virtual uint8_t code();
    virtual uint8_t orientation();
    virtual bool is_alive();
};

class ChatMessage : public Dto
{
private:
    uint8_t dto_code;

public:
    explicit ChatMessage(const std::string &message);
    ChatMessage(const std::string &message, uint8_t cmd);
    ~ChatMessage();
    uint8_t code() override;
    bool is_alive() override;
};

class PlayersMessage : public Dto
{
private:
    const uint8_t dto_code = CODE_PLAYER_CNT;
    uint8_t players;
    std::string msg;

public:
    explicit PlayersMessage(uint8_t a_number);
    ~PlayersMessage();
    uint8_t playersCount() override;
    uint8_t code() override;
    std::string message() override;
    bool is_alive() override;
};

class DeadDto : public Dto
{
public:
    DeadDto();
    ~DeadDto();
    bool is_alive() override;
};

class Move : public Dto
{
public:
    Move();
    ~Move();
    bool is_alive() override;
};

class Jump : public Dto
{
private:
    uint8_t mode;

public:
    Jump(uint8_t m);
    ~Jump();
    bool is_alive() override;
    uint8_t orientation() override;
};

class Dir : public Dto
{
private:
    uint8_t mode;

public:
    Dir(uint8_t m);
    ~Dir();
    bool is_alive() override;
    uint8_t orientation() override;
};

#endif
