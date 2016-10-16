#include <iostream>
#include <cstdio>
#include "recmanage/MyTable.h"
#include "StaticMethod.h"
#include "recmanage/MyFileIO.h"

using namespace std;

int main() {
    FileManager fm;
    int fileID;
    fm.openFile("test",fileID);
    char* b=new char[PAGE_SIZE];
    fm.readPage(fileID,0,b,0);
    MyData myData(b,0,10);
    myData.print();
    MyCol m1(TYPE_INT,10,false,false,"teset1");
    MyCol m2(TYPE_VARCHAR,50,false,false,"teset2");
    MyCol m3(TYPE_VARCHAR,5,false,false,"teset3");
    MyCol m4(TYPE_CHAR,11,false,false,"teset4");
    TableCols tc;
    tc.addCol(m1);
    tc.addCol(m2);
    tc.addCol(m3);
    tc.addCol(m4);
    tc.setOrder();
    myData.setData("012340aaaabcb    0asdf$1$");
    myData.print();
    int num,offset;
    MyCol* tar=tc.getByName("teset3",num,offset);
    bool isNull;
    char* res;
    int dataLen;
    myData.getValue(num,offset,tar,isNull,res,dataLen);
    printf("%d\n",isNull);
    for (size_t i=0;i<dataLen;++i)
    {
        printf("%c",res[i]);
    }
    printf("\n");

    tar=tc.getByName("teset1",num,offset);
    myData.format(33,tar,res,dataLen);
    myData.setValue(num,offset,tar,false,res,dataLen);
    myData.print();

    myData.getValue(num,offset,tar,isNull,res,dataLen);
    printf("%d\n",StaticMethod::toInt(res));


    MyFileIO myFileIO;
    myFileIO.createDB("tes1");
    myFileIO.createDB("tes2");
    myFileIO.useDB("tes1");
    myFileIO.dropDB("tes2");
    myFileIO.createTable("my1",tc.toString());
    myFileIO.createTable("my2",tc.toString());
    myFileIO.dropTable("my1");
    MyTable *m;
    m=myFileIO.getTable("my2");
//    m->insertData(myData);
    Constraints con;
    std::vector<MyData> ress;
    ress.clear();
    m->searchData(&con,ress);
    for (size_t i=0;i<ress.size();++i)
        ress[i].print();
    return 0;
}