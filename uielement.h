#pragma once

#include "raylib.h"
#include "drawable.h"
#include "updatable.h"
#include <iostream>
#include "render.h"

class Clickable 
{
    public:
        virtual void Clicked() = 0;
        virtual void Released() = 0;
        virtual Rectangle GetPosition() = 0;


        bool MousedOver(Rectangle r) {
            return CheckCollisionPointRec(Render::GetMousePos(),r);
        };
        bool clicked;
        bool IsClickable = true;

        Clickable()
        {
            Clickables.push_back(this);
        }
        ~Clickable()
        {
            Clickables.erase(std::remove(Clickables.begin(), Clickables.end(), this), Clickables.end());
        }

        static void UpdateClickables()
        {
            for(Clickable* c : Clickables)
            {
                if (c->IsClickable)
                {
                    if (c->MousedOver(c->GetPosition()))
                    {
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        {
                            c->Clicked();
                            c->clicked = true;
                        }
                        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                        {
                            c->Released();
                            c->clicked = false;
                        }
                    }
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    c->clicked = false;
                }
                
            }
        }

        static std::vector<Clickable*> Clickables;
        


};
class UIElement : public Drawable, public Clickable, public Updatable
{

    public:
        virtual void Clicked() override {};
        virtual void Released() override {};

        void Update(float dt) override {
        };

        Rectangle GetPosition() override { 
            return (Rectangle){(float)x,(float)y,(float)w,(float)h};
        }

        virtual void Draw(Rectangle r) override {

        };

        UIElement(int X, int Y, int W, int H) : Drawable("",300) {
            x = X; 
            y = Y;
            w = W;
            h = H;
        };
        virtual ~UIElement() = default;

        int x;
        int y;
        int w;
        int h;

        void Update();

    private:

};
