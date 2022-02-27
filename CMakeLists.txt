cmake_minimum_required(VERSION 3.0)
project(cuemaker)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS
                    system
                    filesystem
                    program_options
            REQUIRED)

find_package(Ctemplate  REQUIRED)

find_package(Threads REQUIRED)

set(SOURCE_FILES main.cpp)

add_executable(cuemaker ${SOURCE_FILES})

include_directories( cuemaker
                    ${CTEMPLATE_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_SOURCE_DIR}/plog/include>)

target_link_libraries( cuemaker LINK_PUBLIC
                    ${Boost_LIBRARIES}
                    ${CTEMPLATE_LIBRARIES}
                    Threads::Threads)

install(TARGETS cuemaker DESTINATION .)