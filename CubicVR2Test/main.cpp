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
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>

int main(int argc, char * argv[])
{
//    glutInit(&argc, argv);
//    glutInitWindowPosition(-1,-1);
//    glutInitWindowSize(800, 600);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
//    glutCreateWindow("CubicVR2 Shader Test");

    if (!glfwInit())
        return -1;

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
    if (!glfwOpenWindow(640, 480, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
        return -1;
   
    MathTest test1;
    
    test1.run();
 
//    ShaderTest test2;
//    
//    test2.run();

    MeshTest test3;
    
    test3.run();
    
    ShaderRenderTest test4;
    
    test4.run();

    // insert code here...
    std::cout << endl << "-----" << endl << "Done." << endl;
    return 0;
}

