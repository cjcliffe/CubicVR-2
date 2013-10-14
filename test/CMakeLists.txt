cmake_minimum_required (VERSION 2.6)
include (../CMakeCommon.txt)
project (test)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR})

add_subdirectory(${PROJECT_SOURCE_DIR}/../external/glfw-3.0.3 ${PROJECT_BINARY_DIR}/glfw/)
include_directories(${PROJECT_SOURCE_DIR}/../external/glfw-3.0.3/include)
include_directories ( "${PROJECT_SOURCE_DIR}/../build/include" )
link_directories ( "${PROJECT_SOURCE_DIR}/../build/lib" )

SET (test_sources
    main.cpp
    MathTest.cpp
    MeshTest.cpp
    ShaderRenderTest.cpp
    ShaderTest.cpp
)



configure_file(${PROJECT_SOURCE_DIR}/../core_shaders/CubicVR_Core.fs ${PROJECT_BINARY_DIR}/CubicVR_Core.fs COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/../core_shaders/CubicVR_Core.vs ${PROJECT_BINARY_DIR}/CubicVR_Core.vs COPYONLY)


add_executable(test ${test_sources})

target_link_libraries(test cubicvr2 glfw ${GLFW_LIBRARIES})

