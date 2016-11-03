//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_UPDATES_H
#define DBPROJECT_UPDATES_H


#include "../recmanage/MyData.h"
#include "../recmanage/TableCols.h"

class Updates {
private:
    TableCols *cols;
    MyCol *tar;
    int num,offset;
    MyValue oldValue,comValue,newValue;
public:
    Updates()
    {

    }

    Updates(TableCols *c)
    {
        cols=c;
        tar=cols->getByName("teset2",num,offset);
        MyData::format("asdf",tar,comValue);
    }

    bool update(MyData *myData)
    {
        myData->getValue(num,offset,tar,oldValue);
        MyData::format("abcde",tar,newValue);
        if (oldValue.compare(&comValue)==COMPARE_EQUAL)
        {
            myData->setValue(num,offset,tar,newValue);
            return true;
        }
        return false;
    }

};


#endif //DBPROJECT_UPDATES_H
