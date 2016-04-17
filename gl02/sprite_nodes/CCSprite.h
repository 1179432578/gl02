//
//  LNode.hpp
//  gl02
//
//  Created by 鲁飞 on 16/4/6.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef LNode_hpp
#define LNode_hpp

#include "GLUT/glut.h"
#include "CCPoint.hpp"

class CCSprite {
public:
    int m_height;
    int m_width;
    float posX;
    float posY;
    
    GLuint m_tex; //纹理id
    
    CCPoint m_obPosition;   ///< position of the node
    
    GLuint m_program;   //着色程序
    
    //    矩形四个角坐标
    //    平移向量
    //    旋转
    //    缩放
    //    位置 旋转 缩放中心
    
    
    
    //    创建节点
    static CCSprite * create(const char *filename);
    
    
    void visit();
    void transform();
    //    节点渲染
    void draw();
    
    void setShaderProgram();
    
    void setPosition(float x, float y);
    const CCPoint& getPosition();
    
    
    //    void setRotation(float fRotation);
    //    float getRotation();
    //
    //    void setScale(float scale);
    //    float getScale();
};

#endif /* LNode_hpp */
