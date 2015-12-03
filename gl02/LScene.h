//
//  LScene.h
//  gl02
//
//  Created by 鲁飞 on 15/8/17.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef __gl02__LScene__
#define __gl02__LScene__

#include "tinyxml.h"

class LScene{
public:
    void read(const char *filename);
    void drawScene();
private:
    TiXmlDocument m_doc;
};


#endif /* defined(__gl02__LScene__) */
