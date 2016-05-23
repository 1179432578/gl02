//
//  CCShaderCache.cpp
//  gl02
//
//  Created by lewis on 16/5/17.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCShaderCache.h"
#include "ccShaders.h"

enum {
    kCCShaderType_PositionTextureColor,
    kCCShaderType_PositionTextureColorAlphaTest,
    kCCShaderType_PositionColor,
    kCCShaderType_PositionTexture,
    kCCShaderType_PositionTexture_uColor,
    kCCShaderType_PositionTextureA8Color,
    kCCShaderType_Position_uColor,
    kCCShaderType_PositionLengthTexureColor,
    kCCShaderType_ControlSwitch,
    
    kCCShaderType_MAX,
};

//CCShaderCache 是一个单件类
static CCShaderCache *_sharedShaderCache = 0;
CCShaderCache* CCShaderCache::sharedShaderCache()
{
    if (!_sharedShaderCache) {
        _sharedShaderCache = new CCShaderCache();
        if (!_sharedShaderCache->init())
        {
//            CC_SAFE_DELETE(_sharedShaderCache);
        }
    }
    return _sharedShaderCache;
}

bool CCShaderCache::init(){
    m_pPrograms = new CCDictionary();
    loadDefaultShaders();
    return true;
}

//创建默认的着色程序
void CCShaderCache::loadDefaultShaders(){
    // Position Texture Color shader
    CCGLProgram *p = new CCGLProgram();
    loadDefaultShader(p, kCCShaderType_PositionTextureColor);
    
    m_pPrograms->setObject(p, kCCShader_PositionTextureColor);
//    暂不处理内存管理
//    p->release();
}

void CCShaderCache::loadDefaultShader(CCGLProgram *p, int type){
    switch (type) {
        case kCCShaderType_PositionTextureColor:
//            p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColor_frag);
            //初始化着色程序 还没链接
            p->initWithByteArray(ccPositionTextureColor_vert, ccPositionTextureColor_frag);
            
//            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
//            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
//            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            //绑定位置
            glBindAttribLocation(p->m_uProgram, kCCVertexAttrib_Position, kCCAttributeNamePosition);
            glBindAttribLocation(p->m_uProgram, kCCVertexAttrib_Color, kCCAttributeNameColor);
            glBindAttribLocation(p->m_uProgram, kCCVertexAttrib_TexCoords, kCCAttributeNameTexCoord);
            
            
            break;
        default:
            
//            CCLOG("cocos2d: %s:%d, error shader type", __FUNCTION__, __LINE__);
            return;
    }
    
    //链接
    p->link();
    
    p->updateUniforms();
    
//    CHECK_GL_ERROR_DEBUG();
}

CCGLProgram* CCShaderCache::programForKey(const char* key){
     return (CCGLProgram*)m_pPrograms->objectForKey(key);
}

void CCShaderCache::addProgram(CCGLProgram* program, const char* key){
    m_pPrograms->setObject(program, key);
}




