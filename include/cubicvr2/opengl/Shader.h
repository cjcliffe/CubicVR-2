//
//  Shader.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-02-23.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__Shader__
#define __CubicVR2__Shader__

#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>

#include "cubicvr2/opengl/opengl_support.h"
#include "cubicvr2/math/types.h"
#include "cubicvr2/math/vec2.h"
#include "cubicvr2/math/vec3.h"
#include "cubicvr2/math/vec4.h"
#include "cubicvr2/math/mat3.h"
#include "cubicvr2/math/mat4.h"
//#include "GLUT/glut.h"

namespace CubicVR {

    #define uniformFloatSG(c,x,y) \
        __float COMBINE(get,x)() { return y.get(); } \
        c & COMBINE(set,x)(__float value) { y.set(value); return *this; }
    #define uniformVec2SG(c,x,y) \
        vec2 COMBINE(get,x)() { return y.get(); } \
        c & COMBINE(set,x)(vec2 value) { y.set(value); return *this; }
    #define uniformVec3SG(c,x,y) \
        vec3 COMBINE(get,x)() { return y.get(); } \
        c & COMBINE(set,x)(vec3 value) { y.set(value); return *this; }
    #define uniformSampler2DSG(c,x,y) \
        GLuint COMBINE(get,x)() { return y.get(); } \
        c & COMBINE(set,x)(GLuint value) { y.set(value); return *this; }
    #define attributeVec3SG(c,x,y) \
        GLuint COMBINE(get,x)() { return y.get(); } \
        c & COMBINE(set,x)(GLuint value) { y.set(value); return *this; }
    #define attributeVec2SG(c,x,y) \
        GLuint COMBINE(get,x)() { return y.get(); } \
        c & COMBINE(set,x)(GLuint value) { y.set(value); return *this; }
    #define uniformMat4SG(c,x,y) \
        mat4 COMBINE(get,x)() { return y.get(); } \
        c & COMBINE(set,x)(mat4 value) { y.set(value); return *this; }
    #define uniformMat3SG(c,x,y) \
        mat3 COMBINE(get,x)() { return y.get(); } \
        c & COMBINE(set,x)(mat3 value) { y.set(value); return *this; }
    #define uniformVec3VectorSG(c,x,y) \
        vec3 COMBINE(get,x)(unsigned int idx) { return y.get(idx).get(); } \
        c & COMBINE(set,x)(unsigned int idx, vec3 value) { y.get(idx).value = value; return *this; }
    #define uniformFloatVectorSG(c,x,y) \
        float COMBINE(get,x)(unsigned int idx) { return y.get(idx).get(); } \
        c & COMBINE(set,x)(unsigned int idx, float value) { y.get(idx).value = value; return *this; }
      
    
    using namespace std;
    
    struct shaderVariable {
        GLuint index;
        GLint size;
        GLenum type;
        GLchar *name;
        void update() {
            
        };
        shaderVariable() : index(0), size(0), type(0), name(NULL) {
        }
        static void copy(const shaderVariable &src, shaderVariable &dst) {
            dst.index = src.index;
            dst.size = src.size;
            dst.type = src.type;
            dst.name = src.name;
        }
    };


    
    struct shaderVariables {
        shaderVariable emptyVar;
        vector <shaderVariable> uniforms;
        vector <shaderVariable> attributes;
        void clear() {
            uniforms.clear();
            attributes.clear();
        }
        void addUniform(shaderVariable &var) {
            uniforms.push_back(var);
        }
        void addAttribute(shaderVariable &var) {
            attributes.push_back(var);
        }
        shaderVariable &getUniform(string name) {
            vector<shaderVariable>::iterator i;
            
            for (i = uniforms.begin(); i != uniforms.end(); i++) {
                if (name == (*i).name) {
                    return *i;
                }
            }
            return emptyVar;
        }
        shaderVariable &getAttribute(string name) {
            vector<shaderVariable>::iterator i;
            
            for (i = attributes.begin(); i != attributes.end(); i++) {
                if (name == (*i).name) {
                    return *i;
                }
            }
            return emptyVar;
        }
        
