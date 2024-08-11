#include "scene.h"
#include "raylib.h"
#include "render.h"
#include "gamestate.h"
#include "vector.h"
#include <iostream>
//std::unique_ptr<Scene> Scene::currentScene;

Rectangle Scene::GetPosition() { 
    Vector v = GetSize() / 2.0f;
    Vector center = Render::GetScreenCenter() - v;

    Vector size = GetSize();
    std::cout << center.x << ", " << center.y << ", " << size.x << ", " << size.y << "\n";
    return (Rectangle){center.x,center.y,size.x,size.y};
}

void Scene::DrawScene()
{
    Vector v = GetSize() / 2.0f;
    Vector center = Render::GetScreenCenter() - v;
    Drawable::Draw();
}
void Scene::LoadScene(std::string background)
{
    Drawable::SetTexture(background); 
}
void Scene::Draw()
{
    DrawScene();
}
