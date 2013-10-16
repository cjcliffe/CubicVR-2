//
//  CoreShader.cpp
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-04-07.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#include "cubicvr2/opengl/CoreShader.h"
#include "cubicvr2/opengl/Material.h"

namespace CubicVR {

    void CoreShaderVars::setValues(Material *mat) {
        if (materialDiffuse.size) materialDiffuse.set(mat->getDiffuse());
        if (materialSpecular.size) materialSpecular.set(mat->getSpecular());
        if (materialAmbient.size) materialAmbient.set(mat->getAmbient());
        if (materialColor.size) materialColor.set(mat->getColor());
        if (materialAlpha.size) materialAlpha.set(mat->getOpacity());
        if (materialShininess.size) materialShininess.set(mat->getShininess());
        if (pointSize.size) pointSize.set(mat->getPointSize());
        if (materialTexOffset.size) materialTexOffset.set(mat->getUVOffset());
//        if (textureColor.size) textureColor.set(mat->getTextureColor());
//        if (textureNormal.size) textureNormal.set(mat->getTextureNormal());
//        if (textureBump.size) textureBump.set(mat->getTextureBump());
//        if (textureAmbient.size) textureAmbient.set(mat->getTextureAmbient());
//        if (textureSpecular.size) textureSpecular.set(mat->getTextureSpecular());
//        if (textureReflect.size) textureReflect.set(mat->getTextureReflect());
//        if (textureAlpha.size) textureAlpha.set(mat->getTextureAlpha());
//        if (textureEnvSphere.size) textureEnvSphere.set(mat->getTextureEnvSphere());
//        if (textureEnvSphere.size) textureEnvSphere.set(mat->getTextureEnvSphere());
        if (lightAmbient.size) lightAmbient.set(mat->getLightAmbient());
        if (vertexPosition.size) vertexPosition.set(mat->getVertexPosition());
        if (vertexNormal.size) vertexNormal.set(mat->getVertexNormal());
        if (vertexColor.size) vertexColor.set(mat->getVertexColor());
        if (vertexTexCoord.size) vertexTexCoord.set(mat->getVertexTexCoord());
        if (matrixModelView.size) matrixModelView.set(mat->getMatrixModelView());
        if (matrixProjection.size) matrixProjection.set(mat->getMatrixProjection());
        if (matrixObject.size) matrixObject.set(mat->getMatrixObject());
        if (matrixNormal.size) matrixNormal.set(mat->getMatrixNormal());
//        if (lightSpecular.size) lightSpecular.set(mat->getLightSpecular());
//        if (lightDiffuse.size) lightDiffuse.set(mat->getLightDiffuse());
//        if (lightPosition.size) lightPosition.set(mat->getLightPosition());
//        if (lightIntensity.size) lightIntensity.set(mat->getLightIntensity());
//        if (lightDistance.size) lightDistance.set(mat->getLightDistance());
    }

    
    void CoreShader::loadString(string vertex, string fragment) {
        vertexSource = vertex;
        fragmentSource = fragment;
    }
    
    void CoreShader::loadTextFile(string vertexFn, string fragmentFn) {
        vertexSource = util::loadTextFile(vertexFn);
        fragmentSource = util::loadTextFile(fragmentFn);
    }

}