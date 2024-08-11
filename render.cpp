#include "render.h"
#include "sprite.h"
#include <iostream>
#include "UI.h"
#include "raylib.h"


Camera Render::camera = (Camera){
    .position = (Vector3){0,0,0},
    .target = (Vector3){0,0,1},
    .up  = (Vector3){0,1,0},
    .fovy = 90.0f,
    .projection = CameraProjection::CAMERA_ORTHOGRAPHIC
    };
/*Sprite* Render::GetSprite(std::string path)
{
    if (Render::sprites.find(path) != Render::sprites.end())
        return &Render::sprites[path];
    else
    {
        LoadSprite(path);
        if (Render::sprites.find(path) != Render::sprites.end())
            return &Render::sprites[path];
    }
    if (Render::sprites.find("null") == Render::sprites.end())
        GenerateNullSprite();
    return &Render::sprites["null"];
}*/
Vector Render::GetScreenSizeScale()
{
    float percentW = Render::GetBasisWidth() / (float)GetScreenWidth();
    float percentH = Render::GetBasisWidth() / (float)GetScreenWidth();
    return (Vector){percentW,percentH};
}
Rectangle Render::TranslateToScreenSpace(Rectangle r)
{
    Vector percent = GetScreenSizeScale();

    r.x *= percent.x;
    r.y *= percent.y;
    r.width *= percent.x;
    r.height *= percent.y;

    return r;
};

Vector Render::TranslateToScreenSpace(Vector v)
{
    Rectangle r = (Rectangle){v.x,v.y,0,0};
    r = TranslateToScreenSpace(r);

    return (Vector){r.x,r.y};
}

Vector Render::GetScreenCenter()
{
    return (Vector){GetBasisWidth()/2.0f,GetBasisHeight()/2.0f};
}
 void Render::Draw(float dt)
{
}