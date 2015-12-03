//
//  LTool.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/14.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "LTool.h"

void initCT(){
    glMatrixMode(GL_MODELVIEW);
}

void scale2f(float sx, float sy){
    glMatrixMode(GL_MODELVIEW);
    glScalef(sx, sy, 1.0f);
}

void translate2f(float dx, float dy){
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(dx, dy, 0.0f);
}

void rotate2f(float angle){
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
}

void pushCT(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void popCT(){
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}