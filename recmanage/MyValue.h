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

    int compare(MyValue* v);    //NULL最小，包括比""小，索引中使用

    int compareNoNull(MyValue* v);   //NULL不与任何其他串可比，都是undefined，在查询时NULL不参与运算和比较

    static int compare(MyValue* v1,MyValue* v2);    //NULL最小，包括比""小，索引中使用

    static int compareNoNull(MyValue* v1,MyValue* v2);  //NULL不与任何其他串可比，都是undefined，在查询时NULL不参与运算和比较

    void print();

    void get(int valueType,int valueLen,bool canNull,char *pos,int len);
};


#endif //DBPROJECT_MYVALUE_H
