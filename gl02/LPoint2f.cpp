//
//  LPoint2f.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/11.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "LPoint2f.h"
#include "LMatrix.h"


LPoint2f LPoint2f::interpolation2f(LPoint2f a, LPoint2f b, float t){

    return LPoint2f(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}

LPoint2f LPoint2f::interpolation3f(LPoint2f a, LPoint2f b, LPoint2f c, float t){
    int x = (a.x-2*b.x+c.x)*t*t + (1-2*t)*a.x + 2*t*b.x;
    int y = (a.y-2*b.y+c.y)*t*t + (1-2*t)*a.y + 2*t*b.y;
    return LPoint2f(x, y);
}

LPoint2f LVector2f::operator+(LPoint2f p){
    return LPoint2f(p.x+v1,p.y+v2);
}

LPoint2f operator+(LPoint2f p, LVector2f v){
    return LPoint2f(p.x+v.v1,p.y+v.v2);
}

LVector2f::LVector2f(LPoint2f p):v1(p.x),v2(p.y),v3(1.0f){}

void LPolygen::matrixTransfer(LMatrix3x3 m){
    for (int i=0; i<this->n; i++) {
        LVector2f v(this->pts[i]);
        v = m * v;
        this->pts[i] = LPoint2f(v);
    }
}




