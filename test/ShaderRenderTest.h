//
//  ShaderRenderTest.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-03-11.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__ShaderRenderTest__
#define __CubicVR2__ShaderRenderTest__


#include <iostream>
#include "cubicvr2/opengl/Shader.h"
#include "cubicvr2/opengl/Material.h"
#include "cubicvr2/core/Mesh.h"
#include "cubicvr2/core/Camera.h"
#ifdef _WIN32
#define GLFW_INCLUDE_NONE
#else
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>


namespace CubicVR {
    
    
    class ShaderRenderTest {
    public:
        static Shader testShader;
        static Material mat;
        static Camera testCam;
        static Mesh testMesh;
        static int i;
//        static GLuint vao;
        
        static void display(void)
        {
            // Clear frame buffer and depth buffer
            glClearColor(0.3f,0.3f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, testCam.getWidth(), testCam.getHeight());
            
            
            testCam.setPosition(vec3(1.5f*sinf((float)i/100.0f),1.5f*sinf(i/100.0f),1.5f*cosf((float)i/100.0f)));
            testCam.calcProjection();
            mat.setMatrixModelView(testCam.getMatrixModelView());
            mat.setMatrixProjection(testCam.getMatrixProjection());

            mat.use(LIGHT_NONE,0,&testMesh);
            checkError(11);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,testMesh.getVBO()->gl_elements);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
            checkError(414);
            i++;
        }
        
        
        
        
        void run(GLFWwindow *window) {
            Material::coreShader.loadTextFile("CubicVR_Core.vs", "CubicVR_Core.fs");
            
            testCam.setDimensions(640,480);
            testCam.setFOV(60);
            testCam.setTarget(vec3(0,0,0));
//            testCam.setPosition(vec3(0.75,0.75,0.75));
            testCam.calcProjection();
            
            
            testMesh.addPoint(vec3(0.0f, 0.5f, 0.0f));
            testMesh.addPoint(vec3(-0.5f, -0.5f, 0.0f));
            testMesh.addPoint(vec3(0.5f, -0.5f, 0.0f));

            testMesh.newFace().setPoints(triangleFaceRef(0,1,2)).setColors(triangleVec3Ref(vec3(0,1,0),vec3(1,0,0),vec3(0,0,1)));
            
            testMesh.prepare();

//            mat.initShader(&testShader);
            
            mat.setMatrixModelView(testCam.getMatrixModelView());
            mat.setMatrixProjection(testCam.getMatrixProjection()); // 
            mat.setMatrixObject(mat4::identity());
            mat.setColor(vec3(0,0,0));
            mat.setDiffuse(vec3(1,1,1));
            mat.setAmbient(vec3(1,1,1));
            mat.setVertexPosition(testMesh.getVBO()->gl_points);
            mat.setVertexNormal(testMesh.getVBO()->gl_normals);
            mat.setVertexColor(testMesh.getVBO()->gl_colors);
            
                                  
            while (!glfwWindowShouldClose(window))
            {
                /* Render here */
                
                /* Swap front and back buffers and process events */
                display();
                glfwSwapBuffers(window);
                glfwPollEvents();
            }

//            glGenVertexArrays(1, &vao);

        }
    };
}

#endif /* defined(__CubicVR2__ShaderRenderTest__) */
