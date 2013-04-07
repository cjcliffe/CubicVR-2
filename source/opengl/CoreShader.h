//
//  CoreShader.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-04-07.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__CoreShader__
#define __CubicVR2__CoreShader__

#include <iostream>
#include <map>
#include <vector>
#include "Shader.h"
#include "Light.h"
#include "utility.h"

#define MAX_LIGHTS 8
#define SHADER_TEXTURE_COLOR        1
#define SHADER_TEXTURE_SPECULAR     2
#define SHADER_TEXTURE_NORMAL       4
#define SHADER_TEXTURE_BUMP         8
#define SHADER_TEXTURE_REFLECT      16
#define SHADER_TEXTURE_ENVSPHERE    32
#define SHADER_TEXTURE_AMBIENT      64
#define SHADER_TEXTURE_ALPHA        128
#define SHADER_MATERIAL_ALPHA       256
#define SHADER_VERTEX_MORPH         512
#define SHADER_VERTEX_COLOR         1024
#define SHADER_POINT_SPRITE         2048
#define SHADER_POINT_SIZE           4096
#define SHADER_POINT_CIRCLE         8192


namespace CubicVR {
    
    class Material;
    
    struct shaderDef {
        unsigned int mask;
        string name;
        shaderDef(string name_, unsigned int mask_) {
            name = name_;
            mask = mask_;
        }
    };

    struct CoreShaderVars {
        shaderUniformFloat envAmount, pointSize;
        shaderUniformFloat materialShininess, materialAlpha;
        
        shaderUniformSampler2D textureColor, textureNormal, textureBump, textureAmbient, textureSpecular, textureReflect, textureAlpha, textureEnvSphere;
        
        shaderAttributeVec3 vertexPosition, vertexNormal, vertexColor;
        shaderAttributeVec2 vertexTexCoord;
        
        shaderUniformVec2 materialTexOffset;
        shaderUniformVec3 materialColor, materialDiffuse, materialSpecular, materialAmbient;
        
        shaderUniformMat4 matrixModelView, matrixProjection, matrixObject;
        shaderUniformMat3 matrixNormal;
        
        shaderUniformVec3Vector lightSpecular, lightDiffuse, lightPosition;
        shaderUniformFloatVector lightIntensity, lightDistance;
        shaderUniformVec3 lightAmbient;
        
        shaderVariables vars;

        CoreShaderVars() : materialAlpha(1.0f), materialShininess(1.0f), envAmount(1.0f), pointSize(0), materialTexOffset(0,0),
        materialColor(0.5f,0.5f,0.5f), materialDiffuse(1, 1, 1), materialSpecular(0.1f, 0.1f, 0.1f), materialAmbient( 0, 0, 0 ) {
            
            
        }
        
        void initShader(Shader *shader) {
            shader->getVariables(vars);
            
            materialDiffuse = vars.getUniform("materialDiffuse");
            materialSpecular = vars.getUniform("materialSpecular");
            materialAmbient = vars.getUniform("materialAmbient");
            materialColor = vars.getUniform("materialColor");
            materialAlpha = vars.getUniform("materialAlpha");
            materialShininess = vars.getUniform("materialShininess");
            pointSize = vars.getUniform("pointSize");
            materialTexOffset = vars.getUniform("materialTexOffset");
            
            textureColor = vars.getUniform("textureColor");
            textureNormal = vars.getUniform("textureNormal");
            textureBump = vars.getUniform("textureBump");
            textureAmbient = vars.getUniform("textureAmbient");
            textureSpecular = vars.getUniform("textureSpecular");
            textureReflect = vars.getUniform("textureReflect");
            textureAlpha = vars.getUniform("textureAlpha");
            textureEnvSphere = vars.getUniform("textureEnvSphere");
            
            lightAmbient = vars.getUniform("lightAmbient");
            textureEnvSphere = vars.getUniform("textureEnvSphere");
            
            vertexPosition = vars.getAttribute("vertexPosition");
            vertexNormal = vars.getAttribute("vertexNormal");
            vertexColor = vars.getAttribute("vertexColor");
            vertexTexCoord = vars.getAttribute("vertexTexCoord");
            
            matrixModelView = vars.getUniform("matrixModelView");
            matrixProjection = vars.getUniform("matrixProjection");
            matrixObject = vars.getUniform("matrixObject");
            matrixNormal = vars.getUniform("matrixNormal");
            
            lightSpecular = vars.getUniform("lightSpecular");
            lightDiffuse = vars.getUniform("lightDiffuse");
            lightPosition = vars.getUniform("lightPosition");
            lightIntensity = vars.getUniform("lightIntensity");
            lightDistance = vars.getUniform("lightDistance");
            
            lightSpecular.init(*shader);
            lightDiffuse.init(*shader);
            lightPosition.init(*shader);
            lightIntensity.init(*shader);
            lightDistance.init(*shader);
        }
        
