#pragma once

#include "sprite.h"
#include <vector>
#include "raylib.h"
    

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

class Drawable
{

    public:
        
        void SetOrder(int ord);
        int GetOrder();

        static bool IsSorted();

        virtual Rectangle GetPosition() = 0;
        void AddRenderOrder(int amt);

        virtual void Draw(Rectangle r, Color tint);
        virtual void DrawShadow(Rectangle r);
        void HideDrawing();
        void ShowDrawing();
        bool IsHidden();
        virtual void HideChildren() {

        }
        virtual void ShowChildren() {

        }

        ~Drawable();
        Drawable(std::string path, int index);
        
        void SetTexture(std::string path);
        Vector2 GetSize();
        static void DrawAll();
        static std::vector<Drawable*> drawables;
        static inline float LightAngle = 160;
        static inline float lightIntensity = 1.0f;
        static inline Shader ShadowShader;
        void DisableShadow() {
            ShadowDoesDraw = false;
        };
        void EnableShadow()
        {
            ShadowDoesDraw = true;
        }
        bool ShadowEnabled()
        {
            return ShadowDoesDraw;
        }
        void SetTint(Color tint)
        {
            Tint = tint;
        }
    private:
        Sprite sprite;
        int order = 0;
        static bool isSorted;
        bool Hidden = false;
        bool ShadowDoesDraw = true;
        Color Tint = Color{ 255,255,255,255 };


};