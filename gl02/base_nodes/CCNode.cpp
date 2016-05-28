//
//  CCNode.cpp
//  gl02
//
//  Created by lewis on 16/4/17.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCNode.h"
#include "Matrix.h"
#include "mglMatrix.h"
#include <math.h>

CCNode::CCNode()
: m_fRotationX(0.0f)
, m_fRotationY(0.0f)
, m_rotation(0.0f)
, m_fScaleX(1.0f)
, m_fScaleY(1.0f)
, m_obPosition(CCPointZero)
//, m_fSkewX(0.0f)
//, m_fSkewY(0.0f)
, m_obAnchorPointInPoints(CCPointZero)
, m_obAnchorPoint(CCPointZero)
, m_obContentSize(CCSizeZero)
,m_bIgnoreAnchorPointForPosition(false)
,m_pChildren(NULL)
{
}

CCNode::~CCNode(){

}

/*
 A 4x4 matrix opengl矩阵
 
        | 0   4   8  12 |
 mat =  | 1   5   9  13 |
        | 2   6  10  14 |
        | 3   7  11  15 |
 */

//  在draw前计算仿射矩阵
void CCNode::transform(){
    Matrix44 matrix = this->nodeToParentTransform();

//    // Update Z vertex manually
//    transfrom4x4.mat[14] = m_fVertexZ;

    mglMultMatrix(&matrix);
    
//    // XXX: Expensive calls. Camera should be integrated into the cached affine matrix
//    if ( m_pCamera != NULL && !(m_pGrid != NULL && m_pGrid->isActive()) )
//    {
//        bool translate = (m_obAnchorPointInPoints.x != 0.0f || m_obAnchorPointInPoints.y != 0.0f);
//        
//        if( translate )
//            kmGLTranslatef(RENDER_IN_SUBPIXEL(m_obAnchorPointInPoints.x), RENDER_IN_SUBPIXEL(m_obAnchorPointInPoints.y), 0 );
//        
//        m_pCamera->locate();
//        
//        if( translate )
//            kmGLTranslatef(RENDER_IN_SUBPIXEL(-m_obAnchorPointInPoints.x), RENDER_IN_SUBPIXEL(-m_obAnchorPointInPoints.y), 0 );
//    }

//    Matrix44 matrixArray = {1, 0, 0, 0,
//        0, 1, 0, 0,
//        0, 0, 0, 0,
//        0, 0, 0, 1};
//
//     mglMultMatrix(&matrixArray);
}

void CCNode::visit(){
    //    不可见返回
    
    //复制栈顶矩阵kmGLPushMatrix
    mglPushMatrix();
    
    //计算变换矩阵
    transform();
    
    //draw
    if(m_pChildren && m_pChildren->count() > 0)
    {
        sortAllChildren();
        // draw children zOrder < 0
        CCObject **arr = m_pChildren->m_arr;
        CCNode* pNode = NULL;
        int i=0;
        for(; i < m_pChildren->m_count; i++)
        {
            pNode = (CCNode*)arr[i];
            if (pNode && pNode->m_nZOrder < 0){
                pNode->visit();
            }
            else{
                break;
            }
        }
        // self draw
        this->draw();
        
        for(; i < m_pChildren->m_count; i++)
        {
            pNode = (CCNode*)arr[i];
            if (pNode)
            {
                pNode->visit();
            }
        }
    }
    else
    {
        this->draw();
    }

    //弹出栈顶矩阵kmGLPopMatrix
    mglPopMatrix();
}

void CCNode::draw(){

}

void CCNode::setShaderProgram(CCGLProgram *pShaderProgram){
    m_pShaderProgram = pShaderProgram;

}

CCGLProgram* CCNode::getShaderProgram()
{
    return m_pShaderProgram;
}


void CCNode::setAnchorPoint(const CCPoint& point)
{
//    if( ! point.equals(m_obAnchorPoint))
//    {
        m_obAnchorPoint = point;
        m_obAnchorPointInPoints = CCPoint(m_obContentSize.width * m_obAnchorPoint.x, m_obContentSize.height * m_obAnchorPoint.y );
//        m_bTransformDirty = m_bInverseDirty = true;
//    }
}

const CCPoint& CCNode::getPosition()
{
    return m_obPosition;
}

void CCNode::setPosition(const CCPoint& newPosition)
{
    m_obPosition = newPosition;
//    m_bTransformDirty = m_bInverseDirty = true;
}

