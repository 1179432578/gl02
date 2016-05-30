//
//  CCPoint.hpp
//  gl02
//
//  Created by 鲁飞 on 16/4/8.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCPoint_hpp
#define CCPoint_hpp

class CCPoint{
public:
    float x;
    float y;
    
public:
    CCPoint();
    CCPoint(float x, float y);
    
    CCPoint operator+(const CCPoint& right) const;
    
    CCPoint operator*(float a) const;
    
    bool equals(const CCPoint& target) const;
};

//直接使用重载运算符觉得不是太清晰，有点不伦不类，用下面的代替比较好
static inline CCPoint
ccpAdd(const CCPoint& v1, const CCPoint& v2)
{
    return v1 + v2;
}

static inline CCPoint
ccpMult(const CCPoint& v, const float s)
{
    return v * s;
}

#endif /* CCPoint_hpp */
