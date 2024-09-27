#pragma once

#include "raylib.h"
#include "drawable.h"
#include "updatable.h"
#include "render.h"

class Clickable 
{
    public:
        virtual void Clicked() = 0;
        virtual void Released() = 0;
        virtual Rectangle GetPosition() = 0;


        bool MousedOver(Rectangle r);

        bool clicked;
        bool IsClickable = true;

        Clickable();
        ~Clickable();

        static void UpdateClickables();

        static std::vector<Clickable*> Clickables;
        


};
class UIElement : public Drawable, public Clickable, public Updatable
{

    public:
        virtual void Clicked() override {};
        virtual void Released() override {};
    
        void Disable();
        void Enable();

        void Update(float dt) override {
        };

        Rectangle GetPosition() override;
        virtual void Draw(Rectangle r) override {
        };

        UIElement(int X, int Y, int W, int H);
        virtual ~UIElement() = default;

        int x;
        int y;
        int w;
        int h;

        void Update();

    private:

};
