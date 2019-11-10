#ifndef GOALKEEPER_H
#define GOALKEEPER_H

#include "mathLib3D.h"
#include <time.h>
#include <stdlib.h>

class GoalKeeper 
{
    public:
        GoalKeeper(float difflevel, float x, float y, float z);
        Point3D position;
        float speed;
        float difficulty;

        float outfitColor[3];
        float skinColor[3];
        float hairColor[3];

        void changeColors(float r, float g, float b, char option);

    private:
        float getRandomFloat();

};

#endif