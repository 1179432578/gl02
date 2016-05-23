//
//  CCGLProgram.hpp
//  gl02
//
//  Created by 鲁飞 on 16/4/11.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCGLProgram_hpp
#define CCGLProgram_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include "CCObject.h"

/**
 * @addtogroup shaders
 * @{
 */

enum {
    kCCVertexAttrib_Position,
    kCCVertexAttrib_Color,
    kCCVertexAttrib_TexCoords,
    
    kCCVertexAttrib_MAX,
};

enum {
    kCCUniformPMatrix,
    kCCUniformMVMatrix,
    kCCUniformMVPMatrix, //mvp matrix
    kCCUniformTime,
    kCCUniformSinTime,
    kCCUniformCosTime,
    kCCUniformRandom01,
    kCCUniformSampler,
    
    kCCUniform_MAX,//前面枚举元素个数
};

//着色器缓存对象中的着色器程序对应的key
#define kCCShader_PositionTextureColor              "ShaderPositionTextureColor"
#define kCCShader_PositionTextureColorAlphaTest     "ShaderPositionTextureColorAlphaTest"
#define kCCShader_PositionColor                     "ShaderPositionColor"
#define kCCShader_PositionTexture                   "ShaderPositionTexture"
#define kCCShader_PositionTexture_uColor            "ShaderPositionTexture_uColor"
#define kCCShader_PositionTextureA8Color            "ShaderPositionTextureA8Color"
#define kCCShader_Position_uColor                   "ShaderPosition_uColor"
#define kCCShader_PositionLengthTexureColor         "ShaderPositionLengthTextureColor"
#define kCCShader_ControlSwitch                     "Shader_ControlSwitch"

//  uniform是唯一的 在vertex shader与fragment shader里面是共享存在的
//  uniform变量一般用来表示：变换矩阵，材质，光照参数和颜色等信息。
//  而attribute只能在vertex shader中存在
//  一般用函数glBindAttribLocation（）来绑定每个attribute变量的位置，然后用函数glVertexAttribPointer（）为每个attribute变量赋值
//  一般用attribute变量来表示一些顶点的数据，如：顶点坐标，法线，纹理坐标，顶点颜色等。

// uniform names
#define kCCUniformPMatrix_s				"CC_PMatrix"
#define kCCUniformMVMatrix_s			"CC_MVMatrix"
#define kCCUniformMVPMatrix_s			"CC_MVPMatrix"
#define kCCUniformTime_s				"CC_Time"
#define kCCUniformSinTime_s				"CC_SinTime"
#define kCCUniformCosTime_s				"CC_CosTime"
#define kCCUniformRandom01_s			"CC_Random01"
#define kCCUniformSampler_s				"CC_Texture0"
#define kCCUniformAlphaTestValue		"CC_alpha_value"

// Attribute names
#define    kCCAttributeNameColor           "a_color"
#define    kCCAttributeNamePosition        "a_position"
#define    kCCAttributeNameTexCoord        "a_texCoord"


class CCGLProgram : public CCObject {
public:
    //Initializes the CCGLProgram with a vertex and fragment with bytes array
    //bool initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    //用字节数组初始化顶点与片元着色器程序
    bool initWithByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    
    //void addAttribute(const char* attributeName, GLuint index);
    //为着色器程序中的属性变量绑定地址，通过这个地址可以向opengl服务器传送数据
    //void bindAttributeLocation(const char* attributeName, GLuint index);
    
    //链接顶点与片元着色器程序
    bool link();
    
    //使用着色器程序
    void use();
    
    //获取与获得全局共享变量，直接调用opengl的，不提供接口
    //getUniformLocation
    //setUniformLocation
    
    //获得共享变量的位置
    void updateUniforms();
    
    //设置一些共享变量值，CC_MVPMatrix顶点坐标变换矩阵
    //客户自定义的着色程序可能根本没定义这些uniform变量
    void setUniformsForBuiltins();
    
    GLuint            m_uProgram;
private:
    GLuint            m_uVertShader;
    GLuint            m_uFragShader;
    GLint             m_uUniforms[kCCUniform_MAX];//存放uniform变量位置
};


#endif /* CCGLProgram_hpp */
