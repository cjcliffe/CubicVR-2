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
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

int main(int argc, char * argv[])
{
//    glutInit(&argc, argv);
//    glutInitWindowPosition(-1,-1);
//    glutInitWindowSize(800, 600);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
//    glutCreateWindow("CubicVR2 Shader Test");

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

