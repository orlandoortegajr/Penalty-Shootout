#include "goalkeeper.h"

GoalKeeper::GoalKeeper(float difflevel, float x, float y, float z)
{
    this->position = Point3D(x, y, z);
    this->difficulty = difflevel;
    this->speed = 1.0;

    //for testing purposes setting all colors to white

    for(int i = 0; i < 3; i++)
        this->hairColor[i] = 0;

    for (int i = 0; i < 3; i++)
        this->outfitColor[i] = 0;

    for (int i = 0; i < 3; i++)
        this->skinColor[i] = 0;
}

void GoalKeeper::changeColors(float r, float g, float b, char option)
{
    switch (option)
    {
        //outfit color change
        case 'o':
            this->outfitColor[0] = r;
            this->outfitColor[1] = g;
            this->outfitColor[2] = b;
            break;

        //skin color change
        case 's':
            this->skinColor[0] = r;
            this->skinColor[1] = g;
            this->skinColor[2] = b;
            break;
        
        //hair color change
        case 'h':
            this->hairColor[0] = r;
            this->hairColor[1] = g;
            this->hairColor[2] = b;
            break;

        default:
            break;
    }
}

//get float value from 0.0 to 1.0
float GoalKeeper::getRandomFloat()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}
