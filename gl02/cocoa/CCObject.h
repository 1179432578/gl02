//
//  CCObject.hpp
//  gl02
//
//  Created by 鲁飞 on 16/5/18.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCObject_hpp
#define CCObject_hpp

#include <stdio.h>

class CCObject
{
public:
    // object id, CCScriptSupport need public m_uID
    unsigned int        m_uID;
    // Lua reference id
    int                 m_nLuaID;
protected:
    // count of references
    unsigned int        m_uReference;
    // count of autorelease
    unsigned int        m_uAutoReleaseCount;
public:
//    CCObject(void);
    /**
     *  @lua NA
     */
//    virtual ~CCObject(void);
    
//    void release(void);
//    void retain(void);
//    CCObject* autorelease(void);
//    CCObject* copy(void);
//    bool isSingleReference(void) const;
//    unsigned int retainCount(void) const;
//    virtual bool isEqual(const CCObject* pObject);
    
//    virtual void acceptVisitor(CCDataVisitor &visitor);
    
    virtual void update(float dt) {};
    
//    friend class CCAutoreleasePool;
};

#endif /* CCObject_hpp */
