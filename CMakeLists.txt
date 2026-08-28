cmake_minimum_required(VERSION 3.28)
project(rockets LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(rockets src/main.cpp
        src/events.cpp
        src/events.h
        src/config.h
        src/rocket.h
)
target_compile_features(rockets PRIVATE cxx_std_17)
target_link_libraries(rockets PRIVATE SFML::Graphics)

#add_custom_command(
#        TARGET ${PROJECT_NAME}
#        COMMENT "copy res directory"
#        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
#)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT rockets)
