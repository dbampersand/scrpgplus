#pragma once

#include "updatable.h"

#include "raylib.h"

#include <vector>


typedef class DragTarget DragTarget;

class Draggable
{
 public: 

    bool IsDragged = false;

    Draggable();
    ~Draggable();

    //Iterates over all the draggables and checks if they have been clicked on
    static void CheckDraggables(float dt);

    bool Selectable = true;

    Vector2 Offset;

    //Used to call DragClick - i.e. if the player has just clicked and is not holding
    float TimeHasBeenDraggedFor = 0;
    //The maximum amount of time that can be considered a 'click' rather than a drag when the mouse button is released
    inline static float ClickTime = 0.1f;
    //To be overridden - if the player has clicked an object then very quickly released 
    virtual void DragClick() = 0;

    //Adds render order so that when the object is dragged, it is rendered on top of other similar objects
    virtual void AddRenderOrder(int amt) = 0;

    //To be overridden, gets the current position of the object
    virtual Rectangle GetPosition() = 0;
    //To be overridden, gets the default position of the object so that when it is dropped over something that isn't a target, it can return to where it was before
    virtual Rectangle GetDefaultPosition() = 0;
   
    //To be overridden, move the object
    virtual void MoveObject(float x, float y) = 0;

    //Called when the object is dragged
    virtual void Drag();
    
    //To be overridden, returns if the object can be dragged
    virtual bool CanBeDragged() = 0;
    //To be overridden, gets the current drawing order
    virtual int GetDrawingOrder() = 0;

private:
    //Sorts the draggables
    static void SortDraggables();
    //Reverse sort function for AllDraggables, sorts by rendering order
    static bool SortFunc(Draggable* d1, Draggable* d2);

    int RenderOrderAdd = 100;

    //List of all the draggables, automatically managed in constructor/destructor
    static std::vector<Draggable*> AllDraggables;
};

class DragTarget
{
    public:

        DragTarget();
        ~DragTarget();


        //Sorts DragTargets
        static void SortDragTargets();

        //To be overridden, returns true if the DragTarget is hidden
        virtual bool IsHidden() = 0;
        //To be overridden, gets the current drawing order
        virtual int GetDrawingOrder() = 0;

        //Called when a Draggable is released on top of the target
        virtual void OnDrag(Draggable* dr) {};
        //To be overridden, returns the current position
        virtual Rectangle GetPosition() = 0;

        //List of all the DragTargets, automatically managed in constructor/destructor
        static std::vector<DragTarget*> DragTargets;

        void Lock()
        {
            Locked = true;
        }
        void Unlock()
        {
            Locked = false;
        }
        void SetLocked(bool isLocked)
        {
            Locked = isLocked;
        }
        bool IsLocked()
        {
            return Locked;
        }
private:
    //Reverse sort function for DragTargets, sorts by rendering order
    static bool SortFunc(DragTarget* d1, DragTarget* d2);
    //
    bool Locked = false;
};