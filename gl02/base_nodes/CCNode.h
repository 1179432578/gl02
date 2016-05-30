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
#include "Matrix.h"
#include "CCArray.h"

class CCAction;
class CCActionManager;

class CCNode : public CCObject{
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
    
    virtual void setScale(float scale);
    
    virtual void setRotation(float fRotation);
    
    virtual Matrix44 nodeToParentTransform(void);
    
    virtual void addChild(CCNode* child, int zOrder, int tag);
    virtual void onEnter();//触发脚本注册事件的回调
    virtual void onExit();
    
    virtual void sortAllChildren();
    
    //设置没有变换的大小 All nodes has a size. Layer and Scene has the same size of the screen.
    virtual void setContentSize(const CCSize& contentSize);
    //返回没有变换的大小
    virtual const CCSize& getContentSize() const;
    
    CCAction* runAction(CCAction* action);

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
    
    float  m_fScaleX;
    float  m_fScaleY;
    
    float  m_fRotationX;
    float  m_fRotationY;
    float  m_rotation;//旋转角度 度数
    
    Matrix44 m_obTransform;//模型变换矩阵
    
    bool m_bIgnoreAnchorPointForPosition;//默认false
    
    bool m_bRunning;//节点调用过了onEnter，被设置为true
    int m_nZOrder;//渲染循序
    CCArray *m_pChildren;
    CCNode *m_pParent;
    int m_nTag;
    
    CCActionManager *m_pActionManager;
};

#endif /* CCNode_hpp */
