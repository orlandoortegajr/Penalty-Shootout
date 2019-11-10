#include "mathLib3D.h"
#include <math.h>

Point3D::Point3D(float px, float py , float pz){

    Point3D::px = px;
    Point3D::py = py;
    Point3D::pz = pz;

}

Vec3D::Vec3D(float dx, float dy, float dz){

    Vec3D::dx = dx;
    Vec3D::dy = dy;
    Vec3D::dz = dz;

}

Vec3D::Vec3D(){

    Vec3D::dx = 0;
    Vec3D::dy = 0;
    Vec3D::dz = 0;

}


float Vec3D::length(){

    return pow(pow(Vec3D::dx, 2)+ pow(Vec3D::dy, 2)+ pow(Vec3D::dz, 2), 0.5);

}

Vec3D Vec3D::normalize(){

    if (Vec3D::dx ==0 && Vec3D::dy==0 &&Vec3D::dz==0){
        return Vec3D(); // Considered throwing an error size you cannot normalize a zero vector
    }

    float x = Vec3D::dx/Vec3D::length();
    float y = Vec3D::dy/Vec3D::length();
    float z = Vec3D::dz/Vec3D::length();
    return Vec3D(x, y, z);
}

Point3D Vec3D::movePoint(Point3D source){

    
    return Point3D(Vec3D::dx + source.px, Vec3D::dy + source.py, Vec3D::dz + source.pz);
}

Vec3D Vec3D::multiply(float speedx, float speedy, float speedz ){
    return Vec3D( abs(Vec3D::dx) * speedx, abs(Vec3D::dy) * speedy, abs(Vec3D::dz) * speedz);
}