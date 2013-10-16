#include "cubicvr2/opengl/opengl_support.h"
#include <iostream>

namespace CubicVR {
    using namespace std;
    const char *glErrorString(GLuint e) {
        switch( e )
        {
            case GL_NO_ERROR:
                return "NO ERROR";
            case GL_INVALID_ENUM:
                return "GL_INVALID_ENUM";
            case GL_INVALID_VALUE:
                return "GL_INVALID_VALUE";
            case GL_INVALID_OPERATION:
                return "GL_INVALID_OPERATION";
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "GL_INVALID_FRAMEBUFFER_OPERATION";
            case GL_OUT_OF_MEMORY:
                return "GL_OUT_OF_MEMORY";
            default:
                return "UNKNOWN";
        }
    }    
    
    void checkError(int id) {
        GLenum errCode;
        
        if ((errCode = glGetError()) != GL_NO_ERROR) {
            cout << "OpenGL Error " << id << ": " << glErrorString(errCode) << endl;
        }
        
    }
}
