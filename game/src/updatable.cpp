#include "updatable.h"

Updatable::~Updatable()
{
    //if 'this' exists inside of Updatables, add it to the list to remove it later
      std::erase(Updatables, this);
}
Updatable::Updatable() {
    if (Updatables.size() == 0)
        Updatables = std::vector<Updatable*>();
    Updatables.push_back(this);
};
 void Updatable::UpdateAll(float dt)
{   
    for (Updatable* u : Updatables)
    {
        u->Update(dt);
    }
};
 void Updatable::LateUpdateAll(float dt)
{
     for (Updatable* u : Updatables)
     {
        u->LateUpdate(dt);
     }
};
