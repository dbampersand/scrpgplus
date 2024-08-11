#include "uielement.h"
#include "UI.h"
#include "render.h"

std::vector<Clickable*> Clickable::Clickables;


/*Rectangle UIElement::GetPosition() { 
    Rectangle r; r.x = x; r.y = y; r.width = w; r.height = h; 
    r = Render::TranslateToScreenSpace(r);
    return r; 
};
*/