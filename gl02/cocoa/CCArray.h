//
//  CCArray.hpp
//  gl02
//
//  Created by 鲁飞 on 16/5/27.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCArray_hpp
#define CCArray_hpp

#include <stdio.h>
#include "CCObject.h"

class CCArray : public CCObject{
public:
    static CCArray* create();
    
    void addObject(CCObject* object);
    
    unsigned int count() const;
    
    CCObject* objectAtIndex(unsigned int index);

protected:
    bool init();
    
    void resize();
    
public:
    CCObject **m_arr;
    int m_count;
    int m_capacity;
};

#endif /* CCArray_hpp */
