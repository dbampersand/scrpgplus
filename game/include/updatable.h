#pragma once

#include <vector>

class Updatable
{   
    public:

        inline static std::vector<Updatable*> Updatables;
        inline static std::vector<Updatable*> ToRemove;

        virtual void Update(float dt) {};
        virtual void LateUpdate(float dt) {};

         Updatable();
         ~Updatable();


        static void UpdateAll(float dt);
        static void LateUpdateAll(float dt);

};