#include "updatable.h"
#include <iostream>

Updatable::~Updatable()
{
    //if 'this' exists inside of Updatables, add it to the list to remove it later
    if (Updatables.size() > 0 && std::find(Updatables.begin(), Updatables.end(), this) != Updatables.end())
        ToRemove.push_back(this);
     // std::erase(Updatables, this);
}
Updatable::Updatable() {
    if (Updatables.size() == 0)
        Updatables = std::vector<Updatable*>();
    Updatables.push_back(this);
};
void Updatable::RemoveFromUpdatables()
{
    for (Updatable* u : ToRemove)
    {
        Updatables.erase(std::remove(Updatables.begin(), Updatables.end(), u));
    }
    ToRemove.clear();
}
 void Updatable::UpdateAll(float dt)
{   
    for (Updatable* u : Updatables)
    {
        if (std::find(ToRemove.begin(), ToRemove.end(), u) == ToRemove.end())
            u->Update(dt);
    }
    RemoveFromUpdatables();

};
 void Updatable::LateUpdateAll(float dt)
{
     for (Updatable* u : Updatables)
     {
         if (std::find(ToRemove.begin(), ToRemove.end(), u) == ToRemove.end())
            u->LateUpdate(dt);
     }
     RemoveFromUpdatables();


    /* for (int i = Updatables.size() - 1; i >= 0; i--)
    {
        Updatable* u = Updatables[i];
       // if (std::find(ToRemove.begin(), ToRemove.end(), u) == ToRemove.end())
            u->LateUpdate(dt);
    }*/
};
