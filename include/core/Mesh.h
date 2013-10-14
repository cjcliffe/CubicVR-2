//
//  Mesh.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-03-03.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef __CubicVR2__Mesh__
#define __CubicVR2__Mesh__

#include <iostream>
#include <vector>
#include <map>
#include "opengl/Material.h"
#include "math/vec3.h"
#include "math/vec2.h"
#include "math/aabb.h"
#include "math/triangle.h"
#include "core/BitSet.h"

using namespace std;
namespace CubicVR {
    /* Faces */
    
//    function parseTransform(t) {
//        if (t === undef) return undef;
//        if (typeof(t) === 'array') {
//            return t;
//        }
//        if (typeof(t) === 'object') {
//            if (!!t.
//                getResult) {
//                return t.getResult();
//            } else if (!!t.position || !!t.rotation || !!t.scale){
//                return base.mat4.transform(t.position,t.rotation,t.scale);
//            } else {
//                return t;
//            }
//        }
//    }
    
    struct triangleVec2Ref {
        vec2 a,b,c;
        triangleVec2Ref(vec2 a_, vec2 b_, vec2 c_) {
            a=a_; b=b_; c=c_;
        }
    };
    
    struct triangleVec3Ref {
        vec3 a,b,c;
        triangleVec3Ref(vec3 a_, vec3 b_, vec3 c_) {
            a=a_; b=b_; c=c_;
        }
    };
    
    
    struct quadVec3Ref {
        vec3 a,b,c,d;
        quadVec3Ref(vec3 a_, vec3 b_, vec3 c_, vec3 d_) {
            a=a_; b=b_; c=c_; d = d_;
        }
    };
    
    struct quadVec2Ref {
        vec2 a,b,c,d;
        quadVec2Ref(vec2 a_, vec2 b_, vec2 c_, vec2 d_) {
            a=a_; b=b_; c=c_; d=d_;
        }
    };
    
    struct triangleFaceRef {
        unsigned long a,b,c;
        triangleFaceRef(unsigned long a_, unsigned long b_, unsigned long c_) {
            a=a_; b=b_; c=c_;
        }
    };
    
    struct quadFaceRef {
        unsigned long a,b,c,d;
        quadFaceRef(unsigned long a_, unsigned long b_, unsigned long c_, unsigned long d_) {
            a=a_; b=b_; c=c_; d=d_;
        }
    };

    struct uluiPair {
        unsigned long a;
        unsigned int b;
        uluiPair(unsigned long a_, unsigned int b_) {
            a = a_; b = b_;
        }
    };
    
    struct vtxRefTuple {
        unsigned long faceNum;
        unsigned int pointNum;
        unsigned long index;
        vtxRefTuple(unsigned long faceNum_,unsigned int pointNum_, unsigned long index_) {
            faceNum = faceNum_; pointNum = pointNum_; index = index_;
        }
    };
    
    
    struct face {
        vector<unsigned long> points;
        vector<vec3> point_normals;
        vector<vec3> point_colors;
        vector<vec2> uvs;
        vec3 normal;
        unsigned long material;
        unsigned int segment;

        face() : normal(0, 0, 0), material(0), segment(0) {
        };
 
        face &setPoints(triangleFaceRef pts) {
            points.resize(3);
            points[0]=pts.a;
            points[1]=pts.b;
            points[2]=pts.c;
            return *this;
        }

        face &setPoints(quadFaceRef pts) {
            points.resize(4);
            points[0]=pts.a;
            points[1]=pts.b;
            points[2]=pts.c;
            points[3]=pts.d;
            return *this;
        }

        face &setNormals(triangleVec3Ref pts) {
            point_normals.resize(3);
            point_normals[0]=pts.a;
            point_normals[1]=pts.b;
            point_normals[2]=pts.c;
            return *this;
        }

        face &setNormals(quadVec3Ref pts) {
            point_normals.resize(4);
            point_normals[0]=pts.a;
            point_normals[1]=pts.b;
            point_normals[2]=pts.c;
            point_normals[3]=pts.d;
            return *this;
        }

        face &setUVs(triangleVec2Ref pts) {
            uvs.resize(3);
            uvs[0]=pts.a;
            uvs[1]=pts.b;
            uvs[2]=pts.c;
            return *this;
        }

        face &setUVs(quadVec2Ref pts) {
            uvs.resize(4);
            uvs[0]=pts.a;
            uvs[1]=pts.b;
            uvs[2]=pts.c;
            uvs[3]=pts.d;
            return *this;
        }

        face &setColors(triangleVec3Ref pts) {
            point_colors.resize(3);
            point_colors[0]=pts.a;
            point_colors[1]=pts.b;
            point_colors[2]=pts.c;
            return *this;
        }
        
        face &setColors(quadVec3Ref pts) {
            point_colors.resize(4);
            point_colors[0]=pts.a;
            point_colors[1]=pts.b;
            point_colors[2]=pts.c;
            point_colors[3]=pts.d;
            return *this;
        }

        void setPoint(int point_num, unsigned long ptIdx) {
            if (points.size()<=point_num) points.resize(point_num+1);
            points[point_num] = ptIdx;
        }
        
        void setPointUV(int point_num, vec2 uv) {
            if (uvs.size()<=point_num) uvs.resize(point_num+1);
            uvs[point_num] = uv;
        }
        
        void setPointNormal(int point_num, vec3 normal_) {
            if (point_normals.size()<=point_num) point_normals.resize(point_num+1);
            point_normals[point_num] = normal_;
        }
        
        void setPointColor(int point_num, vec3 color) {
            if (point_colors.size()<=point_num) point_colors.resize(point_num+1);
            point_colors[point_num] = color;
        };

        void addPoint(unsigned long ptIdx) {
            points.push_back(ptIdx);
        }
        
        void addPointUV(vec2 uv) {
            uvs.push_back(uv);
        }
            
        void addPointNormal(vec3 normal_) {
            point_normals.push_back(normal_);
        }
        
        void addPointColor(vec3 color) {
            point_colors.push_back(color);
        };

        void setNormal(vec3 normal_) {
            normal = normal_;
            if (point_normals.empty()) {
                vector<vec3>::iterator i;
                for (unsigned long i = 0, iMax=points.size(); i < iMax; i++) {
                    point_normals.push_back(normal);
                }
            }
        }
        
        void flip() {
            vector<vec3>::iterator i;
            for (i = point_normals.begin(); i != point_normals.end(); i++) {
                (*i) = vec3(0,0,0) - (*i);
            }
            
            reverse(points.begin(), points.end());
            reverse(point_normals.begin(), point_normals.end());
            reverse(uvs.begin(), uvs.end());
            reverse(point_colors.begin(), point_colors.end());
            
            normal = vec3(0,0,0) - normal;
        }
    };

 
    typedef map<unsigned long, map<unsigned long, vector<unsigned long> > > normalMapRefMap;
    
    struct normalMapRef {
        normalMapRefMap map;
        vector<unsigned short> faceCount;
        vector<unsigned long> faceNorm;
        vector<unsigned long> faceNormIdx;
    };
    
    struct facePointPair {
        unsigned long faceNum;
        unsigned int pointNum;
        facePointPair(unsigned long faceNum_,unsigned int pointNum_) {
            faceNum = faceNum_; pointNum = pointNum_;
        }
    };

    typedef map<unsigned long, map<unsigned int, vector<unsigned long> > > compileMapVBOElements;
    typedef map<unsigned long, map<unsigned int, vector<unsigned long> > >::iterator compileMapVBOElementsI;
    typedef map<unsigned int, vector<unsigned long> >::iterator compileMapVBOElementsJ;
    typedef vector<unsigned long>::iterator compileMapVBOElementsK;
    
    
    struct compileMapVBO {
        vector<unsigned long> segments;
        aabb bounds;
        compileMapVBOElements elements;
        vector<unsigned long> points;
        vector<facePointPair> normals;
        vector<facePointPair> colors;
        vector<facePointPair> uvs;
        bool dynamic;
    };
    
    struct compiledVBOElementRef {
        unsigned int segmentId;
        unsigned long size;
        compiledVBOElementRef(unsigned int segmentId_, unsigned long size_) {
            segmentId = segmentId_;
            size = size_;
        }
    };
    
    typedef vector <vector <compiledVBOElementRef> > compiledVBOElementsRef;
    typedef vector <vector <compiledVBOElementRef> >::iterator compiledVBOElementsRefI;
    typedef vector <compiledVBOElementRef>::iterator compiledVBOElementsRefJ;
    
    struct compiledVBO {
        vector <vec3> vbo_points;
        vector <vec3> vbo_normals;
        vector <vec3> vbo_colors;
        vector <vec2> vbo_uvs;
        vector <unsigned int> vbo_elements;
        vector <unsigned long> segments;
        compiledVBOElementsRef elements_ref;
        aabb bounds;
    };
    
    struct compiledVBOBuffer {
        GLuint gl_points;
        GLuint gl_normals;
        GLuint gl_uvs;
        GLuint gl_colors;
        GLuint gl_elements;
        GLuint vao;
        vector<unsigned long> segments;
        compiledVBOElementsRef elements_ref;
        aabb bounds;
        compiledVBOBuffer() : gl_points(0), gl_normals(0), gl_uvs(0), gl_colors(0), gl_elements(0) {
            
        }
    };


    class Mesh {
    protected:
//        this.compiled = null; // VBO data
        vector<Material *> materials;
        vector<Material *> instanceMaterials;

        aabb bb;
        
//        this.edges = null;
        vector<face *> faces; // faces with point references
        vector<vec3> points; // point list
        long currentFace; // start with no faces
        long currentMaterial; // null material
        int currentSegment; // default segment
        
//        this.morphTargets = null;
//        this.morphTarget = null;
//        this.morphWeight = 0.0;
//        this.morphSourceIndex = -1;
//        this.morphTargetIndex = -1;
//        this.originBuffer = null;
        
        bool genNormals;
        
        string name;
        bool dynamic;

        bool pointMode;
        bool buildWireframe;
        bool triangulateWireframe;
        Material *wireframeMaterial;
        Material *pointModeMaterial;
        bool wireframe;
        normalMapRef normalMap;
        compileMapVBO *compileMap_;
        
        vector<unsigned long> segments;
        
    public:
        compiledVBOBuffer *compiledBuffer;
        BitSet segment_state;

        Mesh() : currentFace(-1), currentMaterial(0), currentSegment(0), genNormals(true), dynamic(false), pointMode(false), buildWireframe(false),
            triangulateWireframe(false), wireframeMaterial(NULL), pointModeMaterial(NULL), wireframe(false), compileMap_(NULL) {
        }
//    showAllSegments: function () {
//        for (var i in this.segment_state) {
//            if (this.segment_state.hasOwnProperty(i)) {
//                this.segment_state[i] = true;
//            }
//        }
//    },
//        
//    hideAllSegments: function () {
//        for (var i in this.segment_state) {
//            if (this.segment_state.hasOwnProperty(i)) {
//                this.segment_state[i] = false;
//            }
//        }
//    },
//        
//    setSegment: function (i, val) {
//        if (val !== undef) {
//            this.segment_state[i] = val;
//        } else {
//            this.currentSegment = i;
//        }
//    },
        
