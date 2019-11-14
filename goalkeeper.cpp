#include "goalkeeper.h"

Goalkeeper::Goalkeeper()
{
    this->position = Point3D(0, 0, 0);
    this->difficulty = 0;
    this->speed = 1.0;

    this->gkReachedPost = false;

    //set outfit color to green
    this->setColors(0,1,0,'o');

    //skin color = blue
    this->setColors(0,0,1,'s');

    //number of faces for cube
    this->numFaces = 6;
}

void Goalkeeper::drawGKFaceIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {
        glColor3fv(this->skinColor);
        this->drawGKFace(i);
    }
}

void Goalkeeper::drawGKBodyIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {
        glColor3fv(this->outfitColor);
        this->drawGKBody(i);
    }
}

void Goalkeeper::drawGKLegIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {
        glColor3fv(this->outfitColor);
        this->drawGKLeg(i);
    }
}

void Goalkeeper::drawGKArmIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {
        glColor3fv(this->skinColor);
        this->drawGKArm(i);
    }
}

//x coordinate is depth, y is horizontal and z is vertical
void Goalkeeper::drawGK()
{
    //head
    glPushMatrix();
        glTranslatef(18, 0, 1.45);
        this->drawGKFaceIndex();
    glPopMatrix();

    //body
    glPushMatrix();
        glTranslatef(18, 0, 0.95);
        this->drawGKBodyIndex();
    glPopMatrix();

    //right leg
    glPushMatrix();
        glTranslatef(18, 0.085, 0.3);
        this->drawGKLegIndex();
    glPopMatrix();

    //left leg
    glPushMatrix();
        glTranslatef(18, -0.085, 0.3);
        this->drawGKLegIndex();
    glPopMatrix();

    //rght arm
    glPushMatrix();
        glTranslatef(18, 0.27, 1);
        // glRotatef(45, 0, 0, 0);
        this->drawGKArmIndex();
    glPopMatrix();

    // left arm
    glPushMatrix();
        glTranslatef(18, -0.27, 1);
        // glRotatef(-45, 0, 0, 0);
        this->drawGKArmIndex();
    glPopMatrix();
}

void Goalkeeper::gkSideways()
{
    for(int i = 0; i < 8; i++){

        if (this->gkReachedPost == false)
        {
            this->headVerts[i][1] += 0.01;
            this->bodyVerts[i][1] += 0.01;
            this->legVerts[i][1] += 0.01;
            this->armVerts[i][1] += 0.01;

            if (this->bodyVerts[i][1] >= 2.6)
            {
                gkReachedPost = true;
            }
        }

        if (this->gkReachedPost == true)
        {
            this->headVerts[i][1] -= 0.01;
            this->bodyVerts[i][1] -= 0.01;
            this->legVerts[i][1] -= 0.01;
            this->armVerts[i][1] -= 0.01;

            if(this->bodyVerts[i][1] <= -2.6) {
                gkReachedPost = false;
            }
        }   

        
    }
}

void Goalkeeper::setColors(float r, float g, float b, char option)
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

        default:
            break;
    }
}

void Goalkeeper::drawGKFace(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->headVerts[vIndex]);
    }
    glEnd();
}

void Goalkeeper::drawGKBody(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->bodyVerts[vIndex]);
    }
    glEnd();
}

void Goalkeeper::drawGKLeg(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->legVerts[vIndex]);
    }
    glEnd();
}

void Goalkeeper::drawGKArm(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->armVerts[vIndex]);
    }
    glEnd();
}

//get float value from 0.0 to 1.0
float Goalkeeper::getRandomFloat()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}
