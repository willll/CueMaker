cmake_minimum_required(VERSION 3.0)
project(CueMaker)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS
                    system
                    filesystem
                    program_options
            REQUIRED)

find_package(Ctemplate
            REQUIRED)

find_package(Threads REQUIRED)

set(SOURCE_FILES main.cpp)

add_executable(CueMaker ${SOURCE_FILES})

add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories( CueMaker
                    ${CTEMPLATE_INCLUDE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/plog/include
                    )

target_link_libraries( CueMaker
                    ${Boost_LIBRARIES}
                    ${CTEMPLATE_LIBRARIES}
                    Threads::Threads
                    )

install(TARGETS CueMaker DESTINATION .)