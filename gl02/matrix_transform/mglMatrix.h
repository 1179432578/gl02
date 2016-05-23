//
//  mglMatrix.hpp
//  gl02
//
//  Created by 鲁飞 on 16/5/23.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef mglMatrix_hpp
#define mglMatrix_hpp

#include <stdio.h>
#include "MatrixStack.h"

//提供对gl矩阵操作的支持

#define KM_GL_MODELVIEW 0x1700
#define KM_GL_PROJECTION 0x1701
#define KM_GL_TEXTURE 0x1702

typedef unsigned int kmGLEnum;

//void  kmGLFreeAll(void);
void  mglPushMatrix(void);
void  mglPopMatrix(void);
void  mglMatrixMode(kmGLEnum mode);
void  mglLoadIdentity(void);
//void  kmGLLoadMatrix(const kmMat4* pIn);
void  mglMultMatrix(const Matrix44* pIn);
//void  kmGLTranslatef(float x, float y, float z);
//void  kmGLRotatef(float angle, float x, float y, float z);
//void  kmGLScalef(float x, float y, float z);
void  mglGetMatrix(kmGLEnum mode, Matrix44* pOut);
    

#endif /* mglMatrix_hpp */
