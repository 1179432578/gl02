//
//  CCGLProgram.cpp
//  gl02
//
//  Created by 鲁飞 on 16/4/11.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCGLProgram.h"
#include "mglMatrix.h"

/// The max length of CCLog message.
static const int kMaxLogLen = 16*1024;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)

void CCLog(const char * pszFormat, ...)
{
    printf("Cocos2d: ");
    char szBuf[kMaxLogLen+1] = {0};
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}

#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
#define CHECK_GL_ERROR_DEBUG()
#else
#define CHECK_GL_ERROR_DEBUG() \
do { \
GLenum __error = glGetError(); \
if(__error) { \
CCLog("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
} \
} while (false)
#endif

bool CCGLProgram::initWithByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray){
    m_uProgram = glCreateProgram();
    CHECK_GL_ERROR_DEBUG();
    
    //m_uVertShader = m_uFragShader = 0;
    
    const GLchar *vShaderSource[] = {
        "uniform mat4 CC_PMatrix;\n"
        "uniform mat4 CC_MVMatrix;\n"
        "uniform mat4 CC_MVPMatrix;\n"
        "uniform vec4 CC_Time;\n"
        "uniform vec4 CC_SinTime;\n"
        "uniform vec4 CC_CosTime;\n"
        "uniform vec4 CC_Random01;\n"
        "//CC INCLUDES END\n\n",
        vShaderByteArray,
    };
    
    const GLchar *fShaderSource[] = {
        "uniform mat4 CC_PMatrix;\n"
        "uniform mat4 CC_MVMatrix;\n"
        "uniform mat4 CC_MVPMatrix;\n"
        "uniform vec4 CC_Time;\n"
        "uniform vec4 CC_SinTime;\n"
        "uniform vec4 CC_CosTime;\n"
        "uniform vec4 CC_Random01;\n"
        "//CC INCLUDES END\n\n",
        fShaderByteArray,
    };
    
    //与opengl服务器通信，就是创建对象，给对象赋值，操作对象
    //创建着色程序对象
    m_uVertShader = glCreateShader(GL_VERTEX_SHADER);
    //为着色程序对象赋值
    glShaderSource(m_uVertShader, sizeof(vShaderSource)/sizeof(*vShaderSource), vShaderSource, NULL);
    //编译着色程序对象
    glCompileShader(m_uVertShader);
    
    m_uFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_uFragShader, sizeof(fShaderSource)/sizeof(*fShaderSource), fShaderSource, NULL);
    glCompileShader(m_uFragShader);
    
    //为着色程序添加顶点与片元着色程序
    glAttachShader(m_uProgram, m_uVertShader);
    glAttachShader(m_uProgram, m_uFragShader);
    
    return true;
}

bool CCGLProgram::link(){
    glLinkProgram(m_uProgram);
    
    //链接后可以删除了
    glDeleteShader(m_uVertShader);
    glDeleteShader(m_uFragShader);
    
    return true;
}

void CCGLProgram::use(){
    glUseProgram(m_uProgram);
}

void CCGLProgram::updateUniforms(){
    //获得mvp矩阵
    m_uUniforms[kCCUniformMVPMatrix] = glGetUniformLocation(m_uProgram, kCCUniformMVPMatrix_s);
    
    //获得kCCUniformSampler_s="CC_Texture0"纹理采样器
    m_uUniforms[kCCUniformSampler] = glGetUniformLocation(m_uProgram, kCCUniformSampler_s);
    
    use();
    //设置纹理采样器与第0个纹理单元关联
    glUniform1i(m_uUniforms[kCCUniformSampler], 0);
}

void CCGLProgram::setUniformsForBuiltins(){
    Matrix44 matrixP;
    Matrix44 matrixMV;
    Matrix44 matrixMVP;
    
    mglGetMatrix(KM_GL_PROJECTION, &matrixP);
    mglGetMatrix(KM_GL_MODELVIEW, &matrixMV);
    //mat4Multiply(&matrixMVP, &matrixP, &matrixMV);
    mat4Multiply(&matrixMVP, &matrixMV, &matrixP);//这个用于行向量
    
    glUniformMatrix4fv(m_uUniforms[kCCUniformMVPMatrix], 1, GL_FALSE, (float*)&matrixMVP);
}