#include "updatable.h"

std::vector<Updatable*> Updatable::Updatables;
std::vector<Updatable*> Updatable::ToRemove;

Updatable::~Updatable()
{
    //if 'this' exists inside of Updatables, add it to the list to remove it later
    if (Updatables.size() > 0 && std::find(Updatables.begin(), Updatables.end(), this) != Updatables.end())
        ToRemove.push_back(this);
}
Updatable::Updatable() {
    Updatables.push_back(this);
};
 void Updatable::UpdateAll(float dt)
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
 void Updatable::LateUpdateAll(float dt)
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
