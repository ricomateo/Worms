#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <string>

const char VACIO[] = "";
const uint8_t MOVE_CODE = 1;
const uint8_t DIR_CODE = 2;
const uint8_t JUMP_CODE = 3;
const uint8_t CLIENT_CHAT_CODE = 5;
const uint8_t CODE_PLAYER_CNT = 6;
const uint8_t CODE_CHAT_MESSAGE = 9;

class Dto
{
private:
    uint8_t code;

public:
    Dto();
    explicit Dto(uint8_t code);
    virtual ~Dto();

    virtual uint8_t orientation();
    virtual bool is_alive();
    uint8_t return_code();
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
