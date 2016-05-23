//
//  MutableData.hpp
//  LImage
//
//  Created by lewis on 16/4/19.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef MutableData_hpp
#define MutableData_hpp

#include <vector>
using namespace std;

//可变数据 存放的数据在它看来就是一个个字节
//存储的数据都是有符号的
//磁盘文件-》MutableData-》文件解析结构(psd bitmap png and so on)
class MutableData {
public:
    void appendChar(char c);
    
    //添加多个字符
    void appendChars(char *buf, int length);
    //解析出多个字符
    char* parseChars(int length);
    
    void appendShort(short s);
    short parseShort();
    
    void appendInt(int n);
    int parseInt();
    
    void appendString(char *string);
    char* parseString();
    
    void appendFloat(float f);
    
    void appendDoubel(double d);
    
    void appendBytes(void *, int length);
    
    // 从磁盘读文件到内存中
    void readFile(const char *filename);
    
    // 把内存数据写到磁盘文件中
    void writeFile(const char *filename);
    
    void printChar();
    
    void printHexadecimal();
    
    //设置解析位置
    inline void setPos(int _pos){pos = _pos;}
    
    //跳过length个位置
    inline void skip(int length){pos += length;}
private:
    vector<char> m_data;
    int pos = 0;
};

#endif /* MutableData_hpp */

//mode: r r+ rb+ w w+ a a+ windows:文件
//1.在windows系统中，文本模式下，文件以"\r\n"代表换行。若以文本模式打开文件，并用fputs等函数写入换行符"\n"时，函数会自动在"\n"前面加上"\r"。即实际写入文件的是"\r\n" 。
//2.在类Unix/Linux系统中文本模式下，文件以"\n"代表换行。所以Linux系统中在文本模式和二进制模式下并无区别。
//FILE * fopen(const char * path,const char * mode);

//size是数据项大小  count是数据项个数 返回写入的数据项个数
//size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);

//返回读的数据项个数
//size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;

//从文件流中格式化读取数据
//int fscanf(FILE*stream, const char*format, [argument...]);

//数据格式化输出到输出流
//int fprintf( FILE *stream, const char *format, [ argument ]...)

//把位置指针直到开头
//rewind函数作用等同于 (void)fseek(stream, 0L, SEEK_SET)

//fromwhere是指偏移的起始位置， offset是偏移
//stream将指向以fromwhere（偏移起始位置：文件头0(SEEK_SET)，当前位置1(SEEK_CUR)，文件尾2(SEEK_END)）为基准，偏移offset（指针偏移量）个字节的位置
//int fseek(FILE *stream, long offset, int fromwhere);

//fclose(File *stream)