    compiledVBOBuffer *getVBO() {
        return compiledBuffer;
    }
        
    unsigned long addPoint(vec3 p) {
        points.push_back(p);
        return points.size() - 1;
    };

    void setPoint(unsigned long idx, vec3 p) {
        if (points.size()<=idx) { points.resize(idx+1); }
        points[idx]=(p);
    };

        vector<Material *> *getMaterials() {
            return &materials;
        };

        vector<Material *> *getInstanceMaterials() {
            return &instanceMaterials;
        };
        
    long getMaterialIndex(Material *mat, bool autoAdd = false) {
        vector<Material *>::iterator i = find(materials.begin(),materials.end(),mat);
        
        long d = distance(materials.begin(), i);
        if (d == materials.size()) {
            if (autoAdd) {
                materials.push_back(mat);
            } else {
                return -1;
            }
        }
        
        return d;
    };

    void setFaceMaterial(unsigned long mat_id, long facenum=-1) {
        if (facenum != -1) {
            if (facenum<faces.size()) {
                faces[facenum]->material = mat_id;
            }
        } else {
            currentMaterial = mat_id;
        }
    };        

        face &getFace(unsigned long idx) {
            return *faces[idx];
        }
        
    long addFace(vector<unsigned long> &ref) {
        vector<unsigned long>::iterator ref_i;
        unsigned long faceNum = addFace();
        face *newFace = faces[faceNum];

        newFace->points.resize(ref.size());
        copy(ref.begin(),ref.end(),newFace->points.begin());
//        for (ref_i = ref.begin(); ref_i < ref.end(); ref_i++) {
//            newFace->addPoint(*ref_i);
//        }
        
        return faceNum;
    };

    long addFace(const triangleFaceRef &ref) {
        unsigned long faceNum = addFace();
        face *newFace = faces[faceNum];
        newFace->addPoint(ref.a);
        newFace->addPoint(ref.b);
        newFace->addPoint(ref.c);

        return faceNum;
    };

    long addFace(const quadFaceRef &ref) {
        unsigned long faceNum = addFace();

        face *newFace = faces[faceNum];

        newFace->addPoint(ref.a);
        newFace->addPoint(ref.b);
        newFace->addPoint(ref.c);
        newFace->addPoint(ref.d);

        return faceNum;
    };

    face &newFace() {
        return getFace(addFace());
    }
    face &newFace(vector<unsigned long> &ref) {
        return getFace(addFace(ref));
    };
    
    face &newFace(const triangleFaceRef &ref) {
        return getFace(addFace(ref));
    };
    
    face &newFace(const quadFaceRef &ref) {
        return getFace(addFace(ref));
    }
            
//    long addFace(unsigned long a, unsigned long b, unsigned long c) {
//        unsigned long faceNum = addFace();
//        face *newFace = faces[faceNum];
//        newFace->addPoint(a);
//        newFace->addPoint(b);
//        newFace->addPoint(c);
//        
//        return faceNum;
//    };
//
//        
//    long addFace(unsigned long a, unsigned long b, unsigned long c, unsigned long d) {
//        unsigned long faceNum = addFace();
//        face *newFace = faces[faceNum];
//        newFace->addPoint(a);
//        newFace->addPoint(b);
//        newFace->addPoint(c);
//        newFace->addPoint(d);
//        currentFace = faceNum;
//        return currentFace;
//    };
//
//    long addFace(unsigned long a, unsigned long b, unsigned long c) {
//    }
        
    long addFace() {
        long face_num = faces.size();
        faces.push_back(new face());
        currentFace = face_num;
        return currentFace;
    };

    void flipFaces() {
        vector<face *>::iterator i;
        for (i = faces.begin(); i != faces.end(); i++) {
            (*i)->flip();
        }
    };
        
    void triangulate() {
        vector<vec3> *pcolors, *pnorms;
        vector<vec2> *puvs;
        vector<unsigned long> *pts;
        face *tmpFace, *destFace;
        unsigned long i, numFaces = faces.size();
        
        for (i = 0; i < numFaces; i++) {
            tmpFace = faces[i];
            pts = &(tmpFace->points);
            
            if (pts->size() == 4) {

                destFace = faces[addFace()];
                destFace->material = tmpFace->material;
                destFace->segment = tmpFace->segment;
                destFace->addPoint((*pts)[2]);
                destFace->addPoint((*pts)[3]);
                destFace->addPoint((*pts)[0]);
                pts->pop_back();
                destFace->normal = tmpFace->normal;
                
                pcolors = &tmpFace->point_colors;
                if (pcolors->size() == 4) {
                    destFace->addPointColor((*pcolors)[2]);
                    destFace->addPointColor((*pcolors)[3]);
                    destFace->addPointColor((*pcolors)[0]);
                    pcolors->pop_back();
                }
                
                puvs = &tmpFace->uvs;
                if (puvs->size() == 4) {
                    destFace->addPointUV((*puvs)[2]);
                    destFace->addPointUV((*puvs)[3]);
                    destFace->addPointUV((*puvs)[0]);
                    puvs->pop_back();
                }
                
                pnorms = &tmpFace->point_normals;
                if (pnorms->size() == 4) {
                    destFace->addPointNormal((*pnorms)[2]);
                    destFace->addPointNormal((*pnorms)[3]);
                    destFace->addPointNormal((*pnorms)[0]);
                    pnorms->pop_back();
                }
            } else if (pts->size() > 4) {
/*                var contour = [];
                var point_list = [];
                var j,jMax;
                var ctr = [0,0,0];
                var vec3 = base.vec3;
                var initVec;
                
                for (j = 0, jMax = pts.length; j<jMax; j++) {
                    ctr = vec3.add(ctr,this.points[pts[j]]);
                    point_list[j] = this.points[pts[j]];
                }
                ctr[0]/=pts.length;
                ctr[1]/=pts.length;
                ctr[2]/=pts.length;
                
                for (j = 0, jMax = pts.length; j<jMax; j++) {
                    if (!vec3.equal(ctr,this.points[pts[j]])) {
                        initVec = vec3.normalize(vec3.subtract(this.points[pts[j]],ctr));
                        break;
                    }
                }
                
                var norm = face.normal = base.polygon.normal(point_list);
                
                var bvx = initVec;
                var bvy = vec3.normalize(vec3.cross(initVec,norm));
                
                for (j = 0, jMax = pts.length; j<jMax; j++) {
                    var v = vec3.subtract(ctr,this.points[pts[j]]);
                    contour[j] = [vec3.dot(bvx,v),vec3.dot(bvy,v)];
                }
                
                var indices = base.polygon.triangulate2D(contour);
                
                if (indices !== null) {
                    pcolors = face.point_colors;
                    puvs = face.uvs;
                    pnorms = face.point_normals;
                    
                    for (j = 0, jMax = indices.length; j<jMax; j+=3) {
                        if (j === 0) {
                            this.faces[i] = new base.Face();
                            destFace = this.faces[i];
                        } else {
                            destFace = this.faces[this.addFace()];
                        }
                        
                        destFace.material = face.material;
                        destFace.segment = face.segment;
                        destFace.points = [pts[indices[j]], pts[indices[j+1]], pts[indices[j+2]]];
                        destFace.normal = face.normal.slice(0);
                        
                        if (pcolors.length) {
                            destFace.point_colors = [pcolors[indices[j]].slice(0), pcolors[indices[j+1]].slice(0), pcolors[indices[j+2]].slice(0)];
                        }
                        
                        if (puvs.length) {
                            destFace.uvs = [puvs[indices[j]].slice(0), puvs[indices[j+1]].slice(0), puvs[indices[j+2]].slice(0)];
                        }
                        
                        if (pnorms.length) {
                            destFace.point_normals = [pnorms[indices[j]].slice(0), pnorms[indices[j+1]].slice(0), pnorms[indices[j+2]].slice(0)];
                        }
                    }
                } else {
                    base.log("Unable to triangulate face "+i+", possible degenerate poly.");
                }*/
            } 
        }
    };

    void booleanAdd(Mesh &objAdd, mat4 *transform = NULL) {
        unsigned long pofs = points.size();
        
        if (objAdd.wireframeMaterial) {
            wireframeMaterial = objAdd.wireframeMaterial;
        }
        
        if (objAdd.pointModeMaterial) {
            pointModeMaterial = objAdd.pointModeMaterial;
        }
        
        vector<vec3>::iterator i;
        if (transform != NULL) {
            mat4 m = *transform;
            for (i = objAdd.points.begin(); i != objAdd.points.end(); i++) {
                addPoint(mat4::multiply(m, *i));
            }
        } else {
            for (i = objAdd.points.begin(); i != objAdd.points.end(); i++) {
                addPoint(*i);
            }
        }
        
        vector<unsigned long> matMap(objAdd.materials.size());
        vector<Material *>::iterator mat_i;
        for (mat_i = objAdd.materials.begin(); mat_i != objAdd.materials.end(); mat_i++) {
            long mindex = getMaterialIndex(*mat_i);
            if (mindex == -1) {
                materials.push_back(*mat_i);
                matMap.push_back(materials.size() - 1);
            } else {
                matMap.push_back(mindex);
            }
        }
        
        vector<face *>::iterator face_i;
        for (face_i = objAdd.faces.begin(); face_i != objAdd.faces.end(); face_i++) {
            face *nFace = faces[addFace()];
            
            vector<unsigned long>::iterator pts_i;
            for (pts_i = (*face_i)->points.begin(); pts_i != (*face_i)->points.end(); pts_i++) {
                nFace->addPoint(*pts_i + pofs);
            }
            
            nFace->segment = (*face_i)->segment;
            nFace->material = matMap[(*face_i)->material];
            
            vector<vec2>::iterator uvs_i;
            for (uvs_i = (*face_i)->uvs.begin(); uvs_i != (*face_i)->uvs.end(); uvs_i++) {
                nFace->addPointUV(*uvs_i);
            }
            
            vector<vec3>::iterator ptnorm_i;
            for (ptnorm_i = (*face_i)->point_normals.begin(); ptnorm_i != (*face_i)->point_normals.end(); ptnorm_i++) {
                nFace->addPointNormal(*ptnorm_i);
            }
            
            vector<vec3>::iterator ptcolors_i;
            for (ptcolors_i = (*face_i)->point_colors.begin(); ptcolors_i != (*face_i)->point_colors.end(); ptcolors_i++) {
                nFace->addPointColor(*ptcolors_i);
            }
            
        }
    };
        
       
    void calcFaceNormals(long face_start_=-1, long face_end_=-1) {
        vector<face *>::iterator face_i;
        vector<face *>::iterator face_start;
        vector<face *>::iterator face_end;
//        var face, points = this.points, fp;
        
        if (face_start_ != -1) {
            face_start = faces.begin()+face_start_;
        } else {
            face_start = faces.begin();
        }
        
        if (face_end_ != -1) {
            face_end = faces.begin()+face_end_+1;
        } else {
            face_end = faces.end();
        }
        
        for (face_i = face_start; face_i != face_end; face_i++) {
            vector<unsigned long> *fp = &(*face_i)->points;
            if (fp->size() < 3) {
                (*face_i)->normal = vec3(0, 0, 0);
                continue;
            }
            
            (*face_i)->normal = vec3::normalize
                (
                 triangle::normal(points[(*fp)[0]], points[(*fp)[1]], points[(*fp)[2]])
                );
        }
    };

