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
     for (int i = Updatables.size() - 1; i >= 0; i--)
     {
         Updatable* u = Updatables[i];
         u->Update(dt);
     }

};
 void Updatable::LateUpdateAll(float dt)
{
     for (int i = Updatables.size() - 1; i >= 0; i--)
     {
         Updatable* u = Updatables[i];
         u->LateUpdate(dt);
     }
 };
