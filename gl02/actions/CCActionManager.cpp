//
//  CCActionManager.cpp
//  gl02
//
//  Created by lewis on 16/5/30.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCActionManager.h"
#include "CCArray.h"


class HashElement : public CCObject
{
public:
    CCArray             *actions;
    CCObject                    *target;
    unsigned int                actionIndex;
    CCAction                    *currentAction;
    bool                        currentActionSalvaged;
    bool                        paused;
    //UT_hash_handle                hh;
};

CCActionManager::CCActionManager(){
};
CCActionManager::~CCActionManager(void){};

//动作都是依附目标节点的
void CCActionManager::addAction(CCAction *pAction, CCNode *pTarget, bool paused){
//    CCAssert(pAction != NULL, "");
//    CCAssert(pTarget != NULL, "");

    //在所有目标中查找是否存在pTarget对应元素，如果不存在，就在hash表中添加对应元素
    HashElement *pElement = NULL;
    pElement = (HashElement *)m_pTargets.objectForKey((long)pTarget);
    if (!pElement)
    {
        pElement = new HashElement;
        pElement->paused = paused;
//        pTarget->retain();
        pElement->target = pTarget;
        m_pTargets.setObject(pElement, (long)pTarget);
        pElement->actions = CCArray::create();
    }

    pElement->actions->addObject(pAction);
    pAction->startWithTarget(pTarget);
}

void CCActionManager::update(float dt){
    for (CCObject *e=m_pTargets.getFirst(); e; e=m_pTargets.getNext()) {
        HashElement *pElement = (HashElement*)e;
        for (int i=0; i<pElement->actions->count(); i++) {
            ((CCAction*)pElement->actions->objectAtIndex(i))->step(dt);
            
            if (((CCAction*)pElement->actions->objectAtIndex(i))->isDone()) {
//                removeAction(pAction);动作结束后删除

            }
        }
        
        //目标没动作就把目标对应元素从hash表中删除
//        if (m_bCurrentTargetSalvaged && m_pCurrentTarget->actions->num == 0)
//        {
//            deleteHashElement(m_pCurrentTarget);
//        }
    }
}
