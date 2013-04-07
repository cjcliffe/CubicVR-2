//
//  Renderer.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-03-31.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__Renderer__
#define __CubicVR2__Renderer__

#include <iostream>
#include "opengl_support.h"
#include "mat4.h"
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include <vector>

#define MAX_LIGHTS 8

using namespace std;

namespace CubicVR {
    
    static class Renderer {
        bool renderMesh(Mesh *obj_in, Camera *camera, mat4 *o_matrix, vector<Light *> *lighting, bool skip_trans, bool skip_solid, bool force_wire, bool force_point) {
            bool has_transparency = false;
            skip_trans = skip_trans || false;
            skip_solid = skip_solid || false;
            mat4 identitymat = mat4::identity();
            
            if (obj_in->compiledBuffer == NULL) {
                return false;
            }
            
            unsigned int ofs = 0;
            unsigned int nLights, numLights = (lighting==NULL) ? 0 : lighting->size();
            Shader *mshader;
            unsigned int last_ltype;
            Light *l = NULL;
            unsigned int lcount = 0;
            unsigned int j;
            Material *mat = NULL;
            
            vector<Material*> *materials;
            if (obj_in->getInstanceMaterials()->size()) {
                materials = obj_in->getInstanceMaterials();
            } else {
                materials = obj_in->getMaterials();
            }
            
            //        var lines = (obj_in.wireframe || force_wire) && obj_in.compiled.line_elements_ref;
            //        var points = (obj_in.pointMode || force_point) && obj_in.compiled.line_elements_ref;
            
            GLuint primitive_type = GL_TRIANGLES;
            
            //        if (lines) {
            //            primitive_type = gl.LINES;
            //        } else if (points) {
            //            primitive_type = gl.POINTS;
            //        }
            
            //        var elements_ref = (lines || points) ? obj_in.compiled.line_elements_ref : obj_in.compiled.elements_ref;
            //        compiledVBOElementsRef *elements_ref = (lines || points) ? obj_in.compiled.line_elements_ref : obj_in.compiled.elements_ref;
            compiledVBOElementsRef *elements_ref = &obj_in->compiledBuffer->elements_ref;
            
            bool bound = false;
            unsigned int subcount;
            bool blended;
            unsigned int lt;
            glDepthFunc(GL_LEQUAL);
            
            if (o_matrix == NULL) {
                o_matrix = &identitymat;
            }
            
            for (unsigned int ic = 0, icLen = elements_ref->size(); ic < icLen; ic++) {
                //            if (lines && obj_in.wireframeMaterial) {
                //                mat = obj_in.wireframeMaterial;
                //            } else if (points && obj_in.pointModeMaterial) {
                //                mat = obj_in.pointModeMaterial;
                //            } else {
                mat = (*materials)[ic];
                //            }
                
                unsigned int len = 0;
                bool drawn = false;
                
                float opacity = mat->getOpacity();
                
                if (opacity < 1.0 && skip_trans) {
                    has_transparency = true;
                    continue;
                } else if (skip_solid && opacity >= 1.0) {
                    continue;
                }
                
                if (opacity < 1.0) {
                    glEnable(GL_BLEND);
                    glDepthMask(GL_FALSE);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                } else {
                    glDepthMask(GL_TRUE);
                    glDisable(GL_BLEND);
                    glBlendFunc(GL_ONE, GL_ONE);
                }
                
                for (unsigned int jc = 0, jcLen = (*elements_ref)[ic].size(); jc < jcLen; jc++) {
                    j = (*elements_ref)[ic][jc].segmentId;
                    
                    drawn = false;
                    
                    unsigned int this_len = (*elements_ref)[ic][jc].size;
                    len += this_len;
                    
                    if (!mat->visible) {
                        ofs += this_len * 2;
                        len -= this_len;
                        continue;
                    }
                    
                    if (obj_in->segment_state.isSet(j)) {
                        // ...
                    } else if (len > this_len) {
                        ofs += this_len * 2;
                        len -= this_len;
                        
                        // start lighting loop
                        // start inner
                        if (!numLights) {
                            mat->use(0, 0);
                            glBindVertexArray(obj_in->compiledBuffer->vao);

                            mat->setMatrixModelView(camera->getMatrixModelView());
                            mat->setMatrixProjection(camera->getMatrixProjection());
                            mat->setMatrixObject(*o_matrix);
                            mat->setMatrixNormal(camera->getMatrixNormal());
                            
                            if (!bound) {
                                mat->bindObject(obj_in, mat.shader[0][0]);
                                bound = (mat.shader[0][0].vertexTexCoord != -1);
//                                if (lines || points) mat.bindLines(obj_in, mat.shader[0][0]);
                            }
                            
                            //                        if (obj_in.compiled.unrolled) {
                            //                            gl.drawArrays(primitive_type, ofs, len);
                            //                        } else {
                            glDrawElements(primitive_type, len, GL_UNSIGNED_SHORT, (void*)ofs);
                            //                        }
                            
                        } else {
                            subcount = 0;
                            blended = false;
                            
                            for (subcount = 0; subcount < numLights;) {
                                nLights = numLights - subcount;
                                if (nLights > MAX_LIGHTS) {
                                    nLights = MAX_LIGHTS;
                                }
                                
                                if (subcount > 0 && !blended) {
                                    glEnable(GL_BLEND);
                                    glBlendFunc(GL_ONE, GL_ONE);
                                    glDepthFunc(GL_EQUAL);
                                    blended = true;
                                }
                                
                                mshader = NULL;
                                l = (*lighting)[subcount];
                                lt = l->getLightType();
                                
                                for (lcount = 0; lcount < nLights; lcount++) {
                                    if ((*lighting)[lcount + subcount]->getLightType() != lt) {
                                        nLights = lcount;
                                        break;
                                    }
                                }
                                
                                mat.use(l->getLightType(), nLights);
                                glBindVertexArray(obj_in->compiledBuffer->vao);
                                
                                mshader = mat.shader[l->getLightType()][nLights];
                                //                            if (subcount > 0 && mshader.lightAmbient) {
                                //                                gl.uniform3fv(mshader.lightAmbient, [0,0,0]);
                                //                            }
                                
                                mat->setMatrixModelView(camera->getMatrixModelView());
                                mat->setMatrixProjection(camera->getMatrixProjection());
                                mat->setMatrixObject(*o_matrix);
                                mat->setMatrixNormal(camera->getMatrixNormal());
                                
//                            gl.uniformMatrix4fv(mshader.matrixModelView, false, camera.mvMatrix);
//                            gl.uniformMatrix4fv(mshader.matrixProjection, false, camera.pMatrix);
//                            gl.uniformMatrix4fv(mshader.matrixObject, false, o_matrix);
//                            gl.uniformMatrix3fv(mshader.matrixNormal, false, camera.nMatrix);
                                
                                if (!bound) {
                                    
                                    if (obj_in->compiledBuffer->gl_colors)  mat->setVertexColor(obj_in->compiledBuffer->gl_colors);
                                    if (obj_in->compiledBuffer->gl_normals)  mat->setVertexNormal(obj_in->compiledBuffer->gl_normals);
                                    if (obj_in->compiledBuffer->gl_points)  mat->setVertexPosition(obj_in->compiledBuffer->gl_points);
                                    if (obj_in->compiledBuffer->gl_uvs)  mat->setVertexTexCoord(obj_in->compiledBuffer->gl_uvs);
                                    
                                    bound = (mshader.vertexTexCoord != -1);
                                    //                                if (lines || points) mat.bindLines(obj_in, mshader);
                                }
                                
                                for (lcount = 0; lcount < nLights; lcount++) {
                                    (*lighting)[lcount + subcount]->setupShader(mshader, lcount);
                                }
                                
                                //                            if (obj_in.compiled.unrolled) {
                                //                                gl.drawArrays(primitive_type, ofs, len);
                                //                            } else {
                                gl.drawElements(primitive_type, len, gl.UNSIGNED_SHORT, ofs);
                                //                            }
                                // var err = gl.getError();
                                // if (err) {
                                //   var uv = mshader.uniforms["vertexTexCoord"];
                                //   var un = mshader.uniforms["vertexNormal"];
                                //   console.log(obj_in.compiled.gl_uvs!==null,obj_in.compiled.gl_normals!==null, un, uv, len, ofs, subcount);
                                //
                                //   throw new Error('webgl error on mesh: ' + obj_in.name);
                                // }
                                
                                subcount += nLights;
                            }
                            
                            if (blended) {
                                glDisable(GL_BLEND);
                                glDepthFunc(GL_LEQUAL);
                            }
                        }
                        
                        /// end inner
                        
                        
                        ofs += len * 2; // Note: unsigned short = 2 bytes
                        len = 0;
                        drawn = true;
                    } else {
                        ofs += len * 2;
                        len = 0;
                    }
                }
                
                if (!drawn && obj_in->segment_state.isSet(j) && mat->isVisible()) {
                    // this is an exact copy/paste of above
                    // start lighting loop
                    // start inner
                    if (!numLights) {
                        mat.use(0, 0);
                        
                        gl.uniformMatrix4fv(mat.shader[0][0].matrixModelView, false, camera.mvMatrix);
                        gl.uniformMatrix4fv(mat.shader[0][0].matrixProjection, false, camera.pMatrix);
                        gl.uniformMatrix4fv(mat.shader[0][0].matrixObject, false, o_matrix);
                        gl.uniformMatrix3fv(mat.shader[0][0].matrixNormal, false, camera.nMatrix);
                        
                        if (!bound) {
                            mat.bindObject(obj_in, mat.shader[0][0]);
                            bound = (mat.shader[0][0].vertexTexCoord != -1);
                            if (lines || points) mat.bindLines(obj_in, mat.shader[0][0]);
                        }
                        
                        if (obj_in.compiled.unrolled) {
                            gl.drawArrays(primitive_type, ofs, len);
                        } else {
                            gl.drawElements(primitive_type, len, gl.UNSIGNED_SHORT, ofs);
                        }
                        
                    } else {
                        subcount = 0;
                        blended = false;
                        
                        for (subcount = 0; subcount < numLights;) {
                            nLights = numLights - subcount;
                            if (nLights > base.MAX_LIGHTS) {
                                nLights = base.MAX_LIGHTS;
                            }
                            
                            if (subcount > 0 && !blended) {
                                gl.enable(gl.BLEND);
                                gl.blendFunc(gl.ONE, gl.ONE);
                                gl.depthFunc(gl.EQUAL);
                                blended = true;
                            }
                            
                            mshader = undef;
                            l = lighting[subcount];
                            lt = l.light_type;
                            
                            for (lcount = 0; lcount < nLights; lcount++) {
                                if (lighting[lcount + subcount].light_type != lt) {
                                    nLights = lcount;
                                    break;
                                }
                            }
                            
                            mat.use(l.light_type, nLights);
                            
                            mshader = mat.shader[l.light_type][nLights];
                            
                            mshader = mat.shader[l.light_type][nLights];
                            if (subcount > 0 && mshader.lightAmbient) {
                                gl.uniform3fv(mshader.lightAmbient, [0,0,0]);
                            }
                            
                            gl.uniformMatrix4fv(mshader.matrixModelView, false, camera.mvMatrix);
                            gl.uniformMatrix4fv(mshader.matrixProjection, false, camera.pMatrix);
                            gl.uniformMatrix4fv(mshader.matrixObject, false, o_matrix);
                            gl.uniformMatrix3fv(mshader.matrixNormal, false, camera.nMatrix);
                            
                            if (!bound) {
                                mat.bindObject(obj_in, mshader);
                                bound = (mshader.vertexTexCoord != -1);
                                if (lines || points) mat.bindLines(obj_in, mshader);
                            }
                            
                            for (lcount = 0; lcount < nLights; lcount++) {
                                lighting[lcount + subcount].setupShader(mshader, lcount);
                            }
                            
                            if (obj_in.compiled.unrolled) {
                                gl.drawArrays(primitive_type, ofs, len);
                            } else {
                                gl.drawElements(primitive_type, len, gl.UNSIGNED_SHORT, ofs);
                            }
                            // var err = gl.getError();
                            // if (err) {
                            //   var uv = mshader.uniforms["vertexTexCoord"];
                            //   var un = mshader.uniforms["vertexNormal"];
                            //   console.log(obj_in.compiled.gl_uvs!==null,obj_in.compiled.gl_normals!==null, un, uv, len, ofs, subcount);
                            //
                            //   throw new Error('webgl error on mesh: ' + obj_in.name);
                            // }
                            
                            subcount += nLights;
                        }
                        
                        if (blended) {
                            gl.disable(gl.BLEND);
                            gl.depthFunc(gl.LEQUAL);
                        }
                    }
                    
                    /// end inner
                    
                    ofs += len * 2;
                }
            }
            
            //        if (mat && mshader) {
            //            mat.clearObject(obj_in, mshader);
            //        } else {
            //            mat.clearObject(obj_in, null);
            //        }
            
            glDepthMask(1);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
            
            return has_transparency;
        }
    };
}

#endif /* defined(__CubicVR2__Renderer__) */
