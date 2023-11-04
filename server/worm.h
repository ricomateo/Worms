#include "box2d/box2d.h"
#include <list>

class Worm
{
private:
    b2Body *body;
    float x;
    float y;
    uint8_t id;
    uint8_t hp;
    bool is_alive;

public:
    bool isRunning;
    Worm(b2World *b2world, float x, float y, uint8_t id);
    float getXCoordinate();
    float getYCoordinate();
    uint8_t getId();
    void moveLeft();
    void moveRight();
    b2Body* getBody();
    void bat(std::list<Worm*>& worms);
    void makeDamage(uint8_t damage);
    uint8_t getHp();
    bool isAlive(); // Delete
    bool isMoving();
    ~Worm();
};
