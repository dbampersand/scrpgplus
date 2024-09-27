#include "render.h"
#include "sprite.h"
#include "UI.h"
#include "raylib.h"


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
Vector2 Render::GetScreenSizeScale()
{
    float percentW = GetScreenWidth() /  (float)Render::GetBasisWidth();
    float percentH =  GetScreenWidth() / (float)Render::GetBasisWidth();
    return Vector2 {percentW,percentH};
}
Rectangle Render::TranslateToScreenSpace(Rectangle r)
{
    Vector2 percent = GetScreenSizeScale();

    r.x *= percent.x;
    r.y *= percent.y;
    r.width *= percent.x;
    r.height *= percent.y;

    return r;
};
Rectangle Render::TranslateToWorldSpace(Rectangle r)
{
    Vector2 percent = GetScreenSizeScale();
    percent.x = 1/percent.x;
    percent.y = 1/percent.y;

    r.x *= percent.x;
    r.y *= percent.y;
    r.width *= percent.x;
    r.height *= percent.y;

    return r;
};

Vector2 Render::TranslateToScreenSpace(Vector2 v)
{
    Rectangle r = Rectangle{v.x,v.y,0,0};
    r = TranslateToScreenSpace(r);

    return Vector2{r.x,r.y};
}
Vector2 Render::TranslateToWorldSpace(Vector2 v)
{
    Rectangle r = Rectangle{v.x,v.y,0,0};
    r = TranslateToWorldSpace(r);

    return Vector2{r.x,r.y};
}


Vector2 Render::GetScreenCenter()
{
    return Vector2{GetBasisWidth()/2.0f,GetBasisHeight()/2.0f};
}
 void Render::Draw(float dt)
{
}
Vector2 Render::GetMousePos()
{
    Vector2 mouse = GetMousePosition();
    Vector2 v = Vector2{mouse.x,mouse.y};
    
    v = TranslateToWorldSpace(v);

    return Vector2{ v.x,v.y };
}