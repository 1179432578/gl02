//
//  LMesh.h
//  gl02
//
//  Created by 鲁飞 on 15/8/18.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef __gl02__LMesh__
#define __gl02__LMesh__

#include "LPoint2f.h"
#include "tinyxml.h"

struct LVertex{
    int vertexID;
    int normalID;
};

struct LFace{
    int vertexNum;
    LVertex *vertexList;
};

class LMesh{
public:
    int faceNum;
    LFace *faceList;
    int pointNum;
    LPoint3f *pointList;
    int normalNum;
    LVector3f *normalList;
    void read(const char *filename);
    void draw();
private:
    
};

#endif /* defined(__gl02__LMesh__) */
