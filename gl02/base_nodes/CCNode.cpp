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

CCNode::CCNode(){
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
//        m_obAnchorPointInPoints = ccp(m_obContentSize.width * m_obAnchorPoint.x, m_obContentSize.height * m_obAnchorPoint.y );
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
