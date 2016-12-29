//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_CONSTRAINTS_H
#define DBPROJECT_CONSTRAINTS_H


#include <vector>
#include <iostream>
#include "../recmanage/MyData.h"
#include "../recmanage/MyValue.h"
#include "../recmanage/TableCols.h"
#include "../recmanage/MyCol.h"

// #include "../recmanage/MyTable.h"
#include "../query/MyStruct.h"
class Constraints {
private:
    // int ranp,tot;
    int kind;
    std::vector<WhereClause*> *where;
    std::vector<MyCol*> myCols;
    std::vector<int> nums, offsets;
    TableCols *tc;

    //many tables 
    // std::vector<TableCols*> *tcs;
    // std::vector<std::vector<MyCol*>*> myCols2;
    // std::vector<std::vector<int>*> nums2, offsets2;

    // std::vector<MyTable*> *myTbs;
    // std::vector<Selector*> *selector;
    //0 select *
public:
    Constraints(int k = 0)
    {
        kind = k;
        where = 0;
        // 0 all true
        // 1 delete command
        //2 select command
    }
    Constraints(std::vector<WhereClause*> *v, TableCols *t, int k)
    {
        kind = k;
        tc = t;
        where = v;
        int len = v->size();
        myCols.clear();
        nums.clear();
        offsets.clear();
        MyCol* myCol;
        int num, offset;
        for (int i = 0; i < len; ++i)
        {
            myCol = tc->getByName((*where)[i]->leftCol->colName, num, offset);
            myCols.push_back(myCol);
            nums.push_back(num);
            offsets.push_back(offset);
        }
    }
    // Constraints(std::vector<WhereClause*> *v, std::vector<TableCols*> *t, int k)
    // {
    //     kind = k;
    //     tcs = t;
    //     where = v;
    //     myCols2.clear();
    //     nums2.clear();
    //     offsets2.clear();
    //     int len = v->size(), tb_len = t->size();
    //     for (int i = 0; i < tb_len; ++i)
    //     {
    //         MyCol* myCol;
    //         int num, offset;
    //         std::vector<MyCol*> *t_col = new std::vector<MyCol*>;
    //         std::vector<int> *t_num = new std::vector<int>;
    //         std::vector<int> *t_offset = new std::vector<int>;
    //         t_col->clear();
    //         t_num->clear();
    //         t_offset->clear();
    //         for (int j = 0; j < len; ++j)
    //         {
    //             myCol = tcs[i]->getByName((*where)[j]->leftCol->colName, num, offset);
    //             t_col->push_back(myCol);
    //             t_num->push_back(num);
    //             t_offset->push_back(offset);
    //         }
    //         myCols2.push_back(t_col);
    //         nums2.push_back(t_num);
    //         offsets2.push_back(t_offset);
    //     }
    // }
    //返回true表示满足条件
    bool checkData(MyData *data)
    {
        if(where == 0) return true;
        int len = where->size();
        // if(len == 0) return false;
        switch (kind){
            case 0:
                return true;
            case 1:
                for (int i = 0; i < len; ++i)
                {
                    MyValue value;
                    data->getValue(nums[i],offsets[i],myCols[i],value);
                    if(!fitCondition((*where)[i], value)){
                        // std::cout << "bug2";
                        return false;
                    }
                }
                return true;
            default:
                return false;
        }
    }
    bool fitCondition(WhereClause* w, MyValue v)
    {
        // 0 is null
        // 1 is not null
        // 2 =
        // 3 <>
        // 4 <=
        // 5 >=
        // 6 <
        // 7 >
          // rightValKind
          //   0 no
          //   1 int value
          //   2 col name
          //   3 string
        if (w->rightValKind == 2){
            if(w->rightCol2->hasTableName == false || !(w->op == 2))
                return false;
        }
        switch (w->op){
            case 0:
                return v.isNull;
            case 1:
                return !(v.isNull);
            case 2:
                 if(v.type == 0){
                    if(w->rightValKind != 1){
                        std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
                        return false;
                    } else 
                        return *(int*)(v.res) == w->rightCol1;
                 } else{
                    if(w->rightValKind != 3){
                        std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
                        return false;
                    } else return !strncmp(v.res, w->rightCol3.c_str(), v.dataLen);
                 }
            case 3:
                 if(v.type == 0){
                    if(w->rightValKind != 1){
                        std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
                        return false;
                    } else return *(int*)(v.res) != w->rightCol1;
                 } else{
                    if(w->rightValKind != 3){
                        std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
                        return false;
                    } else return strncmp(v.res, w->rightCol3.c_str(), v.dataLen);
                 }
            case 4:
                if(v.type != 0 || w->rightValKind != 1){
                    std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
                    return false;
                } else return *(int*)(v.res) <= w->rightCol1;
            case 5:
                if(v.type != 0 || w->rightValKind != 1){
                    std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
                    return false;
                } else return *(int*)(v.res) >= w->rightCol1;
            case 6:
                if(v.type != 0 || w->rightValKind != 1){
                    std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
                    return false;
                } else return *(int*)(v.res) < w->rightCol1;
            case 7:
                if(v.type != 0 || w->rightValKind != 1){
                    std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
                    return false;
                } else return *(int*)(v.res) > w->rightCol1;
            default:
                std::cout << "ERROR TYPE IN WHERECLAUSE" << std::endl;
        }
    }
};


#endif //DBPROJECT_CONSTRAINTS_H
