#include "draggable.h"
#include "drawable.h"
#include "raylib.h"
#include "render.h"

#include <algorithm>

std::vector<Draggable*> Draggable::AllDraggables;
std::vector<DragTarget*> DragTarget::DragTargets;


Draggable::Draggable()
{
    AllDraggables.push_back(this);
};
Draggable::~Draggable() {
    if (std::find(AllDraggables.begin(), AllDraggables.end(), this) != AllDraggables.end())
        std::erase(AllDraggables, this);
};

void Draggable::Drag() 
{
}

bool DragTarget::SortFunc(DragTarget* d1, DragTarget* d2)
{
    return (d1->GetDrawingOrder() < d2->GetDrawingOrder());
}
bool Draggable::SortFunc(Draggable* d1, Draggable* d2)
{
    return (d1->GetDrawingOrder() < d2->GetDrawingOrder());
}
void Draggable::SortDraggables()
{
    if (!std::is_sorted(AllDraggables.begin(), AllDraggables.end(), Draggable::SortFunc))
        std::sort(AllDraggables.begin(), AllDraggables.end(), Draggable::SortFunc);
}
void DragTarget::SortDragTargets()
{
    if (!std::is_sorted(DragTargets.begin(), DragTargets.end(), DragTarget::SortFunc))
        std::sort(DragTargets.begin(), DragTargets.end(), DragTarget::SortFunc);
}
void Draggable::CheckDraggables(float dt)
{
    Draggable::SortDraggables();
    DragTarget::SortDragTargets();
    for (Draggable* d : AllDraggables)
    {
        Drawable* dr = (Drawable*)d;

        //if not drawing or can't be dragged, continue to next 
        if (!dr)
            continue;
        if (!d->CanBeDragged())
            continue;
        if (dr->IsHidden())
            continue;
        if (!d->Selectable)
            continue;

        //if we've just pressed the mouse button and we're moused over the Draggable
        if (IsMouseButtonPressed(0) && CheckCollisionPointRec(Render::GetMousePos(), d->GetPosition()))
        {
            d->TimeHasBeenDraggedFor = 0;
            d->IsDragged = true;
            d->Offset = Vector2{Render::GetMousePos().x-d->GetPosition().x, Render::GetMousePos().y-d->GetPosition().y};

            //add render order so that we draw this over the top of other similar objects
            if (dr) {
                dr->AddRenderOrder(d->RenderOrderAdd);
                dr->EnableShadow();
            }
        }
        //if we're currently dragging an object and we've just released the mouse button
        if (d->IsDragged && IsMouseButtonReleased(0))
        {
            //if the time the object has been dragged for is less than ClickTime, then activate a click
            //and continue to the next Draggable
            if (d->TimeHasBeenDraggedFor <= Draggable::ClickTime)
            {
                d->DragClick();
                d->IsDragged = false;

                if (dr)
                {
                    dr->AddRenderOrder(-d->RenderOrderAdd);
                    dr->DisableShadow();
                }
                continue;
            }
            bool hasFoundADragTarget = false;
            //otherwise: iterate over all the DragTargets and check if we're hovering over them
            for (DragTarget* dt : DragTarget::DragTargets)
            {
                if (dt->IsHidden() || dt->IsLocked())
                    continue;
                //if we are over one, then call the DragTarget's OnDrag function
                if (CheckCollisionPointRec(Render::GetMousePos(), dt->GetPosition()))
                {
                    d->IsDragged = false;
                    dt->OnDrag(d);  

                    if (dr)
                    {
                        dr->AddRenderOrder(-d->RenderOrderAdd);
                        dr->DisableShadow();
                    }
                    hasFoundADragTarget = true;
                    break;
                }
            }
            //if we haven't found a DragTarget, then we need to reset the object's position
            if (!hasFoundADragTarget)
            {
                d->IsDragged = false;

                Rectangle defaultPosition = d->GetDefaultPosition();
                d->MoveObject(defaultPosition.x, defaultPosition.y);
            }
        }
        //if we're still dragging, then move the object 
        if (d->IsDragged)
        {
            d->TimeHasBeenDraggedFor += dt;
            Vector2 mouse = Render::GetMousePos();
            d->MoveObject(mouse.x-d->Offset.x,mouse.y-d->Offset.y);
        }
    }
}



DragTarget::DragTarget()
{
    DragTargets.push_back(this);
}
DragTarget::~DragTarget() 
{
    if (std::find(DragTargets.begin(), DragTargets.end(), this) != DragTargets.end())
        DragTarget::DragTargets.erase(std::remove(DragTargets.begin(), DragTargets.end(), this), DragTargets.end());
};
