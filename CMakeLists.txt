cmake_minimum_required(VERSION 3.16)
project(Platformer VERSION 0.0.2 LANGUAGES CXX)

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
