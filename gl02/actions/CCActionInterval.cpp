//
//  CCActionInterval.cpp
//  gl02
//
//  Created by 鲁飞 on 16/5/30.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCActionInterval.h"
#include <float.h>
#include "ccMacros.h"

CCActionInterval* CCActionInterval::create(float d){
    CCActionInterval *pAction = new CCActionInterval();
    pAction->initWithDuration(d);
//    pAction->autorelease();
    
    return pAction;
}

//动作初始化
bool CCActionInterval::initWithDuration(float d){
    m_fDuration = d;
    
    // prevent division by 0
    // This comparison could be in step:, but it might decrease the performance
    // by 3% in heavy based action games.
    if (m_fDuration == 0)
    {
        m_fDuration = FLT_EPSILON;//so m_fDuration != 0
    }
    
    m_elapsed = 0;
    m_bFirstTick = true;
    
    return true;

}

bool CCActionInterval::isDone(void){
    //消逝的时间>=持续时间就是完成了
    return m_elapsed >= m_fDuration;
}

void CCActionInterval::step(float dt){
    //第一次执行 具体干什么的不清楚
    if (m_bFirstTick)
    {
        m_bFirstTick = false;
        m_elapsed = 0;
    }
    else
    {
        m_elapsed += dt;
    }
    
    this->update(MIN(1, m_elapsed /m_fDuration) );//m_fDuration != 0
}

void CCActionInterval::startWithTarget(CCNode *pTarget){
    CCFiniteTimeAction::startWithTarget(pTarget);//先执行父类方法
    m_elapsed = 0.0f;
    m_bFirstTick = true;
}