    Material *getMaterial(string m_name) {
        vector<Material *>::iterator i;
        for (i = materials.begin(); i != materials.end(); i++) {
            if ((*i)->name == m_name) {
                return *i;
            }
        }
        
        return NULL;
    };
        
//    void bindInstanceMaterials(mat_inst) {
//        this.instanceMaterials = mat_inst;
//    };

        
    void calcNormals(normalMapRef *outNormalMapRef = NULL) {
        bool updateMap = false;
        normalMapRef normalMapRef_out;
        genNormals = true;
        
        
        if (dynamic && !outNormalMapRef) {
            outNormalMapRef = &normalMap;
        }
        
        if (outNormalMapRef != NULL) {
            updateMap = true;
        }
        
        calcFaceNormals();
        
        unsigned long i, k, iMax, kMax;
        unsigned int jMax, j;
        

        vector<vector<uluiPair> > point_smoothRef;
        point_smoothRef.resize(points.size());
        
        vector<face *>::iterator face_i;
        vector<unsigned long>::iterator pts_i;
        vector<vec3>::iterator vec3_i;
        
        // build a quick list of point/face sharing
        i = 0;
        for (face_i = faces.begin(); face_i != faces.end(); face_i++) {
            j = 0;
            for (pts_i = (*face_i)->points.begin(); pts_i != (*face_i)->points.end(); pts_i++) {
                unsigned long idx = *pts_i;
                
                //      if (point_smoothRef[idx] === undef) point_smoothRef[idx] = [];
                point_smoothRef[idx].push_back(uluiPair(i, j));
                j++;
            }
            i++;
        }
        
        i = 0;
        // step through smoothing references and compute normals
        for (vec3_i = points.begin(); vec3_i != points.end(); vec3_i++) {
            //    if(!point_smoothRef.hasOwnProperty(i)) { continue; }
            //    if (typeof(point_smoothRef[i]) === undef) { continue; }
            unsigned long numPts = point_smoothRef[i].size();
            
            for (j = 0; j < numPts; j++) {
                int ptCount = 1;
                unsigned long faceNum = point_smoothRef[i][j].a;
                unsigned int pointNum = point_smoothRef[i][j].b;
                __float max_smooth = materials.size() ? materials[faces[faceNum]->material]->getMaxSmooth() : 60.0f;
                face *thisFace = faces[faceNum];
                
                // set point to it's face's normal
                vec3 tmpNorm;;
                
                tmpNorm[0] = thisFace->normal[0];
                tmpNorm[1] = thisFace->normal[1];
                tmpNorm[2] = thisFace->normal[2];
                
                // step through all other faces which share this point
                if (max_smooth != 0) {
                    for (k = 0; k < numPts; k++) {
                        if (j == k) {
                            continue;
                        }
                        unsigned long faceRefNum = point_smoothRef[i][k].a;
                        face *thisFaceRef = faces[faceRefNum];
                        
                        __float ang = vec3::angle(thisFaceRef->normal, thisFace->normal);
                        
                        if ((ang != ang) || ((ang * (180.0 / M_PI)) <= max_smooth)) {
                            
                            if (updateMap) {
                                normalMapRef_out.map[faceNum][pointNum].push_back(faceRefNum);
                            }
                            
                            tmpNorm[0] += thisFaceRef->normal[0];
                            tmpNorm[1] += thisFaceRef->normal[1];
                            tmpNorm[2] += thisFaceRef->normal[2];
                            
                            ptCount++;
                        }
                    }
                }
                
                tmpNorm[0] /= ptCount;
                tmpNorm[1] /= ptCount;
                tmpNorm[2] /= ptCount;
                
                faces[faceNum]->setPointNormal(pointNum,vec3::normalize(tmpNorm));
            }
        
            i++;
        }
        
        unsigned long normTotal = 0;
        if (updateMap) {
            
            for (i = 0, iMax= normalMapRef_out.map.size(); i<iMax; i++){
                for (j = 0, jMax = (unsigned int)normalMapRef_out.map[i].size(); j<jMax; j++){
                    normTotal += normalMapRef_out.map[i][j].size();
                }
            }
            
//            bool hasSegments = (segments.size()>1);
            
            outNormalMapRef->faceCount.resize(faces.size()*3);
            outNormalMapRef->faceNorm.resize(normTotal);
            //                if (hasSegments) {
            outNormalMapRef->faceNormIdx.resize(faces.size());
            //              }
            
            unsigned long c = 0;
            
            for (i = 0, iMax = faces.size(); i<iMax; i++){
                for (j = 0; j< 3; j++){
                    vector<unsigned long> *nmij;
                    if (normalMapRef_out.map[i].find(j) != normalMapRef_out.map[i].end()) {
                        nmij = &normalMapRef_out.map[i][j];
                    } else {
                        nmij = NULL;
                    }
                    
                    outNormalMapRef->faceCount[i*3+j] = nmij?nmij->size():0;
                    //                    if (hasSegments) {
                    outNormalMapRef->faceNormIdx[i] = c;
                    //                  }
                    if (nmij) for (k = 0, kMax = nmij->size(); k<kMax; k++){
                        outNormalMapRef->faceNorm[c++] = normalMapRef_out.map[i][j][k];
                    } else {
                        c++;
                    }
                }
            }
            
//            normalMapRef = outNormalMapRef;
            //                this.normalMapRef = normalMapRef_out;
        }
        
    };
        /*
    // New version with linear typed array run
    void recalcNormals(normalMapRef,options) {
        if (!this.genNormals) return;
        
        var faceNum,faceMax,pointNum,pMax,i,l,n,a,b,c,nc,pn,oRef,oFace,face,faceMapRef,nCount;
        
        options = options || {};
        normalMapRef = normalMapRef||this.normalMapRef;
        
        if (!normalMapRef) return;
        
        var hasSegments = (options.segments!==undef)?true:false;
        var segments = options.segments;
        
        
        this.calcFaceNormals();
        
        var refIdx = 0;
        var faceIdx = 0;
        var rc = 0;
        var on;
        
        if (hasSegments) {
            var dm = this.dynamicData.VBO.dynamicMap;
            var faceNormIdx = normalMapRef.faceNormIdx;
            
            for (var seg = 0, segMax = segments.length; seg < segMax; seg++) {
                var dmSeg = dm.segmentMap[segments[seg]];
                for (var idx = 0, idxMax = dmSeg.length; idx < idxMax; idx++) {
                    faceNum = dmSeg[idx];
                    face = this.faces[faceNum];
                    on = face.normal;
                    refIdx = faceNormIdx[faceNum];
                    
                    for (j = 0; j < 3; j++) {
                        pn = face.point_normals[j];
                        a = on[0];
                        b = on[1];
                        c = on[2];
                        
                        nCount = normalMapRef.faceCount[faceNum*3+j];
                        
                        for (i = 0, iMax = nCount; i<iMax; i++) {
                            oRef = normalMapRef.faceNorm[refIdx+i];
                            oFace = this.faces[oRef];
                            n = oFace.normal;
                            a += n[0];
                            b += n[1];
                            c += n[2];
                        }
                        
                        if (nCount) {
                            nc = nCount+1;
                            a /= nc;
                            b /= nc;
                            c /= nc;
                            
                            l = Math.sqrt(a * a + b * b + c * c);
                            
                            a /= l;
                            b /= l;
                            c /= l;
                            
                            pn[0] = a; pn[1] = b; pn[2] = c;
                        } else {
                            rc++;
                        }
                    }
                }
            }
        } else {
            for (faceNum = 0, faceMax = this.faces.length; faceNum < faceMax; faceNum++) {
                face = this.faces[faceNum];
                on = face.normal;
                
                for (j = 0; j < 3; j++) {
                    pn = face.point_normals[j];
                    a = on[0];
                    b = on[1];
                    c = on[2];
                    
                    nCount = normalMapRef.faceCount[faceIdx++];
                    
                    for (i = 0, iMax = nCount; i<iMax; i++) {
                        oRef = normalMapRef.faceNorm[refIdx++];
                        oFace = this.faces[oRef];
                        n = oFace.normal;
                        a += n[0];
                        b += n[1];
                        c += n[2];
                    }
                    
                    if (nCount) {
                        nc = nCount+1;
                        a /= nc;
                        b /= nc;
                        c /= nc;
                        
                        l = Math.sqrt(a * a + b * b + c * c);
                        
                        a /= l;
                        b /= l;
                        c /= l;
                        
                        pn[0] = a; pn[1] = b; pn[2] = c;
                    } else {
                        rc++;
                    }
                }
            }
        }
        
        return this;
    };
        
    void removeDoubles(tolerance) {
        var newPoints = [];
        var remap = [];
        var i, iMax, j, jMax;
        
        for (i = 0, iMax = this.points.length; i < iMax; i++) {
            var foundPt = -1;
            var searchPt = this.points[i];
            for (j = 0, jMax = newPoints.length; j<jMax; j++) {
                var findPt = newPoints[j];
                if (base.vec3.equal(searchPt,findPt,tolerance)) {
                    foundPt=j;
                    break;
                }
            }
            if (foundPt != -1) {
                remap[i] = foundPt;
            } else {
                remap[i] = newPoints.length;
                newPoints.push(this.points[i]);
            }
        }
        
        this.points = newPoints;
        for (i = 0, iMax = this.faces.length; i < iMax; i++) {
            var face = this.faces[i];
            for (j = 0, jMax = face.points.length; j < jMax; j++) {
                face.points[j] = remap[face.points[j]];
            }
        }
        
        return this;
    };
        
        
    void buildEdges() {
        var i,j,iMax,jMax;
        var edges = [];
        var edge_result = [];
        
        for (i = 0, iMax = this.faces.length; i < iMax; i++) {
            var face = this.faces[i];
            for (j = 0, jMax = face.points.length; j < jMax; j++) {
                var pta,ptb,segId;
                
                segId = face.segment;
                matId = face.material;
                
                if (j) {
                    ptb = face.points[j];
                    pta = face.points[j-1];
                    
                } else {
                    ptb = face.points[j];
                    pta = face.points[jMax-1];
                }
                
                edges[pta] = edges[pta] || {};
                edges[pta][matId] = edges[pta][matId] || {};
                edges[pta][matId][segId] = edges[pta][matId][segId] || {};
                
                if (!edges[pta][matId][segId][ptb] && !(edges[ptb] && edges[ptb][matId][segId][pta])) {
                    edge_result.push([matId,segId,pta,ptb]);
                }
            }
        }
        
        this.edges = edge_result;
        
        return this;
    };
        
    void subdivide(level,catmull) { // catmull-clark subdivision with alternate regular subdivision if catmull===false
        var vec3 = base.vec3;
        catmull = (catmull===undef)?true:catmull;
        
        if (level === undef) {
            level = 1;
        }
        if (level === 0) {
            return;
        }
        
        var i,j,iMax,jMax,k,kMax,face,edge;
        var edges = {};
        var point_face_list = [];
        var point_edge_list = [];
        var pointCount = this.points.length;
        var faceCount = this.faces.length;
        
        var face_points = [];
        var face_point_uv = [];
        var face_point_color = [];
        var face_point_normal = [];
        
        for (i = 0, iMax = faceCount; i < iMax; i++) {
            face = this.faces[i];
            if (face.points && (face.points.length===3||face.points.length===4)) {
                
                var face_point = [0,0,0];
                
                for (j = 0, jMax = face.points.length; j < jMax; j++) {
                    var addPoint = this.points[face.points[j]];
                    face_point[0]+=addPoint[0];
                    face_point[1]+=addPoint[1];
                    face_point[2]+=addPoint[2];
                }
                
                face_point[0]/=jMax;
                face_point[1]/=jMax;
                face_point[2]/=jMax;
                face_points[i] = this.addPoint(face_point);
                
                if (face.uvs.length === face.points.length) {
                    var face_uv = [0,0];
                    
                    for (j = 0, jMax = face.uvs.length; j < jMax; j++) {
                        var point_uv = face.uvs[j];
                        face_uv[0]+=point_uv[0];
                        face_uv[1]+=point_uv[1];
                    }
                    
                    face_uv[0]/=jMax;
                    face_uv[1]/=jMax;
                    face_point_uv[i] = face_uv;
                }
                
                if (face.point_colors.length === face.points.length) {
                    var face_color = [0,0,0];
                    
                    for (j = 0, jMax = face.point_colors.length; j < jMax; j++) {
                        var point_color = face.point_colors[j];
                        face_color[0]+=point_color[0];
                        face_color[1]+=point_color[1];
                        face_color[2]+=point_color[2];
                    }
                    
                    face_color[0]/=jMax;
                    face_color[1]/=jMax;
                    face_color[2]/=jMax;
                    face_point_color[i] = face_color;
                }
                
                if (face.point_normals.length === face.points.length) {
                    var face_normal = [0,0,0];
                    
                    for (j = 0, jMax = face.point_normals.length; j < jMax; j++) {
                        var point_normal = face.point_normals[j];
                        face_normal[0]+=point_normal[0];
                        face_normal[1]+=point_normal[1];
                        face_normal[2]+=point_normal[2];
                    }
                    
                    face_normal[0]/=jMax;
                    face_normal[1]/=jMax;
                    face_normal[2]/=jMax;
                    face_point_normal[i] = face_normal;
                }
            }
            
        }
        
        for (i = 0, iMax = this.faces.length; i < iMax; i++) {
            face = this.faces[i];
            for (j = 0, jMax = face.points.length; j < jMax; j++) {
                var pta,ptb,fpa,fpb;
                
                if (j) {
                    fpa = j;
                    fpb = j-1;
                } else {
                    fpa = j;
                    fpb = jMax-1;
                }
                
                ptb = face.points[fpa];
                pta = face.points[fpb];
                
                edges[pta] = edges[pta] || {};
                point_face_list[pta] = point_face_list[pta] || [];
                point_face_list[pta].push(i);
                
                if (edges[pta][ptb]!==undef) {
                    //                        log("Mesh.subdivide warning face #"+i+", edge:["+fpa+"->"+fpb+"] already used by face#"+edges[pta][ptb].face+", edge:["+edges[pta][ptb].fpa+"->"+edges[pta][ptb].fpb+"] possible mangling.");
                }
                
                edges[pta][ptb] = { face:i, a: pta, b: ptb, fpa: fpa, fpb: fpb };
            }
        }
        
        for (i in edges) {
            if (!edges.hasOwnProperty(i)) continue;
            for (j in edges[i]) {
                if (!edges[i].hasOwnProperty(j)) continue;
                var edgeA = edges[i][j];
                var edgeB = edges[j][i];
                if (edgeB===undef) {
                    log("Mesh.subdivide error. Hole at face #"+edgeA.face+", Edge:["+edgeA.fpa+"->"+edgeA.fpb+"], holes not yet supported; perhaps use Mesh.removeDoubles()?");
                    return;
                }
                if (!edgeA.edge_point) {
                    var edge_avg = vec3.multiply(vec3.add(this.points[edgeA.a],this.points[edgeA.b]),0.5);
                    if (catmull) {
                        var face_avg = vec3.multiply(vec3.add(this.points[face_points[edgeA.face]],this.points[face_points[edgeB.face]]),0.5);
                        edgeA.edge_point = vec3.multiply(vec3.add(edge_avg,face_avg),0.5);
                    } else {
                        edgeA.edge_point = edge_avg;
                    }
                    edgeB.edge_point = edgeA.edge_point;
                    edgeA.edge_avg = edge_avg;
                    edgeB.edge_avg = edge_avg;
                    edgeA.ep_idx = this.addPoint(edgeA.edge_point);
                    edgeB.ep_idx = edgeA.ep_idx;
                }
                point_edge_list[edgeA.a] = point_edge_list[edgeA.a] || [];
                point_edge_list[edgeA.a].push(edgeA.edge_avg);
                var edge_uvs = this.faces[edgeA.face].uvs;
                if (edge_uvs.length) {
                    var uv_a = edge_uvs[edgeA.fpa];
                    var uv_b = edge_uvs[edgeA.fpb];
                    
                    edgeA.uv = [(uv_a[0]+uv_b[0])/2,(uv_a[1]+uv_b[1])/2];
                }
                var edge_colors = this.faces[edgeA.face].point_colors;
                if (edge_colors.length) {
                    var color_a = edge_colors[edgeA.fpa];
                    var color_b = edge_colors[edgeA.fpb];
                    
                    edgeA.color = vec3.multiply(vec3.add(color_a,color_b),0.5);
                }
                var edge_normals = this.faces[edgeA.face].point_normals;
                if (edge_normals.length) {
                    var normal_a = edge_normals[edgeA.fpa];
                    var normal_b = edge_normals[edgeA.fpb];
                    
                    edgeA.normal = vec3.normalize(vec3.multiply(vec3.add(normal_a,normal_b),0.5));
                }
            }
        }
        
        if (catmull) {
            var point_face_average = [];
            
            for (i = 0, iMax = pointCount; i<iMax; i++) {
                var pointFaceAvg = [0,0,0];
                if (!point_face_list[i]) continue;
                for (j = 0, jMax = point_face_list[i].length; j < jMax; j++) {
                    var addFacePoint = this.points[face_points[point_face_list[i][j]]];
                    pointFaceAvg[0] += addFacePoint[0];
                    pointFaceAvg[1] += addFacePoint[1];
                    pointFaceAvg[2] += addFacePoint[2];
                }
                pointFaceAvg[0]/=jMax;
                pointFaceAvg[1]/=jMax;
                pointFaceAvg[2]/=jMax;
                
                point_face_average[i] = pointFaceAvg;
            }
            
            var point_edge_average = [];
            
            for (i = 0, iMax = pointCount; i<iMax; i++) {
                var pointEdgeAvg = [0,0,0];
                if (!point_edge_list[i]) continue;
                for (j = 0, jMax = point_edge_list[i].length; j < jMax; j++) {
                    var addEdgePoint = point_edge_list[i][j];
                    pointEdgeAvg[0] += addEdgePoint[0];
                    pointEdgeAvg[1] += addEdgePoint[1];
                    pointEdgeAvg[2] += addEdgePoint[2];
                }
                pointEdgeAvg[0]/=jMax;
                pointEdgeAvg[1]/=jMax;
                pointEdgeAvg[2]/=jMax;
                
                point_edge_average[i] = pointEdgeAvg;
            }
            
            
            for (i = 0, iMax = pointCount; i<iMax; i++) {
                if (!point_face_list[i]) continue;
                var n = point_face_list[i].length;
                var pt = this.points[i];
                
                var m1 = (n-3) / n;
                var m2 = 1.0 / n;
                var m3 = 2.0 / n;
                
                var newPoint = vec3.multiply(pt,m1);
                newPoint = vec3.add(newPoint,vec3.multiply(point_face_average[i],m2));
                newPoint = vec3.add(newPoint,vec3.multiply(point_edge_average[i],m3));
                
                this.points[i] = newPoint;
            }
        }
        
        for (i = 0; i < faceCount; i++) {
            face = this.faces[i];
            if (face.points.length!==3 && face.points.length!==4) continue;
            
            var opt = face.points.slice(0);
            var ouv = face.uvs.slice(0);
            var oc = face.point_colors.slice(0);
            var on = face.point_normals.slice(0);
            var hasUV = ouv.length===opt.length;
            var hasColor = oc.length===opt.length;
            var hasNormal = on.length===opt.length;
            var omat = face.material;
            var faceNum,e1,e2;
            
            if (opt.length === 3) {
                this.setFaceMaterial(omat);
                e1 = edges[opt[0]][opt[1]]; e2 = edges[opt[2]][opt[0]];
                this.addFace([opt[0], e1.ep_idx, face_points[i], e2.ep_idx], i);
                if (hasUV) this.faces[i].uvs = [ouv[0],e1.uv,face_point_uv[i],e2.uv];
                if (hasColor) this.faces[i].point_colors = [oc[0],e1.color,face_point_color[i],e2.color];
                if (hasNormal) this.faces[i].point_normals = [on[0],e1.normal,face_point_normal[i],e2.normal];
                
                e1 = edges[opt[1]][opt[2]]; e2 = edges[opt[0]][opt[1]];
                faceNum = this.addFace([opt[1], e1.ep_idx, face_points[i], e2.ep_idx]);
                if (hasUV) this.faces[faceNum].uvs = [ouv[1],e1.uv,face_point_uv[i],e2.uv];
                if (hasColor) this.faces[faceNum].point_colors = [oc[1],e1.color,face_point_color[i],e2.color];
                if (hasNormal) this.faces[faceNum].point_normals = [on[1],e1.normal,face_point_normal[i],e2.normal];
                
                e1 = edges[opt[2]][opt[0]]; e2 = edges[opt[1]][opt[2]];
                faceNum = this.addFace([opt[2], e1.ep_idx, face_points[i], e2.ep_idx]);
                if (hasUV) this.faces[faceNum].uvs = [ouv[2],e1.uv,face_point_uv[i],e2.uv];
                if (hasColor) this.faces[faceNum].point_colors = [oc[2],e1.color,face_point_color[i],e2.color];
                if (hasNormal) this.faces[faceNum].point_normals = [on[2],e1.normal,face_point_normal[i],e2.normal];
            } else {
                this.setFaceMaterial(omat);
                e1 = edges[opt[0]][opt[1]]; e2 = edges[opt[3]][opt[0]];
                this.addFace([opt[0], e1.ep_idx, face_points[i], e2.ep_idx], i);
                if (hasUV) this.faces[i].uvs = [ouv[0], e1.uv, face_point_uv[i], e2.uv];
                if (hasColor) this.faces[i].point_colors = [oc[0], e1.color, face_point_color[i], e2.color];
                if (hasNormal) this.faces[i].point_normals = [on[0], e1.normal, face_point_normal[i], e2.normal];
                
                e1 = edges[opt[1]][opt[2]]; e2 = edges[opt[0]][opt[1]];
                faceNum = this.addFace([opt[1], e1.ep_idx, face_points[i], e2.ep_idx]);
                if (hasUV) this.faces[faceNum].uvs = [ouv[1], e1.uv, face_point_uv[i], e2.uv];
                if (hasColor) this.faces[faceNum].point_colors = [oc[1], e1.color, face_point_color[i], e2.color];
                if (hasNormal) this.faces[faceNum].point_normals = [on[1], e1.normal, face_point_normal[i], e2.normal];
                
                e1 = edges[opt[2]][opt[3]]; e2 = edges[opt[1]][opt[2]];
                faceNum = this.addFace([opt[2], e1.ep_idx, face_points[i], e2.ep_idx]);
                if (hasUV) this.faces[faceNum].uvs = [ouv[2], e1.uv, face_point_uv[i], e2.uv];
                if (hasColor) this.faces[faceNum].point_colors = [oc[2], e1.color, face_point_color[i], e2.color];
                if (hasNormal) this.faces[faceNum].point_normals = [on[2], e1.normal, face_point_normal[i], e2.normal];
                
                e1 = edges[opt[3]][opt[0]]; e2 = edges[opt[2]][opt[3]];
                faceNum = this.addFace([opt[3], e1.ep_idx, face_points[i], e2.ep_idx]);
                if (hasUV) this.faces[faceNum].uvs = [ouv[3], e1.uv, face_point_uv[i], e2.uv];
                if (hasColor) this.faces[faceNum].point_colors = [oc[3], e1.color, face_point_color[i], e2.color];
                if (hasNormal) this.faces[faceNum].point_normals = [on[3], e1.normal, face_point_normal[i], e2.normal];
            }
        }
        
        level--;
        if (level!==0) {
            this.subdivide(level,catmull);
            return;
        }
        return this;
    };
        
    void removeInternals() {
        var vec3 = base.vec3;
        
        var i,j,iMax,jMax,k,kMax,face,edge;
        var edges = {};
        var pointCount = this.points.length;
        var faceCount = this.faces.length;
        
        var pta,ptb,fpa,fpb;
        
        
        for (i = 0, iMax = this.faces.length; i < iMax; i++) {
            face = this.faces[i];
            for (j = 0, jMax = face.points.length; j < jMax; j++) {
                if (j) {
                    fpa = j;
                    fpb = j-1;
                } else {
                    fpa = j;
                    fpb = jMax-1;
                }
                
                pta = face.points[fpa];
                ptb = face.points[fpb];
                
                edges[pta] = edges[pta] || {};
                
                if (edges[pta][ptb]===undef) {
                    edges[pta][ptb] = [i];
                } else {
                    edges[pta][ptb].push(i);
                }
            }
        }
        
        
        var edgeFunc = function(i) {
            return (edges[ptb][pta].indexOf(i) !== -1);
        };
        
        for (i = 0; i < faceCount; i++) {
            var edgeCount = 0;
            
            face = this.faces[i];
            var edgelist = null;
            
            for (j = 0, jMax = face.points.length; j < jMax; j++) {
                if (j) {
                    fpa = j;
                    fpb = j-1;
                } else {
                    fpa = j;
                    fpb = jMax-1;
                }
                
                pta = face.points[fpa];
                ptb = face.points[fpb];
                
                if (!edgelist) {
                    edgelist = edges[ptb][pta];
                } else {
                    edgelist = edgelist.filter(edgeFunc);
                }
            }
            
            if (edgelist.length) {
                this.faces.splice(i,1);
                faceCount--;
                i--;
            }
        }
        
        return this;
    };
        */
        
