This will be my first platformer game. It will have features people take for granted like:

- [ ] Controlable Character
- [ ] Movements
    - [ ] Run
    - [ ] Walk
    - [ ] Crouch
- [ ] Attacks
    - [ ] Mele
    - [ ] Dash
    - [ ] Block
- [ ] Physics System (Box2D-v3)
- [ ] Animations
- [ ] Enemy AI
- [ ] Level System

## Dependencies:

- Fetched:
    - Entt
    - GLEW
    - Box2D
    - GLM
    - SDL2 -- It is fetched but is recommended to have it in your system pre-installed, otherwise too it'll work (I hope. I mean it should)
- Included:
    - stb_image.h
- Needed: (Users need it by default)
    - OpenGL-v2.1+
- Others:
    - Catch2 -- For debug


## Building Command:

For Unix

```bash
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER="/usr/bin/clang++" -DCMAKE_C_COMPILER="/usr/bin/clang" -DCMAKE_CXX_FLAGS="-Wall -O3 -ffast-math" -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING="OFF"
```

