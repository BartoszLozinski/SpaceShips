cmake_minimum_required(VERSION 3.28)
project(SpaceShips)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FLAGS -Werror -Wall -Wpedantic -Wextra)

find_package(GTest REQUIRED)
set(GMOCK_LIBRARIES /usr/lib/libgmock.a /usr/lib/libgmock_main.a)

set(SFML_LIB    sfml-graphics
                sfml-window
                sfml-system)

set(SRC         Source/Sprite.cpp
                Source/Moveable.cpp
                Source/Controllable.cpp
                Source/Bullet.cpp
                Source/Spaceship.cpp
                Source/EnemiesManager.cpp
                Source/SelfSteering.cpp
                Source/Button.cpp
                Source/Menu.cpp)


add_library(${PROJECT_NAME}-lib STATIC  ${SRC})

add_executable(${PROJECT_NAME}  main.cpp)
add_executable(TESTRUNNER   testRunner.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE   ${SFML_LIB}
                                                ${PROJECT_NAME}-lib)

target_link_libraries(TESTRUNNER PRIVATE    ${GTEST_LIBRARIES}
                                            ${GMOCK_LIBRARIES}
                                            ${PROJECT_NAME}-lib
                                            ${SFML_LIB}
                                            pthread)


target_compile_options(${PROJECT_NAME}-lib PRIVATE  ${FLAGS}
                                                    $<$<CONFIG:DEBUG>:-Og -g>
                                                    $<$<CONFIG:RELEASE>:-O3>)

target_compile_options(${PROJECT_NAME} PRIVATE      ${FLAGS} 
                                                    $<$<CONFIG:DEBUG>:-Og -g>
                                                    $<$<CONFIG:RELEASE>:-O3>)
                                                    
target_compile_options(TESTRUNNER   PRIVATE         ${FLAGS}
                                                    $<$<CONFIG:DEBUG>:-Og -g>
                                                    $<$<CONFIG:RELEASE>:-O3>)

set_target_properties(${PROJECT_NAME}-lib   PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)

set_target_properties(${PROJECT_NAME}   PROPERTIES
                                        CXX_STANDARD 20
                                        CXX_STANDARD_REQUIRED ON)

set_target_properties(TESTRUNNER    PROPERTIES
                                    CXX_STANDARD 20
                                    CXX_STANDARD_REQUIRED ON)

#set(CMAKE_VERBOSE_MAKEFILE ON)
