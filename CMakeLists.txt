cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${sago_background_SOURCE_DIR}/misc/cmake")
project (sago_background)

#Setup SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#Setup things that use pkg-config
find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)

find_package(Boost COMPONENTS program_options REQUIRED)

file(GLOB SOURCES "src/sago/*.cpp")

add_executable(sago_background src/sago_background.cpp ${SOURCES})
TARGET_LINK_LIBRARIES( sago_background ${Boost_LIBRARIES} )
target_link_libraries( sago_background ${SDL2_LIBRARY})
target_link_libraries( sago_background physfs)
target_link_libraries( sago_background ${SDL2MIXER_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
