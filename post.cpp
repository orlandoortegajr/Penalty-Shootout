#include "post.h"

Post::Post()
{
    //set post colors to white
    this->setColors(1,1,1);

    //number of cube faces
    this->numFaces = 6;
}

void Post::drawPostIndex()
{
    for (int i = 0; i < this->numFaces; i++)
    {

        glColor3fv(this->postColor);
        this->drawPost(i);
    }
}

void Post::drawNet()
{
    //top
    glPushMatrix();
        glTranslatef(18, 0, 2.42);
        glScalef(1.0, 30, 1.5);
        this->drawPostIndex();
    glPopMatrix();

    //right
    glPushMatrix();
        glTranslatef(18, 2.9, 1.2);
        glScalef(1.0, 1.0, 11.75);
        this->drawPostIndex();
    glPopMatrix();

    //left
    glPushMatrix();
        glTranslatef(18, -2.9, 1.2);
        glScalef(1.0, 1.0, 11.75);
        this->drawPostIndex();
    glPopMatrix();
}

void Post::setColors(float r, float g, float b)
{
    this->postColor[0] = r;
    this->postColor[1] = g;
    this->postColor[2] = b;
}

void Post::drawPost(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = this->indices[index][i];
        glVertex3fv(this->postVerts[vIndex]);
    }
    glEnd();
}