        static const char *getTypeName(GLenum type) {
            switch (type) {
                case GL_FLOAT: return "GL_FLOAT";
                case GL_FLOAT_VEC2: return "GL_FLOAT_VEC2";
                case GL_FLOAT_VEC3: return "GL_FLOAT_VEC3";
                case GL_FLOAT_VEC4: return "GL_FLOAT_VEC4";
                case GL_FLOAT_MAT2: return "GL_FLOAT_MAT2";
                case GL_FLOAT_MAT3: return "GL_FLOAT_MAT3";
                case GL_FLOAT_MAT4: return "GL_FLOAT_MAT4";
                case GL_FLOAT_MAT2x3: return "GL_FLOAT_MAT2x3";
                case GL_FLOAT_MAT2x4: return "GL_FLOAT_MAT2x4";
                case GL_FLOAT_MAT3x2: return "GL_FLOAT_MAT3x2";
                case GL_FLOAT_MAT3x4: return "GL_FLOAT_MAT3x4";
                case GL_FLOAT_MAT4x2: return "GL_FLOAT_MAT4x2";
                case GL_FLOAT_MAT4x3: return "GL_FLOAT_MAT4x3";
                case GL_INT: return "GL_INT";
                case GL_INT_VEC2: return "GL_INT_VEC2";
                case GL_INT_VEC3: return "GL_INT_VEC3";
                case GL_INT_VEC4: return "GL_INT_VEC4";
                case GL_UNSIGNED_INT_VEC2: return "GL_UNSIGNED_INT_VEC2";
                case GL_UNSIGNED_INT_VEC3: return "GL_UNSIGNED_INT_VEC3";
                case GL_UNSIGNED_INT_VEC4: return "GL_UNSIGNED_INT_VEC4";
                case GL_SAMPLER_2D: return "GL_SAMPLER_2D";
                case GL_SAMPLER_3D: return "GL_SAMPLER_3D";
            }
            return "UNKNOWN?";
        }

        static void dumpVarList(vector<shaderVariable> varList) {
            shaderVariable *tempVar;
            vector<shaderVariable>::iterator i;
            
            for (i = varList.begin(); i != varList.end(); i++) {
                tempVar = &(*i);
                cout << "  " << tempVar->name << ": ";
                cout << getTypeName(tempVar->type);
                if (tempVar->size!=1) {
                    cout << "(" << tempVar->size << ")";
                }
                cout << endl;
            }
        }
        void dump() {
            cout << endl << "Shader variable log:" << endl << "--------------------" << endl;            
            cout << "Attributes:" << endl;
            dumpVarList(attributes);
            cout << "Uniforms:" << endl;
            dumpVarList(uniforms);
        }

    };
    
    
    class Shader {
    public:
        string fragmentSource, vertexSource;
        GLuint program, vertexShader, fragmentShader;
        GLchar *vertexLog;
        GLchar *fragmentLog;
        GLchar *linkLog;
        GLuint vao;
        bool compiled;
    public:
        isBoolSG(Shader, Compiled, compiled);

        Shader();
        Shader(string vertex, string fragment);
        
        void loadString(string vertex, string fragment);
        void loadTextFile(string vertexFn, string fragmentFn);

//        shaderVariable *mkShaderUniform(GLenum type);
//        shaderVariable *mkShaderAttribute(GLenum type);
        void use();
  
        GLuint compileProgram(GLenum type, string str);
        void getVariables(shaderVariables &shaderVars);

