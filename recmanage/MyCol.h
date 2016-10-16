//
// Created by luogan on 16-10-14.
//

#ifndef DBPROJECT_MYCOL_H
#define DBPROJECT_MYCOL_H
#include <string>
#include <vector>
#include "../consts.h"
class MyCol
{
public:
    int type,len;
    bool isPrimary,canBeNull;       //是否是主键
    std::string name,outerTableName;    //名字和外键
    std::vector<std::string> wordList;

    MyCol(int t,int l,bool i,bool c,std::string n,std::string o="")
    {
        type=t;len=l;isPrimary=i;canBeNull=c;name=n;
        wordList.clear();outerTableName=o;
    }

    MyCol(std::string rec)
    {
        getFromString(rec);
    }

    void addWordList(std::string w)
    {
        wordList.push_back(w);
    }

    std::string toString();

    bool getFromString(std::string rec);

};
#endif //DBPROJECT_MYCOL_H