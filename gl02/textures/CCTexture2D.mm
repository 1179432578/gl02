//
//  CCTexture2D.cpp
//  gl02
//
//  Created by lewis on 16/5/28.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCTexture2D.h"
#include <GLUT/GLUT.h>
#import <Cocoa/Cocoa.h>


CCTexture2D* CCTexture2D::create(const char *filename){
    CCTexture2D *ret = new CCTexture2D;
    ret->initWithImage(filename);
    
    return ret;
}

bool CCTexture2D::initWithImage(const char *filename){
    //读取一个外部文件 并获得它的图片信息
    NSImage *img = [[NSImage alloc]initWithContentsOfFile:[[NSString alloc] initWithUTF8String:filename]];
    NSRect rt = NSMakeRect(0, 0, img.size.width , img.size.height);
    CGImageRef temImg = [img CGImageForProposedRect:&rt context:nil hints:nil];
    CGDataProviderRef pr = CGImageGetDataProvider(temImg);
    CFDataRef r = CGDataProviderCopyData(pr);
    void* data = (void*)CFDataGetBytePtr(r);
    m_uHeight = CGImageGetHeight(temImg);
    m_uWidth = CGImageGetWidth(temImg);
    
    //生成纹理
    glGenTextures(1, &m_uName);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_uName);
    
    //纹理参数设置
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    //设置纹理数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_uHeight, m_uWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    //释放图片像素数据， 纹理已经保存在显存中，渲染时gpu直接对纹理操作，图片数据不再需要保存在内存中了
    free((void*)data);
    
    m_obContentSize = CCSizeMake(m_uWidth, m_uHeight);
    m_fMaxS = m_obContentSize.width / (float)(m_uWidth);
    m_fMaxT = m_obContentSize.height / (float)(m_uHeight);
    
    return true;

}

const CCSize& CCTexture2D::getContentSize(){
    return m_obContentSize;
}

unsigned int CCTexture2D::getWidth(){
    return m_uWidth;
}

unsigned int CCTexture2D::getHeight(){
    return m_uHeight;
}

GLuint CCTexture2D::getName()
{
    return m_uName;
}