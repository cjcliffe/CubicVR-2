//
//  MathTest.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-02-23.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__MathTest__
#define __CubicVR2__MathTest__

#include <iostream>
#include <sstream>

#include "cubic_math.h"

using namespace CubicVR;
using namespace std;

class MathTest {
public:
    void run() {
        vec3 a = vec3(1,2,3);
        cout << "vec3:" << endl;
        cout << "\tsizeof(vec3) = " << sizeof(vec3) << endl;
        cout << "\t{1, 2, 3} = " << a << endl;
        cout << "\t{1, 2, 3} ([0][1][2]) = {" << a[0] << ", " << a[1] << ", " << a[2] << "}" << endl;
        cout << "\t{1, 2, 3} (r,g,b) = {" << a.r() << ", " << a.g() << ", " << a.b() << "}" << endl;
        cout << "\t{1, 2, 3} - {2, 3, 1} = " << (a-vec3(2,3,1)) << endl;
        cout << "\t{1, 2, 3} + {2, 3, 1} = " << (a+vec3(2,3,1)) << endl;
        cout << "\t{1, 2, 3} * {2, 3, 1} = " << (a*vec3(2,3,1)) << endl;
        cout << "\t{1, 2, 3} * 10 = " << (a*10) << endl;
        cout << "\t{1, 2, 3} . {2, 3, 1} = " << vec3::dot(a,vec3(2,3,1)) << endl;
        cout << "\t{1, 2, 3} ang {2, 3, 1} = " << vec3::angle(a,vec3(2,3,1)) << endl;
        cout << "\tlength({1, 2, 3}) = " << vec3::length(a) << endl;
        cout << "\t{1, 2, 3} == {2, 3, 1} " << (vec3::equal(a,vec3(2.0f,3.0f,1.0f))?"true":"false") << endl;
        cout << "\t{1, 2, 3} == {1, 2, 3} " << (vec3::equal(a,vec3(1.0f,2.0f,3.0f))?"true":"false") << endl;
        cout << "\t{1, 2, 3} == {1.00000009,2.00000009,3.00000009} " << (vec3::equal(a,vec3(1.00000009,2.00000009,3.00000009))?"true":"false") << endl;
        cout << "\t{1, 2, 3} == {1.0000001, 2.0000001, 3.0000001} " << (vec3::equal(a,vec3(1.0000001f, 2.0000001f, 3.0000001f))?"true":"false") << endl << endl;;
        
        cout << "mat4:" << endl;
        cout << "\tsizeof(mat4) = " << sizeof(mat4) << endl << endl;
        
        mat4 m = mat4::translate(10, 20, 30);
        cout << m << endl;
        m = mat4::rotate(10, 20, 30);
        cout << m << endl;
        m = mat4::scale(10, 20, 30);
        cout << m << endl;
    }
    
};

#endif /* defined(__CubicVR2__MathTest__) */
