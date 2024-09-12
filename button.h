#pragma once

#include "uielement.h"
#include "drawable.h"
#include "raylib.h"

class Button : public UIElement
{
    public:


        void SetText(std::string str) {
            this->text = str;
        };
        void Draw(Rectangle r) override;
        Button(int X, int Y, int W, int H, void (*Callback)()) : UIElement(X,Y,W,H){
            callback = Callback;
        };
        ~Button(){
            
        };

        void Update(float dt)  override {
        };


        static void pr() {
         };

    private:
        Color foreground = (Color){255,255,255,255};
        Color background = (Color){0,0,0,255};
        std::string text;

        void (*callback) ();


        void Clicked() override;
        void Released() override;
    };  