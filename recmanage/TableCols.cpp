//
// Created by luogan on 16-10-15.
//

#include "TableCols.h"

std::string TableCols::toString()
{
    std::string ans="";
    for (size_t i=0;i<cols.size();++i)
    {
        ans+=cols[i].toString()+"$";
    }
    return ans;
}

bool TableCols::getFromString(std::string rec)
{
    cols.clear();
    size_t last=0,i,size=rec.size();
    for (i=0;i<size;++i)
    {
        if (rec[i]=='$')
        {
            cols.push_back(MyCol(rec.substr(last,i-last)));
            last=i+1;
        }
    }
    setOrder();
}

void TableCols::setOrder()
{
    n=cols.size();
    int i,j=0;offset[0]=num[0]=0;
    for (i=0;i<n;++i)
        switch (cols[i].type)
        {
            case TYPE_INT:
                order[j]=i;
                offset[j+1]=offset[j]+5;
                num[j+1]=num[j];
                ++j;
                break;
            case TYPE_CHAR:
                order[j]=i;
                offset[j+1]=offset[j]+cols[i].len+1;
                num[j+1]=num[j];
                ++j;
                break;
        }
    for (i=0;i<n;++i)
        switch (cols[i].type)
        {
            case TYPE_VARCHAR:
                order[j]=i;
                offset[j+1]=offset[j];
                num[j+1]=num[j]+1;
                ++j;
                break;
        }
}

MyCol* TableCols::getByName(std::string _name,int &_num,int &_offset)      //num代表第几个varchar，offset代表数据起始位置偏移量
{
    for (size_t i=0;i<n;++i)
    {
        if (cols[order[i]].name==_name)
        {
            _num=num[i];
            _offset=offset[i];
            return &cols[order[i]];
        }
    }
    _num=_offset=-1;
    return 0;
}