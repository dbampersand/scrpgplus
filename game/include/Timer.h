#pragma once

#include <functional>
#include <memory>
#include "updatable.h"
#include <string>
#include <algorithm>

class Timer : Updatable
{
    public:
    //The function to call when timer hits totalDuration
    std::function<void()> func;

    float totalDuration; 
    float timer;

    //Creates a new timer with a function to call
    static std::shared_ptr<Timer> Create(std::function<void()> toCall, float Duration);

    static void CreateTimer(std::function<void()> toCall, float Duration);
    
    //Updates the current timer, decrementing timer and calling the function if the duration has been hit
    void UpdateTimer(float dt);
    
    void Update(float dt) override;

private:
        Timer(std::function<void()> toCall, float Duration);

        //All the timers which is automatically managed 
        static std::vector<std::shared_ptr<Timer>> Timers;
    
    //Exists to allow shared_ptr with a private constructor
    struct MakeSharedEnabler;   

};