void CCNode::setScale(float scale)
{
    m_fScaleX = m_fScaleY = scale;
//    m_bTransformDirty = m_bInverseDirty = true;
}

void CCNode::setRotation(float newRotation)
{
    m_fRotationX = m_fRotationY = newRotation;
//    m_bTransformDirty = m_bInverseDirty = true;
    m_rotation = -newRotation / 180 * M_PI;//转化为opengl绕局部坐标系z轴转的度数
}

Matrix44 CCNode::nodeToParentTransform(void){
//    if (m_bTransformDirty)//变换改变了，提高效率
//    {
    
        // Translate values
//        //世界坐标系坐标
//        float x = m_obPosition.x;
//        float y = m_obPosition.y;
        
        //如果忽略锚点， 要把x、y减去的加上，后面把锚点带入计算的
//        if (m_bIgnoreAnchorPointForPosition)
//        {
//            x += m_obAnchorPointInPoints.x;
//            y += m_obAnchorPointInPoints.y;
//        }
        
        // Rotation values
        // Change rotation code to handle X and Y
        // If we skew with the exact same value for both x and y then we're simply just rotating
//        float cx = 1, sx = 0, cy = 1, sy = 0;//没旋转的时候的值cos0=1 sin0=0 旋转角只有1个cx==cy sx==sy
        //如果进行了旋转
        //绕z轴转动，opengl里的沿z正向逆时针转动为正方向，这里相反,所以角度前加个负号转化成opengl里的角度
        //先计算cx = cosx sx = sinx etc.
//        if (m_fRotationX || m_fRotationY)
//        {
////            float radiansX = -CC_DEGREES_TO_RADIANS(m_fRotationX);
////            float radiansY = -CC_DEGREES_TO_RADIANS(m_fRotationY);
//            float radiansX = -m_fRotationX / 180 * M_PI;
//            float radiansY = -m_fRotationY / 180 * M_PI;
//            cx = cosf(radiansX);
//            sx = sinf(radiansX);
//            cy = cosf(radiansY);
//            sy = sinf(radiansY);
//        }
        
        //后面添加斜切变换
//        bool needsSkewMatrix = ( m_fSkewX || m_fSkewY );
//        bool needsSkewMatrix = false;
        
        // optimization:
        // inline anchor point calculation if skew is not needed
        // Adjusted transform calculation for rotational skew
//        if (! needsSkewMatrix && !m_obAnchorPointInPoints.equals(CCPointZero))
//        {
//            x += cy * -m_obAnchorPointInPoints.x * m_fScaleX + -sx * -m_obAnchorPointInPoints.y * m_fScaleY;
//            y += sy * -m_obAnchorPointInPoints.x * m_fScaleX +  cx * -m_obAnchorPointInPoints.y * m_fScaleY;
//        }
        //局部坐标平移,确定缩放与旋转中心。一开始局部坐标系与世界坐标系重合节点左下角是原点
        float dx, dy;
        dx = m_bIgnoreAnchorPointForPosition ? 0 : -m_obAnchorPointInPoints.x;
        dy = m_bIgnoreAnchorPointForPosition ? 0 : -m_obAnchorPointInPoints.y;
        
        //在局部坐标系的缩放
        //m_fScaleX,m_fScaleX
        
        //在局部坐标系旋转-m_rotation
        float cosdelta = 1, sindelta = 0;
        if(m_rotation){
            cosdelta = cosf(m_rotation);
            sindelta = sinf(m_rotation);
        }
        
        //旋转缩放只在局部坐标系中进行
        //平移有两部分构成，一个是setposition设置在父节点(参考系)中位置，一个是锚点设置在局部坐标系中偏移
        //最终顶点在世界坐标系平移为局部坐标平移然后进行缩放旋转后加上世界坐标平移
        float dxInWorld = m_obPosition.x + cosdelta * m_fScaleX * dx - sindelta * m_fScaleY * dy;
        float dyInWorld = m_obPosition.y + sindelta * m_fScaleX * dx + cosdelta * m_fScaleY * dy;
        
        //最终矩阵 http://...
        m_obTransform = {cosdelta * m_fScaleX, sindelta * m_fScaleX, 0, 0,
                              -sindelta * m_fScaleY, cosdelta * m_fScaleY, 0, 0,
                                0, 0, 1, 0,
                                dxInWorld, dyInWorld, 0, 1};
//    print(&transform);
    
        // Build Transform Matrix
        // Adjusted transform calculation for rotational skew
        //构造一个矩阵，这里我构造一个自己定义的矩阵
//        m_sTransform = CCAffineTransformMake( cy * m_fScaleX,  sy * m_fScaleX,
//                                             -sx * m_fScaleY, cx * m_fScaleY,
//                                             x, y );
        
        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
//        if (needsSkewMatrix)
//        {
//            CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)),
//                                                                 tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f,
//                                                                 0.0f, 0.0f );
//            m_sTransform = CCAffineTransformConcat(skewMatrix, m_sTransform);
//            
//            // adjust anchor point
//            if (!m_obAnchorPointInPoints.equals(CCPointZero))
//            {
//                m_sTransform = CCAffineTransformTranslate(m_sTransform, -m_obAnchorPointInPoints.x, -m_obAnchorPointInPoints.y);
//            }
//        }
        
//        if (m_bAdditionalTransformDirty)
//        {
//            m_sTransform = CCAffineTransformConcat(m_sTransform, m_sAdditionalTransform);
//            m_bAdditionalTransformDirty = false;
//        }
        
//        m_bTransformDirty = false;
//    }
    
    return m_obTransform;

}

