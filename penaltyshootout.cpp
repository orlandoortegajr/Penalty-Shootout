#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
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
#include "post.h"

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
bool AtMenu = true;
bool gameOngoing = false;
bool gameOverScreen = true;
int textX = 0;
bool isLeftPressed = false;
bool isRightPressed = false;
int score = 0;
const float SPEEDXMINIMUM = 0.3;
const float DIRYMINIMUM = 0;
const float FORCEZMINIMUM = 0;
float speedX = SPEEDXMINIMUM;
float forceZ = FORCEZMINIMUM;
float dirY = DIRYMINIMUM;
float skey = false;

Vec3D currRing = Vec3D();

Ball soccerBall = Ball(0,0,0);

//Goalkeeper Initialization
Goalkeeper gk = Goalkeeper(0.05, 1.35);

//Post Initalization
Post post = Post();

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

void drawPath(){
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0,1,1);

    float x = 0;
    float y = 0;
    float z = 0.5;
    float initialGravity = 1 - forceZ;
    float gravity = 1;

    for ( int i = 0; i < 1000; i++){
        if ( i % 2 == 0){
            x = x + speedX;
            y = y + dirY;

            if (z < 0.1){
                initialGravity *= 0.9;
                gravity = -initialGravity;
                }
            else {
                gravity += 0.2;
            }
                z = z - 0.05*gravity;

            glVertex3f(x,y,z);

        }
        
        
        
    }
    glEnd();
}

void drawHUD(){
    glPushMatrix();
    glTranslatef(60,20,15);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glRasterPos2i(0, 0);
    glPopMatrix();

    // unsigned char text[] = "";

    if ( AtMenu){ //game hasn't started

            const char textIntro[] 
                = "WELCOME TO PENALTY SHOOT OUT! \n  \nTO GET STARTED PRESS THE 'S' KEY!";
            //int lengtext = glutBitmapLength(GLUT_BITMAP_8_BY_13, text);
            //glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*) text );
            for (int i = 0; i < strlen(textIntro); i++){
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, textIntro[i]);
            }
    }

    else if ( gameOngoing) {

        unsigned char PointsQ[] 
                = "CURRENT POINTS:";
        unsigned char timeQ[] 
                = "TIME REMAINING:";
        unsigned char time[2];
        time[0] = cnt & 0xFF;
        time[1] = (cnt >> 8) & 0xFF;

        char buf[256];
        snprintf(buf, sizeof(buf) - 1, "YOU HAVE %d SECONDS REMAINING, %d POINTS SCORED", 60 - cnt/60, score);
        int track = 60 - cnt/60;
        //glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*) buf );
        for (int i = 0; i < strlen(buf); i++){
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
            }

        if (track == 0){
            gameOverScreen = true;
            gameOngoing = false;
        }
    }

    else if (gameOverScreen){

        char buf[256];
        snprintf(buf, sizeof(buf) - 1, "GAME OVER!!\nYou scored %d points!", score);
        //glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*) buf );
        for (int i = 0; i < strlen(buf); i++){
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
            }

    }

    // glutBitmapString(GLUT_BITMAP_HELVETICA_18, text );
}

void createPlane(){
    glPushMatrix();

    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, planeMaterialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, planeMaterialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, planeMaterialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, planeMaterialShiny);

    // // glColor3b(0, 60, 0);
    // glBegin(GL_QUADS);

    // glNormal3f(0,0,1);
    // glVertex3f(-20,-10,0);
    // glVertex3f(20,-10,0);
    // glVertex3f(20,10,0);
    // glVertex3f(-20,10, 0);

    // glEnd();
    // glPopMatrix();
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

void initBall(){
    soccerBall = Ball(forceZ , dirY, speedX);
    
    float speedX = SPEEDXMINIMUM;
    float forceZ = FORCEZMINIMUM;
    float dirY = DIRYMINIMUM;
}

