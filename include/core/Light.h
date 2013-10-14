//
//  Light.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-03-31.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__Light__
#define __CubicVR2__Light__

#include <iostream>
#include "math/types.h"
#include "math/vec3.h"
#include "math/mat4.h"
#include "math/mat3.h"
#include "core/Camera.h"

#define LIGHT_TYPE_MAX 8

namespace CubicVR {

    enum light_enum { LIGHT_NONE, LIGHT_POINT, LIGHT_DIRECTIONAL, LIGHT_SPOT, LIGHT_AREA, LIGHT_DEPTH_PACK, LIGHT_SPOT_SHADOW,             LIGHT_SPOT_SHADOW_PROJECTOR };
    enum light_mode_enum { LIGHT_GLOBAL, LIGHT_STATIC, LIGHT_DYNAMIC };

    class Light {
        
        light_enum light_type;
        unsigned int map_res;
        bool staticLight;
        bool dirty, targeted;
        vec3 diffuse, specular, position, rotation, direction, areaAxis, target, lrotation, lposition, ldirection, lDir, lPos;
        __float intensity, distance, cutoff, ldistance;
        
    public:
        
        lightEnumSG(Light,LightType,light_type);
        vec3SG(Light,Diffuse,diffuse);
        vec3SG(Light,Specular,specular);
        vec3SG(Light,Position,position);
        vec3SG(Light,Rotation,rotation);
        vec3SG(Light,Direction,direction);
        vec3SG(Light,AreaAxis,areaAxis);
        vec3SG(Light,Target,target);
        
        isBoolSG(Light,Static,staticLight);
        isBoolSG(Light,Targeted,targeted);
        
        floatSG(Light,Intensity,intensity);
        floatSG(Light,Distance,distance);
        floatSG(Light,CutOff,cutoff);
        
        
        Light(light_enum ltype) : diffuse(vec3(1,1,1)), specular(vec3(0.3f, 0.3f, 0.3f)), position(vec3(0,0,0)), rotation(vec3(0,0,0)),
        direction(vec3(0,0,0)), areaAxis(vec3(1,1,0)), target(vec3(0,0,0)), intensity(1), distance(30), cutoff(60),
        lposition(vec3(0,0,0)), ldirection(vec3(0,0,0)), lrotation(vec3(0,0,0)) {
            
            setLightType(ltype);
            if (ltype == LIGHT_AREA) {
                map_res = 2048;
            } else {
                map_res = 512;
            }
            
            //            this.areaCam = (light_type.areaCam !== undef) ? light_type.areaCam : null;
            //            this.areaCeiling = (light_type.areaCeiling !== undef) ? light_type.areaCeiling : 40;
            //            this.areaFloor = (light_type.areaFloor !== undef) ? light_type.areaFloor : -40;
            //            this.areaAxis = (light_type.areaAxis !== undef) ? light_type.areaAxis : [1, 1, 0];
            //            this.projectorTex = (light_type.projector !== undef) ? light_type.projector : null;
            
            //        if (this.projectorTex && typeof(this.projectorTex) === "string") {
            //            var tex = this.projectorTex;
            //            this.projectorTex = (base.Textures_ref[tex] !== undef) ? base.Textures_obj[base.Textures_ref[tex]] : (new base.Texture(tex));
            //        }
            
            dirty = true;
            //        this.motion = null;
            //        this.renderTag = -1;
            
            if ((light_type == LIGHT_SPOT_SHADOW || light_type == LIGHT_SPOT_SHADOW_PROJECTOR) || light_type == LIGHT_AREA) { //  && base.features.lightShadows
                //            setShadow(map_res);
            }
            
            //        parent = NULL;
        }
        
        //    setType: function (light_type) {
        //        if (light_type === enums.light.type.AREA && !base.features.lightShadows) {
        //            this.dummyCam = new base.Camera();
        //            this.areaCam = new base.Camera();
        //
        //            this.updateAreaLight();
        //
        //            this.dummyCam = null;
        //            this.areaCam = null;
        //            light_type = enums.light.type.DIRECTIONAL;
        //        } else if ((light_type === enums.light.type.SPOT_SHADOW || light_type === enums.light.type.SPOT_SHADOW_PROJECTOR) && !base.features.lightShadows) {
        //            light_type = enums.light.type.SPOT;
        //        }
        //        this.light_type = light_type;
        //    },
        
