//
// Created by luogan on 16-10-29.
//

#ifndef DBPROJECT_MYINDEX_H
#define DBPROJECT_MYINDEX_H


#include <string>
#include "../bufmanager/BufPageManager.h"
#include "MyData.h"

class MyTable;

class MyIndex {
private:
    void init();

    void getInfo();
public:
    std::string name;
    short colID;
    char type;
    bool canNull,canDel;
    int valueType;
    int valueLen;
    BufPageManager* bm;
    int fileID;
    int totalUsed,index,rootPage;
    vector<char*> pages;
    vector<int> nows,slots,indexs;
    MyTable* myTable;
    MyValue values[2000];
    MyValue vl,vn,vr;

    MyIndex(BufPageManager* bm,std::string n,short c,char t,bool cn,bool cd,int vt,int vl,int f)
    {
        this->bm=bm;
        name=n;colID=c;type=t;canNull=cn;canDel=cd;
        valueType=vt;valueLen=vl;fileID=f;
        this->vl.res=new char[2000];vn.res=new char[2000];vr.res=new char[2000];
        init();
    }

    MyIndex(BufPageManager* bm,std::string n,short c,int f,MyTable* m)
    {
        this->bm=bm;
        name=n;colID=c;fileID=f;
        vl.res=new char[2000];vn.res=new char[2000];vr.res=new char[2000];
        myTable=m;
        getInfo();
    }
    //簇集索引插入的位置必须由索引记录决定
    int insertDataClustered(MyValue &value);
    //范围在value1~value2之间，要求value1<=value2，type1为<=或<，type2为>=或>，用以代表开闭区间，或者取undefined表示不限制
    bool findData(MyValue* value1,int type1,MyValue* value2,int type2,std::vector<std::pair<int,int> > &res);
    //pp=1是添加数据，唯一索引要求不重复，pp=2是删除数据，要求得有那项值才能进行删除
    bool searchData(MyValue* value,int page,int slot,int pp);
    //slot为-1是簇集索引，插入一条值
    bool insertData(MyValue* value,int page,int slot);
    //slot为-1是簇集索引，删除一条值
    bool deleteData(MyValue* value,int page,int slot);

    ~MyIndex()
    {
        delete vl.res;
        delete vn.res;
        delete vr.res;
    }
};


#endif //DBPROJECT_MYINDEX_H
