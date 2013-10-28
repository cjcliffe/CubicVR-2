//
//  main.cpp
//  CubicVR2Test
//
//  Created by Charles J. Cliffe on 2013-02-23.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#include <iostream>
#include "MathTest.h"
//#include "ShaderTest.h"
#include "MeshTest.h"
#include "ShaderRenderTest.h"
//#include <GLUT/GLUT.h>
#ifdef _WIN32
	#define GLFW_INCLUDE_NONE
#else
	#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

int main(int argc, char * argv[])
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(640, 480, "CubicVR-2 Test", NULL, NULL);
	
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

#ifdef _WIN32
	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return -1;
	}
#endif

    MathTest test1;
    
    test1.run();
 
//    ShaderTest test2;
//    
//    test2.run();

    MeshTest test3;
    
    test3.run();
    
    ShaderRenderTest test4;
    
    test4.run(window);

    // insert code here...
    std::cout << endl << "-----" << endl << "Done." << endl;
    
    glfwTerminate();

    return 0;
}

