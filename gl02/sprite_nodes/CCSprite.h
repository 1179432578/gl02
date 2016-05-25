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

class CCSprite : public CCNode{
public:
    int m_height;
    int m_width;
    float posX;
    float posY;
    
    GLuint m_tex; //纹理id
    
    GLuint m_program;   //着色程序
    
    //    矩形四个角坐标
    //    平移向量
    //    旋转
    //    缩放
    //    位置 旋转 缩放中心
    
    
    
    //    创建节点
    static CCSprite * create(const char *filename);

    virtual void draw();
    
//    void setShaderPrograma();
    
//    初始化 初始化变量以及着色程序
    void initWithFile(const char *filename);
    
    
    //    void setRotation(float fRotation);
    //    float getRotation();
    //
    //    void setScale(float scale);
    //    float getScale();
    
    // quadrangle
    // vertex coords, texture coords and color info
    ccV3F_C4B_T2F_Quad m_sQuad;
    
    GLuint            m_uVertShader;
    GLuint            m_uFragShader;
    GLint             m_mvp;
    
    //纹理大小
    CCRect m_obRect;
    //偏移位置
    CCPoint m_obOffsetPosition;
};

#endif /* LNode_hpp */
