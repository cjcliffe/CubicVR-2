//
//  ShaderTest.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-02-24.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__ShaderTest__
#define __CubicVR2__ShaderTest__

#include <iostream>
#include "cubicvr2/math/cubic_math.h"
#include "cubicvr2/opengl/Shader.h"
#include "cubicvr2/core/Camera.h"
#include "cubicvr2/opengl/Material.h"

using namespace CubicVR;
using namespace std;

class ShaderTest {
public:
    void run() {
        
        
        cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
        cout << "Shader language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
        
        Shader testShader;
        testShader.loadTextFile("CubicVR_Core.vs", "CubicVR_Core.fs");
        //       testShader.loadTextFile("CubicVR_TestShader.vert", "CubicVR_TestShader.frag");
        if (!testShader.compile()) {
            testShader.dumpShaderLog();
        } else {
            cout << "Shader compile success." << endl;
            shaderVariables vars;
            testShader.getVariables(vars);
            vars.dump();
        }


    }
};

#endif /* defined(__CubicVR2__ShaderTest__) */
