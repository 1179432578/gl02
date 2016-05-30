//
//  CCAction.cpp
//  gl02
//
//  Created by 鲁飞 on 16/5/30.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCAction.h"

CCAction* CCAction::create(){
    CCAction *ret = new CCAction;
//    ret->autorelease();后面实现内存管理
    return ret;
}

CCAction::CCAction()
:m_pOriginalTarget(NULL)
,m_pTarget(NULL)
//,m_nTag(kCCActionTagInvalid){
{
}

CCAction::~CCAction(){}

bool CCAction::isDone(){
    return true;
}

void CCAction::startWithTarget(CCNode *aTarget){
    m_pOriginalTarget = m_pTarget = aTarget;
}

void CCAction::stop(void){
    m_pTarget = NULL;
}

void CCAction::step(float dt){
//    CC_UNUSED_PARAM(dt);
//    CCLOG("[Action step]. override me");
}

void CCAction::update(float time){
//    CC_UNUSED_PARAM(time);
//    CCLOG("[Action update]. override me");

}
