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
    
    bool equals(const CCSize& target) const;
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

#define CCPointMake(x, y) CCPoint((float)(x), (float)(y))
#define CCSizeMake(width, height) CCSize((float)(width), (float)(height))
#define CCRectMake(x, y, width, height) CCRect((float)(x), (float)(y), (float)(width), (float)(height))

//#define ccp(__X__,__Y__) CCPointMake((float)(__X__), (float)(__Y__))
#define ccp(__X__,__Y__) CCPoint((float)(__X__), (float)(__Y__))

const CCPoint CCPointZero = CCPointMake(0,0);

const CCSize CCSizeZero = CCSizeMake(0,0);

const CCRect CCRectZero = CCRectMake(0,0,0,0);

#endif /* CCGeometry_hpp */
