//
//  matrix_transform.hpp
//  LImage
//
//  Created by lewis on 16/5/15.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef matrix_transform_hpp
#define matrix_transform_hpp

#include <stdio.h>
#include "Matrix.h"
#include <math.h>
#include "Vector3.h"

//3d场景变换
//模型矩阵变换-》视图矩阵变换-》投影矩阵变换（规格化）-》视口矩阵变换（规格化）

//glTranslate multiply the current matrix by a translation matrix
//glRotate multiply the current matrix by a rotation matrix
//glLoadIdentity
//glScale

//模型变换矩阵
//opengl通过glMatrixMode(GL_MODELVIEW)指定操作模型视图矩阵
//生成一个平移矩阵
Matrix44 translate(float dx,float dy, float dz);

//生成一个绕过原点的向量旋转矩阵
Matrix44 rotate(float angle, float a, float b, float c);

//生成一个绕任意轴旋转矩阵

//观察变换矩阵
//opengl通过gluLookAt设置视点的位置以及观察方向生成一个观察矩阵
//http://www.360doc.com/content/14/0822/11/13726687_403784935.shtml
//eye眼睛位置 center观察点 up眼睛上面任意一点
//返回一个观察矩阵 注意矩阵乘法不满足交换律 但是满足结合律
Matrix44 mglLookAt(float eyeX,float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

//生成一个规格化的透视投影矩阵 该矩阵由投影变换矩阵与规格化变换矩阵合成
//http://www.cnblogs.com/cg_ghost/archive/2011/10/13/2210168.html
Matrix44 mgluPerspective(float fovy, float aspect, float zNear, float zFar);

//生成一个视口变换矩阵
//http://baike.baidu.com/link?url=Gtb449fxERqbdZbuGTg3ZYk4cQbIDi87LPNDIqUrLekOQTX6nKaiO9pXbvEJAxX_HNmRaAPjFTmnALsgp1SML_
//glViewport(GLint x,GLint y,GLsizei width,GLsizei height)
Matrix44 mglViewport(int x, int y, int width, int height);

//3d顶点坐标变换管道
void testVertexTransform(Vector4 vertex[], int n);
#endif /* matrix_transform_hpp */
