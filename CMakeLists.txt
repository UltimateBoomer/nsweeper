cmake_minimum_required(VERSION 3.27)

project(
  nsweeper
  LANGUAGES CXX
)

# find_package(Curses REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CURSES_USE_NCURSES TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

function(add_sources target_name source_dir)
  file(GLOB_RECURSE sources "${source_dir}/*.cc")
  target_sources(${target_name} PRIVATE ${sources})
endfunction()

add_executable(${PROJECT_NAME})

add_sources(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wpedantic
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:-O0 -g>
  $<$<CONFIG:Release>:-O3>
)
