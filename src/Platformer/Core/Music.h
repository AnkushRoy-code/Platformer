#ifndef INCLUDE_CORE_MUSIC_H_
#define INCLUDE_CORE_MUSIC_H_

#include <filesystem>
#include <vector>

// My exams are close and I want to close this project faster. So whatever works
// will work. My other code is enou

#include "miniaudio.h"

namespace Platformer
{

class Music
{
public:
    static void init();
    static void close();

    static ma_engine Engine;
};

class SFXs
{
public:
    void addSFX(int Index, const std::filesystem::path &Path);
    void playSFX(int Index);
    void stopSFX(int Index);
    void close();

private:
    std::vector<ma_sound> mSFXes;
};

};  // namespace Platformer

#endif  // INCLUDE_CORE_MUSIC_H_
