//
//  LMath.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/13.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "LMath.h"
#include "math.h"



float LMath::sin(float delta){
    return sinf(delta/360.0f*2.0f*M_PI);
}

float LMath::cos(float delta){
    return cosf(delta/360.0f*2.0f*M_PI);
}

float LMath::sqrt(float real){
    return sqrtf(real);
}

LMath lmath;

