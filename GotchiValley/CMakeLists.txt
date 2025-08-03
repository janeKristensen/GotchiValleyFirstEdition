# CMakeList.txt : CMake project for GotchiValley, include source and define
# project specific logic here.
#



# Add source to this project's executable.
add_executable (GotchiValley 
    "Entities/Creature.cpp"
    "Entities/Creature.h"
    "Entities/Entity.cpp"
    "Entities/Entity.h"
    "Entities/Interfaces.h"
    "Entities/Player.h"
    "Entities/Player.cpp"
    "Entities/Level.h"
    "Entities/Level.cpp"
    "Game/GotchiValley.cpp" 
    "Game/GotchiValley.h"  
    "Game/GameWorld.h"  
    "Game/GameWorld.cpp" 
    "Game/Animations.h"
    "Globals/Components.h"
    "Globals/GlobalVariables.h"
    "Globals/GlobalVariables.cpp"
    "Globals/IObserver.h"  
    "Game/LevelManager.h"
    "Game/LevelManager.cpp"
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
    "Systems/Pathfinder.h"
    "Systems/Pathfinder.cpp"
    "Systems/AudioSystem.h"
    "Systems/AudioSystem.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GotchiValley PROPERTY CXX_STANDARD 20)
endif()

# Include sub-projects.
add_subdirectory ("Entities")
add_subdirectory ("Systems")
add_subdirectory ("Globals")
add_subdirectory ("Game")

# Set the SFML path
set(SFML_DIR ${CMAKE_SOURCE_DIR}/external/SFML-3.0.0)

#Add the include directory
include_directories(GotchiValley
    ${SFML_DIR}/include
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities
    ${CMAKE_CURRENT_SOURCE_DIR}/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Globals
    ${CMAKE_CURRENT_SOURCE_DIR}/Systems
)

# Link SFML libraries
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(GotchiValley PUBLIC
    ${SFML_DIR}/lib/sfml-system-d.lib
    ${SFML_DIR}/lib/sfml-window-d.lib
    ${SFML_DIR}/lib/sfml-audio-d.lib
    ${SFML_DIR}/lib/sfml-graphics-d.lib
    )
else()
    target_link_libraries(GotchiValley PUBLIC
    ${SFML_DIR}/lib/sfml-system.lib
    ${SFML_DIR}/lib/sfml-window.lib
    ${SFML_DIR}/lib/sfml-audio.lib
    ${SFML_DIR}/lib/sfml-graphics.lib
)
endif()


# Get all image files in the resources directory
file(GLOB IMAGE_FILES ${CMAKE_SOURCE_DIR}/resources/*.png)

# Add a custom command for each file
foreach(IMAGE_FILE ${IMAGE_FILES})
    get_filename_component(FILE_NAME ${IMAGE_FILE} NAME)
    add_custom_command(
        TARGET GotchiValley POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${IMAGE_FILE}
            ${CMAKE_BINARY_DIR}/GotchiValley/resources/${FILE_NAME}
    )
endforeach()

# Get all sound files in the resources directory
file(GLOB SOUND_FILES ${CMAKE_SOURCE_DIR}/resources/sounds/*.wav)

# Add a custom command for each file
foreach(SOUND_FILE ${SOUND_FILES})
    get_filename_component(FILE_NAME ${SOUND_FILE} NAME)
    add_custom_command(
        TARGET GotchiValley POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${SOUND_FILE}
            ${CMAKE_BINARY_DIR}/GotchiValley/resources/${FILE_NAME}
    )
endforeach()

# Get all sound files in the resources directory
file(GLOB JSON_FILES ${CMAKE_SOURCE_DIR}/resources/*.json)

# Add a custom command for each file
foreach(JSON_FILE ${JSON_FILES})
    get_filename_component(FILE_NAME ${JSON_FILE} NAME)
    add_custom_command(
        TARGET GotchiValley POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${JSON_FILE}
            ${CMAKE_BINARY_DIR}/GotchiValley/resources/${FILE_NAME}
    )
endforeach()




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
