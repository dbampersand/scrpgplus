#pragma once

#include <functional>
#include <memory>
#include "updatable.h"
#include <string>
#include <algorithm>

class Timer : Updatable
{
    public:
    std::function<void()> func;
    float totalDuration; 
    float timer;

    static std::shared_ptr<Timer> Create(std::function<void()> toCall, float Duration);

    static std::vector<std::shared_ptr<Timer>> Timers;

    
    static void CreateTimer(std::function<void()> toCall, float Duration);
    void Update(float dt);
    void UpdateTimer(float dt);
    private:
        Timer(std::function<void()> toCall, float Duration);

    struct MakeSharedEnabler;   

};

