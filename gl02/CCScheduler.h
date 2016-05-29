//
//  CCScheduler.hpp
//  gl02
//
//  Created by lewis on 16/5/29.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCScheduler_hpp
#define CCScheduler_hpp

#include <stdio.h>
#include "CCObject.h"
#include "CCArray.h"
#include "List.h"

/*调度器
 *
 */

// A list double-linked list used for "updates with priority"
typedef struct ListEntry
{
    struct ListEntry   *prev, *next;
    CCObject            *target;        // not retained (retained by hashUpdateEntry)
    int                 priority;
    bool                paused;
    bool                markedForDeletion; // selector will no longer be called and entry will be removed at end of the next tick
} ListEntry;

class CCScheduler : public CCObject{
public:
    CCScheduler();
    ~CCScheduler(){};
//    inline float getTimeScale(void) { return m_fTimeScale; }
//    inline void setTimeScale(float fTimeScale) { m_fTimeScale = fTimeScale; }
    
    void update(float dt);
    
    void scheduleUpdateForTarget(CCObject *pTarget, int nPriority, bool bPaused);
    void appendIn(struct ListEntry **ppList, CCObject *pTarget, bool bPaused);
protected:
    float m_fTimeScale;
    
    //
    // "updates with priority" stuff
    //
    struct ListEntry *m_pUpdatesNegList;        // list of priority < 0
    struct ListEntry *m_pUpdates0List;            // list priority == 0
    struct ListEntry *m_pUpdatesPosList;        // list priority > 0
//    struct _hashUpdateEntry *m_pHashForUpdates; // hash used to fetch quickly the list entries for pause,delete,etc
    
//    // Used for "selectors with interval"
//    struct _hashSelectorEntry *m_pHashForTimers;
//    struct _hashSelectorEntry *m_pCurrentTarget;
//    bool m_bCurrentTargetSalvaged;
    // If true unschedule will not remove anything from a hash. Elements will only be marked for deletion.
//    bool m_bUpdateHashLocked;
//    CCArray* m_pScriptHandlerEntries;
};

#endif /* CCScheduler_hpp */
