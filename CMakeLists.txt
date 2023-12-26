cmake_minimum_required(VERSION 3.27)

project(
  nsweeper
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

find_package(Notcurses CONFIG REQUIRED)
find_package(Notcurses++ CONFIG REQUIRED)

function(add_sources target_name source_dir)
  file(GLOB_RECURSE sources "${source_dir}/*")
  target_sources(${target_name} PRIVATE ${sources})
endfunction()

add_executable(${PROJECT_NAME})

add_sources(${PROJECT_NAME} src)

target_include_directories(${PROJECT_NAME} PRIVATE
  include
  ${Notcurses_INCLUDE_DIRS}
  ${Notcurses++_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME} PRIVATE
  ${Notcurses_LIBRARY_DIRS}
  ${Notcurses++_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${Notcurses_LIBRARIES}
  ${Notcurses++_LIBRARIES}
)
