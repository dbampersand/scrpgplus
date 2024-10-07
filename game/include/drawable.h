#pragma once

#include "sprite.h"

#include "raylib.h"

#include <vector>

    

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

class Drawable
{

    public:
        ~Drawable();
        Drawable(std::string path, int index);

        //Sets the rendering order / z-index
        void SetOrder(int ord);
        //Gets the rendering order / z-index
        int GetOrder() const;
        //Adds to the rendering order / z-index
        void AddRenderOrder(int amt);

        //Required to be overriden returning a Rectangle with the current drawing position and size (world space) 
        virtual Rectangle GetPosition() = 0;
        
        //Draws the object; the Rectangle is the drawing position in screen space and the Color is the tint to draw with
        virtual void Draw(Rectangle r, Color tint);
        //Draws the shadow; the Rectangle is the drawing position in screen space
        virtual void DrawShadow(Rectangle r);

        //Disables drawing of the object
        void HideDrawing();
        //Enables drawing of the object
        void ShowDrawing();
        //Returns true if the object is hidden
        bool IsHidden() const;
        //To be overridden: called after HideDrawing() is called and should hide any other necessary objects (children)
        virtual void HideChildren() {
        }
        //To be overridden: called after ShowDrawing() is called and should show any other necessary objects (children)
        virtual void ShowChildren() {
        }

        //Sets the texture this Drawable should use. The function will load the texture if it is not in memory already
        void SetTexture(std::string path);

        //Gets the size of the Texture
        Vector2 GetSize();

        //Draws all Drawables in order
        static void DrawAll(float dt);

        //Disables shadow rendering
        void DisableShadow() {
            ShadowDoesDraw = false;
        };
        //Enables shadow rendering
        void EnableShadow()
        {
            ShadowDoesDraw = true;
        }
        //Returns true if the shadow is drawing
        bool ShadowEnabled() const
        {
            return ShadowDoesDraw;
        }
        //Sets the tint of the object 
        void SetTint(Color tint)
        {
            Tint = tint;
        }
    private:
        static std::vector<Drawable*> drawables;

        //Used to set the angle the shadow is drawn at
        static inline float LightAngle = 160;
        //Used to set the distance the shadow is drawn from the object
        static inline float lightIntensity = 1.0f;
        //Shader used to draw the shadow
        static inline Shader ShadowShader;

        Sprite sprite;
        int order = 0;
        static bool isSorted;
        bool Hidden = false;
        bool ShadowDoesDraw = true;
        Color Tint = Color{ 255,255,255,255 };

        //Returns true if the vector of Drawables is sorted
        static bool IsSorted();




};