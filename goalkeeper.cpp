#include "goalkeeper.h"

Goalkeeper::Goalkeeper()
{
    this->position = Point3D(0, 0, 0);
    this->difficulty = 0;
    this->speed = 0.05;
    this->size = 1.35;

    this->gkReachedPost = false;

    //set outfit color to green
    this->setColors(0,1,0,'o');

    //skin color = blue
    this->setColors(0,0,1,'s');

    //number of faces for cube
    this->numFaces = 6;

    //size
    this->setSize(size);

    //set main translation
    this->setStartingTranslation();

    // //set translations based on size
    this->setSizeTranslation();

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

void Goalkeeper::drawGKRightLegIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {
        glColor3fv(this->outfitColor);
        this->drawGKRightLeg(i);
    }
}

void Goalkeeper::drawGKLeftLegIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {
        glColor3fv(this->outfitColor);
        this->drawGKLeftLeg(i);
    }
}

void Goalkeeper::drawGKRightArmIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {
        glColor3fv(this->skinColor);
        this->drawGKRightArm(i);
    }
}

void Goalkeeper::drawGKLeftArmIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {
        glColor3fv(this->skinColor);
        this->drawGKLeftArm(i);
    }
}

//x coordinate is depth, y is horizontal and z is vertical
void Goalkeeper::drawGK()
{

        //head
        this->drawGKFaceIndex();


        //body

        this->drawGKBodyIndex();
 
        //right leg

        this->drawGKRightLegIndex();

        //left leg

        this->drawGKLeftLegIndex();

        //rght arm

            // glRotatef(45, 0, 0, 0);
        this->drawGKRightArmIndex();

        // left arm
            // glRotatef(-45, 0, 0, 0);
        this->drawGKLeftArmIndex();

}

void Goalkeeper::gkSideways()
{
    for(int i = 0; i < 8; i++){

        if (this->bodyVerts[0][1] >= 2)
        {
            gkReachedPost = true;
            // resetLeftVertices();
        } else if (this->bodyVerts[0][1] <= -2.6)
        {
            gkReachedPost = false;
            // resetRightVertices();
            // std::cout << "Reached right side" << std::endl;
        }
        //right side
        if (this->gkReachedPost == false)
        {
            
            this->headVerts[i][1] += this->speed;
            this->bodyVerts[i][1] += this->speed;
            this->rightLegVerts[i][1] += this->speed;
            this->leftLegVerts[i][1] += this->speed;
            this->rightArmVerts[i][1] += this->speed;
            this->leftArmVerts[i][1] += this->speed;
            // std::cout << headVerts[1][1] << std::endl;

            
        }

        //left side
        if (this->gkReachedPost == true)
        {
            this->headVerts[i][1] -= this->speed;
            this->bodyVerts[i][1] -= this->speed;
            this->rightLegVerts[i][1] -= this->speed;
            this->leftLegVerts[i][1] -= this->speed;
            this->rightArmVerts[i][1] -= this->speed;
            this->leftArmVerts[i][1] -= this->speed;
            // std::cout << headVerts[1][1] << std::endl;
        } 
    }
    if (this->gkReachedPost){
        this->position.py += 0.01;
    }
    if (!(this->gkReachedPost)){
        this->position.py -= 0.01;
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

void Goalkeeper::drawGKRightLeg(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->rightLegVerts[vIndex]);
    }
    glEnd();
}

void Goalkeeper::drawGKLeftLeg(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->leftLegVerts[vIndex]);
    }
    glEnd();
}

void Goalkeeper::drawGKRightArm(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->rightArmVerts[vIndex]);
    }
    glEnd();
}

void Goalkeeper::drawGKLeftArm(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->leftArmVerts[vIndex]);
    }
    glEnd();
}

void Goalkeeper::setSize(float a)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->headVerts[i][j] *= a;
            this->bodyVerts[i][j] *= a;
            this->leftLegVerts[i][j] *= a;
            this->rightLegVerts[i][j] *= a;
            this->leftArmVerts[i][j] *= a;
            this->rightArmVerts[i][j] *= a;
        }
    }
}

void Goalkeeper::setStartingTranslation()
{
    //translations
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                this->headVerts[i][0] += 18;
                this->bodyVerts[i][0] += 18;
                this->leftLegVerts[i][0] += 18;
                this->rightLegVerts[i][0] += 18;
                this->leftArmVerts[i][0] += 18;
                this->rightArmVerts[i][0] += 18;
            }
            else if (j == 1)
            {
                this->headVerts[i][1] += 0;
                this->bodyVerts[i][1] += 0;
                this->rightLegVerts[i][1] += 0.085;
                this->leftLegVerts[i][1] -= 0.085;
                this->rightArmVerts[i][1] += 0.27;
                this->leftArmVerts[i][1] -= 0.27;
            }
            else if (j == 2)
            {
                this->headVerts[i][2] += 1.45;
                this->bodyVerts[i][2] += 0.95;
                this->rightLegVerts[i][2] += 0.3 ;
                this->leftLegVerts[i][2] += 0.3 ;
                this->rightArmVerts[i][2] += 1 ;
                this->leftArmVerts[i][2] += 1 ;
            }
        }
    }
}

void Goalkeeper::setSizeTranslation()
{
    
    for (int i = 0; i < 8; i++)
    {
        if(this->size >= 0.98 && this-> size <= 1.02) {
            break;
        }
        for (int j = 0; j < 3; j++)
        {
            if(this->size >= 1.73 && this-> size <= 1.77) {
                if (j == 1)
                {
                    this->headVerts[i][1] += 0;
                    this->bodyVerts[i][1] += 0;
                    this->rightLegVerts[i][1] += this->size * 0.0857;
                    this->leftLegVerts[i][1] -= this->size * 0.0857;
                    this->rightArmVerts[i][1] += this->size * 0.1;
                    this->leftArmVerts[i][1] -= this->size * 0.1;
                }
                else if (j == 2)
                {
                    this->headVerts[i][2] += this->size * 0.2857;
                    this->bodyVerts[i][2] += this->size * 0.1428;
                    this->rightLegVerts[i][2] += this->size * 0.1142;
                    this->leftLegVerts[i][2] += this->size * 0.1142;
                    this->rightArmVerts[i][2] += this->size * 0.1142;
                    this->leftArmVerts[i][2] += this->size * 0.1142;
                }
            } else {
                if (j == 1)
                {
                    this->headVerts[i][1] += 0;
                    this->bodyVerts[i][1] += 0;
                    this->rightLegVerts[i][1] += this->size * 0.0557;
                    this->leftLegVerts[i][1] -= this->size * 0.0557;
                    this->rightArmVerts[i][1] += this->size * 0.08;
                    this->leftArmVerts[i][1] -= this->size * 0.08;
                }
                else if (j == 2)
                {
                    this->headVerts[i][2] += this->size * 0.2257;
                    this->bodyVerts[i][2] += this->size * 0.1428;
                    this->rightLegVerts[i][2] += this->size * 0.1142;
                    this->leftLegVerts[i][2] += this->size * 0.1142;
                    this->rightArmVerts[i][2] += this->size * 0.1142;
                    this->leftArmVerts[i][2] += this->size * 0.1142;
                }
            }
            
        }
    }
}

//get float value from 0.0 to 1.0
float Goalkeeper::getRandomFloat()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}
