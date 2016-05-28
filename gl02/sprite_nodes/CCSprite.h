//
//  LNode.hpp
//  gl02
//
//  Created by 鲁飞 on 16/4/6.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef LNode_hpp1
#define LNode_hpp1

#include "GLUT/glut.h"
#include "CCPoint.h"
#include "ccTypes.h"
#include "CCNode.h"
#include "CCTexture2D.h"

class CCSprite : public CCNode{
public:
    /*精灵创建的三种方法:用图片、用纹理、用精灵帧
     *对应的有3种初始化方法,最终都用到纹理初始化
     */
    
    //指定图片创建精灵
    static CCSprite * create(const char *filename);
    bool initWithFile(const char *filename);
    bool initWithTexture(CCTexture2D *pTexture, const CCRect& rect, bool rotated);
   
    virtual void draw();
    
    //    void setRotation(float fRotation);
    //    float getRotation();
    //    void setScale(float scale);
    //    float getScale();
    
    // quadrangle
    // vertex coords, texture coords and color info
    ccV3F_C4B_T2F_Quad m_sQuad;
    
    GLuint            m_uVertShader;
    GLuint            m_uFragShader;
    GLint             m_mvp;
    
    int m_height;
    int m_width;
    float posX;
    float posY;
    
    CCTexture2D*       m_pobTexture;
    GLuint m_tex; //纹理id
    GLuint m_program;   //着色程序
    
    //纹理大小
    CCRect m_obRect;
    //偏移位置
    CCPoint m_obOffsetPosition;
};

#endif /* LNode_hpp */
