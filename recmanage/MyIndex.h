//
// Created by luogan on 16-10-29.
//

#ifndef DBPROJECT_MYINDEX_H
#define DBPROJECT_MYINDEX_H


#include <string>
#include "../bufmanager/BufPageManager.h"

class MyIndex {
public:
    std::string name;
    short colID;
    char type;
    int valueType;
    int valueLen;
    BufPageManager* bm;
    int fileID;

    MyIndex(BufPageManager* bm,std::string n,short c,char t,int vt,int vl,int f)
    {
        this->bm=bm;
        name=n;colID=c;type=t;valueType=vt;valueLen=vl;fileID=f;
    }

    MyIndex(BufPageManager* bm,std::string n,short c,int f)
    {
        this->bm=bm;
        name=n;colID=c;fileID=f;
    }

    void init();
};


#endif //DBPROJECT_MYINDEX_H
