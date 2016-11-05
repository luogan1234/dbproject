//
// Created by luogan on 16-10-29.
//

#ifndef DBPROJECT_MYVALUE_H
#define DBPROJECT_MYVALUE_H


#include "../consts.h"

class MyValue {
public:
    bool isNull;
    char* res;
    int dataLen;
    int type;

    MyValue()
    {
    }

    int compare(MyValue* v);

    static int compare(MyValue* v1,MyValue* v2);

    void print();
};


#endif //DBPROJECT_MYVALUE_H