    void prepare(bool doClean = true) {
//        if (this.buildWireframe && !this.triangulateWireframe) {
//            this.buildEdges();
//        }
        
        triangulate();
        if (genNormals) calcNormals();
        
//        if (this.buildWireframe && this.triangulateWireframe) {
//            this.buildEdges();
//        }
        
        compile();
        
        if (doClean && !dynamic) {
            clean();
        }
    };
        
    void clean() {
/*        var i, iMax;
        
        
        for (i = 0, iMax = this.points.length; i < iMax; i++) {
            delete(this.points[i]);
            this.points[i] = null;
        }
        this.points = [];
        
        for (i = 0, iMax = this.faces.length; i < iMax; i++) {
            delete(this.faces[i].points);
            delete(this.faces[i].point_normals);
            delete(this.faces[i].uvs);
            delete(this.faces[i].normal);
            delete(this.faces[i]);
            this.faces[i] = null;
        }
        this.faces = [];
        
        
        return this;*/
    };
        
        // generate a compile-map object for the current mesh, used to create a VBO with compileVBO(compileMap)
        compileMapVBO *compileMap(__float tolerance=0.00001) {
            
            compileMapVBO *compileMap = new compileMapVBO;
                        
            vector<map<unsigned int, vector<unsigned long> > > compileRef;
            vector<map<unsigned int, vector<unsigned long> > >::iterator compileRef_i;
            map<unsigned int, vector<unsigned long> >::iterator compileRef_j;
            vector<unsigned long>::iterator compileRef_k;
            vector<face *>::iterator face_i;
            map<unsigned long, bool> segmentRef;
            
            
            unsigned long i, k, iMax, matId;
            unsigned int j;
            unsigned int segId, x;
            
            if (!materials.size()) materials.push_back(new Material());

            compileRef.resize(materials.size());

            for (i = 0, iMax = faces.size(); i < iMax; i++) {
                if (faces[i]->points.size() == 3) {
                    matId = faces[i]->material;
                    segId = faces[i]->segment;
                    
                    if (segmentRef.find(segId) == segmentRef.end()) {
                        compileMap->segments.push_back(segId);
                        segmentRef[segId] = true;
                    }
                    
                    compileRef[matId][segId].push_back(i);
                }
            }
            
            vector<vector<vtxRefTuple> > vtxRef;
            vector<vector<vtxRefTuple> >::iterator vtxRef_i;
            vector<vtxRefTuple>::iterator vtxRef_j;
            
            vtxRef.resize(points.size());
            
            unsigned long idxCount = 0;
            bool hasUV = false;
            bool hasNorm = false;
            bool hasColor = false;
            unsigned long faceNum;
            
            i = 0;
            for (compileRef_i = compileRef.begin(); compileRef_i != compileRef.end(); compileRef_i++) {
                j = 0;
                for (compileRef_j = (*compileRef_i).begin(); compileRef_j != (*compileRef_i).end(); compileRef_j++) {
                    k = 0;
                    for (compileRef_k = (*compileRef_j).second.begin(); compileRef_k != (*compileRef_j).second.end(); compileRef_k++) {
                        faceNum = *compileRef_k; //compileRef[i][j][k];
                        hasUV = hasUV || (!faces[faceNum]->uvs.empty());
                        hasNorm = hasNorm || (!faces[faceNum]->point_normals.empty());
                        hasColor = hasColor || (!faces[faceNum]->point_colors.empty());
                        k++;
                    }
                    j++;
                }
                i++;
            }
            
            if (hasUV||hasNorm||hasColor) {
                for (face_i = faces.begin(); face_i != faces.end(); face_i++) {
                    if (hasUV) {
                        if ((*face_i)->uvs.empty()) {
                            for (j = 0; j < (*face_i)->points.size(); j++) {
                                (*face_i)->addPointUV(vec2(0, 0));
                            }
                        }
                    }
                    if (hasNorm) {
                        if ((*face_i)->point_normals.empty()) {
                            for (j = 0; j < (*face_i)->points.size(); j++) {
                                (*face_i)->addPointNormal(vec3(0, 0, 0));
                            }
                        }
                    }
                    if (hasColor) {
                        if ((*face_i)->point_colors.empty()) {
                            for (j = 0; j < (*face_i)->points.size(); j++) {
                                (*face_i)->addPointColor(vec3(0, 0, 0));
                            }
                        }
                    }
                }
            }
            
            bool boundsInit = false;
            
            i = 0;
            for (compileRef_i = compileRef.begin(); compileRef_i != compileRef.end(); compileRef_i++) {
                j = 0;
                for (compileRef_j = (*compileRef_i).begin(); compileRef_j != (*compileRef_i).end(); compileRef_j++) {
                    k = 0;
                    for (compileRef_k = (*compileRef_j).second.begin(); compileRef_k != (*compileRef_j).second.end(); compileRef_k++) {
                        faceNum = (*compileRef_k); //compileRef[i][j][k];
                        
                        for (x = 0; x < 3; x++) {
                            unsigned long ptNum = faces[*compileRef_k]->points[x];
                            
                            long foundPt = -1;
                            
                            for (vtxRef_j = vtxRef[ptNum].begin(); vtxRef_j != vtxRef[ptNum].end(); vtxRef_j++) {
                                unsigned long oFace = (*vtxRef_j).faceNum; // faceNum
                                unsigned int oPoint = (*vtxRef_j).pointNum; // pointNum
                                unsigned long oIndex = (*vtxRef_j).index; // index
                                foundPt = oIndex;
                                
                                if (hasNorm) {
                                    foundPt = (vec3::equal
                                               (faces[oFace]->point_normals[oPoint],
                                                faces[faceNum]->point_normals[x],
                                                tolerance)
                                               ) ? foundPt : -1;
                                }
                                
                                if (hasUV) {
                                    foundPt = (vec2::equal
                                               (
                                                faces[oFace]->uvs[oPoint],
                                                faces[faceNum]->uvs[x],
                                                tolerance)
                                               ) ? foundPt : -1;
                                }
                                
                                if (hasColor) {
                                    foundPt = (vec3::equal
                                               (
                                                faces[oFace]->point_colors[oPoint],
                                                faces[faceNum]->point_colors[x],
                                                tolerance)
                                               ) ? foundPt : -1;
                                }
                                
                            }
                            
                            
                            if (foundPt != -1) {
                                compileMap->elements[i][j].push_back(foundPt);
                            } else {
                                compileMap->points.push_back(ptNum);
                                
                                if (!boundsInit) {
                                    compileMap->bounds.min = points[ptNum];
                                    compileMap->bounds.max = points[ptNum];
                                    boundsInit = true;
                                } else {
                                    if (points[ptNum][0] < compileMap->bounds.min[0]) {
                                        compileMap->bounds.min[0] = points[ptNum][0];
                                    }
                                    if (points[ptNum][1] < compileMap->bounds.min[1]) {
                                        compileMap->bounds.min[1] = points[ptNum][1];
                                    }
                                    if (points[ptNum][2] < compileMap->bounds.min[2]) {
                                        compileMap->bounds.min[2] = points[ptNum][2];
                                    }
                                    
                                    if (points[ptNum][0] > compileMap->bounds.max[0]) {
                                        compileMap->bounds.max[0] = points[ptNum][0];
                                    }
                                    if (points[ptNum][1] > compileMap->bounds.max[1]) {
                                        compileMap->bounds.max[1] = points[ptNum][1];
                                    }
                                    if (points[ptNum][2] > compileMap->bounds.max[2]) {
                                        compileMap->bounds.max[2] = points[ptNum][2];
                                    }
                                }
                                
                                if (hasNorm) {
                                    compileMap->normals.push_back(facePointPair(faceNum, x));
                                }
                                
                                if (hasColor) {
                                    compileMap->colors.push_back(facePointPair(faceNum, x));
                                }
                                
                                if (hasUV) {
                                    compileMap->uvs.push_back(facePointPair(faceNum, x));
                                }
                                
                                compileMap->elements[i][j].push_back(idxCount);
                                
                                vtxRef[ptNum].push_back(vtxRefTuple(faceNum, x, idxCount));
                                idxCount++;
                            }
                        }
                        
                        k++;
                    }
                    j++;
                }
                i++;
            }
        
        
        
        //        if (this.edges) {
        //
        //            compileMap.line_elements = [];
        //
        //            for (i = 0, iMax = this.edges.length; i < iMax; i++) {
        //                var edge = this.edges[i];
        //                matId = edge[0];
        //                segId = edge[1];
        //                var ptA = edge[2];
        //                var ptB = edge[3];
        //                
        //                compileMap.line_elements[matId] = compileMap.line_elements[matId] || [];
        //                compileMap.line_elements[matId][segId] = compileMap.line_elements[matId][segId] || [];
        //                compileMap.line_elements[matId][segId].push(vtxRef[ptA][0][2]);
        //                compileMap.line_elements[matId][segId].push(vtxRef[ptB][0][2]);
        //            }
        //        }
        
        compileMap->dynamic = dynamic;
        
        return compileMap;
    };
    
