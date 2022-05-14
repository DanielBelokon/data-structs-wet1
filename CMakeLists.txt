cmake_minimum_required(VERSION 3.14)  # CMake version check
project(data-structs-wet1)               # Create project "data-structs-wet1"
set(CMAKE_CXX_STANDARD 11)            # Enable c++14 standard

add_compile_options (-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main1.cpp Wrapper.cpp MainDataStructure.cpp Employee.cpp Company.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(data-structs-1 ${SOURCE_FILES})

file(GLOB inputs "${CMAKE_CURRENT_SOURCE_DIR}/tests/input/*.in")
file(GLOB outputs "${CMAKE_CURRENT_SOURCE_DIR}/tests/output/*.out")

foreach(filename ${inputs})
    get_filename_component(filename_no_extension ${filename} NAME_WE)
    string(REGEX REPLACE "in" "actual" actual_no_extension ${filename_no_extension})

    add_test(NAME "${filename_no_extension}"
       COMMAND sh -c "$<TARGET_FILE:data-structs-1> < ${filename} > ${CMAKE_CURRENT_BINARY_DIR}/${actual_no_extension}.txt")
endforeach()

foreach(filename ${outputs})
    get_filename_component(filename_no_extension ${filename} NAME_WE)
    string(REGEX REPLACE "out" "in" input_no_extension ${filename_no_extension})
    string(REGEX REPLACE "out" "actual" actual ${filename_no_extension})

    add_test(NAME "compare${filename_no_extension}"
       COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/${actual}.txt ${filename})
    set_tests_properties(compare${filename_no_extension} PROPERTIES DEPENDS "${input_no_extension}")

endforeach()


enable_testing()
