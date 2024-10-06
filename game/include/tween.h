#pragma once

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
    
    //if the Tween should reset its OldValue while tweening or not
    //if set to false, then this will visibly jump when the value is changed during tweening
    bool shouldResetWhenChanged = true;

    //Creates a tween given a property, an easing function and the duration for it to occur over
    //See Lerp/EaseOutQuad for creating an EasingFunc
    Tween(T* Property, T (*EasingFunc)(T, T, float), float Duration) : Updatable()
    {
        easingFunc = EasingFunc;

        property = Property;

        oldValue = *property;
        from = *property;
        to = *property;

        duration = Duration;
    }   

    //Linearly interpolates between from and to 
    static T Lerp(T from, T to, float percent)
    {
        return from + (to - from) * percent;
    }
    //Quadratic ease out between from and to
    static T EaseOutQuad(T from, T to, float percent)
    {
        return from + ((to - from)) * (1 - (1 - percent) * (1 - percent));
    }
    //Makes tween from Oldvalue and NewValue
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