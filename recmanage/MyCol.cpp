//
// Created by luogan on 16-10-15.
//

#include "MyCol.h"

std::string MyCol::toString()
{
    char c[100];
    std::string ans;
    sprintf(c,"%d|%d|%d|%d|%s|%s|",type,len,isPrimary,canBeNull,name.c_str(),outerTableName.c_str());
    ans=c;
    for (size_t i=0;i<wordList.size();++i)
    {
        ans+=wordList[i]+"#";
    }
    return ans;
}

bool MyCol::getFromString(std::string rec)
{
    wordList.clear();
    char fin[100];
    std::string words;
    sscanf(rec.c_str(),"%d|%d|%d|%d|%s",&type,&len,&isPrimary,&canBeNull,&fin);
    words=fin;
    size_t last=0,i;
    for (i=0;i<words.size();++i)
    {
        if (words[i]=='|')
        {
            name=words.substr(0,i);
            last=i+1;
            break;
        }
    }
    for (++i;i<words.size();++i)
    {
        if (words[i]=='|')
        {
            outerTableName=words.substr(last,i-last);
            last=i+1;
            break;
        }
    }
    for (++i;i<words.size();++i)
    {
        if (words[i]=='#')
        {
            wordList.push_back(words.substr(last,i-last));
            last=i+1;
        }
    }
    return true;
}