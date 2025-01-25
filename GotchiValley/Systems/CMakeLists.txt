# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB SYSTEMS_SRC CMAKE_CONFIGURE_DEPENDS "*.cpp")

add_library (Systems ${SYSTEMS_SRC})

target_include_directories(Systems PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Link SFML libraries
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(Systems 
    Globals
    ${SFML_DIR}/lib/sfml-system-d.lib
    ${SFML_DIR}/lib/sfml-window-d.lib
    ${SFML_DIR}/lib/sfml-graphics-d.lib
    )
else()
    target_link_libraries(Systems
    Globals
    ${SFML_DIR}/lib/sfml-system.lib
    ${SFML_DIR}/lib/sfml-window.lib
    ${SFML_DIR}/lib/sfml-graphics.lib
)
endif()









