#pragma once

#include <vector>

class Updatable
{   
    public:

        static std::vector<Updatable*> Updatables;
        static std::vector<Updatable*> ToRemove;

        virtual void Update(float dt) {};
        virtual void LateUpdate(float dt) {};

        ~Updatable()
        {
            ToRemove.push_back(this);
            //Updatables.erase(std::remove(Updatables.begin(), Updatables.end(), this), Updatables.end());
        }
        Updatable() {
            Updatables.push_back(this);
        };


        static void UpdateAll(float dt)
        {
            for (Updatable* u : ToRemove)
            {
                Updatables.erase(std::remove(Updatables.begin(), Updatables.end(), u), Updatables.end());
            }
            ToRemove.clear();
            for (Updatable* u : Updatables)
            {
                if (std::find(ToRemove.begin(), ToRemove.end(), u) == ToRemove.end())
                    u->Update(dt);
            }

        };
        static void LateUpdateAll(float dt)
        {
            for (Updatable* u : ToRemove)
            {
                Updatables.erase(std::remove(Updatables.begin(), Updatables.end(), u), Updatables.end());
            }
            ToRemove.clear();

            for (Updatable* u : Updatables)
            {
                if (std::find(ToRemove.begin(), ToRemove.end(), u) == ToRemove.end())
                    u->LateUpdate(dt);
            }
        };

};