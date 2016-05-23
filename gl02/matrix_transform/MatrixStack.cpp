//
//  MatrixStack.cpp
//  gl02
//
//  Created by 鲁飞 on 16/5/23.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "MatrixStack.h"

#define INITIAL_SIZE 30
#define INCREMENT 50

void stackInitialize(MatrixStack* stack){
    stack->arr = new Matrix44[INITIAL_SIZE];
    stack->capacity = INITIAL_SIZE;
    stack->size = 0;
    stack->top = NULL;
}

void stackPush(MatrixStack* stack, const Matrix44* item){
    //占满检查，如果满了分配新空间存储
    
    stack->top = &stack->arr[stack->size++];
    mat4Assign(stack->top, item);
}

void stackPop(MatrixStack* stack, Matrix44* pOut){
//    assert(stack->item_count && "Cannot pop an empty stack");
    
    stack->top = &stack->arr[--stack->size - 1];
}

void stackRelease(MatrixStack* stack){
    delete [] stack->arr;
    stack->top = NULL;
    stack->size = 0;
    stack->capacity = 0;
}