        // Take a compileMap() result and create a compiled mesh VBO object for bufferVBO(VBO)
    compiledVBO *compileVBO(compileMapVBO *compileMap, bool doElements = true, bool doVertex = true, bool doNormal= true, bool doUV = true, bool doColor = true, bool doLines = false, bool doDynamic = false) {
        
//        if (doLines == false) doLines = (!!compileMap.line_elements);
        if (doDynamic == false) doDynamic = compileMap->dynamic;
        
        compiledVBO *compiled = new compiledVBO;
        unsigned long
        ofs,
        ptIdx, faceIdx,
        i, j, iMax;
//        step, sourceIndex;
        
        // dynamicMap,
        
        unsigned long numPoints = compileMap->points.size();    //||compileMap->uvs.size()||compileMap->normals.size()||compileMap->colors.size();
        
//        var doUnroll = (numPoints > 65535);
        
//        if (doDynamic) {
//            dynamicMap = {
//            points: doUnroll?(new Uint32Array(compileMap.points.length)):(new Uint16Array(compileMap.points.length)),
//            face_points: doUnroll?(new Uint32Array(compileMap.points.length * 2)):(new Uint16Array(compileMap.points.length * 2)),
//            segments: null
//            };
//            
//            compiled.dynamicMap = dynamicMap;
//            compiled.dynamic = true;
//        }
        
        doVertex = compileMap->points.size() && doVertex;
        if (doVertex) {
            compiled->vbo_points.resize(numPoints);
            for (i = 0, iMax = numPoints; i < iMax; i++) {
                ptIdx = compileMap->points[i];
                compiled->vbo_points[i] = points[ptIdx];
//                if (doDynamic) {
//                    dynamicMap.points[i] = ptIdx;
//                }
            }
        }
        
//        if (doDynamic) {
//            sourceIndex = compileMap.normals||compileMap.colors||compileMap.uvs;
//            for (i = 0, iMax = sourceIndex.length; i < iMax; i++) {
//                ptIdx = sourceIndex[i];
//                dynamicMap.face_points[i*2] = ptIdx[0];
//                dynamicMap.face_points[i*2+1] = ptIdx[1];
//            }
//        }
        
        doNormal = compileMap->normals.size() && doNormal;
        if (doNormal) {
            compiled->vbo_normals.resize(numPoints);
            ofs = 0;
            for (i = 0, iMax = numPoints; i < iMax; i++) {
                faceIdx = compileMap->normals[i].faceNum;
                ptIdx = compileMap->normals[i].pointNum;
                compiled->vbo_normals[i] = faces[faceIdx]->point_normals[ptIdx];
            }
        }
        
        doColor = compileMap->colors.size() && doColor;
        if (doColor) {
            compiled->vbo_colors.resize(numPoints);
            ofs = 0;
            for (i = 0, iMax = numPoints; i < iMax; i++) {
                faceIdx = compileMap->colors[i].faceNum;
                ptIdx = compileMap->colors[i].pointNum;
                compiled->vbo_colors[i] = faces[faceIdx]->point_colors[ptIdx];
            }
        }
        
        doUV = compileMap->uvs.size() && doUV;
        if (doUV) {
            numPoints = compileMap->uvs.size();
            compiled->vbo_uvs.resize(numPoints);
            ofs = 0;
            for (i = 0, iMax = numPoints; i < iMax; i++) {
                faceIdx = compileMap->uvs[i].faceNum;
                ptIdx = compileMap->uvs[i].pointNum;
                compiled->vbo_uvs[i] = faces[faceIdx]->uvs[ptIdx];
            }
        }
        
        compileMapVBOElementsI elem_i;
        compileMapVBOElementsJ elem_j;
        compileMapVBOElementsK elem_k;

        unsigned long numElements = 0;
        if (doElements) {
            i = 0;
            compiled->elements_ref.resize(compileMap->elements.size());
            for (elem_i = compileMap->elements.begin(); elem_i != compileMap->elements.end(); elem_i++) {
                j = 0;
                
                for (elem_j = (*elem_i).second.begin(); elem_j != (*elem_i).second.end(); elem_j++) {
                    for (elem_k = (*elem_j).second.begin(); elem_k != (*elem_j).second.end(); elem_k++) {
                        compiled->vbo_elements.push_back(*elem_k);
                    }
                        
                    compiled->elements_ref[i].push_back(compiledVBOElementRef((*elem_j).first, (*elem_j).second.size()));
                    j++;
                }
                i++;
            }
            
            numElements = compiled->vbo_elements.size();
        }

        compiled->segments.resize(compileMap->segments.size());
        copy(compileMap->segments.begin(),compileMap->segments.end(), compiled->segments.begin());
        compiled->bounds = compileMap->bounds;
        
        
//        if (doLines) {
//            var unroll_lines = doUnroll;
//            
//            if (unroll_lines) {
//                compiled.vbo_lines = [];
//                if (doNormal) compiled.vbo_line_normals = [];
//                if (doUV) compiled.vbo_line_uvs = [];
//                if (doColor) compiled.vbo_line_colors = [];
//            } else {
//                compiled.vbo_line_elements = [];
//                
//            }
//            compiled.line_elements_ref = [];
//            
//            //       if (unroll_lines) {
//            //         console.log("Unrolling wireframe points, note: currently only Mesh wireframeMaterial option with ambient color will work properly.");
//            //   }
//            
//            for (i = 0, iMax = compileMap.line_elements.length; i < iMax; i++) {
//                compiled.line_elements_ref[i] = [];
//                
//                jctr = 0;
//                
//                for (j in compileMap.line_elements[i]) {
//                    if (compileMap.line_elements[i].hasOwnProperty(j)) {
//                        emap = compileMap.line_elements[i][j];
//                        for (k = 0, kMax = emap.length; k < kMax; k++) {
//                            if (unroll_lines) {
//                                var idx = emap[k];
//                                
//                                compiled.vbo_lines.push(compiled.vbo_points[idx*3]);
//                                compiled.vbo_lines.push(compiled.vbo_points[idx*3+1]);
//                                compiled.vbo_lines.push(compiled.vbo_points[idx*3+2]);
//                                
//                                if (doNormal) {
//                                    compiled.vbo_line_normals.push(compiled.vbo_normals[idx*3]);
//                                    compiled.vbo_line_normals.push(compiled.vbo_normals[idx*3+1]);
//                                    compiled.vbo_line_normals.push(compiled.vbo_normals[idx*3+2]);
//                                }
//                                
//                                if (doColor) {
//                                    compiled.vbo_line_colors.push(compiled.vbo_colors[idx*3]);
//                                    compiled.vbo_line_colors.push(compiled.vbo_colors[idx*3+1]);
//                                    compiled.vbo_line_colors.push(compiled.vbo_colors[idx*3+2]);
//                                }
//                                
//                                if (doUV) {
//                                    compiled.vbo_line_uvs.push(compiled.vbo_uvs[idx*2]);
//                                    compiled.vbo_line_uvs.push(compiled.vbo_uvs[idx*2+1]);
//                                }
//                            } else {
//                                compiled.vbo_line_elements.push(emap[k]);
//                            }
//                        }
//                        
//                        compiled.line_elements_ref[i][jctr] = [j|0, emap.length|0];
//                        
//                        jctr++;
//                    }
//                }
//            }
//            
//            if (!unroll_lines) {
//                compiled.vbo_line_elements = new Uint16Array(compiled.vbo_line_elements);
//            } else {
//                compiled.vbo_lines = new Float32Array(compiled.vbo_lines);
//                if (doNormal) compiled.vbo_line_normals = new Float32Array(compiled.vbo_line_normals);
//                if (doUV) compiled.vbo_line_uvs = new Float32Array(compiled.vbo_line_uvs);
//                if (doColor) compiled.vbo_line_colors = new Float32Array(compiled.vbo_line_colors);
//            }
//        }
        
//        if (doUnroll) {   // OpenGL ES 2.0 limit, todo: disable this if uint32 extension is supported
//            console.log("Mesh "+(this.name?this.name+" ":"")+"exceeded element index limit -- unrolling "+numElements+" triangles..");
//            
//            // Perform an unroll of the element arrays into a linear drawarray set
//            var ur_points, ur_normals, ur_uvs, ur_colors;
//            
//            if (doVertex) {
//                ur_points = new Float32Array(numElements*9);
//            }
//            if (doNormal) {
//                ur_normals = new Float32Array(numElements*9);
//            }
//            if (doUV) {
//                ur_uvs = new Float32Array(numElements*6);
//            }
//            if (doColor) {
//                ur_colors = new Float32Array(numElements*9);
//            }
//            
//            var dyn_face_points_unrolled, dyn_points_unrolled;
//            
//            if (doDynamic) {
//                dyn_face_points_unrolled = new Uint32Array(numElements*3*2);
//                dyn_points_unrolled = new Uint32Array(numElements*3);
//            }
//            
//            for (i = 0, iMax = numElements; i<iMax; i++) {
//                var pt = i*9;
//                
//                var e1 = compiled_elements[i*3]*3, e2 = compiled_elements[i*3+1]*3, e3 = compiled_elements[i*3+2]*3;
//                
//                if (doDynamic) {
//                    var dpt = i*3;
//                    var dfpt = dpt*2;
//                    
//                    dyn_face_points_unrolled[dfpt] = dynamicMap.face_points[compiled_elements[dpt]*2];
//                    dyn_face_points_unrolled[dfpt+1] = dynamicMap.face_points[compiled_elements[dpt]*2+1];
//                    
//                    dyn_face_points_unrolled[dfpt+2] = dynamicMap.face_points[compiled_elements[dpt+1]*2];
//                    dyn_face_points_unrolled[dfpt+3] = dynamicMap.face_points[compiled_elements[dpt+1]*2+1];
//                    
//                    dyn_face_points_unrolled[dfpt+4] = dynamicMap.face_points[compiled_elements[dpt+2]*2];
//                    dyn_face_points_unrolled[dfpt+5] = dynamicMap.face_points[compiled_elements[dpt+2]*2+1];
//                    
//                    dyn_points_unrolled[dpt] = dynamicMap.points[compiled_elements[dpt]];
//                    dyn_points_unrolled[dpt+1] = dynamicMap.points[compiled_elements[dpt+1]];
//                    dyn_points_unrolled[dpt+2] = dynamicMap.points[compiled_elements[dpt+2]];
//                }
//                
//                if (doVertex) {
//                    ur_points[pt] = compiled.vbo_points[e1];
//                    ur_points[pt+1] = compiled.vbo_points[e1+1];
//                    ur_points[pt+2] = compiled.vbo_points[e1+2];
//                    
//                    ur_points[pt+3] = compiled.vbo_points[e2];
//                    ur_points[pt+4] = compiled.vbo_points[e2+1];
//                    ur_points[pt+5] = compiled.vbo_points[e2+2];
//                    
//                    ur_points[pt+6] = compiled.vbo_points[e3];
//                    ur_points[pt+7] = compiled.vbo_points[e3+1];
//                    ur_points[pt+8] = compiled.vbo_points[e3+2];
//                }
//                if (doNormal) {
//                    ur_normals[pt] = compiled.vbo_normals[e1];
//                    ur_normals[pt+1] = compiled.vbo_normals[e1+1];
//                    ur_normals[pt+2] = compiled.vbo_normals[e1+2];
//                    
//                    ur_normals[pt+3] = compiled.vbo_normals[e2];
//                    ur_normals[pt+4] = compiled.vbo_normals[e2+1];
//                    ur_normals[pt+5] = compiled.vbo_normals[e2+2];
//                    
//                    ur_normals[pt+6] = compiled.vbo_normals[e3];
//                    ur_normals[pt+7] = compiled.vbo_normals[e3+1];
//                    ur_normals[pt+8] = compiled.vbo_normals[e3+2];
//                }
//                if (doUV) {
//                    var u1 = compiled_elements[i*3]*2, u2 = compiled_elements[i*3+1]*2, u3 = compiled_elements[i*3+2]*2;
//                    ur_uvs[i*6] = compiled.vbo_uvs[u1];
//                    ur_uvs[i*6+1] = compiled.vbo_uvs[u1+1];
//                    
//                    ur_uvs[i*6+2] = compiled.vbo_uvs[u2];
//                    ur_uvs[i*6+3] = compiled.vbo_uvs[u2+1];
//                    
//                    ur_uvs[i*6+4] = compiled.vbo_uvs[u3];
//                    ur_uvs[i*6+5] = compiled.vbo_uvs[u3+1];
//                }
//                if (doColor) {
//                    ur_colors[pt] = compiled.vbo_colors[e1];
//                    ur_colors[pt+1] = compiled.vbo_colors[e1+1];
//                    ur_colors[pt+2] = compiled.vbo_colors[e1+2];
//                    
//                    ur_colors[pt+3] = compiled.vbo_colors[e2];
//                    ur_colors[pt+4] = compiled.vbo_colors[e2+1];
//                    ur_colors[pt+5] = compiled.vbo_colors[e2+2];
//                    
//                    ur_colors[pt+6] = compiled.vbo_colors[e3];
//                    ur_colors[pt+7] = compiled.vbo_colors[e3+1];
//                    ur_colors[pt+8] = compiled.vbo_colors[e3+2];
//                }
//            }
//            
//            if (doVertex) {
//                compiled.vbo_points = ur_points;
//            }
//            if (doNormal) {
//                compiled.vbo_normals = ur_normals;
//            }
//            if (doUV) {
//                compiled.vbo_uvs = ur_uvs;
//            }
//            if (doColor) {
//                compiled.vbo_colors = ur_colors;
//            }
//            
//            if (doDynamic) {
//                delete dynamicMap.points;
//                delete dynamicMap.face_points;
//                dynamicMap.points = dyn_points_unrolled;
//                dynamicMap.face_points = dyn_face_points_unrolled;
//            }
//            
//            compiled.unrolled = true;
//            
//            
//            // console.log("Points :",ur_points.length);
//            // console.log("Norms :",ur_normals.length);
//            // console.log("Colors :",ur_colors.length);
//            // console.log("UVS :",ur_uvs.length);
//        } else {
//            compiled.unrolled = false;
//        }
        
        // segmented update support
//        if (doDynamic && compileMap.segments.length>1) {
//            var segmentMap = [];
//            var segId;
//            
//            sourceIndex = dynamicMap.points;
//            for (i = 0, iMax = sourceIndex.length; i < iMax; i++) {
//                ptIdx = sourceIndex[i];
//                var f = dynamicMap.face_points[i*2];
//                segId = this.faces[f].segment||0;
//                if (segmentMap[segId] === undef) {
//                    segmentMap[segId] = [];
//                }
//                segmentMap[segId].push(i);
//            }
//            
//            compiled.dynamicMap.segmentMap = segmentMap;
//        }
        
        return compiled;
    };
         
