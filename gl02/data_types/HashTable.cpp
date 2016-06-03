//
//  HashTable.cpp
//  LImage
//
//  Created by lewis on 16/4/23.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "HashTable.h"
#include <stdio.h>

//这个算法是Daniel J.Bernstein 教授发明的，是目前公布的最有效的哈希函数。
int DJBHash(char *str)
{
    int hash = 5381;
    for(int i = 0; i < strlen(str); i++)
    {
        hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
}

int DJBHash(void *bytes, int size)
{
    char *str = (char*)bytes;
    int hash = 5381;
    for(int i = 0; i < size; i++)
    {
        hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
}

HashTable::HashTable(){
    m_loadFactor = DEFAULT_LOAD_FACTOR;
    m_threshold = DEFALUT_INITIAL_CAPACITY * DEFAULT_LOAD_FACTOR;
    m_length = DEFALUT_INITIAL_CAPACITY;
    m_table = new Element*[DEFALUT_INITIAL_CAPACITY];
    
    memset(m_table, 0, sizeof(Entry*) * DEFALUT_INITIAL_CAPACITY);
}

HashTable::HashTable(int initialCapacity){
    HashTable(initialCapacity, DEFAULT_LOAD_FACTOR);
}

HashTable::HashTable(int initialCapacity, float loadFactor){
    if (initialCapacity < 0) {
        //error
    }
    
    if (initialCapacity > MAXIMUM_CAPACITY) {
        initialCapacity = MAXIMUM_CAPACITY;
    }
    
    if (loadFactor < 0) {
        //error
    }
    
    int capacity = 1;
    //ensure capacity is power of 2
    if (capacity < initialCapacity) {
        capacity <<= 1;
    }
    
    m_loadFactor = loadFactor;
    m_threshold = capacity * loadFactor;
    m_length = capacity;
    m_table = new Element*[capacity];
    
    memset(m_table, 0, sizeof(Entry*) * capacity);
}

// not support objects that key equal
void HashTable::put(const char *key, CCObject *value){
    put((void*)key, strlen(key), value);
}

CCObject* HashTable::get(const char *key){
    return (CCObject *)get((void*)key, strlen(key));
}

void HashTable::put(int key, CCObject *value){
    put(&key, 4, value);
}

CCObject* HashTable::get(int key){
    return (CCObject *)get(&key, 4);
}

// get position of item
int HashTable::indexFor(int hash, int length){
     return hash & (length-1);
}

//base put
void HashTable::put(void *key, int size, void *value){
    // caculate hash value
    int hash = DJBHash(key, size);
    
    // get position of item
    int pos = indexFor(hash, m_length);
    
    char *str = (char*)key;
    for (Element *e = m_table[pos]; e != NULL; e = e->next) {
        //size equal
        if (size == e->size) {
            for (int i=0; i<size; i++) {
                if (str[i] != ((char*)e->key)[i]) {
                    // if the two chars are not equeal then break
                    break;
                }
            }
            
            //the two elements have same size and chars
            e->value = value;//set old value
            return;
        }
    }
    
    // not find Element in position pos, then create an Element and insert to HashTable
    Element *e = new Element;
    e->key = key;
    e->size = size;
    e->value = value;
    e->next = m_table[pos];
    m_table[pos] = e;
    
    //if the size of items equal or greater than thewshold, then resize hashtable
    if (++m_size >= m_threshold) {
        //resize(2 * m_length);
    }

}

//base get
void* HashTable::get(void *key, int size){
    int hash = DJBHash(key, size);
    
    char *str = (char*)key;
    for (Element *e = m_table[indexFor(hash, m_length)]; e !=NULL; e = e->next) {
        //check if they have same size
        if (size == e->size) {
            //check if they have same chars
            for (int i=0; i<size; i++) {
                if (str[i] != ((char*)e->key)[i]) {
                    break;
                }
            }
            //the two elements have same size and chars
            return e->value;
        }
    }
    //not find
    return NULL;
}

CCObject* HashTable::getFirst(){
    for(int i=0; i<m_length; i++){
        Element *e = m_table[i];
        if (e) {
            m_nextPos = i + 1;
            m_nextElement = e->next;
            return (CCObject*)e->value;
        }
    }
    
    return NULL;
}

CCObject* HashTable::getNext(){
    if (m_nextElement) {
        Element *tmp = m_nextElement;
        m_nextElement = m_nextElement->next;
        return (CCObject*)tmp->value;
    }
    
    for (int i=m_nextPos; i<m_length; i++) {
        Element *e = m_table[i];
        if (e) {
            m_nextPos = i + 1;
            m_nextElement = e->next;
            return (CCObject*)e->value;

        }
    }
    
    return NULL;
}
