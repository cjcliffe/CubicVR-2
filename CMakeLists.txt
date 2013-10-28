cmake_minimum_required (VERSION 2.6)
project (cubicvr2)

SET(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build/")

include_directories(include)

SET(CubicVR_SRCS
    source/core/BitSet.cpp
    source/core/Camera.cpp
    source/core/Light.cpp
    source/core/Mesh.cpp
    source/core/Timer.cpp
    
    source/math/cubic_math.cpp
    
    source/opengl/CoreShader.cpp
    source/opengl/Material.cpp
    source/opengl/opengl_support.cpp
    # source/opengl/Renderer.cpp
    source/opengl/Shader.cpp
)

SET (CubicVR_HDRS    
    include/cubicvr2/core/BitSet.h
    include/cubicvr2/core/Camera.h
    include/cubicvr2/core/Light.h
    include/cubicvr2/core/Mesh.h
    include/cubicvr2/core/Timer.h
     
    include/cubicvr2/math/aabb.h
    include/cubicvr2/math/cubic_math.h
    include/cubicvr2/math/frustum.h
    include/cubicvr2/math/mat3.h
    include/cubicvr2/math/mat4.h
    include/cubicvr2/math/plane.h
    include/cubicvr2/math/quaternion.h
    include/cubicvr2/math/sphere.h
    include/cubicvr2/math/transform.h
    include/cubicvr2/math/triangle.h
    include/cubicvr2/math/types.h
    include/cubicvr2/math/vec2.h
    include/cubicvr2/math/vec3.h
    include/cubicvr2/math/vec4.h    
    
    include/cubicvr2/opengl/CoreShader.h
    include/cubicvr2/opengl/Material.h
    include/cubicvr2/opengl/opengl_support.h
    # include/cubicvr2/opengl/Renderer.h
    include/cubicvr2/opengl/Shader.h
    
    include/cubicvr2/utility.h
)

if (DEFINED WIN32)
	include_directories(external/glew-1.10.0/include)
	SET (CubicVR_SRCS ${CubicVR_SRCS} external/glew-1.10.0/src/glew.c)
	SET (CubicVR_HDRS ${CubicVR_HDRS} external/glew-1.10.0/include/GL/glew.h)
	FILE(GLOB cubicvr_glew_files "${CMAKE_CURRENT_SOURCE_DIR}/external/glew-1.10.0/include/GL/*.h")
	INSTALL(FILES ${cubicvr_glew_files} DESTINATION include/GL/)
endif (DEFINED WIN32)


add_library(cubicvr2 
  ${CubicVR_SRCS}
  ${CubicVR_HDRS}
)

FILE(GLOB cubicvr_header_files "${CMAKE_CURRENT_SOURCE_DIR}/include/cubicvr2/*.h")
INSTALL(FILES ${cubicvr_header_files} DESTINATION include/cubicvr2/)

FILE(GLOB cubicvr_header_files1 "${CMAKE_CURRENT_SOURCE_DIR}/include/cubicvr2/core/*.h")
INSTALL(FILES ${cubicvr_header_files1} DESTINATION include/cubicvr2/core/)

FILE(GLOB cubicvr_header_files2 "${CMAKE_CURRENT_SOURCE_DIR}/include/cubicvr2/math/*.h")
INSTALL(FILES ${cubicvr_header_files2} DESTINATION include/cubicvr2/math/)

FILE(GLOB cubicvr_header_files2 "${CMAKE_CURRENT_SOURCE_DIR}/include/cubicvr2/opengl/*.h")
INSTALL(FILES ${cubicvr_header_files2} DESTINATION include/cubicvr2/opengl/)

INSTALL(TARGETS cubicvr2
  ARCHIVE DESTINATION lib/
)

