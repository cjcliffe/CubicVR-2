//
//  Shader.cpp
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-02-23.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#include "opengl/Shader.h"
#include "utility.h"


namespace CubicVR {
    
    Shader::Shader() {
        vertexLog = NULL;
        fragmentLog = NULL;
        linkLog = NULL;
        compiled = false;
    }
    
    Shader::Shader(string vertex, string fragment)  {
        Shader();
        loadString(vertex,fragment);
    }
    
    void Shader::loadString(string vertex, string fragment) {
        vertexSource = vertex;
        fragmentSource = fragment;
    }
    
    void Shader::loadTextFile(string vertexFn, string fragmentFn) {
        vertexSource = util::loadTextFile(vertexFn);
        fragmentSource = util::loadTextFile(fragmentFn);
    }
    
//    shaderVariable *Shader::mkShaderAttribute(GLenum type) {
//        switch (type) {
//            case GL_FLOAT: return new shaderAttributeFloat;
//            case GL_FLOAT_VEC2: return new shaderAttributeVec2;
//            case GL_FLOAT_VEC3: return new shaderAttributeVec3;
//            case GL_FLOAT_VEC4: return new shaderAttributeVec4;
//        }
//        return NULL;
//    }
//    
//    shaderVariable *Shader::mkShaderUniform(GLenum type) {
//        switch (type) {
//            case GL_FLOAT: return new shaderUniformFloat;
//            case GL_FLOAT_VEC2: return new shaderUniformVec2;
//            case GL_FLOAT_VEC3: return new shaderUniformVec3;
//            case GL_FLOAT_VEC4: return new shaderUniformVec4;
//            case GL_FLOAT_MAT3: return new shaderUniformMat3;
//            case GL_FLOAT_MAT4: return new shaderUniformMat4;
//            case GL_INT: return new shaderUniformInt;
//            case GL_SAMPLER_2D: return new shaderUniformSampler2D;
////                case GL_SAMPLER_3D: return "GL_SAMPLER_3D";
//        }
//        return NULL;
//    }
    
    
    // GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
    GLuint Shader::compileProgram(GLenum type, string str) {
        GLuint shader;
        
        const GLchar *shaderString[1];
        shaderString[0] = str.c_str();
        
        GLint shaderLen[1];
        shaderLen[0] = (GLint)str.length();
        
        glPointSize(1.0f);
        
        shader = glCreateShader(type);
        
        glShaderSource(shader, 1, shaderString, shaderLen);
        glCompileShader(shader);
        
        return shader;
    }
    
    void Shader::getVariables(shaderVariables &shaderVars) {
        // collect variables..
        GLuint index = 0;
        
        GLchar attribute_name[GL_ACTIVE_ATTRIBUTE_MAX_LENGTH+1];
        GLchar uniform_name[GL_ACTIVE_UNIFORM_MAX_LENGTH+1];
        GLsizei length;
        GLint numVars;
        
        
        glGetProgramiv(program,GL_ACTIVE_ATTRIBUTES,&numVars);
        
        GLint size;
        GLenum type;
        shaderVariable *newVar;
        
        for (index = 0; index < numVars; index++) {
            glGetActiveAttrib(program, index, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH+1, &length, &size, &type, attribute_name);
            newVar = new shaderVariable;
            
            newVar->size = size;
            newVar->type = type;
            newVar->name = (GLchar *)malloc(length+1);
            memcpy(newVar->name, attribute_name, length);
            newVar->name[length] = NULL;
            newVar->index = glGetAttribLocation(program,newVar->name);
            
            shaderVars.addAttribute(*newVar);
        }
        
        glGetProgramiv(program,GL_ACTIVE_UNIFORMS,&numVars);
        
        for (index = 0; index < numVars; index++) {
            
            glGetActiveUniform(program, index, GL_ACTIVE_UNIFORM_MAX_LENGTH+1, &length, &size, &type, uniform_name);
            newVar = new shaderVariable;
            
            newVar->size = size;
            newVar->type = type;
            newVar->name = (GLchar *)malloc(length+1);
            memcpy(newVar->name, uniform_name, length);
            newVar->name[length] = NULL;
            newVar->index = glGetUniformLocation(program,newVar->name);
            
            shaderVars.addUniform(*newVar);
        }
        
        glGenVertexArrays(1, &vao);
    }
    
    bool Shader::compile() {
        int max_log = 2048;
        
        compiled = true;
        
        if (vertexLog != NULL) {
            free(vertexLog);
            vertexLog = NULL;
        }
        if (fragmentLog != NULL) {
            free(fragmentLog);
            fragmentLog = NULL;
        }
        if (linkLog != NULL) {
            free(linkLog);
            linkLog = NULL;
        }
        
        vertexShader = compileProgram(GL_VERTEX_SHADER, vertexSource);
        
        GLsizei logLen;
        GLint vertResult;
        GLint fragResult;
        GLchar tmpChar;
        
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertResult);
        
        if (vertResult == GL_FALSE) {
            glGetShaderInfoLog(vertexShader, 1, &logLen, &tmpChar);
            max_log = logLen;
            vertexLog = (GLchar *)malloc(max_log);
            glGetShaderInfoLog(vertexShader, max_log, &logLen, vertexLog);
            compiled = false;
        }
        
        fragmentShader = compileProgram(GL_FRAGMENT_SHADER, fragmentSource);
        
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragResult);
        
        if (fragResult == GL_FALSE) {
            glGetShaderInfoLog(fragmentShader, 1, &logLen, &tmpChar);
            max_log = logLen;
            fragmentLog = (GLchar *)malloc(max_log);
            glGetShaderInfoLog(fragmentShader, max_log, &logLen, fragmentLog);
            compiled = false;
        }
        
        if (!compiled) {
            return false;
        }
        
        program = glCreateProgram();
        
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        
        GLint linkResult;
        glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
        
        if (linkResult == GL_FALSE) {
            glGetProgramInfoLog(program, 1, &logLen, &tmpChar);
            max_log = logLen;
            linkLog = (GLchar *)malloc(max_log);
            glGetProgramInfoLog(program, max_log, &logLen, linkLog);
            compiled = false;
            return false;
        }
        
        if (!glIsProgram(program)) {
            cout << "Program is not valid.\n" << endl;
        }

        
        return compiled;
    }
    
    void Shader::use() {
        glUseProgram(program);
        glBindVertexArray(vao);
    }
    
    void Shader::dumpShaderLog() {
        if (vertexLog) {
            cout << "Shader Vertex Log:" << endl;
            cout << vertexLog << endl << endl;
            cout << "---------------------------------[End Vertex Log]" << endl << endl;
        }
        if (fragmentLog) {
            cout << "Shader Fragment Log:" << endl;
            cout << "-----------------------------------" << endl << endl;
            cout << fragmentLog << endl << endl;
            cout << "-----------------------------------[End Fragment Log]" << endl << endl;
        }
        if (linkLog) {
            cout << "Shader Link Log:" << endl;
            cout << "-----------------------------------" << endl << endl;
            cout << linkLog << endl << endl;
            cout << "-----------------------------------[End Link Log]" << endl << endl;
        }
        
    }
    
}