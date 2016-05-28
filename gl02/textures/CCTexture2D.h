//
//  CCTexture2D.hpp
//  gl02
//
//  Created by lewis on 16/5/28.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCTexture2D_hpp
#define CCTexture2D_hpp

//用与向opengl服务器创建一个纹理

#include <stdio.h>
#include "CCObject.h"
#include "CCGeometry.h"
#include <GLUT/GLUT.h>

class CCTexture2D : public CCObject{
public:
    CCTexture2D(){};
    virtual ~CCTexture2D(){};
    
//    bool initWithImage(CCImage * uiImage);
    static CCTexture2D* create(const char *filename);
    bool initWithImage(const char *filename);
    
    const CCSize& getContentSize();
    
    unsigned int getWidth();
    unsigned int getHeight();
    
    GLuint getName();
protected:
    GLfloat m_fMaxS;
    GLfloat m_fMaxT;
    
    GLuint m_uName;//纹理ID
    
    unsigned int m_uHeight;
    unsigned int m_uWidth;
    
    CCSize m_obContentSize;
    
    
//    CCGLProgram*  m_pShaderProgram;
};

#endif /* CCTexture2D_hpp */
