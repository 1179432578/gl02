//
//  CCShaderCache.hpp
//  gl02
//
//  Created by lewis on 16/5/17.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCShaderCache_hpp
#define CCShaderCache_hpp

#include <stdio.h>
#include "CCGLProgram.h"
#include "CCDictionary.h"

//sington class
class CCShaderCache{
public:

    static CCShaderCache* sharedShaderCache();
    
    /** loads the default shaders */
    void loadDefaultShaders();
    
    CCGLProgram * programForKey(const char* key);
    void addProgram(CCGLProgram* program, const char* key);
private:
    bool init();
    void loadDefaultShader(CCGLProgram *program, int type);
    
    CCDictionary* m_pPrograms;

};

#endif /* CCShaderCache_hpp */
