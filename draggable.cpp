#include "draggable.h"
#include "raylib.h"
#include "render.h"

std::vector<Draggable*> Draggable::AllDraggables;
std::vector<DragTarget*> DragTarget::DragTargets;

void Draggable::Drag() 
{
    
}

void Draggable::DragCheck()
{
    if (IsDragged && IsMouseButtonReleased(0))
    {
        for (DragTarget* dt : DragTarget::DragTargets)
        {
            if (CheckCollisionPointRec(Render::GetMousePos(), dt->GetPosition()))
            {
                //dt->OnDrag(this);
            }
        }
    }
}
void Draggable::CheckDraggables()
{
    for (Draggable* d : AllDraggables)
    {
        if (IsMouseButtonPressed(0) && CheckCollisionPointRec(Render::GetMousePos(), d->GetPosition()))
        {
            d->IsDragged = true;
        }
        if (d->IsDragged && IsMouseButtonReleased(0))
        {
            for (DragTarget* dt : DragTarget::DragTargets)
            {
                if (CheckCollisionPointRec(Render::GetMousePos(), dt->GetPosition()))
                {
                    d->IsDragged = false;
                    dt->OnDrag(d);  
                    break;
                }
            }
        }
        if (IsMouseButtonReleased(0) && d->IsDragged)
        {
            d->IsDragged = false;

            Rectangle defaultPosition = d->GetDefaultPosition();
            d->MoveObject(defaultPosition.x,defaultPosition.y);
        }
        if (d->IsDragged)
        {
            Vector2 mouse = Render::GetMousePos();
            d->MoveObject(mouse.x,mouse.y);
        }
    }
}