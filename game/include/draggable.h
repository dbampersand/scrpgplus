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
    static void CheckDraggables(float dt);

    virtual Rectangle GetPosition() = 0;
    virtual Rectangle GetDefaultPosition() = 0;

    int RenderOrderAdd = 100;
    virtual void AddRenderOrder(int amt) = 0;
    bool Selectable = true;

    Vector2 Offset;

    //used to call DragClick - i.e. if the player has just clicked and is not holding
    float TimeHasBeenDraggedFor = 0;
    inline static float ClickTime = 0.25f;
    virtual void DragClick() = 0;

    virtual bool CanBeDragged() = 0;
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
        ~DragTarget(){
            DragTarget::DragTargets.erase(std::remove(DragTargets.begin(), DragTargets.end(), this), DragTargets.end());
        };

        static std::vector<DragTarget*> DragTargets;

};