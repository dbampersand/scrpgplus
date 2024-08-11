#pragma once

#include <vector>

class Updatable
{   
    public:
        virtual void Update(float dt) = 0;
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
        }
};