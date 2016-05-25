//
//  LNode.cpp
//  gl02
//
//  Created by 鲁飞 on 16/4/6.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCSprite.h"
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "CCGLProgram.h"
#include "ccShaders.h"
#include "CCGeometry.h"
#include "CCShaderCache.h"

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
    glBindTexture(GL_TEXTURE_2D, m_tex);
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
    
//    init...
    ret->initWithFile(filename);

    return ret;
}


//创建一个sprite，调用initWithFile-》initWithTexture
//initWithTexture 会设置很多东西  里面设置了着色程序 以及纹理
//CCSprite* CCSprite::create(const char *pszFileName, const CCRect& rect)
//{
//    CCSprite *pobSprite = new CCSprite();
//    if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
//    {
//        pobSprite->autorelease();
//        return pobSprite;
//    }
//    CC_SAFE_DELETE(pobSprite);
//    return NULL;
//}

void CCSprite::initWithFile(const char *filename){
    //创建纹理 并把纹理加入到纹理缓存
    //然后用纹理初始化精灵
//    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
//    if (pTexture)
//    {
//        CCRect rect = CCRectZero;
//        rect.size = pTexture->getContentSize();
//        return initWithTexture(pTexture, rect);
//    }
    
    //下面代码后面将移到CCTexture2D中去
    //    读取图片 获得图片像素数据与宽高
    //读取一个外部文件 并获得它的图片信息
    NSImage *img = [[NSImage alloc]initWithContentsOfFile:[[NSString alloc] initWithUTF8String:filename]];
    NSRect rt = NSMakeRect(0, 0, img.size.width , img.size.height);
    CGImageRef temImg = [img CGImageForProposedRect:&rt context:nil hints:nil];
    CGDataProviderRef pr = CGImageGetDataProvider(temImg);
    CFDataRef r = CGDataProviderCopyData(pr);
    void* data = (void*)CFDataGetBytePtr(r);
    m_height = CGImageGetHeight(temImg);
    m_width = CGImageGetWidth(temImg);
    
    //    生成纹理
    glGenTextures(1, &m_tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tex);
    
    //    纹理参数设置
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    //    纹理关联图片数据设置
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_height, m_width, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    //    释放图片像素数据， 纹理已经保存在显存中，渲染时gpu直接对纹理操作，图片数据不再需要保存在内存中了
    free((void*)data);
    
    // clean the Quad
    memset(&m_sQuad, 0, sizeof(m_sQuad));
    
    //  设置顶点的颜色
    // Atlas: Color
    ccColor4B tmpColor = { 255, 255, 255, 255 };
    m_sQuad.bl.colors = tmpColor;
    m_sQuad.br.colors = tmpColor;
    m_sQuad.tl.colors = tmpColor;
    m_sQuad.tr.colors = tmpColor;
    
    //    设置着色程序
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    
//    // update texture (calls updateBlendFunc)
//    setTexture(pTexture); //m_pobTexture = pTexture
//    setTextureRect(rect, rotated, rect.size);在这里面设置纹理坐标 顶点坐标
    
//    setTextureRect包含下面3行代码
//    setContentSize(untrimmedSize); 设置节点的内部大小
//    ！！！！！！！！这里设置节点逻辑大小
    m_obContentSize.width = m_width;
    m_obContentSize.height = m_height;
    
//    setVertexRect(rect); 设置纹理大小
    m_obRect.size.width = m_width;
    m_obRect.size.height = m_height;
    m_obRect.origin = CCPoint(0, 0);
    
//    setTextureCoords(rect); 设置纹理坐标
//    float atlasWidth = (float)tex->getPixelsWide();
//    float atlasHeight = (float)tex->getPixelsHigh();
//    left    = rect.origin.x/atlasWidth;
//    right    = (rect.origin.x+rect.size.height) / atlasWidth;
//    top        = rect.origin.y/atlasHeight;
//    bottom    = (rect.origin.y+rect.size.width) / atlasHeight;
    float left, right, top, bottom;
    left    = m_obRect.origin.x/m_obRect.size.width;
    right    = (m_obRect.origin.x + m_obRect.size.width) / m_obRect.size.width;
    top        = m_obRect.origin.y/m_obRect.size.height;
    bottom    = (m_obRect.origin.y + m_obRect.size.height) / m_obRect.size.height;
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
    
    //  设置顶点的坐标 他跟纹理
    float x1 = 0 + m_obOffsetPosition.x;
    float y1 = 0 + m_obOffsetPosition.y;
    float x2 = x1 + m_obRect.size.width;
    float y2 = y1 + m_obRect.size.height;
//    float x1 = 0.0f;
//    float y1 = 0.0f;
//    float x2 = 0.5f;
//    float y2 = 0.5f;
    
    
    // Don't update Z.
    m_sQuad.bl.vertices = vertex3(x1, y1, 0);
    m_sQuad.br.vertices = vertex3(x2, y1, 0);
    m_sQuad.tl.vertices = vertex3(x1, y2, 0);
    m_sQuad.tr.vertices = vertex3(x2, y2, 0);

    //  设置顶点纹理坐标
    
    
//
//    left    = 0.0f;
//    right    = 1.0;
//    top        = 0.0f;
//    bottom    = 1.0f;

    
//    m_sQuad.bl.texCoords.u = left;
//    m_sQuad.bl.texCoords.v = bottom;
//    m_sQuad.br.texCoords.u = right;
//    m_sQuad.br.texCoords.v = bottom;
//    m_sQuad.tl.texCoords.u = left;
//    m_sQuad.tl.texCoords.v = top;
//    m_sQuad.tr.texCoords.u = right;
//    m_sQuad.tr.texCoords.v = top;
}

void CCSprite::setPosition(float x, float y){
    m_obPosition.x = x;
    m_obPosition.y = y;
}

const CCPoint& CCSprite::getPosition(){
    return m_obPosition;
}