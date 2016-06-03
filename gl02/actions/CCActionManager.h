//
//  CCActionManager.hpp
//  gl02
//
//  Created by lewis on 16/5/30.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCActionManager_hpp
#define CCActionManager_hpp

#include <stdio.h>
#include "CCObject.h"
#include "CCAction.h"
#include "CCDictionary.h"

typedef struct ActionList{
    CCNode *pTarget;
    CCArray *actions;
}ActionList;

class CCActionManager :public CCObject{
public:
    CCActionManager(void);
    ~CCActionManager(void);
    
    //动作都是依附目标节点的
    void addAction(CCAction *pAction, CCNode *pTarget, bool paused);
    
//    void removeAllActions(void);
    
//    /** Removes all actions from a certain target.
//     All the actions that belongs to the target will be removed.
//     */
//    void removeAllActionsFromTarget(CCObject *pTarget);
//    
//    /** Removes an action given an action reference.
//     */
//    void removeAction(CCAction *pAction);
//    
//    /** Removes an action given its tag and the target */
//    void removeActionByTag(unsigned int tag, CCObject *pTarget);
//    
//    /** Gets an action given its tag an a target
//     @return the Action the with the given tag
//     */
//    CCAction* getActionByTag(unsigned int tag, CCObject *pTarget);
//    
//    /** Returns the numbers of actions that are running in a certain target.
//     * Composable actions are counted as 1 action. Example:
//     * - If you are running 1 Sequence of 7 actions, it will return 1.
//     * - If you are running 7 Sequences of 2 actions, it will return 7.
//     */
//    unsigned int numberOfRunningActionsInTarget(CCObject *pTarget);
//    
//    /** Pauses the target: all running actions and newly added actions will be paused.
//     */
//    void pauseTarget(CCObject *pTarget);
//    
//    /** Resumes the target. All queued actions will be resumed.
//     */
//    void resumeTarget(CCObject *pTarget);
//    
//    /** Pauses all running actions, returning a list of targets whose actions were paused.
//     */
//    CCSet* pauseAllRunningActions();
//    
//    /** Resume a set of targets (convenience function to reverse a pauseAllRunningActions call)
//     */
//    void resumeTargets(CCSet *targetsToResume);
    
protected:
    // declared in CCActionManager.m
    
//    void removeActionAtIndex(unsigned int uIndex, struct _hashElement *pElement);
//    void deleteHashElement(struct _hashElement *pElement);
//    void actionAllocWithHashElement(struct _hashElement *pElement);
    void update(float dt);
    
protected:
//    struct _hashElement    *m_pTargets;
//    struct _hashElement    *m_pCurrentTarget;
//    bool            m_bCurrentTargetSalvaged;
    ActionList m_al;//just for test
    CCDictionary m_pTargets;
};

#endif /* CCActionManager_hpp */
