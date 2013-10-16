//
//  Material.cpp
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-03-02.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#include "cubicvr2/opengl/Material.h"
#include "cubicvr2/core/Mesh.h"

namespace CubicVR {
    
    CoreShader Material::coreShader;

    unsigned int Material::computeMeshMask(Mesh *meshObj) {
        unsigned int objMask = 0;
        
        if (meshObj->getVBO()->gl_colors) {
            objMask += SHADER_VERTEX_COLOR;
        }
        
        /*
         #define SHADER_VERTEX_MORPH         512
         #define SHADER_POINT_SPRITE         2048
         #define SHADER_POINT_SIZE           4096
         #define SHADER_POINT_CIRCLE         8192
         */
        
        return objMask;
    }

}