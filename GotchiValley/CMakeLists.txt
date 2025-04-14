# CMakeList.txt : CMake project for GotchiValley, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GotchiValley 
    "Game/GotchiValley.cpp" 
    "Game/GotchiValley.h"  
    "Game/GameWorld.h"  
    "Game/GameWorld.cpp" 
    "Game/Factory.h"
    "Game/Animations.h"
    "Globals/Components.h"
    "Globals/GlobalVariables.h"
    "Globals/SharedObjects.h"
    "Globals/SharedObjects.cpp"
    "Globals/IObserver.h"  
    "Managers/ComponentManager.h"
    "Managers/ComponentRegistry.h"
    "Managers/EntityManager.h"
    "Managers/EntityManager.cpp"
    "Managers/LevelManager.h"
    "Managers/LevelManager.cpp"
    "Systems/AnimationSystem.h"
    "Systems/AnimationSystem.cpp"
    "Systems/CollisionSystem.h"
    "Systems/CollisionSystem.cpp"
    "Systems/MovementSystem.h"
    "Systems/MovementSystem.cpp"
    "Systems/PhysicsSystem.h"
    "Systems/PhysicsSystem.cpp"
    "Systems/RenderSystem.h"
    "Systems/RenderSystem.cpp"
    "Systems/UISystem.h"
    "Systems/UISystem.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GotchiValley PROPERTY CXX_STANDARD 20)
endif()

# Include sub-projects.
add_subdirectory ("Systems")
add_subdirectory ("Managers")
add_subdirectory ("Globals")
add_subdirectory ("Game")

# Get all image files in the resources directory
file(GLOB IMAGE_FILES ${CMAKE_SOURCE_DIR}/resources/*.png)

# Add a custom command for each file
foreach(IMAGE_FILE ${IMAGE_FILES})
    get_filename_component(FILE_NAME ${IMAGE_FILE} NAME)
    add_custom_command(
        TARGET GotchiValley POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${IMAGE_FILE}
            ${CMAKE_BINARY_DIR}/GotchiValley/${FILE_NAME}
    )
endforeach()


# Set the SFML path
set(SFML_DIR ${CMAKE_SOURCE_DIR}/external/SFML-3.0.0)

# Add the include directory
include_directories(
    ${SFML_DIR}/include
    ${CMAKE_SOURCE_DIR}/GotchiValley/Globals
    ${CMAKE_SOURCE_DIR}/GotchiValley/Managers
    ${CMAKE_SOURCE_DIR}/GotchiValley/Systems
    ${CMAKE_SOURCE_DIR}/GotchiValley/Game
)

# Link SFML libraries
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(GotchiValley
    ${SFML_DIR}/lib/sfml-system-d.lib
    ${SFML_DIR}/lib/sfml-window-d.lib
    ${SFML_DIR}/lib/sfml-graphics-d.lib
    )
else()
    target_link_libraries(GotchiValley
    ${SFML_DIR}/lib/sfml-system.lib
    ${SFML_DIR}/lib/sfml-window.lib
    ${SFML_DIR}/lib/sfml-graphics.lib
)
endif()


# Optional: Add runtime DLLs to the output directory (Windows-specific)
if (WIN32)
    file(GLOB SFML_DLLS "${SFML_DIR}/bin/*.dll")
    add_custom_command(TARGET GotchiValley PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_DLLS}
          $<TARGET_FILE_DIR:GotchiValley>)
endif()

if(MSVC)
    target_compile_options(GotchiValley PRIVATE "/Zc:__cplusplus")
    target_compile_options(GotchiValley PRIVATE "/std:c++20")
else()
    target_compile_features(GotchiValley PRIVATE cxx_std_20)
endif()
