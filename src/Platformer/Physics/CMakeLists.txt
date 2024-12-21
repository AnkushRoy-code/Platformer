add_library(Physics
    Physics.cpp
    Physics.h
)

target_include_directories(Physics PUBLIC     
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(Physics PUBLIC box2d)
