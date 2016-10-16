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

    MyCol* getByName(std::string _name,int &_num,int &_offset);      //num代表第几个varchar，offset代表数据起始位置偏移量
};

#endif //DBPROJECT_TABELCOLS_H