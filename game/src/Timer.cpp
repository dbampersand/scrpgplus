#include "Timer.h"

std::vector<std::shared_ptr<Timer>> Timer::Timers;

struct Timer::MakeSharedEnabler : public Timer {
    MakeSharedEnabler(std::function<void()> toCall, float Duration) : Timer(toCall,Duration) {
    }
};

std::shared_ptr<Timer> Timer::Create(std::function<void()> toCall, float Duration) {
    return std::make_shared<MakeSharedEnabler>(toCall,Duration);
}
void Timer::CreateTimer(std::function<void()> toCall, float Duration)
{
    std::shared_ptr<Timer> timer = Create(toCall, Duration);//Create(toCall,Duration);
    Timers.push_back(std::move(timer));
}
void Timer::Update(float dt)
{
    UpdateTimer(dt);
}
void Timer::UpdateTimer(float dt)
{
    timer -= dt;
    if (timer <= 0)
    {
        func();

        auto isThis = [this](std::shared_ptr<Timer> timer) { return timer.get() == this; };
        Timers.erase(std::remove_if(Timers.begin(), Timers.end(), isThis));
    }
}
Timer::Timer(std::function<void()> toCall, float Duration) {
    func = toCall;
    totalDuration = Duration;
    timer = totalDuration;
}
