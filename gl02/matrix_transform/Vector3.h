//
//  Vector3.hpp
//  LImage
//
//  Created by lewis on 16/5/4.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef Vector3_hpp
#define Vector3_hpp

//kmVec3
class Vector3 {
public:
    float x, y, z;
    
public:
    //Vector3 operator+();
    //Vector3 operator-(const Vector3& right) const;
    //Vector3 operator*(const Vector3* right) const;
    Vector3():x(0.0f), y(0.0f), z(0.0f){}
    Vector3(float _x, float _y, float _z):x(_x), y(_y), z(_z){}
    
    static Vector3 vec3Add(const Vector3 &v1, const Vector3 &v2);
    
    static Vector3 vec3Sub(const Vector3 &v1, const Vector3 &v2);
    
    static float vec3Dot(const Vector3 &v1, const Vector3 &v2);
    
    static Vector3 vec3Cross(const Vector3 &v1, const Vector3 &v2);
    
    static Vector3 vec3Scale(const Vector3 &v1, float s);
    
    static float   vec3Divide(const Vector3 &v1, const Vector3 &v2);
    
    Vector3 normalize();
};

#endif /* Vector3_hpp */
