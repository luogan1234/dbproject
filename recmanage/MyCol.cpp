//
// Created by luogan on 16-10-15.
//

#include "MyCol.h"
#include "../StaticMethod.h"

std::string MyCol::toString()
{
    char c[100];
    std::string ans;
    char format[20];
    sprintf(format,"%cd%c%cd%c%cd%c%cd%c%cs%c%cs%c",'%',StaticMethod::p1,'%',StaticMethod::p1,'%',StaticMethod::p1,'%',StaticMethod::p1,'%',StaticMethod::p1,'%',StaticMethod::p1);
    sprintf(c,format,type,len,isPrimary,canBeNull,name.c_str(),outerTableName.c_str());
    ans=c;
    for (size_t i=0;i<wordList.size();++i)
    {
        ans+=wordList[i]+StaticMethod::p2;
    }
    return ans;
}

bool MyCol::getFromString(std::string rec)
{
    wordList.clear();
    char fin[100];
    std::string words;
    char format[20];
    sprintf(format,"%cd%c%cd%c%cd%c%cd%c%cs%c",'%',StaticMethod::p1,'%',StaticMethod::p1,'%',StaticMethod::p1,'%',StaticMethod::p1,'%',StaticMethod::p1);
    sscanf(rec.c_str(),format,&type,&len,&isPrimary,&canBeNull,&fin);
    words=fin;
    size_t last=0,i;
    for (i=0;i<words.size();++i)
    {
        if (words[i]==StaticMethod::p1)
        {
            name=words.substr(0,i);
            last=i+1;
            break;
        }
    }
    for (++i;i<words.size();++i)
    {
        if (words[i]==StaticMethod::p1)
        {
            outerTableName=words.substr(last,i-last);
            last=i+1;
            break;
        }
    }
    for (++i;i<words.size();++i)
    {
        if (words[i]==StaticMethod::p2)
        {
            wordList.push_back(words.substr(last,i-last));
            last=i+1;
        }
    }
    return true;
}