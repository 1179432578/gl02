//
//  mglMatrix.cpp
//  gl02
//
//  Created by 鲁飞 on 16/5/23.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "mglMatrix.h"
//gl02 使用行向量

//矩阵栈
MatrixStack modelview_matrix_stack;
MatrixStack projection_matrix_stack;
MatrixStack texture_matrix_stack;

MatrixStack* current_stack = NULL;

static bool initialized = false;

void lazyInitialize()
{
    if (!initialized) {
        initialized = true;
        
        //Initialize all 3 stacks
        stackInitialize(&modelview_matrix_stack);
        stackInitialize(&projection_matrix_stack);
        stackInitialize(&texture_matrix_stack);
        
        //set current stack
        current_stack = &modelview_matrix_stack;
        
        Matrix44 identity; //Temporary identity matrix
        mat4Identity(&identity);
        
        //Make sure that each stack has the identity matrix
        stackPush(&modelview_matrix_stack, &identity);
        stackPush(&projection_matrix_stack, &identity);
        stackPush(&texture_matrix_stack, &identity);
    }
}

//矩阵操作
//glPushMatrix() 拷贝栈顶元素到栈顶
//glPopMatrix() 把栈顶元素弹出
//glMatrixMode() 改变当前栈操作的栈 GL_PROJECTION GL_MODEVIEW
//glLoadIdentity () 设置当前栈顶元素设置为单位矩阵
// glLoadMatrixf(const GLfloat *m)设置当前栈顶元素为指定的值
//glMultMatrixf(const GLfloat *m)把m与当前矩阵相乘，用于列向量，行向量是当前矩阵与m相乘

void  mglMatrixMode(kmGLEnum mode){
    lazyInitialize();
    
    switch(mode)
    {
        case KM_GL_MODELVIEW:
            current_stack = &modelview_matrix_stack;
            break;
        case KM_GL_PROJECTION:
            current_stack = &projection_matrix_stack;
            break;
        case KM_GL_TEXTURE:
            current_stack = &texture_matrix_stack;
            break;
        default:
//            assert(0 && "Invalid matrix mode specified"); //TODO: Proper error handling
            break;
    }
}


void  mglPushMatrix(void){
    Matrix44 top;
    
    lazyInitialize(); //Initialize the stacks if they haven't been already
    
    //Duplicate the top of the stack (i.e the current matrix)
    mat4Assign(&top, current_stack->top);
    stackPush(current_stack, &top);
}

void  mglPopMatrix(void){
//    assert(initialized && "Cannot Pop empty matrix stack");
    //No need to lazy initialize, you shouldn't be popping first anyway!
    stackPop(current_stack, NULL);
}


void  mglLoadIdentity(void){
    lazyInitialize();
    
    mat4Identity(current_stack->top); //Replace the top matrix with the identity matrix
}

void  mglMultMatrix(const Matrix44* pIn){
    lazyInitialize();
//    mat4Multiply(current_stack->top, current_stack->top, pIn); //用于列向量
     mat4Multiply(current_stack->top, pIn, current_stack->top); //用于行向量
}

void  mglGetMatrix(kmGLEnum mode, Matrix44* pOut){
    lazyInitialize();
    
    switch(mode)
    {
        case KM_GL_MODELVIEW:
            mat4Assign(pOut, modelview_matrix_stack.top);
            break;
        case KM_GL_PROJECTION:
            mat4Assign(pOut, projection_matrix_stack.top);
            break;
        case KM_GL_TEXTURE:
            mat4Assign(pOut, texture_matrix_stack.top);
            break;
        default:
//            assert(1 && "Invalid matrix mode specified"); //TODO: Proper error handling
            break;
    }

}