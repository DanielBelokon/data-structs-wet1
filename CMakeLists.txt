cmake_minimum_required(VERSION 3.14)  # CMake version check
project(data-structs-wet1)               # Create project "data-structs-wet1"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

add_compile_options (-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main1.cpp Wrapper.cpp MainDataStructure.cpp Employee.cpp Company.cpp)


# Add executable target with source files listed in SOURCE_FILES variable
add_executable(data-structs-1 ${SOURCE_FILES})


file(GLOB inputs "${CMAKE_CURRENT_SOURCE_DIR}/tests/input/*.txt")
file(GLOB ac_outputs "${CMAKE_BINARY_DIR}/actual*")

set(i 0)
foreach(filename ${inputs})
    add_test(NAME "input-${i}"
       COMMAND sh -c "$<TARGET_FILE:data-structs-1> < ${filename} > ./actual${i}.txt")
    math(EXPR i "${i} + 1")
endforeach()

set(i 0)
foreach(filename ${ac_outputs})
    add_test(NAME "output-compare-${i}"
       COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${filename} ${CMAKE_CURRENT_SOURCE_DIR}/tests/output/out${i}.txt)
    math(EXPR i "${i} + 1")
endforeach()


enable_testing()
