//
//  GLView.cpp
//  gl02
//
//  Created by 鲁飞 on 16/5/31.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "GLView.h"
#include <GLUT/GLUT.h>
#include "CCDirector.h"
#include "ccMacros.h"
#include <math.h>

GLView::GLView(){
    
}

static GLView *instance = NULL;
GLView* GLView::sharedOpenGLView()
{
    if (!instance) {
        instance = new GLView;
    }
    
    return instance;
}

const CCSize& GLView::getFrameSize() const{
    return m_obScreenSize;
}

void GLView::setFrameSize(float width, float height){
    //默认设计大小等于屏幕大小
    m_obDesignResolutionSize = m_obScreenSize = CCSizeMake(width, height);
    
    int argc = 0;
    const char **argv = NULL;
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("GLO2 2D Game Enginer");
    glEnable(GL_TEXTURE_2D);      // 启用纹理映射
}

CCSize GLView::getVisibleSize() const{
    if (m_eResolutionPolicy == kResolutionNoBorder)
    {
        return CCSizeMake(m_obScreenSize.width/m_fScaleX, m_obScreenSize.height/m_fScaleY);
    }
    else
    {
        return m_obDesignResolutionSize;
    }
}

CCPoint GLView::getVisibleOrigin() const{
    if (m_eResolutionPolicy == kResolutionNoBorder)
    {
        return CCPointMake((m_obDesignResolutionSize.width - m_obScreenSize.width/m_fScaleX)/2,
                           (m_obDesignResolutionSize.height - m_obScreenSize.height/m_fScaleY)/2);
    }
    else
    {
        return CCPointZero;
    }
}


void GLView::setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy){
//    CCAssert(resolutionPolicy != kResolutionUnKnown, "should set resolutionPolicy");
    
    m_obDesignResolutionSize.width = width;
    m_obDesignResolutionSize.height = height;
    
    m_fScaleX = m_obScreenSize.width / m_obDesignResolutionSize.width;
    m_fScaleY = m_obScreenSize.height / m_obDesignResolutionSize.height;
    
    //第一种情况是没有黑边，那么设计的绘图区域要充满整个屏幕，有可能宽或高方向超出屏幕
    if (resolutionPolicy == kResolutionNoBorder)
    {
        m_fScaleX = m_fScaleY = MAX(m_fScaleX, m_fScaleY);
    }
    
    //设计的绘图区域全部显示，但不超出屏幕，有可能有黑边
    if (resolutionPolicy == kResolutionShowAll)
    {
        m_fScaleX = m_fScaleY = MIN(m_fScaleX, m_fScaleY);
    }
    
    /*下面两个设计策略，考虑的以高跟宽为主的游戏，实际游戏制作中，完全可以自己定制策略*/
    
    //高是固定的，等比例缩放，设计窗口视口变换后不会超出屏幕
    if ( resolutionPolicy == kResolutionFixedHeight) {
        m_fScaleX = m_fScaleY;
        m_obDesignResolutionSize.width = ceilf(m_obScreenSize.width/m_fScaleX);
    }
    
    //宽是固定的，等比例缩放，设计窗口视口变换后不会超出屏幕
    if ( resolutionPolicy == kResolutionFixedWidth) {
        m_fScaleY = m_fScaleX;
        m_obDesignResolutionSize.height = ceilf(m_obScreenSize.height/m_fScaleY);
    }
    
    //设置视口区域大小，视口变换后，设计窗口是居中的
    float viewPortW = m_obDesignResolutionSize.width * m_fScaleX;
    float viewPortH = m_obDesignResolutionSize.height * m_fScaleY;
    m_obViewPortRect.setRect((m_obScreenSize.width - viewPortW) / 2, (m_obScreenSize.height - viewPortH) / 2, viewPortW, viewPortH);
    
    m_eResolutionPolicy = resolutionPolicy;
    
    // 设计窗口大小
    CCDirector::sharedDirector()->m_obWinSizeInPoints = getDesignResolutionSize();
//    CCDirector::sharedDirector()->createStatsLabel();
    //改变opengl的配置
    CCDirector::sharedDirector()->setGLDefaultValues();
}

const CCSize&  GLView::getDesignResolutionSize() const{
    return m_obDesignResolutionSize;
}

void GLView::setViewPortInPoints(float x , float y , float w , float h){
    glViewport((GLint)(x * m_fScaleX + m_obViewPortRect.origin.x),
               (GLint)(y * m_fScaleY + m_obViewPortRect.origin.y),
               (GLsizei)(w * m_fScaleX),
               (GLsizei)(h * m_fScaleY));
}

const CCRect& GLView::getViewPortRect() const{
    return m_obViewPortRect;
}

float GLView::getScaleX() const{
    return m_fScaleX;
}

float GLView::getScaleY() const{
    return m_fScaleY;
}
