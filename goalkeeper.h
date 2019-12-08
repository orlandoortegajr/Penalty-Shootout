#ifndef GOALKEEPER_H
#define GOALKEEPER_H

#include "mathLib3D.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/freeglut.h>
#endif

class Goalkeeper 
{
    public:
        Goalkeeper();
        Point3D position;
        float speed;
        float difficulty;
        bool gkReachedPost;

        //vertices for each goalkeeper bodypart
        /*
        GOALKEEPER Vertices
            x = 3Dness
            ? y = thickness
            z = length 
        */
        float headVerts[8][3] = {
            {-0.1, -0.1, 0.1},
            {-0.1, 0.1, 0.1},
            {0.1, 0.1, 0.1},
            {0.1, -0.1, 0.1},
            {-0.1, -0.1, -0.1},
            {-0.1, 0.1, -0.1},
            {0.1, 0.1, -0.1},
            {0.1, -0.1, -0.1}
        };

        float bodyVerts[8][3] = {
            {-0.5, -0.2, 0.35},
            {-0.5, 0.2, 0.35},
            {0.5, 0.2, 0.35},
            {0.5, -0.2, 0.35},
            {-0.5, -0.2, -0.35},
            {-0.5, 0.2, -0.35},
            {0.5, 0.2, -0.35},
            {0.5, -0.2, -0.35}
        };

        float leftLegVerts[8][3] = {
            {-0.5, -0.05, 0.25},
            {-0.5, 0.05, 0.25},
            {0.5, 0.05, 0.25},
            {0.5, -0.05, 0.25},
            {-0.5, -0.05, -0.25},
            {-0.5, 0.05, -0.25},
            {0.5, 0.05, -0.25},
            {0.5, -0.05, -0.25}
        };

        float rightLegVerts[8][3] = {
            {-0.5, -0.05, 0.25},
            {-0.5, 0.05, 0.25},
            {0.5, 0.05, 0.25},
            {0.5, -0.05, 0.25},
            {-0.5, -0.05, -0.25},
            {-0.5, 0.05, -0.25},
            {0.5, 0.05, -0.25},
            {0.5, -0.05, -0.25}
        };

        float leftArmVerts[8][3] = {
            {-0.4, -0.05, 0.225},
            {-0.4, 0.05, 0.225},
            {0.4, 0.05, 0.225},
            {0.4, -0.05, 0.225},
            {-0.4, -0.05, -0.225},
            {-0.4, 0.05, -0.225},
            {0.4, 0.05, -0.225},
            {0.4, -0.05, -0.225}
        };

        float rightArmVerts[8][3] = {
            {-0.4, -0.05, 0.225},
            {-0.4, 0.05, 0.225},
            {0.4, 0.05, 0.225},
            {0.4, -0.05, 0.225},
            {-0.4, -0.05, -0.225},
            {-0.4, 0.05, -0.225},
            {0.4, 0.05, -0.225},
            {0.4, -0.05, -0.225}
        };

        float oGheadVerts[8][3] = {
            {-0.1, -0.1, 0.1},
            {-0.1, 0.1, 0.1},
            {0.1, 0.1, 0.1},
            {0.1, -0.1, 0.1},
            {-0.1, -0.1, -0.1},
            {-0.1, 0.1, -0.1},
            {0.1, 0.1, -0.1},
            {0.1, -0.1, -0.1}};

        float oGbodyVerts[8][3] = {
            {-0.5, -0.2, 0.35},
            {-0.5, 0.2, 0.35},
            {0.5, 0.2, 0.35},
            {0.5, -0.2, 0.35},
            {-0.5, -0.2, -0.35},
            {-0.5, 0.2, -0.35},
            {0.5, 0.2, -0.35},
            {0.5, -0.2, -0.35}};

        float oGleftLegVerts[8][3] = {
            {-0.5, -0.05, 0.25},
            {-0.5, 0.05, 0.25},
            {0.5, 0.05, 0.25},
            {0.5, -0.05, 0.25},
            {-0.5, -0.05, -0.25},
            {-0.5, 0.05, -0.25},
            {0.5, 0.05, -0.25},
            {0.5, -0.05, -0.25}};

        float oGrightLegVerts[8][3] = {
            {-0.5, -0.05, 0.25},
            {-0.5, 0.05, 0.25},
            {0.5, 0.05, 0.25},
            {0.5, -0.05, 0.25},
            {-0.5, -0.05, -0.25},
            {-0.5, 0.05, -0.25},
            {0.5, 0.05, -0.25},
            {0.5, -0.05, -0.25}};

        float oGleftArmVerts[8][3] = {
            {-0.4, -0.05, 0.225},
            {-0.4, 0.05, 0.225},
            {0.4, 0.05, 0.225},
            {0.4, -0.05, 0.225},
            {-0.4, -0.05, -0.225},
            {-0.4, 0.05, -0.225},
            {0.4, 0.05, -0.225},
            {0.4, -0.05, -0.225}};

        float oGrightArmVerts[8][3] = {
            {-0.4, -0.05, 0.225},
            {-0.4, 0.05, 0.225},
            {0.4, 0.05, 0.225},
            {0.4, -0.05, 0.225},
            {-0.4, -0.05, -0.225},
            {-0.4, 0.05, -0.225},
            {0.4, 0.05, -0.225},
            {0.4, -0.05, -0.225}};

        //indices for each of the faces of the cube
        int indices[6][4] = {
            //top
            {1, 2, 6, 5},
            //left
            {1, 5, 4, 0},
            //back
            {5, 7, 7, 4},
            //right
            {2, 3, 7, 6},
            //bottom
            {0, 4, 7, 3},
            //front
            {1, 0, 3, 2}
        };

        float outfitColor[3];
        float skinColor[3];

        void setColors(float r, float g, float b, char option);
        

        //GK body part draws based on index of cube face
        void drawGKFaceIndex();
        void drawGKBodyIndex();
        void drawGKRightLegIndex();
        void drawGKLeftLegIndex();
        void drawGKRightArmIndex();
        void drawGKLeftArmIndex();

        void drawGK();
        void gkSideways();

        //number of faces for cube
        int numFaces;
        

    private:
        float getRandomFloat();

        //function that draw gk body parts
        void drawGKFace(int index);
        void drawGKBody(int index);
        void drawGKRightLeg(int index);
        void drawGKLeftLeg(int index);
        void drawGKRightArm(int index);
        void drawGKLeftArm(int index);

        void setSize(float a);
};

#endif