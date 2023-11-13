#include "bazooka_rocket.h"
#include "worm.h"


BazookaRocket::BazookaRocket(b2World *world, float x, float y, float angle) {
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.userData.pointer = (uintptr_t)this;
	body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.15f, 0.025f);
    b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.5f;
    fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xFD;
    body->CreateFixture(&fixtureDef);

    /*b2FixtureDef fixtureDef2;
    b2PolygonShape dynamicBox2;
	dynamicBox2.SetAsBox(0.05f, 0.05f, b2Vec2(0.015f, 0.0f), 0);
    fixtureDef2.shape = &dynamicBox2;
	fixtureDef2.density = 5.0f;
    fixtureDef2.filter.categoryBits = 0x02;
    fixtureDef2.filter.maskBits = 0xFD;

    body->CreateFixture(&fixtureDef2);*/


    body->SetTransform(b2Vec2(x, y), angle);
}


float BazookaRocket::getXCoordinate() {
    return body->GetPosition().x;
}

float BazookaRocket::getYCoordinate() {
    return body->GetPosition().y;
}

float getDistance(float x1, float y1, float x2, float y2) {
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}


void BazookaRocket::shoot(Direction direction, float angle, int power) {
    
    float xComponent = (float(power) / 10.0f ) * cos(angle);
    float yComponent = (float(power) / 10.0f ) * sin(angle);
    if (direction == LEFT) {
        body->ApplyLinearImpulseToCenter(b2Vec2(-xComponent, yComponent), true);
    } else if (direction == RIGHT) {
        body->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
    } else {
        throw std::runtime_error("Invalid direction");
    }
    dir = direction;
}



void BazookaRocket::startContact() {
    if (exploded) return;
    explode();
}
    
void BazookaRocket::endContact() {}

void BazookaRocket::explode() {
    float xComponent; float yComponent;
    for ( b2Body* b = body->GetWorld()->GetBodyList(); b; b = b->GetNext())
    {   
        float distance = getDistance(body->GetPosition().x, body->GetPosition().y,
                                     b->GetPosition().x, b->GetPosition().y);
        if (b->GetType() == b2_dynamicBody && distance < 4.0f && distance != 0.0f) {
            Entity *entity = (Entity*)b->GetUserData().pointer;
	  
            if (entity != NULL) {
                if ((entity->entityType == WORM)) {;
                    Worm *worm = (Worm*)entity;
                    worm->takeDamage(30);
                }
            } 
            xComponent = 5*(b->GetPosition().x - body->GetPosition().x) / distance;
            yComponent = abs(b->GetPosition().y - body->GetPosition().y) + 5.0f;
            b->ApplyLinearImpulseToCenter(b2Vec2(xComponent, yComponent), true);
        }
    }
    exploded = true;
}


float BazookaRocket::getAngle() {
    return body->GetAngle() * 180.0f / 3.14f;
}


void BazookaRocket::updateAngle() {
    float angle = atan2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
    body->SetTransform(body->GetPosition(), angle);
}

BazookaRocket::~BazookaRocket() {}