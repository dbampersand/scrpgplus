#include "raylib.h"
#include "vector.h"

Vector Vector::operator+=(Vector b)
{
    float xN = x + b.x;
    float yN = y + b.y;
    return (Vector){xN,yN}; 
}
Vector Vector::operator/=(Vector b)
{
    float xN = x / b.x;
    float yN = y / b.y;
    return (Vector){xN,yN}; 
}
Vector Vector::operator/(float b)
{
    float xN = x / b;
    float yN = y / b;
    return (Vector){xN,yN}; 
}
Vector Vector::operator-(float b)
{
    float xN = x - b;
    float yN = y - b;
    return (Vector){xN,yN}; 
}
Vector Vector::operator-(Vector b)
{
    float xN = x - b.x;
    float yN = y - b.y;
    return (Vector){xN,yN}; 
}


Vector2 Vector::ToRLVector2()
{
    return (Vector2){x,y};
}
/*Vector2 ToRaylibVector()
{
    return (Vector2){x,y};
}
operator const Vector2()
{

}*/