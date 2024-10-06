#pragma once

#include <vector>

class Updatable
{   
    public:

         Updatable();
         ~Updatable();

        //To be overridden, called every frame before Draw
        virtual void Update(float dt) {};
        //To be overridden, called every frame after Draw
        virtual void LateUpdate(float dt) {};

        //Updates every Updatable, called before Draw
        static void UpdateAll(float dt);
        //Updates every Updatable, called after Draw
        static void LateUpdateAll(float dt);

private:
    inline static std::vector<Updatable*> Updatables;

};