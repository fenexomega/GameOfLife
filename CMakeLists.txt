project("GAME OF LIFE" CXX C)
cmake_minimum_required(VERSION 2.8)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

file(GLOB_RECURSE variable src/*.cpp src/*.h)

add_executable(game ${variable}
)
set(FILEPATH src/GameFiles/)

set(CMAKE_BINARY_DIR ../gof-build)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

if(UNIX)
    message("Unix Detected, using shared libraries for Linux")
    include_directories( ${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIR} )
    set(COMPILER_LIBS ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY})
else(UNIX)
    message("Windows Detected, using static libraries for Windows")
    set(COMPILER_LIBS  -lmingw32 
    -lSDLmain -lSDL -lwinmm  -mwindows -liconv -lm -luser32 -lgdi32 -lwinmm -ldxguid
    -ltiff -llzma -ljpeg -lpng16 -lz -lSDL_image)
endif(UNIX)

target_link_libraries(game ${COMPILER_LIBS} )
