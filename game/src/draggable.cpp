#include "draggable.h"
#include "drawable.h"
#include "raylib.h"
#include "render.h"


std::vector<Draggable*> Draggable::AllDraggables;
std::vector<DragTarget*> DragTarget::DragTargets;


Draggable::Draggable()
{
    AllDraggables.push_back(this);
};
Draggable::~Draggable() {
    Draggable::AllDraggables.erase(std::remove(AllDraggables.begin(), AllDraggables.end(), this), AllDraggables.end());
};

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
void Draggable::CheckDraggables(float dt)
{
    for (Draggable* d : AllDraggables)
    {
        Drawable* dr = (Drawable*)d;
        if (!dr)
            continue;
        if (!d->CanBeDragged())
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
DragTarget::~DragTarget() {
    DragTarget::DragTargets.erase(std::remove(DragTargets.begin(), DragTargets.end(), this), DragTargets.end());
};
