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
        if (!dr)
            continue;
        if (!d->CanBeDragged())
            continue;
        if (dr->IsHidden())
            continue;

        if (IsMouseButtonPressed(0) && CheckCollisionPointRec(Render::GetMousePos(), d->GetPosition()))
        {
            if (d->Selectable)
            {
                d->TimeHasBeenDraggedFor = 0;

                d->IsDragged = true;
                d->Offset = Vector2{Render::GetMousePos().x-d->GetPosition().x, Render::GetMousePos().y-d->GetPosition().y};
                if (dr) {
                    dr->AddRenderOrder(d->RenderOrderAdd);
                    dr->EnableShadow();
                }
            }
        }
        if (d->IsDragged && IsMouseButtonReleased(0))
        {
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

            for (DragTarget* dt : DragTarget::DragTargets)
            {
                if (dt->IsHidden())
                    continue;
                if (CheckCollisionPointRec(Render::GetMousePos(), dt->GetPosition()))
                {
                    d->IsDragged = false;
                    dt->OnDrag(d);  

                    if (dr)
                    {
                        dr->AddRenderOrder(-d->RenderOrderAdd);
                        dr->DisableShadow();
                    }
                    break;
                }
            }
        }
        if (IsMouseButtonReleased(0) && d->IsDragged)
        {
            d->IsDragged = false;
            if (dr)
            {
                dr->AddRenderOrder(-d->RenderOrderAdd);
                dr->DisableShadow();
            }

            if (d->TimeHasBeenDraggedFor <= Draggable::ClickTime)
            {
                d->DragClick();
            }
            else
            {
                Rectangle defaultPosition = d->GetDefaultPosition();
                d->MoveObject(defaultPosition.x,defaultPosition.y);
            }
        }
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