        void doTransform() {
            if ((distance != ldistance) || !vec3::equal(position,lposition) || !vec3::equal(rotation,lrotation)) {
                lposition = position;
                lrotation = rotation;
                ldistance = distance;
                dirty = true;
            }
        }
        
        //    setParent: function(lParent) {
        //        this.parent = lParent;
        //    },
        
        void prepare(Camera &camera) {
            
            if (targeted) {
                lookat(target);
            }
            
            //        if (parent) {
            //            if (ltype === enums.light.type.SPOT || ltype === enums.light.type.SPOT_SHADOW || ltype === enums.light.type.SPOT_SHADOW_PROJECTOR) {
            //                var dMat = mat4.inverse_mat3(this.parent.tMatrix);
            //                mat3.transpose_inline(dMat);
            //                this.lDir = mat3.vec3_multiply(this.direction, dMat);
            //                this.lDir = mat3.vec3_multiply(this.lDir, camera.nMatrix);
            //                this.lPos = mat4.vec3_multiply(this.position, mat4.multiply(camera.mvMatrix,this.parent.tMatrix));
            //            } else if (ltype === enums.light.type.POINT) {
            //                this.lPos = mat4.vec3_multiply(this.position, mat4.multiply(camera.mvMatrix,this.parent.tMatrix));
            //            }
            //        } else {
            if (light_type == LIGHT_DIRECTIONAL) {
                lDir = mat3::multiply(camera.getMatrixNormal(), direction);
            } else if (light_type == LIGHT_SPOT || light_type == LIGHT_SPOT_SHADOW || light_type == LIGHT_SPOT_SHADOW_PROJECTOR) {
                lDir = mat3::multiply(camera.getMatrixNormal(), direction);
                lPos = mat4::multiply(camera.getMatrixModelView(), position);
            } else if (light_type == LIGHT_POINT) {
                lPos = mat4::multiply(camera.getMatrixModelView(), position);
            } else if (light_type == LIGHT_AREA) {
                lDir = mat3::multiply(camera.getMatrixNormal(), direction);
            }
            //        }
        }
        
        //    control: function (controllerId, motionId, value) {
        //        if (controllerId === enums.motion.POS) {
        //            this.position[motionId] = value;
        //        } else if (controllerId === enums.motion.INTENSITY) {
        //            this.intensity = value;
        //        }
        //
        //        // else if (controllerId === enums.motion.ROT) {
        //        //    this.rotation[motionId] = value;
        //        //  }
        //    },
        
        //    getAABB: function () {
        //        if (this.dirty) {
        //
        //            var vec3 = base.vec3;
        //            var aabbMath = base.aabb;
        //            var aabb;
        //
        //            if (this.light_type == enums.light.type.POINT) {
        //                aabb = [
        //                        [0, 0, 0],
        //                        [0, 0, 0]
        //                        ];
        //
        //                aabbMath.engulf(aabb, [this.distance, this.distance, this.distance]);
        //                aabbMath.engulf(aabb, [-this.distance, -this.distance, -this.distance]);
        //                aabb[0] = vec3.add(aabb[0], this.position);
        //                aabb[1] = vec3.add(aabb[1], this.position);
        //            } else if (this.light_type == enums.light.type.SPOT || enums.light.type.SPOT_SHADOW || SPOT_SHADOW_PROJECTOR) {
        //
        //                var cpos = this.position.slice(0);
        //                aabb = [cpos,cpos];
        //
        //                var tempCam = new base.Camera({
        //                position: this.position.slice(0),
        //                width: 10,
        //                height: 10,
        //                nearClip: 0.01,
        //                farClip: this.distance,
        //                fov: this.cutoff,
        //                target: base.vec3.add(this.position,base.vec3.multiply(this.direction,10)),
        //                targeted: true,
        //                });
        //
        //                tempCam.calcProjection();
        //
        //                aabb.engulf( aabb, tempCam.unProject(0,0,this.distance) );
        //                aabb.engulf( aabb, tempCam.unProject(0,10,this.distance) );
        //                aabb.engulf( aabb, tempCam.unProject(10,10,this.distance) );
        //                aabb.engulf( aabb, tempCam.unProject(10,0,this.distance) );
        //
        //            }
        //
        //            this.dirty = false;
        //            this.aabb = aabb||this.aabb;
        //        }
        //
        //        return this.aabb;
        //    },
        
