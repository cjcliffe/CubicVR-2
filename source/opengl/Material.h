//
//  Material.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-03-02.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__Material__
#define __CubicVR2__Material__

#include <iostream>
#include "Shader.h"
#include "CoreShader.h"

namespace CubicVR {
    
    class Material {
    public:
        static CoreShader coreShader;
        
        __float maxSmooth, friction;
        bool colorMap, pointSprite, pointCircle, visible , collision, noFog, morph;
        
        float materialAlpha, materialShininess;
        float envAmount, pointSize;
        
        vec2 materialTexOffset;
        vec3 materialDiffuse, materialSpecular, materialAmbient, materialColor, lightAmbient;
        mat4 matrixModelView, matrixProjection, matrixObject;
        mat3 matrixNormal;
        
        GLint vertexPosition, vertexNormal, vertexColor;
        GLint vertexTexCoord;
        ShaderInstance *shaderInst;
        unsigned int mask;

    public:
        string name;
        
        floatSG(Material, Opacity, materialAlpha);
        floatSG(Material, Shininess, materialShininess);
        
        floatSG(Material, EnvAmount, envAmount);
        floatSG(Material, PointSize, pointSize);
        
        vec2SG(Material, UVOffset, materialTexOffset);
        vec3SG(Material, Diffuse, materialDiffuse);
        vec3SG(Material, Specular, materialSpecular);
        vec3SG(Material, Ambient, materialAmbient);
        vec3SG(Material, Color, materialColor);
        
        vec3SG(Material, LightAmbient, lightAmbient);
        
//        sampler2DSG(Material, TextureColor, textureColor);
//        sampler2DSG(Material, TextureNormal, textureNormal);
//        sampler2DSG(Material, TextureBump, textureBump);
//        sampler2DSG(Material, TextureAmbient, textureAmbient);
//        sampler2DSG(Material, TextureSpecular, textureSpecular);
//        sampler2DSG(Material, TextureReflect, textureReflect);
//        sampler2DSG(Material, TextureAlpha, textureAlpha);
//        sampler2DSG(Material, TextureEnvSphere, textureEnvSphere);
        

        uintSG(Material, VertexPosition, vertexPosition);
        uintSG(Material, VertexNormal, vertexNormal);
        uintSG(Material, VertexColor, vertexColor);
        uintSG(Material, VertexTexCoord, vertexTexCoord);
        
        mat4SG(Material, MatrixModelView, matrixModelView);
        mat4SG(Material, MatrixProjection, matrixProjection);
        mat4SG(Material, MatrixObject, matrixObject);
        mat3SG(Material, MatrixNormal, matrixNormal);

//        uniformVec3VectorSG(Material, LightSpecular, lightSpecular);
//        uniformVec3VectorSG(Material, LightDiffuse, lightDiffuse);
//        uniformVec3VectorSG(Material, LightPosition, lightPosition);
//        uniformFloatVectorSG(Material, LightIntensity, lightIntensity);
//        uniformFloatVectorSG(Material, LightDistance, lightDistance);
        
        floatSG(Material, MaxSmooth, maxSmooth);
        floatSG(Material, Friction, friction);

        isBoolSG(Material, Collision, collision);
        isBoolSG(Material, ColorMap, colorMap);
        isBoolSG(Material, Morph, morph);
        isBoolSG(Material, PointSprite, pointSprite);
        isBoolSG(Material, PointCircle, pointCircle);
        isBoolSG(Material, Visible, visible);
        
        Material() :
        shaderInst(NULL),
        
        maxSmooth(60.0f), friction(0.3f), colorMap(false), pointSprite(false), pointCircle(false), visible(true), collision(true),
        noFog(false), morph(false), vertexPosition(-1), vertexNormal(-1), vertexColor(-1), vertexTexCoord(-1),
        materialAlpha(1.0f), materialShininess(1.0f), envAmount(1.0f), pointSize(0), materialTexOffset(0,0),
        materialColor(0.5f,0.5f,0.5f), materialDiffuse(1, 1, 1), materialSpecular(0.1f, 0.1f, 0.1f), materialAmbient( 0, 0, 0 )
        {
            mask = 0;
        }
        
        unsigned int computeMask() {
            
//            if (textureColor.get()!=-1) mask += SHADER_TEXTURE_COLOR;
//            if (textureSpecular.get()!=-1) mask += SHADER_TEXTURE_SPECULAR;
//            if (textureNormal.get()!=-1) mask += SHADER_TEXTURE_NORMAL;
//            if (textureBump.get()!=-1) mask += SHADER_TEXTURE_BUMP;
//            if (textureReflect.get()!=-1) mask += SHADER_TEXTURE_REFLECT;
//            if (textureEnvSphere.get()!=-1) mask += SHADER_TEXTURE_ENVSPHERE;
//            if (textureAmbient.get()!=-1) mask += SHADER_TEXTURE_AMBIENT;
//            if (textureAlpha.get()!=-1) mask += SHADER_TEXTURE_ALPHA;
//            if (materialAlpha.get()<1) mask += SHADER_MATERIAL_ALPHA;
            //            if () mask += MATERIAL_VERTEX_MORPH;
            //            if () mask += MATERIAL_VERTEX_COLOR;
            //            if () mask += MATERIAL_POINT_SPRITE;
            //            if () mask += MATERIAL_POINT_SIZE;
            //            if () mask += MATERIAL_POINT_CIRCLE;
            
            return mask;
        }
        
        void use(light_enum lightType, unsigned short lightCount) {
            if (mask == 0) {
                mask = computeMask();
                shaderInst = coreShader.getShaderInstance(lightType, lightCount, mask);
            }
            shaderInst->shader->use();
            shaderInst->values->setValues(this);
            shaderInst->values->update(shaderInst->shader);
        }
        

    };

}

#endif /* defined(__CubicVR2__Material__) */