void CCNode::addChild(CCNode* child, int zOrder, int tag){
//    CCAssert( child != NULL, "Argument must be non-nil");
//    CCAssert( child->m_pParent == NULL, "child already added. It can't be added again");

    if (!m_pChildren) {
        m_pChildren = CCArray::create();
    }
    m_pChildren->addObject(child);
    
    child->m_nZOrder = zOrder;
    child->m_nTag = tag;
    child->m_pParent = this;

//    child->setOrderOfArrival(s_globalOrderOfArrival++);
    
    if(m_bRunning)//it's onEnter have been called
    {
        child->onEnter();
//        child->onEnterTransitionDidFinish();
    }

}

void CCNode::onEnter(){
    m_bRunning = true;
    
//    if (m_eScriptType != kScriptTypeNone)
//    {
//        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeNodeEvent(this, kCCNodeOnEnter);
//    }
    
    //它会调用子节点的onEnter，addChild也会调用，都是通过m_bRunning状态来进行的
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* child;
        CCNode* node;
//        CCARRAY_FOREACH(m_pChildren, child)
//        {
//            node = (CCNode*)child;
//            if (!node->isRunning())
//            {
//                node->onEnter();
//            }
//        }
        for (int i=0; i<m_pChildren->count(); i++) {
            node = (CCNode*)m_pChildren->objectAtIndex(i);
            if (!node->m_bRunning)
            {
                node->onEnter();
            }
        }
    }
    
//    this->resumeSchedulerAndActions();
}

void CCNode::onExit(){

}

//使用插入排序以zorder为关键字排序
void CCNode::sortAllChildren()
{
//    if (m_bReorderChildDirty)
//    {
//        int i,j,length = m_pChildren->data->num;
//        CCNode ** x = (CCNode**)m_pChildren->data->arr;
//        CCNode *tempItem;
//        
//        // insertion sort
//        for(i=1; i<length; i++)
//        {
//            tempItem = x[i];
//            j = i-1;
//            
//            //continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
//            while(j>=0 && ( tempItem->m_nZOrder < x[j]->m_nZOrder || ( tempItem->m_nZOrder== x[j]->m_nZOrder && tempItem->m_uOrderOfArrival < x[j]->m_uOrderOfArrival ) ) )
//            {
//                x[j+1] = x[j];
//                j = j-1;
//            }
//            x[j+1] = tempItem;
//        }
//
    int count = m_pChildren->m_count;
    CCNode **pArr = (CCNode**)m_pChildren->m_arr;
    CCNode *k;
    int j;
    for (int i=1; i<count; i++) {
        k = pArr[i];
        for (j=i-1; j>=0; j--) {
            if (pArr[j]->m_nZOrder > k->m_nZOrder) {
                pArr[j+1] = pArr[j];
            }
            else{
                break;
            }
        }
        
        pArr[j+1] = k;
    }
    
        
//        m_bReorderChildDirty = false;
//    }
}

/// contentSize getter
const CCSize& CCNode::getContentSize() const
{
    return m_obContentSize;
}

void CCNode::setContentSize(const CCSize & size)
{
    if (! size.equals(m_obContentSize))
    {
        m_obContentSize = size;
        
        m_obAnchorPointInPoints = ccp(m_obContentSize.width * m_obAnchorPoint.x, m_obContentSize.height * m_obAnchorPoint.y );
        //        m_bTransformDirty = m_bInverseDirty = true;
    }
}