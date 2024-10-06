#pragma once

#include "raylib.h"
#include "drawable.h"
#include "updatable.h"
#include "render.h"

class Clickable 
{
    public:
        //Returns true if the Clickable is moused over
        bool MousedOver(Rectangle r);


        Clickable();
        ~Clickable();

        //Updates all clickables
        static void UpdateClickables();

        bool clicked;
        bool IsClickable = true;

        //To be overridden, called when the object is clicked on
        virtual void Clicked() = 0;
        //To be overridden, called when the object is clicked and then released
        virtual void Released() = 0;
        //To be overridden, called when the object has been clicked on, then the mouse moved off it's rectangle, and then released
        virtual void Unclicked() {};

        //To be overridden, returns the position in world space
        virtual Rectangle GetPosition() = 0;

private:

    static std::vector<Clickable*> Clickables;

};
class UIElement : public Drawable, public Clickable, public Updatable
{

    public:
        
        //Disables the UI element
        void Disable();
        //Enables the UI element
        void Enable();

        UIElement(float X, float Y, float W, float H);
        virtual ~UIElement() = default;

        float x;
        float y;
        float w;
        float h;

        //To be overridden, called when the object is clicked on
        virtual void Clicked() override {};
        //To be overridden, called when the object is clicked and then released
        virtual void Released() override {};
        //To be overridden, called when the object has been clicked on, then the mouse moved off it's rectangle, and then released
        virtual void Unclicked() override {};

        Rectangle GetPosition() override;

        void Update(float dt) override {
        };
        virtual void Draw(Rectangle r, Color tint) override {
        };


    private:

};
