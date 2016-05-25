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
, m_fScaleX(1.0f)
, m_fScaleY(1.0f)
, m_obPosition(CCPointZero)
//, m_fSkewX(0.0f)
//, m_fSkewY(0.0f)
, m_obAnchorPointInPoints(CCPointZero)
, m_obAnchorPoint(CCPointZero)
, m_obContentSize(CCSizeZero)
,m_bIgnoreAnchorPointForPosition(false)
{
}

CCNode::~CCNode(){

}

//  在draw前计算仿射矩阵
void CCNode::transform(){
    //    仿射矩阵
    //    CCAffineTransform CCNode::nodeToParentTransform(void)
    
    
    //    下面是没有用到着色程序时的调用函数进行矩阵的设置
    //    设置平移矩阵
    
    
    //    设置缩放矩阵
    
    //    设置旋转矩阵
    
/*----------------------------------------------------------*
 *    cocs2dx: void CCNode::transform()                     *
 *----------------------------------------------------------*/
//    kmMat4 transfrom4x4;
//    
//    // Convert 3x3 into 4x4 matrix
//    CCAffineTransform tmpAffine = this->nodeToParentTransform();//这个是变换的重点
//    CGAffineToGL(&tmpAffine, transfrom4x4.mat);//转化到opengl中1d数组
//    
//    // Update Z vertex manually
//    transfrom4x4.mat[14] = m_fVertexZ;
//    
//    kmGLMultMatrix( &transfrom4x4 );
//    
//    
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
    
    //  设置mvp矩阵
/*
 A 4x4 matrix
 
        | 0   4   8  12 |
 mat =  | 1   5   9  13 |
        | 2   6  10  14 |
        | 3   7  11  15 |
 */
    Matrix44 matrixArray = {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 1};

     mglMultMatrix(&matrixArray);
}

void CCNode::visit(){
    //    不可见返回
    
    //    复制栈顶矩阵kmGLPushMatrix
    
    //    计算变换矩阵
    transform();
    
    //    遍历zorder<0的节点visit
    
    //    draw
    draw();
    
    //    遍历zorder>0的节点visit
    
    //    弹出栈顶矩阵kmGLPopMatrix
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
}

Matrix44 CCNode::nodeToParentTransform(void){
//    if (m_bTransformDirty)//变换改变了，提高效率
    {
        
        // Translate values
        //世界坐标系坐标
        float x = m_obPosition.x;
        float y = m_obPosition.y;
        
        //如果忽略锚点， 要把x、y减去的加上，后面把锚点带入计算的
        if (m_bIgnoreAnchorPointForPosition)
        {
            x += m_obAnchorPointInPoints.x;
            y += m_obAnchorPointInPoints.y;
        }
        
        // Rotation values
        // Change rotation code to handle X and Y
        // If we skew with the exact same value for both x and y then we're simply just rotating
        float cx = 1, sx = 0, cy = 1, sy = 0;//没旋转的时候的值cos0=1 sin0=0 旋转角只有1个cx==cy sx==sy
        //如果进行了旋转
        //绕z轴转动，opengl里的沿z正向逆时针转动为正方向，这里相反,所以角度前加个负号转化成opengl里的角度
        //先计算cx = cosx sx = sinx etc.
        if (m_fRotationX || m_fRotationY)
        {
//            float radiansX = -CC_DEGREES_TO_RADIANS(m_fRotationX);
//            float radiansY = -CC_DEGREES_TO_RADIANS(m_fRotationY);
            float radiansX = -m_fRotationX / 180 * M_PI;
            float radiansY = -m_fRotationY / 180 * M_PI;
            cx = cosf(radiansX);
            sx = sinf(radiansX);
            cy = cosf(radiansY);
            sy = sinf(radiansY);
        }
        
        //后面添加斜切变换
//        bool needsSkewMatrix = ( m_fSkewX || m_fSkewY );
        bool needsSkewMatrix = false;
        
        // optimization:
        // inline anchor point calculation if skew is not needed
        // Adjusted transform calculation for rotational skew
        if (! needsSkewMatrix && !m_obAnchorPointInPoints.equals(CCPointZero))
        {
            x += cy * -m_obAnchorPointInPoints.x * m_fScaleX + -sx * -m_obAnchorPointInPoints.y * m_fScaleY;
            y += sy * -m_obAnchorPointInPoints.x * m_fScaleX +  cx * -m_obAnchorPointInPoints.y * m_fScaleY;
        }
        
        
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
    
    return m_sTransform;

}