//
// Created by luogan on 16-10-14.
//

#ifndef DBPROJECT_TABELCOLS_H
#define DBPROJECT_TABELCOLS_H
#include "MyCol.h"
#include <string>
#include <vector>

class TableCols
{
public:
    std::vector<MyCol> cols;
    int n,offset[31],order[31],num[31];

    TableCols()
    {
        cols.clear();
    };

    TableCols(std::string rec)
    {
        getFromString(rec);
    };

    void addCol(MyCol col)
    {
        cols.push_back(col);
    }

    std::string toString();

    bool getFromString(std::string rec);

    void setOrder();
    //num代表第几个varchar，offset代表数据起始位置偏移量，通过列名查找
    MyCol* getByName(std::string _name,int &_num,int &_offset);
    //通过列号查找，VARCHAR将统一放在定长数据之后
    MyCol* getByCol(int colID,int &_num,int &_offset);
    //通过数据存储的顺序查找
    MyCol* getByOrder(int p,int &_num,int &_offset);
    //通过名字查找列ID
    int getColID(std::string _name);

    //-----add by lmq------
    void setPrimary(std::string name)
    {
        int len = cols.size();
        for (int i = 0; i < len; ++i)
        {
            if(name == cols[i].name){
                cols[i].isPrimary = true;
                break;
            }
        }
    }
};

#endif //DBPROJECT_TABELCOLS_H
