#include "Timer.h"

std::vector<std::shared_ptr<Timer>> Timer::Timers;

struct Timer::MakeSharedEnabler : public Timer {
    MakeSharedEnabler(std::function<void()> toCall, float Duration) : Timer(toCall,Duration) {
    }
};

std::shared_ptr<Timer> Timer::Create(std::function<void()> toCall, float Duration) {
    return std::make_shared<MakeSharedEnabler>(toCall,Duration);
}
