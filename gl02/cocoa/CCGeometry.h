//
//  CCGeometry.hpp
//  gl02
//
//  Created by 鲁飞 on 16/4/11.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCGeometry_hpp
#define CCGeometry_hpp

#include "CCPoint.h"

class CCSize
{
public:
    float width;
    float height;
    
public:
    CCSize();
    CCSize(float width, float height);

};

class CCRect
{
public:
    CCPoint origin;
    CCSize  size;
    
public:
    CCRect();
    CCRect(float x, float y, float width, float height);
    CCRect(const CCRect& other);
    
    void setRect(float x, float y, float width, float height);
};




#endif /* CCGeometry_hpp */