        void setValues(Material *mat);
        
        void update(Shader *shader) {
            if (materialDiffuse.size) materialDiffuse.update();
            if (materialSpecular.size) materialSpecular.update();
            if (materialAmbient.size) materialAmbient.update();
            if (materialColor.size) materialColor.update();
            if (materialAlpha.size) materialAlpha.update();
            if (materialShininess.size) materialShininess.update();
            if (pointSize.size) pointSize.update();
            if (materialTexOffset.size) materialTexOffset.update();
            if (textureColor.size) textureColor.update();
            if (textureNormal.size) textureNormal.update();
            if (textureBump.size) textureBump.update();
            if (textureAmbient.size) textureAmbient.update();
            if (textureSpecular.size) textureSpecular.update();
            if (textureReflect.size) textureReflect.update();
            if (textureAlpha.size) textureAlpha.update();
            if (textureEnvSphere.size) textureEnvSphere.update();
            if (lightAmbient.size) lightAmbient.update();
            if (textureEnvSphere.size) textureEnvSphere.update();
            if (vertexPosition.size) vertexPosition.update();
            if (vertexNormal.size) vertexNormal.update();
            if (vertexColor.size) vertexColor.update();
            if (vertexTexCoord.size) vertexTexCoord.update();
            if (matrixModelView.size) matrixModelView.update();
            if (matrixProjection.size) matrixProjection.update();
            if (matrixObject.size) matrixObject.update();
            if (matrixNormal.size) matrixNormal.update();
            if (lightSpecular.size) lightSpecular.update();
            if (lightDiffuse.size) lightDiffuse.update();
            if (lightPosition.size) lightPosition.update();
            if (lightIntensity.size) lightIntensity.update();
            if (lightDistance.size) lightDistance.update();
        }
    };
    
    struct ShaderInstance {
        Shader *shader;
        CoreShaderVars *values;
    };
    
    
    class CoreShader {
        vector<shaderDef> defs;
        vector<vector<map<unsigned int, ShaderInstance> > > instances;
        string fragmentSource, vertexSource;
    public:
        CoreShader() {
            addDefinition("TEXTURE_COLOR", SHADER_TEXTURE_COLOR);
            addDefinition("TEXTURE_SPECULAR", SHADER_TEXTURE_SPECULAR);
            addDefinition("TEXTURE_NORMAL", SHADER_TEXTURE_NORMAL);
            addDefinition("TEXTURE_BUMP", SHADER_TEXTURE_BUMP);
            addDefinition("TEXTURE_REFLECT", SHADER_TEXTURE_REFLECT);
            addDefinition("TEXTURE_ENVSPHERE", SHADER_TEXTURE_ENVSPHERE);
            addDefinition("TEXTURE_AMBIENT", SHADER_TEXTURE_AMBIENT);
            addDefinition("TEXTURE_ALPHA", SHADER_TEXTURE_ALPHA);
            addDefinition("MATERIAL_ALPHA", SHADER_MATERIAL_ALPHA);
            addDefinition("VERTEX_MORPH", SHADER_VERTEX_MORPH);
            addDefinition("VERTEX_COLOR", SHADER_VERTEX_COLOR);
            addDefinition("POINT_SPRITE", SHADER_POINT_SPRITE);
            addDefinition("POINT_SIZE", SHADER_POINT_SIZE);
            addDefinition("POINT_CIRCLE", SHADER_POINT_CIRCLE);
        }
        
