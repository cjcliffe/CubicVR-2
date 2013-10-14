cmake_minimum_required (VERSION 2.6)
project (cubicvr2)

SET(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build/")

include_directories(include)

SET(CubicVR_SRCS
    source/core/BitSet.cpp
    source/core/Camera.cpp
    source/core/Light.cpp
    source/core/Mesh.cpp
    
    source/math/cubic_math.cpp
    
    source/opengl/CoreShader.cpp
    source/opengl/Material.cpp
    source/opengl/opengl_support.cpp
    # source/opengl/Renderer.cpp
    source/opengl/Shader.cpp
)

SET (CubicVR_HDRS    
    include/core/BitSet.h
    include/core/Camera.h
    include/core/Light.h
    include/core/Mesh.h
     
    include/math/aabb.h
    include/math/cubic_math.h
    include/math/frustum.h
    include/math/mat3.h
    include/math/mat4.h
    include/math/plane.h
    include/math/quaternion.h
    include/math/sphere.h
    include/math/transform.h
    include/math/triangle.h
    include/math/types.h
    include/math/vec2.h
    include/math/vec3.h
    include/math/vec4.h    
    
    include/opengl/CoreShader.h
    include/opengl/Material.h
    include/opengl/opengl_support.h
    # include/opengl/Renderer.h
    include/opengl/Shader.h
    
    include/utility.h
)


add_library(cubicvr2 
  ${CubicVR_SRCS}
  ${CubicVR_HDRS}
)

FILE(GLOB cubicvr_header_files "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
INSTALL(FILES ${cubicvr_header_files} DESTINATION include/)

FILE(GLOB cubicvr_header_files1 "${CMAKE_CURRENT_SOURCE_DIR}/include/core/*.h")
INSTALL(FILES ${cubicvr_header_files1} DESTINATION include/core/)

FILE(GLOB cubicvr_header_files2 "${CMAKE_CURRENT_SOURCE_DIR}/include/math/*.h")
INSTALL(FILES ${cubicvr_header_files2} DESTINATION include/math/)

FILE(GLOB cubicvr_header_files2 "${CMAKE_CURRENT_SOURCE_DIR}/include/opengl/*.h")
INSTALL(FILES ${cubicvr_header_files2} DESTINATION include/opengl/)

INSTALL(TARGETS cubicvr2
  ARCHIVE DESTINATION lib/
)

