//
//  CCArray.cpp
//  gl02
//
//  Created by 鲁飞 on 16/5/27.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCArray.h"
#include <string.h>

#define DEFAULTSIZE 4
CCArray* CCArray::create(){
    CCArray *arr = new CCArray;
    arr->init();
    
    return arr;
}

bool CCArray::init(){
    m_arr = new CCObject*[DEFAULTSIZE];
    m_capacity = DEFAULTSIZE;
    m_count = 0;
    
    return true;
}

void CCArray::resize(){
    CCObject **tmp = m_arr;
    
    m_arr = new CCObject*[m_capacity * 2];
    memcpy(m_arr, tmp, m_count);
    m_capacity *= 2;
    
    delete [] tmp;
}

void CCArray::addObject(CCObject* object){
    if (m_count+1 > m_capacity) {
        resize();
    }
    
    m_arr[m_count++] = object;
}

unsigned int CCArray::count() const
{
    return m_count;
}

CCObject* CCArray::objectAtIndex(unsigned int index)
{
//    CCAssert(index < data->num, "index out of range in objectAtIndex()");
    
    return m_arr[index];
}