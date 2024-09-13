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
    float percentW = GetScreenWidth() /  (float)Render::GetBasisWidth();
    float percentH =  GetScreenWidth() / (float)Render::GetBasisWidth();
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
Rectangle Render::TranslateToWorldSpace(Rectangle r)
{
    Vector percent = GetScreenSizeScale();
    percent.x = 1/percent.x;
    percent.y = 1/percent.y;

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
Vector Render::TranslateToWorldSpace(Vector v)
{
    Rectangle r = (Rectangle){v.x,v.y,0,0};
    r = TranslateToWorldSpace(r);

    return (Vector){r.x,r.y};
}


Vector Render::GetScreenCenter()
{
    return (Vector){GetBasisWidth()/2.0f,GetBasisHeight()/2.0f};
}
 void Render::Draw(float dt)
{
}
Vector2 Render::GetMousePos()
{
    Vector2 mouse = GetMousePosition();
    Vector v = (Vector){mouse.x,mouse.y};
    
    v = TranslateToWorldSpace(v);

    return (Vector2){v.x,v.y};
}