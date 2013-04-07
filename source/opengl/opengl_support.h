//
//  opengl.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-02-23.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef CubicVR2_opengl_h
#define CubicVR2_opengl_h

#include <OpenGL/gl3.h> 
#include <OpenGL/gl3ext.h>
#include <string>

namespace CubicVR {
    const char *getGLErrorString(GLuint e);
    void checkError(int id);
}

#endif
