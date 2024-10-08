#include "render.h"
#include "sprite.h"
#include "UI.h"

#include "raylib.h"

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
Vector2 Render::GetMousePos()
{
    Vector2 mouse = GetMousePosition();
    Vector2 v = Vector2{mouse.x,mouse.y};
    
    v = TranslateToWorldSpace(v);

    return Vector2{ v.x,v.y };
}

void Render::DrawText(std::string text, std::string fontPath, int size, Rectangle screenSpaceRect, Color color, Sprite::SPRITE_ALIGN align)
{
    size = (int)(size *  GetScreenSizeScale().x);

    //if we haven't loaded the font ever, we need to add it to the list of all potential fonts 
    if (fonts.find(fontPath) == fonts.end())
    {
        std::map <int, Font> fontList;
        fonts.insert({ fontPath, fontList });
    }
    std::map <int, Font> fontList = fonts.at(fontPath);

    //if we don't have the font in the current size, then we need to load it 
    if (fontList.find(size) == fontList.end())
    {
        int codepoints = 0;
        fonts.at(fontPath).insert({ size, LoadFontEx(fontPath.c_str(),size,0,0) });
        SetTextureFilter(fonts.at(fontPath).at(size).texture, TEXTURE_FILTER_BILINEAR);
    }
    //finally - we have the font at the correct size, we can render
    Font f = fonts.at(fontPath).at(size);
    if (IsFontReady(f))
    {
        Vector2 measured = MeasureTextEx(f, text.c_str(), (float)size, 1);

        if (align == Sprite::SPRITE_ALIGN::LEFT)
        {
            screenSpaceRect.y = screenSpaceRect.y + screenSpaceRect.height / 2.0f - measured.y / 2.0f;
            DrawTextEx(f, text.c_str(), Vector2{ screenSpaceRect.x,screenSpaceRect.y }, (float)size, 1, color);
        }
        if (align == Sprite::SPRITE_ALIGN::CENTER)
        {
            screenSpaceRect.x = screenSpaceRect.x + screenSpaceRect.width/2.0f - measured.x / 2.0f;
            screenSpaceRect.y = screenSpaceRect.y + screenSpaceRect.height/2.0f - measured.y / 2.0f;

            DrawTextEx(f, text.c_str(), Vector2{ screenSpaceRect.x,screenSpaceRect.y }, (float)size, 1, color);
        }
        if (align == Sprite::SPRITE_ALIGN::RIGHT)
        {
            screenSpaceRect.x = screenSpaceRect.x + screenSpaceRect.width - measured.x;
            screenSpaceRect.y = screenSpaceRect.y + screenSpaceRect.height / 2.0f - measured.y / 2.0f;

            DrawTextEx(f, text.c_str(), Vector2{ screenSpaceRect.x,screenSpaceRect.y }, (float)size, 1, color);
        }
    }

}