        void loadString(string vertex, string fragment);
        void loadTextFile(string vertexFn, string fragmentFn);

        void addDefinition(string defname, unsigned int mask) {
            defs.push_back(shaderDef(defname,mask));
        }
        
        ShaderInstance *getShaderInstance(light_enum lightType, unsigned short lightCount, unsigned int mask) {
            checkError(101);
            map<unsigned int,ShaderInstance> *lInstance;
            map<unsigned int,ShaderInstance>::iterator instances_i;
            
            if (instances.size() == 0) {
                instances.resize(LIGHT_TYPE_MAX);
            }
            
            if (instances[lightType].size() == 0) {
                instances[lightType].resize(MAX_LIGHTS);
            }
            
            lInstance = &instances[lightType][lightCount];
            
            
            instances_i = (*lInstance).find(mask);
            
            if (instances_i == (*lInstance).end()) {
                // build new instance
                stringstream headerStr;
                
                headerStr << "#version 150" << endl;
                
                vector<shaderDef>::iterator defs_i;
                for (defs_i = defs.begin(); defs_i != defs.end(); defs_i++) {
                    if ((*defs_i).mask && mask) {
                        headerStr << "#define " << (*defs_i).name << " 1" << endl;
                    } else {
                        headerStr << "#define " << (*defs_i).name << " 0" << endl;
                    }
                }
                
                headerStr << "#define LIGHT_COUNT " << lightCount << endl << endl;
                headerStr << "#define LIGHT_IS_POINT " << ((lightType == LIGHT_POINT)?"1":"0") << endl;
                headerStr << "#define LIGHT_IS_DIRECTIONAL " << ((lightType == LIGHT_DIRECTIONAL)?"1":"0") << endl;
                headerStr << "#define LIGHT_IS_SPOT " << ((lightType == LIGHT_SPOT)?"1":"0") << endl;
                headerStr << "#define LIGHT_IS_AREA " << ((lightType == LIGHT_AREA)?"1":"0") << endl;
                
                // todo: test states
                bool depthpass = false, shadowed = false, shadowed_soft = false, projector = false;
                
                headerStr << "#define LIGHT_IS_PROJECTOR " << (projector?"1":"0") << endl;
                headerStr << "#define LIGHT_DEPTH_PASS " << (depthpass?"1":"0") << endl;
                headerStr << "#define LIGHT_SHADOWED " << (shadowed?"1":"0") << endl;
                headerStr << "#define LIGHT_SHADOWED_SOFT " << (shadowed_soft?"1":"0") << endl;
                
                // todo: implement profiles
                bool depthAlpha = false, fog = false, fogExp = false, fogLinear = false, perPixel = true;
                
                headerStr << "#define FX_DEPTH_ALPHA " << (depthAlpha?"1":"0") << endl;
                headerStr << "#define FOG_ENABLED " << (fog?"1":"0") << endl;
                headerStr << "#define USE_FOG_EXP " << (fogExp?"1":"0") << endl;
                headerStr << "#define USE_FOG_LINEAR " << (fogLinear?"1":"0") << endl;
                headerStr << "#define LIGHT_PERPIXEL " << (perPixel?"1":"0") << endl;
                
                stringstream fragStr;
                stringstream vertStr;
                
                fragStr << headerStr.str() << fragmentSource;
                vertStr << headerStr.str() << vertexSource;
                
                cout<<fragStr.str()<<endl;
                
                Shader *program = new Shader();
                program->loadString(vertStr.str(),fragStr.str());
                program->compile();
                
                CoreShaderVars *shaderVars = new CoreShaderVars();
                shaderVars->initShader(program);
                
                if (program->isCompiled()) {
                    (*lInstance)[mask].shader = program;
                    (*lInstance)[mask].values = shaderVars;
                } else {
                    program->dumpShaderLog();
                }
            }
            
            return &(*lInstance)[mask];
        }
    };
    
}

/*
vector<shaderDef> defs;
vector<vector<map<unsigned int,GLuint> > > instances;
*/


#endif /* defined(__CubicVR2__CoreShader__) */
