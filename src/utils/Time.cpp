#include "utils/Time.h"
#include <chrono>
#include <thread>

namespace Platformer
{

double Time::mDeltaTime = 0.0;
std::chrono::time_point<std::chrono::high_resolution_clock> Time::mPreviousTime;
std::chrono::time_point<std::chrono::high_resolution_clock> Time::mCurrentTime;

const int Time::mTargetFPS = 60;  // In seconds
const std::chrono::milliseconds Time::mFrameDuration =
    std::chrono::milliseconds(1000 / mTargetFPS);  // In miliseconds

void Time::init()
{
    mPreviousTime = std::chrono::high_resolution_clock::now();
}

double Time::deltaTime(){
    return mDeltaTime;
}
void Time::updateDeltaTime()
{
    using namespace std::chrono;

    mCurrentTime                  = high_resolution_clock::now();
    duration<double> elapsedTime = mCurrentTime - mPreviousTime;

    mDeltaTime    = elapsedTime.count();
    mPreviousTime = mCurrentTime;
}

void Time::capFPS()
{
    using namespace std::chrono;

    auto frameTime = high_resolution_clock::now() - mCurrentTime;

    if (frameTime < mFrameDuration)
    {
        std::this_thread::sleep_for(mFrameDuration - frameTime);
    }
}

}  // namespace Platformer
