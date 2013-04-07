//
//  MeshTest.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-03-03.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__MeshTest__
#define __CubicVR2__MeshTest__

#include <iostream>
#include <cstring>
#include "cubic_math.h"
#include "Mesh.h"
#include "Camera.h"

namespace CubicVR {
    using namespace std;

    class MeshTest {
    public:
        void run() {
            Mesh test;

            __float half_box = 1;
            test.addPoint(vec3(half_box, -half_box, half_box));
            test.addPoint(vec3(half_box, half_box, half_box));
            test.addPoint(vec3(-half_box, half_box, half_box));
            test.addPoint(vec3(-half_box, -half_box, half_box));
            test.addPoint(vec3(half_box, -half_box, -half_box));
            test.addPoint(vec3(half_box, half_box, -half_box));
            test.addPoint(vec3(-half_box, half_box, -half_box));
            test.addPoint(vec3(-half_box, -half_box, -half_box));

            quadVec3Ref faceColors(vec3(1,0,0),vec3(0,1,0),vec3(0,0,1),vec3(1,1,1));
            quadVec2Ref faceUVs(vec2(0,1),vec2(1,1),vec2(1,0),vec2(0,0));

            test.newFace(quadFaceRef(0, 1, 2, 3)).setUVs(faceUVs).setColors(faceColors);
            test.newFace(quadFaceRef(0, 1, 2, 3)).setUVs(faceUVs).setColors(faceColors);
            test.newFace(quadFaceRef(7, 6, 5, 4)).setUVs(faceUVs).setColors(faceColors);
            test.newFace(quadFaceRef(4, 5, 1, 0)).setUVs(faceUVs).setColors(faceColors);
            test.newFace(quadFaceRef(5, 6, 2, 1)).setUVs(faceUVs).setColors(faceColors);
            test.newFace(quadFaceRef(6, 7, 3, 2)).setUVs(faceUVs).setColors(faceColors);
            test.newFace(quadFaceRef(7, 4, 0, 3)).setUVs(faceUVs).setColors(faceColors);
  
            test.prepare();
//            test.triangulate();
            
//            compileMapVBO *vbo_map = test.compileMap();
//            compiledVBO *vbo_compiled = test.compileVBO(vbo_map);
//            compiledVBOBuffer *vbo_buffer = test.bufferVBO(vbo_compiled);
        }
    };
}

#endif /* defined(__CubicVR2__MeshTest__) */
