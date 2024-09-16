#pragma once

#include <vector>

class Updatable
{   
    public:
        virtual void Update(float dt) {};
        virtual void LateUpdate(float dt) {};

        ~Updatable()
        {
            Updatables.erase(std::remove(Updatables.begin(), Updatables.end(), this), Updatables.end());
        }
        Updatable() {
            Updatables.push_back(this);
        };
        static std::vector<Updatable*> Updatables;

        static void UpdateAll(float dt)
        {
            for (Updatable* u : Updatables)
            {
                u->Update(dt);
            }
        };
        static void LateUpdateAll(float dt)
        {
            for (Updatable* u : Updatables)
            {
                u->LateUpdate(dt);
            }
        };

};