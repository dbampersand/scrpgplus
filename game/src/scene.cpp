#include "scene.h"
#include "raylib.h"
#include "render.h"
#include "gamestate.h"
//std::shared_ptr<Scene> Scene::currentScene;

Rectangle Scene::GetPosition() { 
    Vector2 v = Vector2{GetSize().x / 2.0f, GetSize().y / 2.0f};
    Vector2 center = Vector2 {Render::GetScreenCenter().x - v.x, Render::GetScreenCenter().y - v.y};

    Vector2 size = GetSize();
    return Rectangle{center.x,center.y,size.x,size.y};
}

void Scene::DrawScene()
{
    Vector2 v = Vector2{GetSize().x / 2.0f, GetSize().y / 2.0f};
    Vector2 center = Vector2{Render::GetScreenCenter().x - v.x, Render::GetScreenCenter().y - v.y};
    //Drawable::Draw();
}
    