        //    setDirection: function (x, y, z) {
        //        var vec3 = base.vec3;
        //        if (typeof (x) === 'object') {
        //            this.setDirection(x[0], x[1], x[2]);
        //            return;
        //        }
        //
        //
        //        this.direction = vec3.normalize([x, y, z]);
        //        this.target = null;
        //
        //        return this;
        //    },
        
        void lookat(vec3 looktarget) {
            direction = vec3::normalize(vec3::subtract(looktarget, position));
            target = looktarget;
        }
        
        //    void setRotation(vec3 rot) {
        //
        //        var t = new base.Transform();
        //        t.rotate([-x, -y, -z]);
        //        t.pushMatrix();
        //
        //        this.direction = vec3.normalize(mat4.vec3_multiply([1, 0, 0], t.getResult()));
        //        this.rotation = [x, y, z];
        //
        //        return this;
        //    };
        
        //    setupShader: function (lShader, lNum) {
        //        var gl = GLCore.gl;
        //
        //        var lUniforms = lShader;
        //
        //        gl.uniform3fv(lUniforms.lightDiffuse[lNum], this.diffuse);
        //        gl.uniform3fv(lUniforms.lightSpecular[lNum], this.specular);
        //        if (this.lPos) gl.uniform3fv(lUniforms.lightPosition[lNum], this.lPos);
        //        if (this.lDir) gl.uniform3fv(lUniforms.lightDirection[lNum], this.lDir);
        //
        //        gl.uniform1f(lUniforms.lightIntensity[lNum], this.intensity);
        //        gl.uniform1f(lUniforms.lightDistance[lNum], this.distance);
        //
        //        if ((this.light_type === enums.light.type.SPOT_SHADOW) || (this.light_type === enums.light.type.SPOT_SHADOW_PROJECTOR) || (this.light_type === enums.light.type.SPOT)) {
        //            gl.uniform1f(lUniforms.lightCutOffAngle[lNum], this.cutoff);
        //        }
        //        if ((this.light_type === enums.light.type.SPOT_SHADOW) || (this.light_type === enums.light.type.SPOT_SHADOW_PROJECTOR) || (this.light_type === enums.light.type.AREA)) {
        //            if (this.light_type === enums.light.type.SPOT_SHADOW_PROJECTOR) {
        //                this.shadowMapTex.texture.use(GLCore.gl.TEXTURE0 + lNum*2); // reserved in material for shadow map
        //                gl.uniform1i(lShader.lightShadowMap[lNum], lNum*2);
        //                this.projectorTex.use(GLCore.gl.TEXTURE0 + lNum*2+1); // reserved in material for projector map
        //                gl.uniform1i(lShader.lightProjectionMap[lNum], lNum*2+1);
        //            } else {
        //                this.shadowMapTex.texture.use(GLCore.gl.TEXTURE0 + lNum); // reserved in material for shadow map
        //                gl.uniform1i(lShader.lightShadowMap[lNum], lNum);
        //            }
        //
        //            gl.uniform3fv(lShader.lightDepthClip[lNum], [this.dummyCam.nearclip, this.dummyCam.farclip, 1.0 / this.map_res]);
        //            gl.uniformMatrix4fv(lShader.lightShadowMatrix[lNum], false, this.spMatrix);
        //        }
        //    },
        
        //    setShadow: function (map_res_in) // cone_tex
        //        {
        //            if (!base.features.lightShadows) return;
        //
        //            this.map_res = map_res_in;
        //            this.shadowMapTex = new base.RenderBuffer(this.map_res, this.map_res, true);
        //            this.shadowMapTex.texture.setFilter(enums.texture.filter.NEAREST);
        //
        //            this.dummyCam = new base.Camera(this.map_res, this.map_res, 80, 0.1, this.distance);
        //            this.dummyCam.calc_nmatrix = false; // don't need a normal matrix, save some cycles and determinant issues
        //            this.dummyCam.setTargeted(true);
        //            // if(!(strncmp(cone_tex.c_str(),"null",4) == 0 || strncmp(cone_tex.c_str(),"Null",4) == 0 || strncmp(cone_tex.c_str(),"NULL",4) == 0))
        //            // {
        //            //  coneTex = Texture::create(cone_tex);
        //            //  has_projector = true;
        //            // }
        //            this.has_shadow = true;
        //        },
        
        bool hasShadow() {
            //        return has_shadow;
            return false;
        }
        
