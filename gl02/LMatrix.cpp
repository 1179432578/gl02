//
//  transfer.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/13.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "LMatrix.h"
#include "LPoint2f.h"

LMatrix3x3 LMatrix3x3::operator*(LMatrix3x3 m){
    m11 = m11*m.m11+m12*m.m21+m13*m.m31;
    m12 = m11*m.m12+m12*m.m22+m13*m.m32;
    m13 = m11*m.m13+m12*m.m23+m13*m.m33;
    m21 = m21*m.m11+m22*m.m21+m23*m.m31;
    m22 = m21*m.m12+m22*m.m22+m23*m.m32;
    m23 = m21*m.m13+m22*m.m23+m23*m.m33;
    return LMatrix3x3(m11,m12,m13,m21,m22,m23);
}

LVector2f LMatrix3x3::operator*(LVector2f v){
    return LVector2f(m11*v.v1+m12*v.v2+m13*v.v3,
                     m21*v.v1+m22*v.v2+m23*v.v3,
                     m31*v.v1+m32*v.v2+m33*v.v3);
}


