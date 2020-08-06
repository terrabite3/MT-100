cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIED ON)

project(MT100_tests)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

add_executable(${PROJECT_NAME}
    Source/Property/IProperty.h
    Source/Property/IntProperty.h
    Source/Property/FloatProperty.h
    Source/Property/GroupProperty.h

    Source/Memory/IMemory.h
    Source/Memory/SysExMemory.cpp
    Source/Memory/SysExMemory.h

    Source/json.hpp

    test/SysExMemory_test.cpp
    test/IntProperty_test.cpp
    test/FloatProperty_test.cpp
    test/GroupProperty_test.cpp

    test/Memory_mock.h
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${CONAN_LIBS}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE Source
)

enable_testing()

add_test(NAME ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND ${PROJECT_NAME}
)