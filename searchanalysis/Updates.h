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
        tar=cols->getByName("teset1",num,offset);
        MyData::format(99,tar,comValue);
    }
    //返回true表示更新成功
    bool update(MyData *myData)
    {
        myData->getValue(num,offset,tar,oldValue);
        MyData::format(99,tar,newValue);
//        if (oldValue.compare(&comValue)==COMPARE_EQUAL)
        {
            myData->setValue(num,offset,tar,newValue);
            return true;
        }
        return false;
    }

};


#endif //DBPROJECT_UPDATES_H
