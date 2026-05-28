cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "Chip8")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project

project(${PROJECT_NAME}
  VERSION 1.0
  DESCRIPTION "A simple Chip8 emulator"
  LANGUAGES C CXX
)

# main files

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME} ${SRC_FILES})

# include to project

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include/SDL2
)

# link to project

if(WIN32)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC
    IMGUI_LIB

    mingw32
    ${CMAKE_SOURCE_DIR}/lib/SDL2/win/libSDL2main.a
    ${CMAKE_SOURCE_DIR}/lib/SDL2/win/libSDL2.a
    ${CMAKE_SOURCE_DIR}/lib/SDL2/win/libSDL2_image.a

    # windows libraries
    imm32 setupapi winmm gdi32 ole32 oleaut32 uuid version
  )
else()
  find_package(SDL2)
  find_package(SDL2_image)

  target_link_libraries(${PROJECT_NAME}
    PUBLIC

    SDL2::SDL2
    SDL2_image::SDL2_image
  )
endif()
