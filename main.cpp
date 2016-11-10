#include <iostream>
#include <cstdio>
#include "recmanage/MyTable.h"
#include "StaticMethod.h"
#include "recmanage/MyFileIO.h"
#include "recmanage/MyValue.h"
#include "fileio/FileManager.h"

using namespace std;

int main() {
    FileManager fm;
    int fileID;
    MyCol m1(TYPE_INT, 10, false, false, "teset1");
    MyCol m2(TYPE_VARCHAR, 50, false, false, "teset2");
    MyCol m3(TYPE_VARCHAR, 5, false, false, "teset3");
    MyCol m4(TYPE_CHAR, 11, false, false, "teset4");
    TableCols tc;
    tc.addCol(m1);
    tc.addCol(m2);
    tc.addCol(m3);
    tc.addCol(m4);
    tc.setOrder();
/*    myData.print();
    int num, offset;
    MyCol *tar = tc.getByName("teset3", num, offset);
    MyValue v;
    myData.getValue(num, offset, tar, v);
    printf("%d\n", v.isNull);
    for (size_t i = 0; i < v.dataLen; ++i) {
        printf("%c", v.res[i]);
    }
    printf("\n");

    tar = tc.getByName("teset1", num, offset);
    MyValue v2;
    myData.format(33, tar, v2);
    myData.setValue(num, offset, tar, v2);
    myData.print();
    MyValue v3;
    myData.getValue(num, offset, tar, v3);
    printf("%d\n", StaticMethod::toInt(v3.res));*/


    printf("-------------------------------------\n");
    MyFileIO myFileIO;
    myFileIO.createDB("tes1");
//    myFileIO.createDB("tes2");
    myFileIO.useDB("tes1");
//    myFileIO.dropDB("tes2");
//    myFileIO.createTable("my1", tc.toString());
    myFileIO.createTable("my2", tc.toString());
//    myFileIO.dropTable("my1");
    MyTable *myTable;
    myTable = myFileIO.getTable("my2");
    bool p=myTable->createIndex(0,INDEX_UNCLUSTERED,true,true);
    printf("%d\n",p);
//    MyData* myData=new MyData("012350aaaabcb    0asdf$1$");
//    MyData* myData2=new MyData("011240adfojdioejo0asdffff$0aa$");
//    MyData* myData3=new MyData("013120adfo22ioejo0ascdffff$0aa$");
    vector<MyData*> datas;
    datas.clear();
//    datas.push_back(myData);
//    datas.push_back(myData2);
//    datas.push_back(myData3);
    vector<MyData *> ress;
    ress.clear();
    Constraints con(1),con0(0);
    Updates upd(&tc);
    myTable->searchData(&con, ress);
    printf("%d\n",ress.size());
    int num,offset;
    MyCol* tar = tc.getByName("teset1", num, offset);
    MyValue value;
    int tt1=0,tt2=1000,tt3=99,tt4=100;
    for (int i=0;i<100000;++i)
    {
        MyData* data=new MyData("000000adfo22ioejo0ascdffff$0aa$");
        MyData::format(i, tar, value);
        data->setValue(num, offset, tar, value);
        datas.push_back(data);
    }
    if (myTable->isUnique(datas));
    printf("%d\n",datas.size());
    myTable->insertData(datas);
/*    datas.clear();
    for (int i=0;i<1000;++i)
    {
        MyData* data=new MyData("000000adfo22ioejo0ascdffff$0aa$");
        MyData::format(i, tar, value);
        data->setValue(num, offset, tar, value);
        datas.push_back(data);
    }
    if (myTable->isUnique(datas));
    printf("%d\n",datas.size());
    bool pp=myTable->insertData(datas);
    printf("%d\n",pp);
    myTable->indexInfoUpdate();*/
//    myData=new MyData("012340aaaabcb    0asdf$1$");
//    if (myTable->isUnique(myData))
//        myTable->insertData(myData);
//    myTable->indexInfoUpdate();
    ress.clear();
    myTable->searchData(&con, ress);
    printf("%d\n",ress.size());
    MyValue v1,v2;
    MyData::format(98,tar,v1);
    MyData::format(101,tar,v2);
    MyIndex* index=myTable->getIndex(0);
    vector<pair<int,int>> res;
    index->findData(&v1,COMPARE_SMALLER_EQUAL,&v2,COMPARE_LARGER_EQUAL,res);
    ress.clear();
    myTable->getData(res,ress);
    printf("%d\n",res.size());
    printf("%d\n",ress.size());
    myTable->updateDataSafe(&con0,&upd);
    res.clear();
//    index->findData(&v1,COMPARE_UNDEFINED,&v2,COMPARE_UNDEFINED,res);
    index->findData(&v1,COMPARE_SMALLER_EQUAL,&v2,COMPARE_LARGER_EQUAL,res);
    ress.clear();
    myTable->searchData(&con, ress);
    printf("%d\n",ress.size());
    ress.clear();
    myTable->getData(res,ress);
    printf("%d\n",res.size());
    printf("%d\n",ress.size());
//    for (int i=0;i<ress.size();++i)
//        ress[i]->print();
//    for (size_t i = 0; i < ress.size(); ++i)
//        ress[i]->print();
/*    Constraints con(1), con2(4);
    Updates upd(&tc);
    ress.clear();
    m->searchData(&con, ress);
    for (size_t i = 0; i < ress.size(); ++i)
        ress[i]->print();
    printf("-------------------------------------\n");
    m->deleteData(&con2);
    ress.clear();
    m->searchData(&con, ress);
    for (size_t i = 0; i < ress.size(); ++i)
        ress[i]->print();
    printf("-------------------------------------\n");
    m->updateData(&con, &upd);
    ress.clear();
    m->searchData(&con, ress);
    for (size_t i = 0; i < ress.size(); ++i)
        ress[i]->print();
    printf("-------------------------------------\n");
    for (int i = 0; i < 300000; ++i)
    {
        m->insertData(&myData);
        m->insertData(&myData2);
        m->insertData(&myData3);
    }
    vector<MyData*> datas;
    for (int i=0;i<300000;++i)
    {
        datas.push_back(&myData);
        datas.push_back(&myData2);
        datas.push_back(&myData3);
    }
    m->insertData(datas);
    printf("insert done\n");
    m->deleteData(&con2);
    printf("delete done\n");
    ress.clear();
    m->searchData(&con,ress);
    printf("%d\n",ress.size());
    m->updateData(&con,&upd);
    ress.clear();
    m->searchData(&con,ress);
    printf("%d\n",ress.size());*/
    myFileIO.closeAll();
    return 0;
}