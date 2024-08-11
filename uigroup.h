#pragma once

#include <vector>
#include "uielement.h"
#include <memory>
#include "button.h"

class UIGroup
{
    public:
        template <typename T> void AddElement(std::shared_ptr<T> b)
        {
            //elements.push_back(std::make_unique<T>(b));
            elements.push_back(b);
        }
        void Show();
        void Hide();
        void UpdateGroup(float dt);
        void DrawGroup();
        UIGroup(std::string Name) { name = Name; };
        std::vector<std::shared_ptr<UIElement>> elements;
        std::string name;        
    private:    

};