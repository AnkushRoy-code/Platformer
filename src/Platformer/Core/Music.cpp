#define MINIAUDIO_IMPLEMENTATION  // compile the functions here

#include "Music.h"
#include <filesystem>
#include <iostream>

namespace Platformer
{

ma_engine Music::Engine {};

void Music::init()
{
    if (ma_engine_init(nullptr, &Engine) != MA_SUCCESS)
    {
        std::cerr << "Failed to initialise Mucis engine!\n";
        return;
    }
}

void Music::close()
{
    ma_engine_uninit(&Engine);
}

void SFXs::addSFX(int Index, const std::filesystem::path &Path)
{
    if (Index >= mSFXes.size())
    {
        mSFXes.resize(Index + 10);
        // I kept space for (Index + 10) SFXes. If there are more than that many
        // sfxes in one Object.... It won't work because C++ and it is perfectly
        // reasonable why it won't work. Anyway this is temporary and will
        // remove it when I find a alt soln or become smart enough
    }
    auto result = ma_sound_init_from_file(&Music::Engine, Path.c_str(),
                                          MA_SOUND_FLAG_STREAM, nullptr,
                                          nullptr, &mSFXes[Index]);

    if (result != MA_SUCCESS)
    {
        std::cerr << "Yeah... No I am done\n";
    }
}

void SFXs::playSFX(int Index)
{
    if (Index < 0 || Index >= mSFXes.size())
    {
        std::cerr << "Invalid Index" << Index << std::endl;
        return;
    }

    if (ma_sound_is_playing(&mSFXes[Index]))
    {
        ma_sound_stop(&mSFXes[Index]);
    }

    ma_sound_start(&mSFXes[Index]);
}

void SFXs::stopSFX(int Index)
{
    if (Index < 0 || Index >= mSFXes.size())
    {
        std::cerr << "Invalid Index" << Index << std::endl;
        return;
    }

    if (ma_sound_is_playing(&mSFXes[Index]))
    {
        ma_sound_stop(&mSFXes[Index]);
    }
}
void SFXs::close()
{
    for (auto sound: mSFXes)
    {
        ma_sound_uninit(&sound);
    }
}

}  // namespace Platformer

// ma_sound Music::createSFXFromFile(const std::filesystem::path &Path)
// {
//     ma_sound sound;

//     if (!std::filesystem::exists(Path))
//     {
//         std::cerr << "File not found" << Path.string() << "\n";
//         return sound;  // Not good. Only for now.
//     }

//     auto result = ma_sound_init_from_file(
//         &Engine, Path.c_str(), MA_SOUND_FLAG_DECODE, nullptr, nullptr,
//         &sound);

//     if (result != MA_SUCCESS)
//     {
//         std::cerr << "Couldn't initialise sound: " << Path.string() << "\n";
//     }

//     return sound;
// }
