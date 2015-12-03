//
//  LPoint2f.h
//  gl02
//
//  Created by 鲁飞 on 15/8/11.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef __gl02__LPoint2f__
#define __gl02__LPoint2f__

class LPoint2f;
class LMatrix3x3;

class LVector2f{
public:
    LVector2f(){}
    // point to vector
    LVector2f(LPoint2f p);
    // point
    LVector2f(float vv1, float vv2, float vv3):v1(vv1),v2(vv2),v3(vv3){}
    LVector2f(float vv1, float vv2):v1(vv1),v2(vv2){}
    float v1, v2, v3;
    LVector2f numMul(float s){ return LVector2f(s*v1, s*v2);}
    LVector2f operator+(LVector2f v){return LVector2f(v1+v.v1, v2+v.v2);}
    LPoint2f operator+(LPoint2f p);
    float dotMuti(LVector2f v){return v1*v.v1+v2*v.v2;}
    friend LPoint2f operator+(LPoint2f p, LVector2f v);
};

class LPoint2f{
public:
    LPoint2f(){}
    // vector to point
    LPoint2f(LVector2f v):x(v.v1), y(v.v2){}
    LPoint2f(float xx, float yy):x(xx), y(yy){}
    static LPoint2f interpolation2f(LPoint2f a, LPoint2f b, float t);
    static LPoint2f interpolation3f(LPoint2f a, LPoint2f b, LPoint2f c, float t);
    LVector2f operator-(LPoint2f pt){return LVector2f(x-pt.x,y-pt.y);}
    float x;
    float y;
};

class Rect4f{
public:
    Rect4f(){}
    Rect4f(float left1, float right1, float bottom1, float top1)
    :left(left1),right(right1),bottom(bottom1),top(top1){}
    float left, right, bottom, top;
};

class LPolygen{
public:
    LPoint2f *pts; // point set
    int n; // point num
    void matrixTransfer(LMatrix3x3 m);
};

LPoint2f operator+(LPoint2f p, LVector2f v);

class LPoint3f{
public:
    float x, y, z;
};

class LVector3f{
public:
    float v1, v2, v3, v4;
};

#endif /* defined(__gl02__LPoint2f__) */
