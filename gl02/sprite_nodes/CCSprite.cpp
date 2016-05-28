//
//  LNode.cpp
//  gl02
//
//  Created by 鲁飞 on 16/4/6.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCSprite.h"
#include "CCGLProgram.h"
#include "ccShaders.h"
#include "CCGeometry.h"
#include "CCShaderCache.h"
#include <stddef.h>

void CCSprite::draw(){
      /*---------------------------------------------------------*/
    //    下面是一个节点的draw方法  一个sprite的draw方法
    //    visit是遍历节点的方法，它会遍历子节点，以及调用自己的draw方法
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    
    //    进行混合
    
    //    绑定激活纹理
    //    现在没有用了  必需设置shader program了(opengl 2.0 is cool)
    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_tex);
    glBindTexture(GL_TEXTURE_2D, m_pobTexture->getName());
    //    printf("tex%d\n", m_tex);
    
    //  开启顶点属性
    GLuint vao_id;
    glGenVertexArraysAPPLE(1, &vao_id);
    glBindVertexArrayAPPLE(vao_id);
    glEnableVertexAttribArray(kCCVertexAttrib_Position);
    glEnableVertexAttribArray(kCCVertexAttrib_Color);
    glEnableVertexAttribArray(kCCVertexAttrib_TexCoords);
    
    
#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
    long offset = 0;
    setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
    long offset = (long)&m_sQuad;
#endif // EMSCRIPTEN
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
//    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CHECK_GL_ERROR_DEBUG();
}

//    创建节点
CCSprite * CCSprite::create(const char *filename){
    CCSprite *ret = new CCSprite;
    ret->initWithFile(filename);

    return ret;
}

bool CCSprite::initWithFile(const char *filename){
    //创建纹理并把纹理加入到纹理缓存,然后用纹理初始化精灵

    CCTexture2D *pTexture = CCTexture2D::create(filename);

    CCRect rect = CCRectZero;
    rect.size = pTexture->getContentSize();
    
    return initWithTexture(pTexture, rect, false);
}

bool CCSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect, bool rotated)
{
    // default transform anchor: center
    setAnchorPoint(ccp(0.5f, 0.5f));
    
    // zwoptex default values
    m_obOffsetPosition = CCPointZero;

    // clean the Quad
    memset(&m_sQuad, 0, sizeof(m_sQuad));
    
    // Atlas: Color
    ccColor4B tmpColor = { 255, 255, 255, 255 };
    m_sQuad.bl.colors = tmpColor;
    m_sQuad.br.colors = tmpColor;
    m_sQuad.tl.colors = tmpColor;
    m_sQuad.tr.colors = tmpColor;
    
    // shader program
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    
    // update texture (calls updateBlendFunc)
    m_pobTexture = pTexture;
    setContentSize(rect.size);
    m_obRect = rect;
    
    CCTexture2D *tex = m_pobTexture;
    float left, right, top, bottom;
    float atlasWidth = (float)tex->getWidth();
    float atlasHeight = (float)tex->getHeight();
    left    = rect.origin.x/atlasWidth;
    right    = (rect.origin.x+rect.size.width) / atlasWidth;
    top     = rect.origin.y/atlasHeight;
    bottom    = (rect.origin.y+rect.size.height) / atlasHeight;
    
    m_sQuad.bl.texCoords.u = left;
    m_sQuad.bl.texCoords.v = bottom;
    m_sQuad.br.texCoords.u = right;
    m_sQuad.br.texCoords.v = bottom;
    m_sQuad.tl.texCoords.u = left;
    m_sQuad.tl.texCoords.v = top;
    m_sQuad.tr.texCoords.u = right;
    m_sQuad.tr.texCoords.v = top;
    
    //如果纹理比内容小 就会产生偏移了
    m_obOffsetPosition.x = (m_obContentSize.width - m_obRect.size.width) / 2;
    m_obOffsetPosition.y = (m_obContentSize.height - m_obRect.size.height) / 2;
    
    //设置顶点的坐标 他跟纹理
    float x1 = 0 + m_obOffsetPosition.x;
    float y1 = 0 + m_obOffsetPosition.y;
    float x2 = x1 + m_obRect.size.width;
    float y2 = y1 + m_obRect.size.height;
    
    // Don't update Z.
    m_sQuad.bl.vertices = vertex3(x1, y1, 0);
    m_sQuad.br.vertices = vertex3(x2, y1, 0);
    m_sQuad.tl.vertices = vertex3(x1, y2, 0);
    m_sQuad.tr.vertices = vertex3(x2, y2, 0);

    return true;
}