void targets(){
    int track = 60 - cnt/60;
    switch (track){
    
    case 50 ... 60:
    case 20 ... 29:
    currRing = Vec3D(20.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(20.0,0.0,1.0);
    glRotatef(90.0,0.0,1.0,0);
    glBegin(GL_POINTS);
    for(int i=0;i<1000;++i)
    {
    glVertex3f(cos(2*3.14159*i/1000.0),sin(2*3.14159*i/1000.0),0);
    }
    glEnd();
    glPopMatrix();;   
    break;
    case 40 ... 49:
    case 10 ... 19:
    currRing = Vec3D(20.0,2.0,1.0);
    glPushMatrix();
    glTranslatef(20.0,2.0,1.0);
    glRotatef(90.0,0.0,1.0,0);
    glBegin(GL_POINTS);
    for(int i=0;i<1000;++i)
    {
    glVertex3f(cos(2*3.14159*i/1000.0),sin(2*3.14159*i/1000.0),0);
    }
    glEnd();
    glPopMatrix();;   
    break;

    case 30 ... 39:
    case 0 ... 9:
    currRing = Vec3D(20.0,-2.0,1.0);
    glPushMatrix();
    glTranslatef(20.0,-2.0,1.0);
    glRotatef(90.0,0.0,1.0,0);
    glBegin(GL_POINTS);
    for(int i=0;i<1000;++i)
    {
    glVertex3f(cos(2*3.14159*i/1000.0),sin(2*3.14159*i/1000.0),0);
    }
    glEnd();
    glPopMatrix();;   
    break;
    
    }
}



void update(){

    if ( gameOngoing){
    
    if (soccerBall.position.px >= 45){
        initBall();
        skey = false;
        score += 1;
    }
    else if (soccerBall.speed <= -0.5){
        initBall();
        skey = false;
    }
    else if (skey){
        soccerBall.update();
        Point3D temppos = soccerBall.position;
        if (soccerBall.speed <= 0)
            soccerBall.speed -= 0.005;
        
        if ( fabs(temppos.py - gk.position.py) <= 0.01 ){
            //COLLISION!
            soccerBall.speed *= -1.0;
        }
        else if (fabs(currRing.dy - soccerBall.position.py) <= 0.5 && fabs(currRing.dx - soccerBall.position.px) <= 0.5){
            initBall();
            skey = false;
            score += 2;
        }
    }
    }
    if ( cnt/60 == 60){
        gameOverScreen = true;
        gameOngoing = false;
    }

    
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
  
    glPushMatrix();
    
    glTranslatef(2,0,1);
    update();
    soccerBall.draw();
    glPopMatrix();    
    targets();
    gk.drawGK();
    gk.gkSideways();
    createPlane();
    drawHUD();
    drawPath();
    post.drawNet();

    ang++;
}


void FPS(int val){
    cnt++;
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

void kbd(unsigned char key, int x, int y)
{
    switch(key){
        
        
        case 't':
            textX--;
            break;
        case 'q':
        case 27:
            exit(0);
            break;
        case 's':
            if (cnt/60 < 60){
                AtMenu = false;
                gameOngoing = true;
                skey = !skey;
            }
            break;
        case 'x':
            speedX += 0.1;
            break;
        case 'c':
            speedX -= 0.1;
            break;
        case ' ':
            if (!AtMenu && gameOngoing){
                initBall();
            }
            break;
        case '1':
            gk = Goalkeeper(0.025,1);
            break;
        case '2':
            gk = Goalkeeper(0.05, 1.35);
            break;
        case '3':
            gk = Goalkeeper(0.1, 1.75);
            break;
        case 'r':
            gk = Goalkeeper(0.05, 1.35);
            score = 0;
            cnt = 0;
    }


}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            forceZ += 0.2;
        break;

        case GLUT_KEY_DOWN:
            forceZ -= 0.2;
        break;

        case GLUT_KEY_LEFT:
            dirY += 0.01;
        break;

        case GLUT_KEY_RIGHT:
            dirY -= 0.01;
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
    printf("\n"
           "up arrow -> increase upward momentum of the kick\n"
           "down arrow -> decrease upward momentum of the kick\n"
           "left arrow -> angle kick to the left\n"
           "right arrow -> angle kick to the right\n"
           "x -> increase speed of the ball\n"
           "c -> decrease speed of the ball\n"
           "r -> reset\n"
           "s -> to kick\n"
           "1 -> change difficulty to EASY\n"
           "2 -> change difficulty to MEDIUM\n"
           "3 -> change difficulty to HARD\n"
    );

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