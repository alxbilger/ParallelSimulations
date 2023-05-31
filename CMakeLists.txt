cmake_minimum_required(VERSION 3.14)
project(ParallelSimulations)

find_package(Sofa.Component REQUIRED)
find_package(Sofa.Simulation REQUIRED)
set(PARALLELSIMULATIONS_SRC "src")

set(HEADER_FILES "")
set(SOURCE_FILES ${PARALLELSIMULATIONS_SRC}/Main.cpp)

list(APPEND HEADER_FILES
)
list(APPEND SOURCE_FILES
    ${PARALLELSIMULATIONS_SRC}/Main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Sofa.Component Sofa.Simulation)
target_include_directories(${PROJECT_NAME} PUBLIC ${PARALLELSIMULATIONS_SRC})
