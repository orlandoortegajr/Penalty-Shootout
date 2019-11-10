#include <stdlib.h>
#include <iostream>
#include <vector>
#include <bits/stdc++.h> 

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

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



void setMaterials(unsigned int index) {
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular[index]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShiny[index]);

}



void update(){

    gluLookAt(5,0,5, mouseX, 5 , 5, 0, 0, 1);

   
}

void drawNet(){
    //temporary net

    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glVertex3f(18,-4,0);
    glVertex3f(18,-4,2);
    glVertex3f(18,4,2);
    glVertex3f(18,4, 0);
    glEnd();

    glColor3f(1, 1, 1);

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


    // gluLookAt(0,0,2, 2, mouseX*100 , mouseY*100, 0, 0, 1);
  
    cnt++;

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
    draw3DScene();
    glutSwapBuffers();
}

void kbd(unsigned char key, int x, int y)
{
    switch(key){
        
        case 'q':
            exit(0);
            break;
             


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




