//
//  CCActionManager.cpp
//  gl02
//
//  Created by lewis on 16/5/30.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCActionManager.h"

CCActionManager::CCActionManager(){
    m_al.pTarget = NULL;
    m_al.actions = CCArray::create();
};
CCActionManager::~CCActionManager(void){};



//动作都是依附目标节点的
void CCActionManager::addAction(CCAction *pAction, CCNode *pTarget, bool paused){
//    CCAssert(pAction != NULL, "");
//    CCAssert(pTarget != NULL, "");
//    
//    tHashElement *pElement = NULL;
//    // we should convert it to CCObject*, because we save it as CCObject*
//    CCObject *tmp = pTarget;
//    HASH_FIND_INT(m_pTargets, &tmp, pElement);
//    if (! pElement)
//    {
//        pElement = (tHashElement*)calloc(sizeof(*pElement), 1);
//        pElement->paused = paused;
//        pTarget->retain();
//        pElement->target = pTarget;
//        HASH_ADD_INT(m_pTargets, target, pElement);
//    }
//    
//    actionAllocWithHashElement(pElement);
//    
//    CCAssert(! ccArrayContainsObject(pElement->actions, pAction), "");
//    ccArrayAppendObject(pElement->actions, pAction);
//    
//    pAction->startWithTarget(pTarget);
    
//    just for quick implement
    m_al.pTarget = pTarget;
    m_al.actions->addObject(pAction);
    
    pAction->startWithTarget(pTarget);
}

void CCActionManager::update(float dt){
    if (m_al.pTarget) {
        ((CCAction*)(m_al.actions->objectAtIndex(0)))->step(dt);
        
        if (((CCAction*)(m_al.actions->objectAtIndex(0)))->isDone()) {
            m_al.pTarget = NULL;
        }
    }
    
}
