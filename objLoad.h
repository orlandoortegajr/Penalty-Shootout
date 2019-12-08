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
using namespace std;

class objLoad{
public:
    objLoad(string filename);
    void draw();
    vector<Vec3D> tempVertices;
    vector<Vec3D> tempTextures;
    vector<Vec3D> tempNormals;
    vector<int> tempVerticesInd;
    vector<int> tempTexturesInd;
    vector<int> tempNormalsInd;
};