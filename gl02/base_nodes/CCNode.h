//
//  CCNode.hpp
//  gl02
//
//  Created by lewis on 16/4/17.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCNode_hpp
#define CCNode_hpp

#include "CCGLProgram.h"
#include "CCGeometry.h"

class CCNode{
public:
    CCNode();
    
    virtual ~CCNode();
    
    // 遍历子节点并且call draw()
    virtual void visit();
    
    // 计算变化矩阵
    void transform();
    
    // 渲染节点
    virtual void draw();
    
    virtual void setShaderProgram(CCGLProgram *pShaderProgram);
    virtual CCGLProgram* getShaderProgram();
    
    virtual void setAnchorPoint(const CCPoint& point);
    
    virtual const CCPoint& getPosition();
    virtual void setPosition(const CCPoint& newPosition);
public:
    CCGLProgram *m_pShaderProgram;
    
protected:
    //node 位置
    CCPoint m_obPosition;
    //node的锚点 （200,300）
    CCPoint m_obAnchorPointInPoints;
    //node的锚点 （0.5, 0.5）
    CCPoint m_obAnchorPoint;
    
    //node的逻辑大小 不是纹理大小
    CCSize m_obContentSize;
};

#endif /* CCNode_hpp */
