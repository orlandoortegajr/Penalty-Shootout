#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "mathLib3D.h"
#include "objLoad.h"
using namespace std;

objLoad::objLoad(string filename){
    this->tempVertices.clear();
    this->tempTextures.clear();
    this->tempNormals.clear();
    this->tempVerticesInd.clear();
    this->tempTexturesInd.clear();
    this->tempNormalsInd.clear();
    FILE * file = fopen(filename.c_str(), "r");
    if (!file) {
        cout << "UNABLE TO LOAD OBJ FILE" << endl;
    }
    while (true){
        string currline;
        int res = fscanf(file, "%s", currline.c_str());
        if (res == -1)
            break;
        if (strcmp(currline.c_str(), "v") == 0){
            Vec3D temp = Vec3D();
            fscanf(file, "%f %f %f\n", &temp.dx, &temp.dy, &temp.dz);
            tempVertices.push_back(temp);
        }
        else if (strcmp(currline.c_str(), "vt") == 0){
            Vec3D temp = Vec3D();
            fscanf(file, "%f %f\n", &temp.dx, &temp.dy);
            tempTextures.push_back(temp);
        }
        else if (strcmp(currline.c_str(), "vn") == 0){
            Vec3D temp = Vec3D();
            fscanf(file, "%f %f %f\n", &temp.dx, &temp.dy, &temp.dz);
            tempNormals.push_back(temp);
        }
        else if (strcmp(currline.c_str(), "f") == 0){
            int vertInd[4], textInd[4], normInd[4];
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertInd[0], &textInd[0], &normInd[0], &vertInd[1], &textInd[1], &normInd[1], &vertInd[2], &textInd[2], &normInd[2], &vertInd[3], &textInd[3], &normInd[3]);
            tempVerticesInd.push_back(vertInd[0]);
            tempVerticesInd.push_back(vertInd[1]);
            tempVerticesInd.push_back(vertInd[2]);
            //tempVerticesInd.push_back(vertInd[3]);
            tempNormalsInd.push_back(normInd[0]);
            tempNormalsInd.push_back(normInd[1]);
            tempNormalsInd.push_back(normInd[2]);
            //tempNormalsInd.push_back(normInd[3]);
        }
    }
}

void objLoad::draw(){
    glPushMatrix();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < this->tempVerticesInd.size(); i++){
        int index = this->tempVerticesInd[i];
        Vec3D tempVer = this->tempVertices[index - 1];
        Vec3D tempNorm = this->tempNormals[index - 1];
        glNormal3f(tempNorm.dx,tempNorm.dy,tempNorm.dz);
        glVertex3f(tempVer.dx,tempVer.dy,tempVer.dz);
        if(i%3 == 0)
            glColor3f(0,0,0);
        else{
            glColor3f(0.569,0.639,0.69);
        }
    }
    glEnd();
    glPopMatrix();
}