        /*
    void updateVBO(VBO,options) {
        if (!VBO.dynamic) return false;
        
        var i,iMax;
        var dm = VBO.dynamicMap;
        
        var doPoint = options.points && !!VBO.vbo_points;
        var doNormal = options.normals && !!VBO.vbo_normals;
        var doUV = options.uvs && !!VBO.vbo_uvs;
        var doColor = options.colors && !!VBO.vbo_colors;
        var hasSegments = (options.segments!==undef)?true:false;
        var segments = options.segments;
        
        var pt,face,fp;
        
        if (hasSegments) {
            for (var seg = 0, segMax = segments.length; seg < segMax; seg++) {
                var dmSeg = dm.segmentMap[segments[seg]];
                for (var idx = 0, idxMax = dmSeg.length; idx<idxMax; idx++) {
                    i = dmSeg[idx];
                    face = this.faces[dm.face_points[i*2]];
                    fp = dm.face_points[i*2+1];
                    if (doPoint) {
                        pt = this.points[dm.points[i]];
                        VBO.vbo_points[i*3] = pt[0];
                        VBO.vbo_points[i*3+1] = pt[1];
                        VBO.vbo_points[i*3+2] = pt[2];
                    }
                    if (doNormal) {
                        pt = face.point_normals[fp];
                        VBO.vbo_normals[i*3] = pt[0];
                        VBO.vbo_normals[i*3+1] = pt[1];
                        VBO.vbo_normals[i*3+2] = pt[2];
                    }
                    if (doColor) {
                        pt = face.point_colors[fp];
                        VBO.vbo_colors[i*3] = pt[0];
                        VBO.vbo_colors[i*3+1] = pt[1];
                        VBO.vbo_colors[i*3+2] = pt[2];
                    }
                    if (doUV) {
                        pt = face.uvs[fp];
                        VBO.vbo_uvs[i*2] = pt[0];
                        VBO.vbo_uvs[i*2+1] = pt[1];
                    }
                }
            }
        } else {
            for (i = 0, iMax = dm.points.length; i < iMax; i++) {
                face = this.faces[dm.face_points[i*2]];
                fp = dm.face_points[i*2+1];
                if (!face) {
                    console.log(dm.face_points[i*2]);
                    return;
                }
                if (doPoint) {
                    pt = this.points[dm.points[i]];
                    VBO.vbo_points[i*3] = pt[0];
                    VBO.vbo_points[i*3+1] = pt[1];
                    VBO.vbo_points[i*3+2] = pt[2];
                }
                if (doNormal) {
                    pt = face.point_normals[fp];
                    VBO.vbo_normals[i*3] = pt[0];
                    VBO.vbo_normals[i*3+1] = pt[1];
                    VBO.vbo_normals[i*3+2] = pt[2];
                }
                if (doColor) {
                    pt = face.point_colors[fp];
                    VBO.vbo_colors[i*3] = pt[0];
                    VBO.vbo_colors[i*3+1] = pt[1];
                    VBO.vbo_colors[i*3+2] = pt[2];
                }
                if (doUV) {
                    pt = face.uvs[fp];
                    VBO.vbo_uvs[i*2] = pt[0];
                    VBO.vbo_uvs[i*2+1] = pt[1];
                }
            }
        }
        
        return this;
    };
        
    void rebufferVBO(VBO, buffer, opt) {
        var gl = GLCore.gl;
        var hasSegments = (opt.segments!==undef)?true:false;
        var segments = opt.segments;
        
        
        if (opt.points) {
            gl.bindBuffer(gl.ARRAY_BUFFER, buffer.gl_points);
            gl.bufferData(gl.ARRAY_BUFFER, VBO.vbo_points, gl.DYNAMIC_DRAW);
        }
        
        if (opt.normals && VBO.vbo_normals) {
            gl.bindBuffer(gl.ARRAY_BUFFER, buffer.gl_normals);
            gl.bufferData(gl.ARRAY_BUFFER, VBO.vbo_normals, gl.DYNAMIC_DRAW);
        }
        
        if (opt.uvs && VBO.vbo_uvs) {
            gl.bindBuffer(gl.ARRAY_BUFFER, buffer.gl_uvs);
            gl.bufferData(gl.ARRAY_BUFFER, VBO.vbo_uvs, gl.DYNAMIC_DRAW);
        }
        
        if (opt.colors && VBO.vbo_colors) {
            gl.bindBuffer(gl.ARRAY_BUFFER, buffer.gl_colors);
            gl.bufferData(gl.ARRAY_BUFFER, VBO.vbo_colors, gl.DYNAMIC_DRAW);
        }
        
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
        
        return this;
    };
        */
        // take a compiled VBO from compileVBO() and create a mesh buffer object for bindBuffer(), fuse with baseBuffer overlay if provided
    compiledVBOBuffer *bufferVBO(compiledVBO *VBO) { // , baseBuffer
        
        compiledVBOBuffer *buffer = new compiledVBOBuffer;
//        if (baseBuffer === undef) baseBuffer = {};

        glGenVertexArrays(1, &buffer->vao);
        
        glGenBuffers(1, &buffer->gl_points);
        glBindBuffer(GL_ARRAY_BUFFER, buffer->gl_points);
        glBufferData(GL_ARRAY_BUFFER, VBO->vbo_points.size()*sizeof(vec3), VBO->vbo_points.data(), GL_STATIC_DRAW);
        
        if (VBO->vbo_normals.size()) {
            glGenBuffers(1, &buffer->gl_normals);
            glBindBuffer(GL_ARRAY_BUFFER, buffer->gl_normals);
            glBufferData(GL_ARRAY_BUFFER, VBO->vbo_normals.size()*sizeof(vec3), VBO->vbo_normals.data(), GL_STATIC_DRAW);
        }
//        else {
//            buffer.gl_normals = baseBuffer.gl_normals ? baseBuffer.gl_normals : null;
//        }
        
        if (VBO->vbo_uvs.size()) {
            glGenBuffers(1, &buffer->gl_uvs);
            glBindBuffer(GL_ARRAY_BUFFER, buffer->gl_uvs);
            glBufferData(GL_ARRAY_BUFFER, VBO->vbo_uvs.size()*sizeof(vec2), VBO->vbo_uvs.data(), GL_STATIC_DRAW);
        }
//        else {
//            buffer.gl_uvs = baseBuffer.gl_uvs ? baseBuffer.gl_uvs : null;
//        }
        
        if (VBO->vbo_colors.size()) {
            glGenBuffers(1, &buffer->gl_colors);
            glBindBuffer(GL_ARRAY_BUFFER, buffer->gl_colors);
            glBufferData(GL_ARRAY_BUFFER, VBO->vbo_colors.size()*sizeof(vec3), VBO->vbo_colors.data(), GL_STATIC_DRAW);
        }
//        else {
//            buffer.gl_colors = baseBuffer.gl_colors ? baseBuffer.gl_colors : null;
//        }
        
//        if (!VBO.vbo_elements && baseBuffer.gl_elements) {
//            buffer.gl_elements = baseBuffer.gl_elements;
//            buffer.elements_ref = baseBuffer.elements_ref;
//        } else {
            if (VBO->vbo_elements.size()) {
                glGenBuffers(1, &buffer->gl_elements);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->gl_elements);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, VBO->vbo_elements.size()*sizeof(unsigned int), VBO->vbo_elements.data(), GL_STATIC_DRAW);
            }
        
