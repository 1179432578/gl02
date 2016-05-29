//
//  CCScheduler.cpp
//  gl02
//
//  Created by lewis on 16/5/29.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCScheduler.h"
#include <stdlib.h>

CCScheduler::CCScheduler(void)
: m_fTimeScale(1.0f)
, m_pUpdatesNegList(NULL)
, m_pUpdates0List(NULL)
, m_pUpdatesPosList(NULL)
//, m_pHashForUpdates(NULL)
//, m_pHashForTimers(NULL)
//, m_pCurrentTarget(NULL)
//, m_bCurrentTargetSalvaged(false)
//, m_bUpdateHashLocked(false)
//, m_pScriptHandlerEntries(NULL)
{
    
}

void CCScheduler::update(float dt){
//    m_bUpdateHashLocked = true;
    
//    if (m_fTimeScale != 1.0f)
//    {
//        dt *= m_fTimeScale;
//    }
    
    // Iterate over all the Updates' selectors
    ListEntry *pEntry, *pTmp;
    
    // updates with priority < 0
    /* this version is safe for deleting the elements during iteration */
    for (pEntry = m_pUpdatesNegList; pEntry && (pTmp = pEntry->next , 1); pEntry = pTmp) {
        if ((! pEntry->paused) && (! pEntry->markedForDeletion))
        {
            pEntry->target->update(dt);
        }
    }
    
    // updates with priority == 0
    for (pEntry = m_pUpdates0List; pEntry && (pTmp = pEntry->next , 1); pEntry = pTmp) {
        if ((! pEntry->paused) && (! pEntry->markedForDeletion))
        {
            pEntry->target->update(dt);
        }
    }
    
    // updates with priority > 0
    for (pEntry = m_pUpdatesPosList; pEntry && (pTmp = pEntry->next , 1); pEntry = pTmp) {
        if ((! pEntry->paused) && (! pEntry->markedForDeletion))
        {
            pEntry->target->update(dt);
        }
    }
    
//    // delete all updates that are marked for deletion
//    // updates with priority < 0
//    DL_FOREACH_SAFE(m_pUpdatesNegList, pEntry, pTmp)
//    {
//        if (pEntry->markedForDeletion)
//        {
//            this->removeUpdateFromHash(pEntry);
//        }
//    }
//    
//    // updates with priority == 0
//    DL_FOREACH_SAFE(m_pUpdates0List, pEntry, pTmp)
//    {
//        if (pEntry->markedForDeletion)
//        {
//            this->removeUpdateFromHash(pEntry);
//        }
//    }
//    
//    // updates with priority > 0
//    DL_FOREACH_SAFE(m_pUpdatesPosList, pEntry, pTmp)
//    {
//        if (pEntry->markedForDeletion)
//        {
//            this->removeUpdateFromHash(pEntry);
//        }
//    }
    
//    m_bUpdateHashLocked = false;
    
//    m_pCurrentTarget = NULL;

}

//为目标进行调度
void CCScheduler::scheduleUpdateForTarget(CCObject *pTarget, int nPriority, bool bPaused){
    //加入hash表，在hash中查找，hash表主要用来加速查找的
//    tHashUpdateEntry *pHashElement = NULL;
//    HASH_FIND_INT(m_pHashForUpdates, &pTarget, pHashElement);
//    if (pHashElement)
//    {
//#if COCOS2D_DEBUG >= 1
//        CCAssert(pHashElement->entry->markedForDeletion,"");
//#endif
//        // TODO: check if priority has changed!
//        
//        pHashElement->entry->markedForDeletion = false;
//        return;
//    }
    
    // most of the updates are going to be 0, that's way there
    // is an special list for updates with priority 0
    if (nPriority == 0)
    {
        appendIn(&m_pUpdates0List, pTarget, bPaused);
    }
    //下面的进行排序的
//    else if (nPriority < 0)
//    {
//        priorityIn(&m_pUpdatesNegList, pTarget, nPriority, bPaused);
//    }
//    else
//    {
//        // priority > 0
//        priorityIn(&m_pUpdatesPosList, pTarget, nPriority, bPaused);
//    }
}

void CCScheduler::appendIn(ListEntry **ppList, CCObject *pTarget, bool bPaused)
{
    ListEntry *pListElement = (ListEntry *)malloc(sizeof(ListEntry));
    
    pListElement->target = pTarget;
    pListElement->paused = bPaused;
    pListElement->markedForDeletion = false;
    
    DL_APPEND(*ppList, pListElement, prev, next);
    
//    // update hash entry for quicker access
//    tHashUpdateEntry *pHashElement = (tHashUpdateEntry *)calloc(sizeof(*pHashElement), 1);
//    pHashElement->target = pTarget;
//    pTarget->retain();
//    pHashElement->list = ppList;
//    pHashElement->entry = pListElement;
//    HASH_ADD_INT(m_pHashForUpdates, target, pHashElement);
}