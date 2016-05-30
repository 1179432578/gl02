//
//  CCActionInterval.hpp
//  gl02
//
//  Created by 鲁飞 on 16/5/30.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCActionInterval_hpp
#define CCActionInterval_hpp

#include <stdio.h>
#include "CCAction.h"

//间隔动作 每帧都有动画
class CCActionInterval : public CCFiniteTimeAction
{
public:
    static CCActionInterval* create(float d);
    
    //获得消逝的时间
    inline float getElapsed(void) { return m_elapsed; }
    
    //动作初始化
    bool initWithDuration(float d);
    
    /** returns true if the action has finished */
    virtual bool isDone(void);

//    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void step(float dt);
    virtual void startWithTarget(CCNode *pTarget);
    /** returns a reversed action */
//    virtual CCActionInterval* reverse(void);
    
//public:
//    //extension in CCGridAction
//    void setAmplitudeRate(float amp);
//    float getAmplitudeRate(void);
    
protected:
    float m_elapsed;
    bool   m_bFirstTick;
};

//间隔动作派生的动作 平移、旋转、缩放
class CCMoveBy : public CCActionInterval
{
public:
    static CCMoveBy* create(float duration, const CCPoint& deltaPosition);
    bool initWithDuration(float duration, const CCPoint& deltaPosition);

//    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
//    virtual CCActionInterval* reverse(void);
    virtual void update(float time);
protected:
    CCPoint m_positionDelta;
    CCPoint m_startPosition;
    CCPoint m_previousPosition;
};

#endif /* CCActionInterval_hpp */