            compiledVBOElementsRefI ref_i;
            compiledVBOElementsRefJ ref_j;
        
        buffer->elements_ref.resize(VBO->elements_ref.size());
        unsigned long i = 0;
        for (ref_i = VBO->elements_ref.begin(); ref_i != VBO->elements_ref.end(); ref_i++) {
            for (ref_j = (*ref_i).begin(); ref_j != (*ref_i).end(); ref_j++) {
                buffer->elements_ref[i].push_back(*ref_j);
            }
        }
        
        
//        }
        
//        if (!VBO.vbo_line_elements && baseBuffer.gl_line_elements) {
//            buffer.gl_line_elements = baseBuffer.gl_line_elements;
//            buffer.line_elements_ref = baseBuffer.line_elements_ref;
//        } else if (VBO.vbo_line_elements){
//            buffer.gl_line_elements = gl.createBuffer();
//            gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.gl_line_elements);
//            gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, VBO.vbo_line_elements, gl.STATIC_DRAW);
//            buffer.line_elements_ref = VBO.line_elements_ref;
//        }
        
//        if (!VBO.vbo_lines && baseBuffer.gl_lines) {
//            buffer.gl_lines = baseBuffer.gl_lines;
//        } else if (VBO.vbo_lines) {
//            buffer.gl_lines = gl.createBuffer();
//            gl.bindBuffer(gl.ARRAY_BUFFER, buffer.gl_lines);
//            gl.bufferData(gl.ARRAY_BUFFER, VBO.vbo_lines, gl.STATIC_DRAW);
//            buffer.line_elements_ref = VBO.line_elements_ref;
//        } else {
//            buffer.gl_lines = null;
//        }
        
//        if (!VBO.vbo_line_colors && baseBuffer.gl_line_colors) {
//            buffer.gl_line_colors = baseBuffer.gl_line_colors;
//        } else if (VBO.vbo_line_colors) {
//            buffer.gl_line_colors = gl.createBuffer();
//            gl.bindBuffer(gl.ARRAY_BUFFER, buffer.gl_line_colors);
//            gl.bufferData(gl.ARRAY_BUFFER, VBO.vbo_line_colors, gl.STATIC_DRAW);
//        } else {
//            buffer.gl_line_colors = null;
//        }
        
//        if (!VBO.vbo_line_uvs && baseBuffer.gl_line_uvs) {
//            buffer.gl_line_uvs = baseBuffer.gl_line_uvs;
//        } else if (VBO.vbo_line_uvs){
//            buffer.gl_line_uvs = gl.createBuffer();
//            gl.bindBuffer(gl.ARRAY_BUFFER, buffer.gl_line_uvs);
//            gl.bufferData(gl.ARRAY_BUFFER, VBO.vbo_line_uvs, gl.STATIC_DRAW);
//        } else {
//            buffer.gl_line_uvs = null;
//        }
        
//        if (!VBO.vbo_line_normals && baseBuffer.gl_line_normals) {
//            buffer.gl_line_normals = baseBuffer.gl_line_normals;
//        } else if (VBO.vbo_line_normals) {
//            buffer.gl_line_normals = gl.createBuffer();
//            gl.bindBuffer(gl.ARRAY_BUFFER, buffer.gl_line_normals);
//            gl.bufferData(gl.ARRAY_BUFFER, VBO.vbo_line_normals, gl.STATIC_DRAW);
//        } else {
//            buffer.gl_line_normals = null;
//        }
        
