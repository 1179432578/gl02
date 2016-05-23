//
//  Vector3.cpp
//  LImage
//
//  Created by lewis on 16/5/4.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "Vector3.h"
#include <math.h>

Vector3 Vector3::vec3Add(const Vector3 &v1, const Vector3 &v2){
    return Vector3(v1.x + v2.x,
                   v1.y + v2.y,
                   v1.z + v2.z);
}

Vector3 Vector3::vec3Sub(const Vector3 &v1, const Vector3 &v2){
    return Vector3(v1.x - v2.x,
                   v1.y - v2.y,
                   v1.z - v2.z);
}

float Vector3::vec3Dot(const Vector3 &v1, const Vector3 &v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::vec3Cross(const Vector3 &v1, const Vector3 &v2){
    return Vector3(v1.y * v2.z - v1.z * v2.y,
                   v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
}

Vector3 Vector3::vec3Scale(const Vector3 &v, float s){
    return Vector3(v.x * s, v.y * s, v.z *s);
}

float   Vector3::vec3Divide(const Vector3 &v1, const Vector3 &v2){
    //与0比较要修改
    if (v2.x != 0.0f) {
        return v1.x / v2.x;
    }
    else if (v2.y != 0.0f){
        return v1.y / v2.y;
    }
    else if (v2.z != 0.0f){
        return v1.z / v2.z;
    }
    else{
        //error 除0向量
        return 0.0f;
    }
}

Vector3 Vector3::normalize(){
    float squareSum = x*x + y*y + z*z;
    if (squareSum < 0.000001) {
        return *this;
    }
    
    float length = sqrtf(squareSum);
    
    x /= length;
    y /= length;
    z /= length;
    
    return *this;
}

//void print(Vector3 *v){
//    printf("Vector3:%f %f %f %f\n", v->x, v->y, v->z);
//}