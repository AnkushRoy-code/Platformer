#include "utils/Time.h"
#include <chrono>
#include <thread>

namespace Platformer
{

double Time::deltaTime = 0.0;
std::chrono::time_point<std::chrono::high_resolution_clock> Time::previousTime;
std::chrono::time_point<std::chrono::high_resolution_clock> Time::currentTime;

const int Time::targetFPS = 60;  // In seconds
const std::chrono::milliseconds Time::frameDuration =
    std::chrono::milliseconds(1000 / targetFPS);  // In miliseconds

void Time::init()
{
    previousTime = std::chrono::high_resolution_clock::now();
}

void Time::updateDeltaTime()
{
    using namespace std::chrono;

    currentTime                  = high_resolution_clock::now();
    duration<double> elapsedTime = currentTime - previousTime;

    deltaTime    = elapsedTime.count();
    previousTime = currentTime;
}

void Time::capFPS()
{
    using namespace std::chrono;

    auto frameTime = high_resolution_clock::now() - currentTime;

    if (frameTime < frameDuration)
    {
        std::this_thread::sleep_for(frameDuration - frameTime);
    }
}

}  // namespace Platformer
