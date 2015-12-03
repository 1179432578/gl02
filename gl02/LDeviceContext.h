//
//  LDeviceContext.h
//  gl02
//
//  Created by 鲁飞 on 15/8/10.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef __gl02__LDeviceContext__
#define __gl02__LDeviceContext__

#include "LPoint2f.h"

class LDeviceContext
{
public:
    void moveTo(LPoint2f p);
    void lineTo(LPoint2f p);
    void pixel(LPoint2f p);
private:
    LPoint2f m_currentPoint;
    LPoint2f m_beginPoint;
};

#endif /* defined(__gl02__LDeviceContext__) */
