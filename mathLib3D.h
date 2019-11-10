#ifndef MATHLIB_3D_H
#define MATHLIB_3D_H


class Point3D {
public:
    Point3D(float px, float py, float pz);

    float px;
    float py;
    float pz;
    
    // float distanceTo(Point3D other);
    // float fastDistanceTo(Point3D other);
};

class Vec3D {
public:
    Vec3D(float dx, float dy, float dz);
    Vec3D();
    float dx;
    float dy;
    float dz;

    float length();
    Vec3D normalize();
    Vec3D multiply(float speedx, float speedy, float speedz);
    Point3D movePoint(Point3D source);

    static Vec3D createVector(Point3D p1, Point3D p2);
};

#endif