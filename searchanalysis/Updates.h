//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_UPDATES_H
#define DBPROJECT_UPDATES_H


#include "../recmanage/MyData.h"
#include "../recmanage/TableCols.h"

#define COMPARE_EQUAL 0
#define COMPARE_NOT_EQUAL 1
class Updates {
private:
    TableCols *cols;
    MyCol *tar;
    int num,offset,newDataLen,oldDataLen,compareDataLen;
    char *newRes,*oldRes,*compareRes;
    bool oldIsNull;
    int compare()
    {
        if (compareDataLen!=oldDataLen)
            return COMPARE_NOT_EQUAL;
        else
            for (int i=0;i<compareDataLen;++i)
                if (compareRes[i]!=oldRes[i])
                    return COMPARE_NOT_EQUAL;
        return COMPARE_EQUAL;
    }
public:
    Updates()
    {

    }

    Updates(TableCols *c)
    {
        cols=c;
        tar=cols->getByName("teset2",num,offset);
        MyData::format("asdf",tar,compareRes,compareDataLen);
    }

    bool update(MyData *myData)
    {
        myData->getValue(num,offset,tar,oldIsNull,oldRes,oldDataLen);
        MyData::format("abcde",tar,newRes,newDataLen);
        if (compare()==COMPARE_EQUAL)
        {
            myData->setValue(num,offset,tar,false,newRes,newDataLen);
            return true;
        }
        return false;
    }

};


#endif //DBPROJECT_UPDATES_H
