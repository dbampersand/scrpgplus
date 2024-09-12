#pragma once
#include <vector>
#include "updatable.h"
#include "raylib.h"

typedef class DragTarget DragTarget;

class Draggable
{
    public: 
    virtual void Drag();

    bool IsDragged = false;

    Draggable()
    {
        AllDraggables.push_back(this);
    };
    ~Draggable(){
        Draggable::AllDraggables.erase(std::remove(AllDraggables.begin(), AllDraggables.end(), this), AllDraggables.end());
    };
    void DragCheck();

    virtual void MoveObject(float x, float y) = 0;

    static std::vector<Draggable*> AllDraggables;
    static void CheckDraggables();

    virtual Rectangle GetPosition() = 0;
    virtual Rectangle GetDefaultPosition() = 0;
};

class DragTarget
{
    public:
        virtual void OnDrag(Draggable* dr) {};
        virtual Rectangle GetPosition() = 0;

        DragTarget()
        {
            DragTargets.push_back(this);
        }
        static std::vector<DragTarget*> DragTargets;

};