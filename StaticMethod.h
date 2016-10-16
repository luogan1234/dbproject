//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_STATICMETHOD_H
#define DBPROJECT_STATICMETHOD_H

#include <string>

class StaticMethod
{
public:
    static char p1,p2,p3;
    void static addBlank(std::string &word,int len)
    {
        int n=word.size();
        while (n<len)
            ++n,word+=' ';
    }

    void static removeBlank(std::string &word)
    {
        int n=word.size(),i=n-1;
        while (i>=0&&word[i]==' ')
            --i;
        word=word.substr(0,i+1);
    }

    int static toInt(char* res)
    {
        return *(int*)res;
    }

    unsigned int static toUnsigned(char* res)
    {
        return *(unsigned int*)res;
    }
};

#endif //DBPROJECT_STATICMETHOD_H