        bool compile();
        void dumpShaderLog();
    };
    
    

#define shaderAssign(x) x& operator=(const shaderVariable &var) { \
shaderVariable::copy(var,*this); \
return *this; \
} \

    
    // Uniforms
    // --------
    
    //  GL_FLOAT
    struct shaderUniformFloat : shaderVariable {
        GLfloat value;
        void set(GLfloat val) {
            value = val;
        }
        GLfloat get() {
            return value;
        }
        void update() {
            if (!size) return;
            glUniform1f(index, value);
        }
        shaderUniformFloat() {
            set(0);
        }
        shaderUniformFloat(__float x) {
            set(x);
        }
        shaderAssign(shaderUniformFloat)
    };
    
    
    // GL_FLOAT_VEC2
    struct shaderUniformVec2 : shaderVariable {
        vec2 value;
        void set(vec2 val) {
            value = val;
        }
        vec2 get() {
            return value;
        }
        void update() {
            if (!size) return;
            glUniform2f(index, value[0], value[1]);
        }
        shaderUniformVec2() {
            set(vec2(0,0));
        }
        shaderUniformVec2(__float x, __float y) {
            set(vec2(x,y));
        }
        shaderAssign(shaderUniformVec2)
    };
    
    // GL_FLOAT_VEC3
    struct shaderUniformVec3 : shaderVariable {
        vec3 value;
        void set(vec3 val) {
            value = val;
        }
        vec3 get() {
            return value;
        }
        void update() {
            if (!size) return;
            glUniform3f(index, value[0], value[1], value[2]);
        }
        shaderUniformVec3() {
            set(vec3(0,0,0));
        }
        shaderUniformVec3(__float x, __float y, __float z) {
            set(vec3(x,y,z));
        }
        shaderAssign(shaderUniformVec3)
    };
    
    
    
    // GL_FLOAT_VEC4
    struct shaderUniformVec4 : shaderVariable {
        vec4 value;
        void set(vec4 val) {
            value = val;
        }
        vec4 get() {
            return value;
        }
        void update() {
            if (!size) return;
            glUniform4f(index, value[0], value[1], value[2], value[3]);
        }
        shaderUniformVec4() {
            set(vec4(0,0,0,0));
        }
        shaderUniformVec4(__float x, __float y, __float z, __float w) {
            set(vec4(x,y,z,w));
        }
        shaderAssign(shaderUniformVec4)
    };
    
    // GL_FLOAT_MAT3
    struct shaderUniformMat3 : shaderVariable {
        mat3 value;
        void set(mat3 val) {
            value = val;
        }
        mat3 get() {
            return value;
        }
        void update() {
            if (!size) return;
            glUniformMatrix3fv(index, 1, false, (GLfloat *)&value);
            checkError(405);
       }
        shaderUniformMat3() {
        }
        shaderUniformMat3(mat3 val) {
            set(val);
        }
        shaderAssign(shaderUniformMat3)
    };
    
    // GL_FLOAT_MAT4
    struct shaderUniformMat4 : shaderVariable {
        mat4 value;
        void set(mat4 val) {
            value = val;
        }
        mat4 get() {
            return value;
        }
        void update() {
            glUniformMatrix4fv(index, 1, false, (GLfloat *)&value);
            checkError(404);
        }
        shaderUniformMat4() {
        }
        shaderUniformMat4(mat4 val) {
            set(val);
        }
        shaderAssign(shaderUniformMat4)
    };
    
    // GL_INT
    struct shaderUniformInt : shaderVariable {
        GLint value;
        void set(GLint val) {
            value = val;
        }
        GLint get() {
            return value;
        }
        void update() {
            if (!size) return;
            glUniform1i(index, value);
        }
        shaderUniformInt() {
            set(0);
        }
        shaderUniformInt(GLint x) {
            set(x);
        }
        shaderAssign(shaderUniformInt)
    };
    
    // GL_SAMPLER_2D
    struct shaderUniformSampler2D : shaderVariable {
        GLint value;
        void set(GLint val) {
            value = val;
        }
        GLint get() {
            return value;
        }
        void update() {
            if (!size) return;
            glUniform1i(index, value);
        }
        shaderAssign(shaderUniformSampler2D)
    };
    // GL_SAMPLER_3D
    
    
    
    // Attributes
    // ----------
    
    //  GL_FLOAT
    struct shaderAttributeFloat : shaderVariable {
        GLfloat *value;
        void set(GLfloat *val) {
            value = val;
        }
        GLfloat *get() {
            return value;
        }
        void update() {
            if (!size) return;
            glVertexAttrib1fv(index, value);
        }
        shaderAssign(shaderAttributeFloat)
    };
    
    // GL_FLOAT_VEC2
    struct shaderAttributeVec2 : shaderVariable {
        GLuint value;
        shaderAttributeVec2() {
            value = -1;
        }
        void set(GLuint val) {
            value = val;
        }
        GLuint get() {
            return value;
        }
        void update() {
            if (!size || value == -1) return;
            glBindBuffer(GL_ARRAY_BUFFER, value);
            glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, (void *)NULL);
            glEnableVertexAttribArray(index);
            checkError(1002);
        }
        shaderAssign(shaderAttributeVec2)
    };
    
    // GL_FLOAT_VEC3
    struct shaderAttributeVec3 : shaderVariable {
        GLuint value;
        shaderAttributeVec3() {
            value = -1;
        }
        void set(GLuint val) {
            value = val;
        }
        GLuint get() {
            return value;
        }
        void update() {
            if (!size || value == -1) return;

            glBindBuffer(GL_ARRAY_BUFFER, value);
            glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void *)NULL);
            glEnableVertexAttribArray(index);
            checkError(1003);
        }
        shaderAssign(shaderAttributeVec3)
    };
    
    
    
    // GL_FLOAT_VEC4
    struct shaderAttributeVec4 : shaderVariable {
        GLfloat *value;
        void set(GLfloat *val) {
            value = val;
        }
        GLfloat *get() {
            return value;
        }
        void update() {
            if (!size) return;
            glVertexAttrib4fv(index,value);
        }
        shaderAssign(shaderAttributeVec4)
    };
 
    
    // Vector Uniforms
    // ---------------
    
    // GL_FLOAT_VEC3
    struct shaderUniformFloatVector : shaderVariable {
        GLfloat *values;
        GLfloat *get() {
            return values;
        }
        void set(GLfloat *values_in) {
            values = values_in;
        }
        void update() {
            if (!size) return;

            glUniform1fv(index, size, values);
            
            checkError(1010);
        }
        
        shaderAssign(shaderUniformFloatVector)
    };
    
    
    // GL_FLOAT_VEC3
    struct shaderUniformVec3Vector : shaderVariable {
        vector<shaderUniformVec3> values;
        shaderUniformVec3 &get(unsigned int idx) {
            if (values.size() < size) {
                values.resize(size);
            }
            return values[(unsigned long)idx];
        }
        void update() {
            if (!size) return;
            for (unsigned int i = 0; i < size; i++) {
                this->get(i).update();
            }
        }
        void init(Shader &shader) {
            //TODO: this
        }
        shaderAssign(shaderUniformVec3Vector)
    };
    

}


#endif /* defined(__CubicVR2__Shader__) */
