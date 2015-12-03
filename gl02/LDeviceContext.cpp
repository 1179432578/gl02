//
//  LDeviceContext.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/10.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "LDeviceContext.h"
#include "GLUT/glut.h"

void LDeviceContext::moveTo(LPoint2f p)
{
    this->m_currentPoint = p;
}

void LDeviceContext::lineTo(LPoint2f p)
{
    glBegin(GL_LINES);
    glVertex2f(this->m_currentPoint.x, this->m_currentPoint.y);
    glVertex2f(p.x, p.y);
    glEnd();
    glFlush();
    this->m_currentPoint = p;
}

void LDeviceContext::pixel(LPoint2f p){
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
    glFlush();
}

