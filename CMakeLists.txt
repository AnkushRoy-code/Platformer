cmake_minimum_required(VERSION 3.16)
project(Platformer VERSION 0.1.3 LANGUAGES CXX)

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

find_package(OpenGL REQUIRED)

set(FETCHCONTENT_QUIET FALSE)

# SDL -- Please do not compile this, have a heart for you...
FetchContent_Declare(
    SDL2
    URL https://github.com/libsdl-org/SDL/releases/download/release-2.30.10/SDL2-2.30.10.zip
    URL_HASH SHA256=14b06b30d3400953875e73b0c4771cad1483488a1ef816803610f22b32300ce8
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(SDL2)

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

# GLM (OpenGL Mathematics)
FetchContent_Declare(
	glm
    URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
    URL_HASH SHA256=9a995de4da09723bd33ef194e6b79818950e5a8f2e154792f02e4615277cfb8d
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(glm)

# Entt Fetch (ECS - Entity Component System)
FetchContent_Declare(
    EnTT
    URL https://github.com/skypjack/entt/archive/refs/tags/v3.14.0.zip
    URL_HASH SHA256=3c3d8014294bf1918e5e1aae537dc823f68964fa3c3dec99d10fa22e5d63a6fe
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(EnTT)

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
# Define package types (e.g., ZIP, DEB)
# set(CPACK_GENERATOR "NSIS;DEB;ZIP;TGZ")
set(CPACK_GENERATOR "DEB;ZIP;TGZ")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}")

include(CPack)

