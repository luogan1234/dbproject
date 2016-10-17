#include <iostream>
#include <cstdio>
#include "recmanage/MyTable.h"
#include "StaticMethod.h"
#include "recmanage/MyFileIO.h"

using namespace std;

int main() {
    FileManager fm;
    int fileID;
    fm.openFile("test", fileID);
    char *b = new char[PAGE_SIZE];
    fm.readPage(fileID, 0, b, 0);
    MyData myData(b, 0, 10);
    myData.print();
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
    myData.setData("012340aaaabcb    0asdf$1$");
    MyData myData2("011110adfojdioejo0asdffff$0aa$"), myData3("011110adfo22ioejo0ascdffff$0aa$");
    myData.print();
    int num, offset;
    MyCol *tar = tc.getByName("teset3", num, offset);
    bool isNull;
    char *res;
    int dataLen;
    myData.getValue(num, offset, tar, isNull, res, dataLen);
    printf("%d\n", isNull);
    for (size_t i = 0; i < dataLen; ++i) {
        printf("%c", res[i]);
    }
    printf("\n");

    tar = tc.getByName("teset1", num, offset);
    myData.format(33, tar, res, dataLen);
    myData.setValue(num, offset, tar, false, res, dataLen);
    myData.print();

    myData.getValue(num, offset, tar, isNull, res, dataLen);
    printf("%d\n", StaticMethod::toInt(res));


    printf("-------------------------------------\n");
    MyFileIO myFileIO;
    myFileIO.createDB("tes1");
    myFileIO.createDB("tes2");
    myFileIO.useDB("tes1");
    myFileIO.dropDB("tes2");
    myFileIO.createTable("my1", tc.toString());
    myFileIO.createTable("my2", tc.toString());
    myFileIO.dropTable("my1");
    MyTable *m;
    m = myFileIO.getTable("my2");
    m->insertData(&myData2);
    m->insertData(&myData3);
    m->insertData(&myData);
    Constraints con(1), con2(4);
    Updates upd(&tc);
    std::vector<MyData *> ress;
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
    m->deleteData(&con2);
    ress.clear();
    m->searchData(&con,ress);
    ress.clear();
    m->updateData(&con,&upd);
    return 0;
}