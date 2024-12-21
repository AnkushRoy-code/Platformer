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

    /// Delta time or delta timing is the time elapsed between the previous
    /// frame and the current frame in a game loop.
    static double deltaTime();

private:
    static double mDeltaTime;

    static std::chrono::time_point<std::chrono::high_resolution_clock>
        mPreviousTime;
    static std::chrono::time_point<std::chrono::high_resolution_clock>
        mCurrentTime;

    // --------------------- Cap FPS ---------------------
public:
    static void capFPS();

private:
    static const int mTargetFPS;
    static const std::chrono::milliseconds mFrameDuration;  // Frame duration
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_DELTATIME_H_
