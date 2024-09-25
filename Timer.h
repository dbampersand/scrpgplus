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

    
    static void CreateTimer(std::function<void()> toCall, float Duration)
    {
        std::shared_ptr<Timer> timer = Create(toCall,Duration);//Create(toCall,Duration);
        Timers.push_back(std::move(timer));
    }
    void Update(float dt) override
    {
        UpdateTimer(dt);
    } 
    void UpdateTimer(float dt)
    {
        timer -= dt;
        if (timer <= 0)
        {
            func();

            auto isThis = [this](std::shared_ptr<Timer> timer) { return timer.get() == this; };
            Timers.erase(std::remove_if(Timers.begin(), Timers.end(), isThis));
        }
    }

    private:
    Timer(std::function<void()> toCall, float Duration){
        func = toCall;
        totalDuration = Duration;
        timer = totalDuration;
    }

    struct MakeSharedEnabler;   

};

