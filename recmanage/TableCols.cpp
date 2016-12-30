//
// Created by luogan on 16-10-15.
//

#include "TableCols.h"
#include "../StaticMethod.h"
#include "MyData.h"
#include "MyTable.h"
#include "MyFileIO.h"

using namespace std;

string TableCols::toString()
{
    string ans="";
    for (size_t i=0;i<cols.size();++i)
    {
        ans+=cols[i].toString()+StaticMethod::p3;
    }
    return ans;
}

bool TableCols::getFromString(string rec)
{
    cols.clear();
    size_t last=0,i,size=rec.size();
    for (i=0;i<size;++i)
    {
        if (rec[i]==StaticMethod::p3)
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

MyCol* TableCols::getByName(string _name,int &_num,int &_offset)      //num代表第几个varchar，offset代表数据起始位置偏移量
{
    for (int i=0;i<n;++i)
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

MyCol* TableCols::getByCol(int colID,int &_num,int &_offset)
{
    if (colID<n)
    {
        for (int i=0;i<n;++i)
            if (order[i]==colID)
            {
                _num=num[i];
                _offset=offset[i];
            }
        return &cols[colID];
    }
    _num=_offset=-1;
    return 0;
}

MyCol* TableCols::getPrimaryCol(int &_num,int &_offset)
{
    for (int i=0;i<n;++i)
        if (cols[i].isPrimary)
            return getByCol(i,_num,_offset);
    _num=_offset=-1;
    return 0;
}

MyCol* TableCols::getByOrder(int p, int &_num,int &_offset)
{
    if (p<n)
    {
        _num=num[p];_offset=offset[p];
        return &cols[order[p]];
    }
    _num=_offset=-1;
    return 0;
}

int TableCols::getColID(string _name)
{
    for (int i=0;i<n;++i)
        if (cols[order[i]].name==_name)
            return i;
    return -1;
}

int TableCols::hasPrimaryKey()
{
    for (int i=0;i<n;++i)
        if (cols[i].isPrimary)
            return i;
    return -1;
}

bool TableCols::hasForeignKey()
{
    for (int i=0;i<n;++i)
        if (cols[i].outerTableName!="")
            return true;
    return false;
}

void TableCols::getAllForeignKey(vector<pair<int,string> > &res)
{
    res.clear();
    for (int i=0;i<n;++i)
        if (cols[i].outerTableName!="")
            res.push_back(make_pair(i,cols[i].outerTableName));
}

void TableCols::getForeignKey(string name,vector<int> &res)
{
    res.clear();
    for (int i=0;i<n;++i)
        if (cols[i].outerTableName==name)
            res.push_back(i);
}

bool TableCols::checkData(MyData* data,MyFileIO* myFileIO)
{
    int num,offset,num2,offset2;
    MyCol* myCol,*col;
    MyValue value,v;
    std::vector<std::pair<int,int> > res;
    std::vector<MyData*> datas;
    for (int i=0;i<n;++i)
    {
        myCol=getByCol(i,num,offset);
        data->getValue(num,offset,myCol,value);
        if (value.isNull)
            continue;
        if (cols[i].wordList.size()>0)
        {
            if (!myCol->isInWordList(value))
                return false;
        }
        if (cols[i].outerTableName!="")
        {
            MyTable *table=myFileIO->getTable(cols[i].outerTableName);
            if (table&&table->cols.hasPrimaryKey()!=-1)
            {
                if (value.type!=TYPE_INT)
                {
                    delete table;
                    return false;
                }
                MyIndex* myIndex=table->getClusteredIndex();
                if (!myIndex)
                {
                    delete table;
                    return false;
                }
                myIndex->findData(&value,COMPARE_SMALLER_EQUAL,&value,COMPARE_LARGER_EQUAL,res);
                datas.clear();
                table->getData(res,datas);
                col=table->cols.getPrimaryCol(num2,offset2);
                int m=datas.size();bool p=false;
                for (int j=0;j<m;++j)
                {
                    datas[j]->getValue(num2,offset2,col,v);
                    if (value.compare(&v)==COMPARE_EQUAL)
                    {
                        p=true;
                        break;
                    }
                }
                if (!p)
                {
                    delete table;
                    delete myIndex;
                    return false;
                }
                delete myIndex;
            }
            if (table)
                delete table;
        }
    }
    return true;
}