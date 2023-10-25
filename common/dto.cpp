#include "dto.h"

Dto::Dto() {}

Dto::Dto(uint8_t code) : code(code) {}

Dto::~Dto() {}

uint8_t Dto::return_code() { return code; }

uint8_t Dto::orientation() { return 1; }

std::string Dto::return_line() { return VACIO; }

bool Dto::is_alive() { return false; }

uint32_t Dto::x_pos() { return 0; }
uint32_t Dto::y_pos() { return 0; }
/*--------------------------------------------------------------------------------------------*/
/*-------------------------------DEAD_MESSAGE-------------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/

DeadDto::DeadDto() : Dto() {}

DeadDto::~DeadDto() {}

bool DeadDto::is_alive() { return false; }

/*--------------------------------------------------------------------------------------------*/
/*-------------------------------DEAD_MESSAGE-------------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/

Move::Move() : Dto(MOVE_CODE) {}

Move::~Move() {}

bool Move::is_alive() { return true; }

/*--------------------------------------------------------------------------------------------*/
/*-------------------------------DEAD_MESSAGE-------------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/

Dir::Dir(uint8_t m) : Dto(DIR_CODE), mode(m) {}

Dir::~Dir() {}

bool Dir::is_alive() { return true; }

uint8_t Dir::orientation() { return mode; }

/*--------------------------------------------------------------------------------------------*/
/*-------------------------------DEAD_MESSAGE-------------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/

Jump::Jump(uint8_t m) : Dto(JUMP_CODE), mode(m) {}

Jump::~Jump() {}

bool Jump::is_alive() { return true; }

uint8_t Jump::orientation() { return mode; }

/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////

MapLine::MapLine(std::string l) : Dto(MAP_CODE), line(l) {}

MapLine::~MapLine() {}

bool MapLine::is_alive() { return true; }

std::string MapLine::return_line() { return line; }

Position::Position(std::vector<uint32_t> pos) : Dto(POS_CODE), x(pos[1]), y(pos[0]) {}

Position::~Position() {}

bool Position::is_alive() { return true; }
uint32_t Position::x_pos() { return x; }
uint32_t Position::y_pos() { return y; }