//
// Created by luogan on 16-11-3.
//

#ifndef DBPROJECT_MODIFYINFO_H
#define DBPROJECT_MODIFYINFO_H


#include "MyData.h"

class ModifyInfo {
public:
    MyData* data;
    int oldPage,oldSlot;
    int newPage,newSlot;

    ModifyInfo()
    {}

    ~ModifyInfo()
    {
        delete data;
    }
};


#endif //DBPROJECT_MODIFYINFO_H
