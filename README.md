This will be my first platformer game. It will have features people take for granted like:

- [x] Controlable Character
- [x] Movements
    - [x] Run
    - [x] Walk 
    - [x] ~Crouch~
    - [x] Jump
- [x] ~Attacks~ (I support peece)
    - [x] ~Mele~
    - [x] ~Dash~
    - [x] ~Block~
- [x] Physics System (Box2D-v3)
- [x] Animations
- [x] ~Enemy AI~ (I said I love pieas)
- [x] Level System (Not the best rn. Can improve on it)
- [x] Music
    - [x] Background Music
    - [x] Player Music

## Dependencies:

- Fetched:
    - GLEW
    - Box2D
    - GLM
    - SDL2 -- It is fetched but is recommended to have it in your system pre-installed, otherwise too it'll work (I hope. I mean it should)
- Included:
    - stb_image.h
    - miniaudio.h
- Needed: (Users need it by default)
    - OpenGL-v2.1+
- Others:
    - Catch2 -- For unit tests (There are none, I just wanted to know how they work. But didn't know when to make them so I have no unit tests. But I have support for them)


## Building Command:

For Unix

```bash
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER="/usr/bin/clang++" -DCMAKE_C_COMPILER="/usr/bin/clang" -DCMAKE_CXX_FLAGS="-Wall -O3 -ffast-math" -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING="OFF"
make
./src/main/PlatformerExe
```

