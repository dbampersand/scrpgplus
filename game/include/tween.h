#pragma once

#include <memory>
#include "updatable.h"

template <typename T>
class Tween : Updatable
{
    public:
    float timer = 0;
    float duration = 1.0f;

    T from;
    T to; 

    T oldValue;

    T* property;

    T (*easingFunc)(T, T, float);

    bool shouldResetWhenChanged = true;
    Tween(T* Property, T (*EasingFunc)(T, T, float), float Duration) : Updatable()
    {
        easingFunc = EasingFunc;

        property = Property;

        oldValue = *property;
        from = *property;
        to = *property;

        duration = Duration;
    }   

    static T Lerp(T from, T to, float percent)
    {
        return from + (to - from) * percent;
    }
    static T EaseOutQuad(T from, T to, float percent)
    {
        return from + ((to - from)) * (1 - (1 - percent) * (1 - percent));
    }

    void MakeTween(T OldValue, T NewValue)
    {
        if (shouldResetWhenChanged)
        {
            from = OldValue;
            timer = 0;
        }
        if (timer >= duration)
        {
            from = OldValue;
            timer = 0;
        }
        to = NewValue;
    }
    void LateUpdate(float dt) override
    {
        timer += dt;

        //if the value has been updated since we last tweened
        if (oldValue != *property)
            MakeTween(easingFunc(oldValue,to,timer / duration),*property);    
        
        if (timer >= duration)
        {
            *property = to;
            oldValue = *property;
            return;
        }
        *property = easingFunc(from,to,timer / duration);
        oldValue = *property;
    }
    
};