        //    setProjector: function(projectorTex_in) {
        //        this.projectorTex = projectorTex_in;
        //    },
        //
        //    hasProjector: function() {
        //        return ((this.projectorTex!==null)?true:false);
        //    },
        
        //    shadowBegin: function () {
        //        var gl = GLCore.gl;
        //        var mat4 = base.mat4;
        //        var mat3 = base.mat3;
        //
        //        this.shadowMapTex.use();
        //
        //        gl.viewport(0, 0, this.map_res, this.map_res);
        //
        //        gl.clear(gl.DEPTH_BUFFER_BIT | gl.COLOR_BUFFER_BIT);
        //
        //        if (this.light_type !== enums.light.type.AREA) {
        //            this.dummyCam.setClip(0.1, this.distance);
        //            this.dummyCam.setFOV(this.cutoff);
        //        } else {
        //            this.dummyCam.calcProjection();
        //        }
        //
        //        if (this.parent) {
        //            var dMat = mat4.inverse_mat3(this.parent.tMatrix);
        //            mat3.transpose_inline(dMat);
        //            var lDir = mat3.vec3_multiply(this.direction, dMat);
        //            var lPos = mat4.vec3_multiply(this.position, this.parent.tMatrix);
        //            this.dummyCam.lookat(this.position[0], this.position[1], this.position[2], this.position[0] + this.direction[0] * 10.0, this.position[1] + this.direction[1] * 10.0, this.position[2] + this.direction[2] * 10.0, 0, 1, 0);
        //            mat4.multiply(this.dummyCam.mvMatrix.slice(0),mat4.inverse(this.parent.tMatrix),this.dummyCam.mvMatrix);
        //
        //            //               this.dummyCam.lookat(lPos[0], lPos[1], lPos[2], lPos[0] + lDir[0] * 10.0, lPos[1] + lDir[1] * 10.0, lPos[2] + lDir[2] * 10.0, 0, 1, 0);
        //        } else {
        //            this.dummyCam.lookat(this.position[0], this.position[1], this.position[2], this.position[0] + this.direction[0] * 10.0, this.position[1] + this.direction[1] * 10.0, this.position[2] + this.direction[2] * 10.0, 0, 1, 0);
        //        }
        //
        //        gl.cullFace(gl.FRONT);
        //    },
        
        //    shadowEnd: function () {
        //        var gl = GLCore.gl;
        //
        //        gl.bindFramebuffer(gl.FRAMEBUFFER, null);
        //
        //        gl.cullFace(gl.BACK);
        //
        //        this.setupTexGen();
        //    },
        
        //    setupTexGen: function () {
        //        var mat4 = base.mat4;
        //        var biasMatrix = [0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0];
        //
        //        this.spMatrix = mat4.multiply(cubicvr_identity, biasMatrix);
        //        this.spMatrix = mat4.multiply(this.spMatrix, this.dummyCam.pMatrix);
        //        this.spMatrix = mat4.multiply(this.spMatrix, this.dummyCam.mvMatrix);
        //    },
        
        //    setAreaAxis: function (degs_in) {
        //        this.areaAxis = degs_in;
        //    },
        
