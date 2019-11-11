#include <stdlib.h>
#include <iostream>
#include <vector>
//#include <bits/stdc++.h> 

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "goalkeeper.h"
#include "ball.h"

using namespace std;

bool isPaused = false;
int gHeight = 400;
int gWidth = 400;
int ang = 0;	
int cnt = 0;
float eye[3] = {20,20,20};
float light_pos[2][4] = {{3,5,0,1}, {1,-5,0,1} };
float amb[2][4] = { { 0.976470588, 0.843137255,1, 1} , {0,0.2,1,0.5} };
float diff[2][4] = { {0,0,1,1} , {1,0,0,1}  };
float spec[2][4] = { {1,1,1,1}, {1,0,1,1}  };
float mouseX = 0;
float mouseY = 0;

bool isLeftPressed = false;
bool isRightPressed = false;

Ball soccerBall;

GLfloat materialAmbient[3][4] = {
    { 0.2, 0.2, 1, 1.0 },
    { 0.0215, 0.1745, 1, 1.0 },
     { 0.0, 0.019, 1, 1.0 }
};
GLfloat materialDiffuse[3][4] = {
    { 0.8, 0.8, 0.8, 1.0 },
    { 0.07568, 0.61424, 0.07568, 1.0 },
    { 0.04, 0.12, 0.07568, 1.0 }

};
GLfloat materialSpecular[3][4] = {
    { 0, 0, 1, 1 },
    { 0.11, 0.20, 0.7, 1 },
    { 0.2, 0.2, 1, 1 }
};
GLfloat materialShiny[3] = {
    0,
    0.6,
    0.9
};

GLfloat planeMaterialAmbient[4] = 
    { 0.9, 0.1 ,1, 1 }
;
GLfloat planeMaterialDiffuse[4] = 
    {0.184313725, 0.458823529 ,0.196078431, 1 };

GLfloat planeMaterialSpecular[4] = 
    { 0.0, 0.0, 0.0, 1 };

GLfloat planeMaterialShiny = 
    0.6
;

