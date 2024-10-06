#pragma once

#include <vector>
#include "uielement.h"
#include <memory>
#include "button.h"

class UIGroup
{
    public:
        //Adds an element to the UIGroup
        template <typename T> void AddElement(std::shared_ptr<T> b)
        {
            static_assert(std::is_base_of<UIElement, T>::value, "AddElement: wrong template type. Must inherit from UIElement");
            elements.push_back(b);
        }
        //Shows the UIGroup
        void Show();
        //Hides the UIGroup
        void Hide();
        //Updates the UIGroup
        void UpdateGroup(float dt);
        //Draws the UIGroup
        void DrawGroup();
        UIGroup(std::string Name) { name = Name; };
        
        std::vector<std::shared_ptr<UIElement>> elements;
        std::string name;        
    private:    

};