        //    updateAreaLight: function () {
        //        var vec3 = base.vec3;
        //        var areaHeight = this.areaCeiling - this.areaFloor;
        //
        //        this.dummyCam.ortho = true;
        //        this.dummyCam.setClip(0.01, 1); // set defaults
        //        var dist = 0.0;
        //        var sx = Math.tan((this.areaCam.fov / 2.0) * (Math.PI / 180.0));
        //        // var far_clip_range = far_range;
        //        var vview = vec3.subtract(this.areaCam.target, this.areaCam.position);
        //        vview[1] = 0;
        //        vview = vec3.normalize(vview);
        //
        //        var vleft = vec3.normalize(vec3.cross(vview, [0, 1, 0]));
        //
        //        var fwd_ang = -Math.atan2(vview[2], vview[0]);
        //
        //        dist = ((this.distance / 2.0) * Math.abs(sx)) - (this.distance / 2.0);
        //
        //        if (dist < (this.distance / 3.0) / 2.0) dist = (this.distance / 3.0) / 2.0;
        //
        //        vview = vec3.multiply(vview, dist);
        //
        //        var zang = this.areaAxis[0] * (Math.PI / 180);
        //        var xang = this.areaAxis[1] * (Math.PI / 180);
        //
        //        var tzang = Math.tan(zang);
        //        var txang = Math.tan(xang);
        //
        //        var l_vec = [txang, 0.0, tzang];
        //
        //        fwd_ang -= Math.atan2(l_vec[0], l_vec[2]);
        //
        //        this.position = vec3.add(vec3.add(this.areaCam.position, vview), vec3.multiply(l_vec, areaHeight));
        //        this.position[1] = this.areaCeiling;
        //        this.target = vec3.add(vec3.add(this.areaCam.position, vview), vec3.multiply(l_vec, -areaHeight));
        //        this.target[1] = this.areaFloor;
        //        this.direction = vec3.normalize(vec3.subtract(this.target, this.position));
        //        this.dummyCam.rotation[2] = fwd_ang * (180.0 / Math.PI);
        //
        //        var nearclip = this.dummyCam.nearclip;
        //        var farclip = this.dummyCam.farclip * (Math.abs(this.direction[1]) * areaHeight);
        //
        //        // adjust clipping ranges to fit ortho bounds
        //        var aabb = this.orthoBounds(this.position, this.distance, this.distance, this.dummyCam.pMatrix, this.dummyCam.mvMatrix, this.dummyCam.nearclip);
        //        var diff;
        //
        //        if (aabb[0][1] < this.areaCeiling) {
        //            diff = (this.areaCeiling - aabb[0][1]);
        //            nearclip -= diff / Math.abs(this.direction[1]);
        //        }
        //        
        //        aabb = this.orthoBounds(this.position, this.distance, this.distance, this.dummyCam.pMatrix, this.dummyCam.mvMatrix, this.dummyCam.farclip);
        //        
        //        if (aabb[1][1] > this.areaFloor) {
        //            diff = (aabb[1][1] - this.areaFloor);
        //            farclip += diff / Math.abs(this.direction[1]);
        //        }
        //        
        //        //if (nearclip < 0.01)
        //        nearclip = 0.01;
        //        this.dummyCam.nearclip = nearclip;
        //        this.dummyCam.farclip = farclip;
        //        
        //        this.dummyCam.setOrtho(-this.distance / 2.0, this.distance / 2.0, -this.distance / 2.0, this.distance / 2.0);
        //    },
        //        
        //    orthoBounds: function (position, ortho_width, ortho_height, projMatrix, modelMatrix, clipDist) {
        //        var vec3 = base.vec3;
        //        var right = vec3.normalize([modelMatrix[0], modelMatrix[4], modelMatrix[8]]);
        //        var up = vec3.normalize([modelMatrix[1], modelMatrix[5], modelMatrix[9]]);
        //        var forward = vec3.normalize(vec3.cross(up, right));
        //        
        //        var hw, hh;
        //        
        //        hw = ortho_width / 2.0;
        //        hh = ortho_height / 2.0;
        //        
        //        var f_bounds = [];
        //        
        //        var rightHW = vec3.multiply(right, hw);
        //        var upHH = vec3.multiply(up, hh);
        //        var forwardClip = vec3.multiply(forward, clipDist);
        //        
        //        
        //        f_bounds[0] = vec3.add(vec3.subtract(position, rightHW), vec3.add(upHH, forwardClip));
        //        f_bounds[1] = vec3.add(vec3.add(position, rightHW), vec3.add(upHH, forwardClip));
        //        f_bounds[2] = vec3.subtract(vec3.subtract(position, rightHW), vec3.add(upHH, forwardClip));
        //        f_bounds[3] = vec3.subtract(vec3.add(position, rightHW), vec3.add(upHH, forwardClip));
        //        
        //        aabb1 = f_bounds[0];
        //        aabb2 = f_bounds[0];
        //        
        //        for (var i = 1; i < 4; i++) {
        //            if (aabb1[0] > f_bounds[i][0]) aabb1[0] = f_bounds[i][0];
        //            if (aabb1[1] > f_bounds[i][1]) aabb1[1] = f_bounds[i][1];
        //            if (aabb1[2] > f_bounds[i][2]) aabb1[2] = f_bounds[i][2];
        //            
        //            if (aabb2[0] < f_bounds[i][0]) aabb2[0] = f_bounds[i][0];
        //            if (aabb2[1] < f_bounds[i][1]) aabb2[1] = f_bounds[i][1];
        //            if (aabb2[2] < f_bounds[i][2]) aabb2[2] = f_bounds[i][2];
        //        }
        //        
        //        return [aabb1, aabb2];
        //    }
    };
}

#endif /* defined(__CubicVR2__Light__) */
