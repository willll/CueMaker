cmake_minimum_required(VERSION 3.0)
project(CueMaker)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(BUILD_SHARED_LIBS FALSE)

find_package(Boost COMPONENTS
                    system
                    filesystem
                    program_options
            REQUIRED)

find_package(Threads REQUIRED)

set(SOURCE_FILES main.cpp)

add_executable(CueMaker ${SOURCE_FILES})

add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories( CueMaker
                    ${CMAKE_CURRENT_SOURCE_DIR}/inja/include/inja
                    ${CMAKE_CURRENT_SOURCE_DIR}/inja/third_party/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/plog/include
                    )

target_link_libraries( CueMaker
                    PRIVATE
                    ${Boost_LIBRARIES}
                    )

install(TARGETS CueMaker DESTINATION .)