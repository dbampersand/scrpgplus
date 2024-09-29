#include "gameobject.h"

void GameObject::Update(float dt)
{
}

GameObject::GameObject(std::string path) : Drawable(path, 100), Updatable()
{
    x = 0; y = 0;
};
Rectangle GameObject::GetHealthBarRectangle()
{
    Rectangle r = Rectangle{ x-GetSize().x/2.0f,y-GetSize().y/2.0f,GetSize().x,20};
    r.height = 20;
    return r;
}
void GameObject::Draw(Rectangle r)  {
    Drawable::Draw(r);
};
Rectangle GameObject::GetPosition()  {
    Vector2 size = GetSize();
    return Rectangle{ (float)x - size.x / 2.0f,(float)y - size.y / 2.0f,(float)size.x,(float)size.y };
}
