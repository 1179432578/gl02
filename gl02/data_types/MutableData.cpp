//
//  MutableData.cpp
//  LImage
//
//  Created by lewis on 16/4/19.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "MutableData.h"
#include <stdio.h>

void MutableData::appendBytes(void *bytes, int length){
    char* data = (char*)bytes;
    for (int i=0; i<length; i++) {
        m_data.push_back(data[i]);
    }
}

void MutableData::appendChar(char c){
    
}

void MutableData::appendChars(char *buf, int length){
    for (int i=0; i<length; i++) {
        m_data.push_back(buf[i]);
    }
}

char* MutableData::parseChars(int length){
    char *buf = new char[length];
    for (int i=0; i<length; i++) {
        buf[i] = m_data[pos];
        pos++;
    }
    
    return buf;
}

void MutableData::appendShort(short s){

}

short MutableData::parseShort(){
    char s[2];
    for (int i=0; i<2; i++) {
        s[i] = m_data[pos];
        pos++;
    }
    
    return *(short*)s;
}

void MutableData::appendInt(int n){
    appendBytes(&n, 4);
}

int MutableData::parseInt(){
    char buf[4];
    
    for (int i=0; i<4; i++) {
        buf[i] = m_data[pos];
        pos++;
    }
    
    return *(int*)buf;
}


void MutableData::appendString(char *string){
    appendBytes(string, strlen(string) + 1);
}

//调用者负责buf的释放
char* MutableData::parseString(){
    vector<char> v;
    while (m_data[pos]) {
        v.push_back(m_data[pos]);
        pos++;
    }
    v.push_back('\0');
    pos++;
    
    char *buf = new char[v.size()];
    for (int i=0; i<v.size(); i++) {
        buf[i] = v[i];
    }
    
    return buf;
}

void MutableData::appendFloat(float f){}

void MutableData::appendDoubel(double d){}

void MutableData::printChar(){
    for (int i=0; i<m_data.size(); i++) {
        if (i > 0 && i % 16 == 0) {
            printf("\n");
        }
        printf("%c ", m_data[i]);
    }
}

void MutableData::printHexadecimal(){
    for (int i=0; i<m_data.size(); i++) {
        if (i > 0 && i % 16 == 0) {
            printf("\n");
        }
        printf("%02x ", m_data[i]);
    }
}

void MutableData::readFile(const char *filename){
    FILE *stream = fopen(filename, "rb");
    if (!stream) {
        printf("cannot open %s.", filename);
    }
    
    fseek(stream, 0, SEEK_END);
    int length = ftell(stream);
    fseek(stream, 0, SEEK_SET);
    
    unsigned char *buf = new unsigned char[length];
    fread(buf, length, 1, stream);
    
    fclose(stream);
    
    for (int i=0; i<length; i++) {
        m_data.push_back(buf[i]);
    }
    
    delete buf;
}

void MutableData::writeFile(const char *filename){
    FILE *stream = fopen(filename, "wb");
    if (!stream) {
        printf("cannot open %s.", filename);
    }
    
    unsigned char *buf = new unsigned char[m_data.size()];
    for (int i=0; i<m_data.size(); i++) {
        buf[i] = m_data[i];
    }
    
    fwrite(buf, m_data.size(), 1, stream);
    
    fclose(stream);
    
    delete buf;
}