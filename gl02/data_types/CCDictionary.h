//
//  CCDictonary.hpp
//  LImage
//
//  Created by lewis on 16/4/26.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef CCDictonary_hpp
#define CCDictonary_hpp
#include "HashTable.h"

//key:object pairs
//用散列表存储数据
//散列表很像字典，通过字典可以指定查找的单词在什么地方或者大致位置，散列表亦是如此
class CCDictionary{
public:
    CCDictionary(){m_dictionary = new HashTable;};
    
    ~CCDictionary(){delete m_dictionary;};
    
//    unsigned int count();
    
//    CCArray* allKeys();
    
//    CCArray* allKeysForObject(CCObject* object);
    
    CCObject* objectForKey(const char *key);
    
    CCObject* objectForKey(int key);
    
    void setObject(CCObject* pObject, const char *key);
    
    void setObject(CCObject* pObject, int key);
    
    void removeObjectForKey(char *key);
    
    void removeObjectForKey(int key);
    
//    void removeObjectsForKeys(CCArray* pKeyArray);
    
//    void removeObjectForElememt(CCDictElement* pElement);
    
//    void removeAllObjects();
    
//    static CCDictionary* create();
    
//     static CCDictionary* createWithDictionary(CCDictionary* srcDict);
    
    //Write a dictionary to a plist file.
    //bool writeToFile(const char *fullPath);
    
    HashTable *m_dictionary;
    //CCDictElement* m_pElements;
private:
    
    
};

#endif /* CCDictonary_hpp */
