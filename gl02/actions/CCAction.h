//
//  CCAction.hpp
//  gl02
//
//  Created by 鲁飞 on 16/5/30.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCAction_hpp
#define CCAction_hpp

#include <stdio.h>
#include "CCObject.h"
#include "CCNode.h"

//动作基类
class CCAction : public CCObject{
public:
    static CCAction* create();
    
    CCAction();
    virtual ~CCAction();
    
    virtual bool isDone();
    
    virtual void startWithTarget(CCNode *aTarget);
    
    virtual void stop(void);
    
    virtual void step(float dt);
    
    /**
     called once per frame. time a value between 0 and 1
     
     For example:
     - 0 means that the action just started
     - 0.5 means that the action is in the middle
     - 1 means that the action is over
     */
    virtual void update(float time);
protected:
    CCNode    *m_pOriginalTarget;
    CCNode    *m_pTarget;
    int     m_nTag;
};

/*直接派生于CCAction的类
 *
 */
//有限时间动作：包含间隔动作与立即动作
class CCFiniteTimeAction : public CCAction
{
public:
    CCFiniteTimeAction()
    : m_fDuration(0)
    {}
    virtual ~CCFiniteTimeAction(){}
    
    //! get duration in seconds of the action
    inline float getDuration(void) { return m_fDuration; }
    //! set duration in seconds of the action
    inline void setDuration(float duration) { m_fDuration = duration; }
    
    /** returns a reversed action */
//    后面实现
//    virtual CCFiniteTimeAction* reverse(void);
protected:
    //! duration in seconds
    float m_fDuration;
};

#endif /* CCAction_hpp */
