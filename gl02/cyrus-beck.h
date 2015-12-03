//
//  cyrus-beck.h
//  gl02
//
//  Created by 鲁飞 on 15/8/12.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef __gl02__cyrus_beck__
#define __gl02__cyrus_beck__

#include "LPoint2f.h"

class LSegment{
public:
    LPoint2f pt1;
    LPoint2f pt2;
};

class LPolygen2{
public:
    LPolygen2(int n){
        pts = new LPoint2f[n];
        vectors = new LVector2f[n];
        lines = n;
    }
    LPoint2f *pts;
    LVector2f *vectors;
    static LPolygen2* create(LPoint2f *pts, int N);
    int lines;
};



int cycus_beck(LSegment &s, LPolygen2 *polygen);

#endif /* defined(__gl02__cyrus_beck__) */
