//
//  CCScene.hpp
//  gl02
//
//  Created by lewis on 16/4/17.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCScene_hpp
#define CCScene_hpp

#include "CCNode.h"

class CCScene : public CCNode {
public:
    CCScene();
    virtual ~CCScene();
    
    static CCScene *create(void);
    
    bool init();
};

#endif /* CCScene_hpp */
