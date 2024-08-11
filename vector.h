#pragma once
#include "raylib.h"


class Vector {  
    public:
    float x; float y;
    Vector();
    Vector(float _x, float _y) {x = _x; y = _y;}; 

    Vector operator+=(Vector b);
    Vector operator/=(Vector b);
    Vector operator/(float b);
    Vector operator-(float b);
    Vector operator-(Vector b);

    Vector2 ToRLVector2();
};