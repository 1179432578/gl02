//
//  Matrix.cpp
//  LImage
//
//  Created by lewis on 16/5/8.
//  Copyright © 2016年 lewis. All rights reserved.
//



#include <math.h>
#include "Matrix.h"
#include <string.h>

Matrix44 multiply(Matrix44 *ma, Matrix44 *mb){
    Matrix44 mc;
    mc.m11 = ma->m11 * mb->m11 + ma->m12 * mb->m21 + ma->m13 * mb->m31 + ma->m14 * mb->m41;
    mc.m12 = ma->m11 * mb->m12 + ma->m12 * mb->m22 + ma->m13 * mb->m32 + ma->m14 * mb->m42;
    mc.m13 = ma->m11 * mb->m13 + ma->m12 * mb->m23 + ma->m13 * mb->m33 + ma->m14 * mb->m43;
    mc.m14 = ma->m11 * mb->m14 + ma->m12 * mb->m24 + ma->m13 * mb->m34 + ma->m14 * mb->m44;
    
    mc.m21 = ma->m21 * mb->m11 + ma->m22 * mb->m21 + ma->m23 * mb->m31 + ma->m24 * mb->m41;
    mc.m22 = ma->m21 * mb->m12 + ma->m22 * mb->m22 + ma->m23 * mb->m32 + ma->m24 * mb->m42;
    mc.m23 = ma->m21 * mb->m13 + ma->m22 * mb->m23 + ma->m23 * mb->m33 + ma->m24 * mb->m43;
    mc.m24 = ma->m21 * mb->m14 + ma->m22 * mb->m24 + ma->m23 * mb->m34 + ma->m24 * mb->m44;
    
    mc.m31 = ma->m31 * mb->m11 + ma->m32 * mb->m21 + ma->m33 * mb->m31 + ma->m34 * mb->m41;
    mc.m32 = ma->m31 * mb->m12 + ma->m32 * mb->m22 + ma->m33 * mb->m32 + ma->m34 * mb->m42;
    mc.m33 = ma->m31 * mb->m13 + ma->m32 * mb->m23 + ma->m33 * mb->m33 + ma->m34 * mb->m43;
    mc.m34 = ma->m31 * mb->m14 + ma->m32 * mb->m24 + ma->m33 * mb->m34 + ma->m34 * mb->m44;
    
    mc.m41 = ma->m41 * mb->m11 + ma->m42 * mb->m21 + ma->m43 * mb->m31 + ma->m44 * mb->m41;
    mc.m42 = ma->m41 * mb->m12 + ma->m42 * mb->m22 + ma->m43 * mb->m32 + ma->m44 * mb->m42;
    mc.m43 = ma->m41 * mb->m13 + ma->m42 * mb->m23 + ma->m43 * mb->m33 + ma->m44 * mb->m43;
    mc.m44 = ma->m41 * mb->m14 + ma->m42 * mb->m24 + ma->m43 * mb->m34 + ma->m44 * mb->m44;
    
    return mc;
}

Vector4 multiply(Vector4 *v, Matrix44 *m){
    Vector4 ret;
    
    ret.x = v->x * m->m11 + v->y * m->m21 + v->z * m->m31 + v->w * m->m41;
    ret.y = v->x * m->m12 + v->y * m->m22 + v->z * m->m32 + v->w * m->m42;
    ret.z = v->x * m->m13 + v->y * m->m23 + v->z * m->m33 + v->w * m->m43;
    ret.w = v->x * m->m14 + v->y * m->m24 + v->z * m->m34 + v->w * m->m44;
    
    return ret;
}

void print(Vector4 *v){
    printf("Vector4:%f %f %f %f\n", v->x, v->y, v->z, v->w);
}

void print(Matrix44 *m){
    printf("Matrix44:\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
           m->m11, m->m12, m->m13, m->m14,
           m->m21, m->m22, m->m23, m->m24,
           m->m31, m->m32, m->m33, m->m34,
           m->m41, m->m42, m->m43, m->m44);
}

Matrix44* const mat4Assign(Matrix44* pOut, const Matrix44* pIn){
//    assert(pOut != pIn && "You have tried to self-assign!!");
    
    memcpy(pOut, pIn, sizeof(float) * 16);
    
    return pOut;
}

Matrix44* const mat4Identity(Matrix44* pOut){
    memset(pOut, 0, sizeof(float) * 16);
//    pOut->mat[0] = pOut->mat[5] = pOut->mat[10] = pOut->mat[15] = 1.0f;
    pOut->m11 = pOut->m22 = pOut->m33 = pOut->m44 = 1.0f;
    return pOut;
}

Matrix44* const mat4Multiply(Matrix44* pOut, const Matrix44* ma, const Matrix44* mb){
    Matrix44 mc;
    mc.m11 = ma->m11 * mb->m11 + ma->m12 * mb->m21 + ma->m13 * mb->m31 + ma->m14 * mb->m41;
    mc.m12 = ma->m11 * mb->m12 + ma->m12 * mb->m22 + ma->m13 * mb->m32 + ma->m14 * mb->m42;
    mc.m13 = ma->m11 * mb->m13 + ma->m12 * mb->m23 + ma->m13 * mb->m33 + ma->m14 * mb->m43;
    mc.m14 = ma->m11 * mb->m14 + ma->m12 * mb->m24 + ma->m13 * mb->m34 + ma->m14 * mb->m44;
    
    mc.m21 = ma->m21 * mb->m11 + ma->m22 * mb->m21 + ma->m23 * mb->m31 + ma->m24 * mb->m41;
    mc.m22 = ma->m21 * mb->m12 + ma->m22 * mb->m22 + ma->m23 * mb->m32 + ma->m24 * mb->m42;
    mc.m23 = ma->m21 * mb->m13 + ma->m22 * mb->m23 + ma->m23 * mb->m33 + ma->m24 * mb->m43;
    mc.m24 = ma->m21 * mb->m14 + ma->m22 * mb->m24 + ma->m23 * mb->m34 + ma->m24 * mb->m44;
    
    mc.m31 = ma->m31 * mb->m11 + ma->m32 * mb->m21 + ma->m33 * mb->m31 + ma->m34 * mb->m41;
    mc.m32 = ma->m31 * mb->m12 + ma->m32 * mb->m22 + ma->m33 * mb->m32 + ma->m34 * mb->m42;
    mc.m33 = ma->m31 * mb->m13 + ma->m32 * mb->m23 + ma->m33 * mb->m33 + ma->m34 * mb->m43;
    mc.m34 = ma->m31 * mb->m14 + ma->m32 * mb->m24 + ma->m33 * mb->m34 + ma->m34 * mb->m44;
    
    mc.m41 = ma->m41 * mb->m11 + ma->m42 * mb->m21 + ma->m43 * mb->m31 + ma->m44 * mb->m41;
    mc.m42 = ma->m41 * mb->m12 + ma->m42 * mb->m22 + ma->m43 * mb->m32 + ma->m44 * mb->m42;
    mc.m43 = ma->m41 * mb->m13 + ma->m42 * mb->m23 + ma->m43 * mb->m33 + ma->m44 * mb->m43;
    mc.m44 = ma->m41 * mb->m14 + ma->m42 * mb->m24 + ma->m43 * mb->m34 + ma->m44 * mb->m44;
    
    memcpy(pOut, &mc, sizeof(float)*16);
    
    return pOut;

}