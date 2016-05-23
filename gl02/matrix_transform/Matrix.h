//
//  Matrix.hpp
//  LImage
//
//  Created by lewis on 16/5/8.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>

//从三维世界到二维世界变换，从浮点类型到整型变换
//
//局部坐标系(物体自己的坐标系)-》世界坐标-》模型视图坐标（摄像机坐标系坐标）-》摄像机投影平面（一个规格化的平面）-》视口平面(窗口的以部分或者全部)
//
//从世界坐标到摄像机坐标，顶点为浮点数。光栅化的视口平面由一个点的整数坐标求出它在规格化平面的浮点坐标，然后求由摄像机原点通过该点
//的射线与摄像机坐标系中多边形的交点。这个交点就是要被光栅化的一点，它存储了相关信息用于光栅化

struct Vector4{
    float x, y, z, w;
};

struct Matrix44{
    float m11, m12, m13, m14,
    m21, m22, m23, m24,
    m31, m32, m33, m34,
    m41, m42, m43, m44;
};

Matrix44 multiply(Matrix44 *ma, Matrix44 *mb);

Vector4 multiply(Vector4 *v, Matrix44 *m);

//产生一个单位矩阵
Matrix44 normalMatrix();

void print(Vector4 *v);
void print(Matrix44 *m);

//矩阵常见操作
Matrix44* const mat4Assign(Matrix44* pOut, const Matrix44* pIn);

Matrix44* const mat4Identity(Matrix44* pOut);

Matrix44* const mat4Multiply(Matrix44* pOut, const Matrix44* pM1, const Matrix44* pM2);

#endif /* Matrix_hpp */