        buffer->segments.resize(VBO->segments.size());
        copy(VBO->segments.begin(), VBO->segments.end(), buffer->segments.begin());
        buffer->bounds = VBO->bounds;
//        buffer.unrolled = VBO.unrolled;
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
        
        return buffer;
    };
        /*
    void update(opt) {
        opt = opt||{};
        
        var doPoint = true;
        if (opt.points !== undef) {
            doPoint = opt.points;
        }
        var doUV = opt.uvs||opt.uv||opt.texture||opt.all||false;
        
        var doNormal = true;
        if (opt.normals !== undef) {
            doNormal = opt.normals;
        }
        var doColor = opt.colors||opt.color||opt.all||false;
        var segments = opt.segments||opt.segment;
        if (segments !== undef && segments.length === undef) {
            segments = [segments];
        }
        
        if (!this.dynamic) {
            log("Mesh not defined as dynamic, cannot update.");
            return false;
        }
        if (doNormal && this.normalMapRef) {
            this.recalcNormals(undef,{segments: segments});
        }
        
        var options = { points: doPoint, uvs: doUV, normals: doNormal, colors: doColor, segments: segments };
        
        this.updateVBO(this.dynamicData.VBO,options);
        this.rebufferVBO(this.dynamicData.VBO,this.dynamicData.buffer,options);
    };
         */
        
    // bind a bufferVBO object result to the mesh
    void bindBuffer(compiledVBOBuffer *vbo_buffer) {
//        if (this.originBuffer === null) {
//            this.originBuffer = vbo_buffer;
//        }
        
        compiledBuffer = vbo_buffer;

        unsigned long i,iMax,maxSegments = 0;
        
        for (i = 0, iMax = vbo_buffer->segments.size(); i < iMax; i++) {
            if (vbo_buffer->segments[i] < maxSegments) maxSegments = vbo_buffer->segments[i];
        }

        
        segment_state.init((unsigned int)maxSegments);
        for (i = 0, iMax = vbo_buffer->segments.size(); i < iMax; i++) {
            segment_state.set((unsigned int)vbo_buffer->segments[i]);
        }
        bb = vbo_buffer->bounds;
    };
        // Do the works
    void compile(__float tolerance=0.00001f) {
        if (faces.size() > 0 && points.size() > 0 ) {
            
            compileMapVBO *VBOMap = compileMap(tolerance);
            if (dynamic) {
                compileMap_ = VBOMap;
            }
            compiledVBO *VBO = compileVBO(VBOMap);
            if (!dynamic) {
                delete VBOMap;
            }
            compiledVBOBuffer *buffer = bufferVBO(VBO);
            bindBuffer(buffer);
//            if (this.dynamic) {
//                this.sourcePoints = [];
//                for (var i = 0, iMax = this.points.length; i<iMax; i++) {
//                    this.sourcePoints[i] = this.points[i].slice(0);
//                }
//                this.dynamicData = {
//                VBO: VBO,
//                buffer: buffer
//                };
//            }
        }
    };
        
//    addMorphTarget: function (targetBuffer) {
//        if (this.morphTargets === null) {
//            this.morphTargets = [];
//        }
//        this.morphTargets.push(targetBuffer);
//    },
//        
//    setMorphSource: function (idx) {
//        if (this.morphSourceIndex === idx) return;
//        this.morphSourceIndex = idx;
//        this.bindBuffer(this.morphTargets[idx]);
//    },
//        
//    setMorphTarget: function (idx) {
//        if (this.morphTargetIndex === idx) return;
//        this.morphTargetIndex = idx;
//        this.morphTarget = this.morphTargets[idx];
//    },
//        
//    setMorphWeight: function (weight) {
//        this.morphWeight = weight;
//    },
//        
//    morphTargetCount: function () {
//        return (this.morphTargets !== null) ? this.morphTargets.length : 0;
//    }

         };
}

#endif /* defined(__CubicVR2__Mesh__) */
