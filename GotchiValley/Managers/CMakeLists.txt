# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)


file(GLOB MANAGERS_SRC CMAKE_CONFIGURE_DEPENDS "*.cpp")

add_library(Managers ${MANAGERS_SRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Managers PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Managers PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(Managers 
    Globals)









