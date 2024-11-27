#ifndef INCLUDE_UTILS_DELTATIME_H_
#define INCLUDE_UTILS_DELTATIME_H_

#include <chrono>

namespace Platformer
{

class Time
{
    // --------------------- DeltaTime ---------------------
public:
    static void updateDeltaTime();
    static void init();

public:
    static double deltaTime;

private:
    static std::chrono::time_point<std::chrono::high_resolution_clock>
        previousTime;
    static std::chrono::time_point<std::chrono::high_resolution_clock>
        currentTime;

    // --------------------- Cap FPS ---------------------
public:
    static void capFPS();

private:
    static const int targetFPS;
    static const std::chrono::milliseconds frameDuration;  // Frame duration
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_DELTATIME_H_
