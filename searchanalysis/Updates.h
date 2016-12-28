//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_UPDATES_H
#define DBPROJECT_UPDATES_H


#include "../recmanage/MyData.h"
#include "../recmanage/TableCols.h"
#include "../query/MyStruct.h"

class Updates {
private:
    TableCols *cols;
    std::vector<MyCol*> tar;
    std::vector<int> num,offset;
    // std::vector<MyValue> oldValue,comValue,newValue;
    std::vector<MyValue> comValue;
    std::vector<SetClause*> *set;
public:
    Updates()
    {

    }

    Updates(TableCols *c, std::vector<SetClause*> *s)
    {
        set = s;
        cols = c;
        int len = s->size();
        tar.clear();
        num.clear();
        offset.clear();
        // oldValue.clear();
        comValue.clear();
        // newValue.clear();
        int l_num, l_offset;
        for (int i = 0; i < len; ++i)
        {
            tar.push_back(cols->getByName((*set)[i]->colName ,l_num,l_offset));
            num.push_back(l_num);
            offset.push_back(l_offset);
            MyValue l_value;
            switch ((*set)[i]->val->kind){
                case 1:
                    MyData::format((*set)[i]->val->intVal, tar[i], l_value);
                    break;
                case 2:
                    MyData::format((*set)[i]->val->strVal, tar[i], l_value);
                    break;
                case 3:
                    MyData::format("", tar[i], l_value, true);
                    break;
                default:
                    break;
            }
            comValue.push_back(l_value);
        }
    }
    //返回true表示更新成功
    bool update(MyData *myData)
    {
        int len = set->size();
        int i;
        for (i = 0; i < len; ++i)
        {
            myData->setValue(num[i],offset[i],tar[i],comValue[i]);
        }
        if (i == len) return true;
        else return false;            
    }
};

#endif //DBPROJECT_UPDATES_H