/*
GOALKEEPER Vertices
x= ?
y = thickness
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

float legVerts[8][3] = {
    {-0.5, -0.05, 0.25},
    {-0.5, 0.05, 0.25},
    {0.5, 0.05, 0.25},
    {0.5, -0.05, 0.25},
    {-0.5, -0.05, -0.25},
    {-0.5, 0.05, -0.25},
    {0.5, 0.05, -0.25},
    {0.5, -0.05, -0.25}
};

float armVerts[8][3] = {
    {-0.4, -0.05, 0.225},
    {-0.4, 0.05, 0.225},
    {0.4, 0.05, 0.225},
    {0.4, -0.05, 0.225},
    {-0.4, -0.05, -0.225},
    {-0.4, 0.05, -0.225},
    {0.4, 0.05, -0.225},
    {0.4, -0.05, -0.225}
};

int indices[6][4] = {
    //top
    {1,2,6,5},
    //left
    {1,5,4,0},
    //back 
    {5,7,7,4},
    //right
    {2,3,7,6},
    //bottom
    {0,4,7,3},
    //front
    {1,0,3,2}
};

//GoalKeeper Initialization
GoalKeeper goalie = GoalKeeper(1,0,0,0);

//number of faces for cube
int numFaces = 6;

//Goalkeeper Face
void drawGKFace(int index) 
{
    glBegin(GL_POLYGON);
        for(int i = 0; i < 4; i++) {
            int vIndex = indices[index][i];
            glVertex3fv(headVerts[vIndex]);
        }   
    glEnd();
}

float color[3] = {0,0,1};

void drawGKFaceIndex()
{
    for(int i = 0; i < numFaces; i++) {

        glColor3fv(color);
        drawGKFace(i);
    }
}

//Goalkeeper Body
void drawGKBody(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = indices[index][i];
        glVertex3fv(bodyVerts[vIndex]);
    }
    glEnd();
}

float colorB[3] = {0, 1, 0};

void drawGKBodyIndex()
{
    for (int i = 0; i < numFaces; i++)
    {
        glColor3fv(colorB);
        drawGKBody(i);
    }
}

//Goalkeeper Legs
void drawGKLeg(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = indices[index][i];
        glVertex3fv(legVerts[vIndex]);
    }
    glEnd();
}

float colorL[3] = {1, 0, 0};

void drawGKLegIndex()
{
    for (int i = 0; i < numFaces; i++)
    {
        glColor3fv(colorL);
        drawGKLeg(i);
    }
}

//Goalkeeper Arms
void drawGKArm(int index)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        int vIndex = indices[index][i];
        glVertex3fv(armVerts[vIndex]);
    }
    glEnd();
}

float colorA[3] = {1, 0, 0};

void drawGKArmIndex()
{
    for (int i = 0; i < numFaces; i++)
    {
        glColor3fv(colorA);
        drawGKArm(i);
    }
}

void setMaterials(unsigned int index) {
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular[index]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShiny[index]);

}

void drawNet(){
    //temporary net

    glColor3f(0, 0, 0);

    //inner part of net
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glVertex3f(18,-4,0);
    glVertex3f(18,-4,2);
    glVertex3f(18,4,2);
    glVertex3f(18,4, 0);
    glEnd();

    glColor3f(1, 1, 1);

    //crossbars
    glBegin(GL_QUADS);
    glVertex3f(18.01,-4.25,0);
    glVertex3f(18.01,-4.25,2.25);
    glVertex3f(18.01,4.25,2.25);
    glVertex3f(18.01,4.25, 0);
    glEnd();


}

void createPlane(){
    glPushMatrix();

    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, planeMaterialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, planeMaterialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, planeMaterialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, planeMaterialShiny);

    glColor3b(0, 60, 0);
    glBegin(GL_QUADS);

    glNormal3f(0,0,1);
    glVertex3f(-20,-10,0);
    glVertex3f(20,-10,0);
    glVertex3f(20,10,0);
    glVertex3f(-20,10, 0);

    glEnd();
    glPopMatrix();
}


void reshape( int w, int h){
    gWidth = w;
    gHeight = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,w,h);

    glutPostRedisplay();
}


void draw3DScene(){
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Static view of end of field
    gluLookAt(0,0,2,    20, 0 , 0,      0, 0, 1);

    //gluLookAt(0,0,2, 2, mouseX*100 , mouseY*100, 0, 0, 1);
  
    cnt++;
    glPushMatrix();
    glTranslatef(2,0,1);
    soccerBall.draw();
    glPopMatrix();

    //head
    glPushMatrix();
    glTranslatef(17,0,1.45);
    drawGKFaceIndex();
    glPopMatrix();

    //body
    glPushMatrix();
    glTranslatef(18, 0, 0.95);
    drawGKBodyIndex();
    glPopMatrix();

    //right leg
    glPushMatrix();
    glTranslatef(18, 0.085, 0.3);
    drawGKLegIndex();
    glPopMatrix();

    //left leg
    glPushMatrix();
    glTranslatef(18, -0.085, 0.3);
    drawGKLegIndex();
    glPopMatrix();

    //rght arm
    glPushMatrix();
    glTranslatef(18, 0.3, 1);
    glRotatef(45,0,0,0);
    drawGKArmIndex();
    glPopMatrix();

    // left arm
    glPushMatrix();
    glTranslatef(18, -0.3, 1);
    glRotatef(-45, 0, 0, 0);
    drawGKArmIndex();
    glPopMatrix();

    createPlane();
    drawNet();
    

    ang++;

   

}


void FPS(int val){
    if (!isPaused){
        glutPostRedisplay();
    }
    glutTimerFunc(17, FPS, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw3DScene();
    glutSwapBuffers();
}

void initBall(){
    soccerBall = Ball();
}

void kbd(unsigned char key, int x, int y)
{
    switch(key){
        
        case 'q':
        case 27:
            exit(0);
            break;
        case ' ':
            initBall();
    }


}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
        break;

        case GLUT_KEY_DOWN:
        break;

        case GLUT_KEY_LEFT:    
        break;

        case GLUT_KEY_RIGHT:
        break;
}

}

void updateMousePos(int x, int y){

    mouseX = x;
    mouseY = y;
    
}

void mouse(int btn, int state, int x, int y){
    mouseX = x;
    mouseY = y;

    switch (btn)
    {
    case GLUT_LEFT_BUTTON:
        isLeftPressed = (state == GLUT_DOWN);
        break;

    case GLUT_RIGHT_BUTTON:
        isRightPressed = (state == GLUT_DOWN);
        break;
    
    default:
        break;
    }

}


int main(int argc, char** argv)
{
    
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Penalty Shootout");
	glutTimerFunc(0, FPS, 0);
    glutPassiveMotionFunc(updateMousePos);
    glutMotionFunc(updateMousePos);
    glutMouseFunc(mouse);
   
    initBall();
	glClearColor(0.5294117647,0.807,0.98, 0.8);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


    glLightfv(GL_LIGHT0, GL_POSITION, light_pos[0]);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb[0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff[0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec[0]);



    
    glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace( GL_BACK );
    

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

	glutKeyboardFunc(kbd);
    glutSpecialFunc(SpecialInput);
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}




