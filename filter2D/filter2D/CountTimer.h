#pragma once
#include "Header.h"
class ScopedTimer {
public:
    using ClockType = std::chrono::steady_clock;

    ScopedTimer(const char* func)
        : function_name_{ func }, start_{ ClockType::now() } {}

    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer(ScopedTimer&&) = delete;
    auto operator=(const ScopedTimer&)->ScopedTimer & = delete;
    auto operator=(ScopedTimer&&)->ScopedTimer & = delete;

    ~ScopedTimer() {
        using namespace std::chrono;
        auto stop = ClockType::now();
        auto duration = (stop - start_);
        auto ms = duration_cast<microseconds>(duration).count();
        std::ofstream file; file.open("measuringTime.log", std::ios_base::app); file << function_name_ << " : " << ms << " microseconds " << '\n'; file.close();
    }
private:
    const char* function_name_{};
    const ClockType::time_point start_{};
};

#define USE_TIMER 1
#if USE_TIMER
#define MEASURE_FUNCTION() ScopedTimer timer{__func__}
#else
#define MEASURE_FUNCTION()
#endif

