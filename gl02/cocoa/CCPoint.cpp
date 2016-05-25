//
//  CCPoint.cpp
//  gl02
//
//  Created by 鲁飞 on 16/4/8.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCPoint.h"
#include <math.h>

CCPoint::CCPoint() : x(0), y(0){

}

CCPoint::CCPoint(float x, float y) : x(x), y(y){

}

bool CCPoint::equals(const CCPoint& target) const
{
    return (fabs(this->x - target.x) < __FLT_EPSILON__)
    && (fabs(this->y - target.y) < __FLT_EPSILON__);
}