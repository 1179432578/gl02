//
//  cyrus-beck.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/12.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "cyrus-beck.h"
#include "stdio.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

LPolygen2* LPolygen2::create(LPoint2f *pts, int N){
    LPolygen2 *ret = new LPolygen2(N);
    ret->lines = N;
    for (int i=0; i<N; i++) {
        ret->pts[i] = pts[i]; // line's point
        ret->vectors[i] = LVector2f(-(pts[(i+1)%N].y-pts[i].y), pts[(i+1)%N].x-pts[i].x); // line's normal vector
    }
    return ret;
}

int cycus_beck(LSegment &s, LPolygen2 *polygen){
    LVector2f AB(s.pt2.x-s.pt1.x, s.pt2.y-s.pt1.y); // vector AB
  
    LPoint2f A(s.pt1);
    float tin = 0.0f;
    float tout = 1.0f;
    float t;
    for (int i=0; i<polygen->lines; i++) {
        t = (polygen->pts[i]-A).dotMuti(polygen->vectors[i])/
        (AB.dotMuti(polygen->vectors[i]));
        // in
        if (AB.dotMuti(polygen->vectors[i]) < 0) {
            tin = MAX(tin, t);
            printf("tin:%f", tin);
        }
        else
        {
            tout = MIN(tout, t);
            printf("tout:%f", tin);
        }
    }
    if (tin>=0.0f && tin<tout && tout<1.0f) {
        s.pt1 = LPoint2f(A+AB.numMul(tin));
        s.pt2 = LPoint2f(A+AB.numMul(tout));
        return 1;
    }
    return 0;
}
