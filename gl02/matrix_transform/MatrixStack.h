//
//  MatrixStack.hpp
//  gl02
//
//  Created by 鲁飞 on 16/5/23.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef MatrixStack_hpp
#define MatrixStack_hpp

#include <stdio.h>
#include "Matrix.h"

//操作矩阵的栈

struct MatrixStack{
    int capacity;
    int size;
    Matrix44 *top;
    Matrix44 *arr;
};

void stackInitialize(MatrixStack* stack);
void stackPush(MatrixStack* stack, const Matrix44* item);
void stackPop(MatrixStack* stack, Matrix44* pOut);
void stackRelease(MatrixStack* stack);

#endif /* MatrixStack_hpp */
