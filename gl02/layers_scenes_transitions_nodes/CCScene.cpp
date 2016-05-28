//
//  CCScene.cpp
//  gl02
//
//  Created by lewis on 16/4/17.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCScene.h"
#include "CCDirector.h"

CCScene::CCScene(){
    m_bIgnoreAnchorPointForPosition = false;
    m_bIgnoreAnchorPointForPosition = true;
    setAnchorPoint(ccp(0.5f, 0.5f));
};

CCScene::~CCScene(){
};

CCScene *CCScene::create(void){
    CCScene *ret = new CCScene;
    ret->init();
    
    return ret;
}

bool CCScene::init(){
    setContentSize(CCDirector::sharedDirector()->getWinSize());
    
    return true;
}