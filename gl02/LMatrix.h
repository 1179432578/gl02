//
//  transfer.h
//  gl02
//
//  Created by 鲁飞 on 15/8/13.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef __gl02__transfer__
#define __gl02__transfer__

class LVector2f;

class LMatrix3x3{
public:
    LMatrix3x3(){LMatrix3x3(1.0f,0.0f,0.0f,0.0f,1.0f,0.0f);}
    LMatrix3x3(float _m11, float _m12, float _m13,
            float _m21, float _m22, float _m23)
    :m11(_m11),m12(_m12),m13(_m13),m21(_m21),m22(_m22),m23(_m23),
    m31(0),m32(0),m33(1){}
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    LMatrix3x3 operator*(LMatrix3x3 m);
    LVector2f operator*(LVector2f v);
};

#endif /* defined(__gl02__transfer__) */
