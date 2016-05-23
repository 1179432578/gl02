//
//  CCGeometry.cpp
//  gl02
//
//  Created by 鲁飞 on 16/4/11.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCGeometry.h"


// implementation of CCRect

CCRect::CCRect(void)
{
    setRect(0.0f, 0.0f, 0.0f, 0.0f);
}

CCRect::CCRect(float x, float y, float width, float height)
{
    setRect(x, y, width, height);
}

CCRect::CCRect(const CCRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

void CCRect::setRect(float x, float y, float width, float height)
{
    // CGRect can support width<0 or height<0
    // CCAssert(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");
    
    origin.x = x;
    origin.y = y;
    
    size.width = width;
    size.height = height;
}



CCSize::CCSize(void) : width(0), height(0)
{
}

CCSize::CCSize(float width, float height) : width(width), height(height)
{
}