cmake_minimum_required(VERSION 3.16)
project(Platformer VERSION 1.0.7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the build type." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message("${PROJECT_NAME} Build Type: ${CMAKE_BUILD_TYPE}")
message("${PROJECT_NAME} version: ${PROJECT_VERSION}")

# Copy the res directory to the build directory
set(RESOURCES_OUTPUT_DIR "${CMAKE_BINARY_DIR}/res")
add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${RESOURCES_OUTPUT_DIR}
    COMMENT "Copying resources to the build directory."
)

# Getting Dependencies

include(FetchContent)

option(isStatic "Build with static linking" OFF)
set(FETCHCONTENT_QUIET FALSE)

find_package(OpenGL REQUIRED)

if(isStatic)
    set(SDL_SHARED OFF)
    set(SDL_STATIC ON)
    set(BUILD_SHARED_LIBS OFF)
    set(BOX2D_BUILD_SHARED OFF)

    FetchContent_Declare(
        sdl2
        URL https://github.com/libsdl-org/SDL/releases/download/release-2.30.10/SDL2-2.30.10.zip
        URL_HASH SHA256=14b06b30d3400953875e73b0c4771cad1483488a1ef816803610f22b32300ce8
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(sdl2)

else() # Note to self: The if statements are not same. If user wants static SDL2 then it has to be compiled. If not then he doesn't need to compile it. FIND_PACKAGE_ARGS option asks CMake ti first find the system for packages if not found compile it. But it doesn't work for Static

    # SDL -- Please do not compile this, have a heart for you...
    FetchContent_Declare(
        SDL2
        URL https://github.com/libsdl-org/SDL/releases/download/release-2.30.10/SDL2-2.30.10.zip
        URL_HASH SHA256=14b06b30d3400953875e73b0c4771cad1483488a1ef816803610f22b32300ce8
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        FIND_PACKAGE_ARGS
    )
    FetchContent_MakeAvailable(SDL2)
endif()

# GLM (OpenGL Mathematics)
FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
    URL_HASH SHA256=9a995de4da09723bd33ef194e6b79818950e5a8f2e154792f02e4615277cfb8d
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG        origin/master
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(glew)
FetchContent_GetProperties(glew)

if(NOT glew_POPULATED)
  FetchContent_Populate(glew)
  add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# box2d Fetch (Physics)
FetchContent_Declare(
    box2d
    URL https://github.com/erincatto/box2d/archive/f0763aca7d4dfa8f1c19c2c4a9e66fa6e93ea32e.zip
    URL_HASH SHA256=87b5c2006ce45bf3621cba25db62595d44e9bb4d07bac0f35d06ec073dc75cf0
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(box2d)

add_subdirectory(src)

option(ENABLE_TESTING "Enable building tests" ON)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# Install rules
install(TARGETS PlatformerExe PlatformerLib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/res DESTINATION .)

include(InstallRequiredSystemLibraries)
# CPack configuration
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "Ankush Roy")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A platformer game created with SDL2.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# Set maintainer/contact information
set(CPACK_PACKAGE_CONTACT "Ankush Roy <ankush3411111@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_CONTACT}")

# Debain Package dependencies
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2-2.0-0, libsdl2-image-2.0-0")

# set(CPACK_GENERATOR "NSIS;DEB;ZIP;TGZ")
set(CPACK_GENERATOR "ZIP;TGZ")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OS_NAME "Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OS_NAME "Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(OS_NAME "macOS")
else()
    set(OS_NAME "UnknownOS")
endif()

set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${OS_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}")

include(CPack)

