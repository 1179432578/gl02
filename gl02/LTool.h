//
//  LTool.h
//  gl02
//
//  Created by 鲁飞 on 15/8/14.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef __gl02__LTool__
#define __gl02__LTool__

#include "GLUT/glut.h"

void initCT();

void scale2f(float sx, float sy);

void translate2f(float dx, float dy);

void rotate2f(float angle);

void pushCT();

void popCT();

#endif /* defined(__gl02__LTool__) */
