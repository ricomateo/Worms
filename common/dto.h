#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <string>
#include <vector>

const char VACIO[] = "";
const uint8_t MOVE_CODE = 1;
const uint8_t DIR_CODE = 2;
const uint8_t JUMP_CODE = 3;
const uint8_t MAP_CODE = 4;
const uint8_t POS_CODE = 5;
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

    virtual std::string return_line();
    virtual uint8_t orientation();
    virtual bool is_alive();
    virtual uint32_t x_pos();
    virtual uint32_t y_pos();
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

class Position : public Dto
{
private:
    uint32_t x;
    uint32_t y;

public:
    Position(std::vector<uint32_t> pos);
    ~Position();
    bool is_alive() override;
    uint32_t x_pos() override;
    uint32_t y_pos() override;
};

class MapLine : public Dto
{
private:
    std::string line;

public:
    MapLine(std::string l);
    ~MapLine();
    bool is_alive() override;
    std::string return_line() override;
};

#endif
