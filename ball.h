#ifndef BALL_H
#define BALL_H

#include "mathLib3D.h"

class Ball{
public:
    Ball(float forceZ, float dirY, float speedX); // Initialization With All Values as 0
    Ball(Point3D pos, Vec3D dir, float friction, float spd); // Initialization With Given Values
    Point3D position; // Current Position of the Ball
    Vec3D direction; // Direction the Ball Will Travel
    float friction; // Percentage of Friction, i.e. 90 => 10% Lost to Friction
    float speed; // Speed the Ball is Kicked
    float gravity = 1;
    float initialGravity = 1;
    float kickzSpeed;
    void draw(); // Draws Ball At its Current Position
    void update(); // Updates Ball's Position using Speed, Direction and Friction
};

#endif