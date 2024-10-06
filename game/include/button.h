#pragma once

#include "uielement.h"
#include "raylib.h"

class Button : public UIElement
{
    public:

        Button(int X, int Y, int W, int H, void (*Callback)());

        void SetText(std::string str);
        void Draw(Rectangle r, Color tint) override;

        void Update(float dt)  override {
        };


    private:

        Color foreground = Color{255,255,255,255};
        Color background = Color{0,0,0,255};
        std::string text;

        void (*callback) ();


        void Clicked() override;
        void Released() override;
        void Unclicked() override;
    };  