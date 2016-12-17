#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H

#include "../recmanage/MyFileIO.h"
#include "../recmanage/TableCols.h"
#include "../recmanage/MyTable.h"
#include "../recmanage/MyData.h"
struct MyType
{
    int dataType;
    int dataWide;
    MyType(int dataType, int dataWide):dataType(dataType), dataWide(dataWide)
    {};
    ~MyType();
};
struct AllValue
{
    int intVal;
    string strVal;
    int kind;
    AllValue(int p, bool is_null)
    {
        if(is_null) 
            kind = 3;
        else{
            intVal = p;
            kind = 1;
        }
    };
    AllValue(char *p, bool is_null)
    {
        if(is_null) 
            kind = 3;
        else{
            strVal = string(p);
            kind = 2;
        }
    };
    ~AllValue();
};
// struct DataVector
// {
//     vector<MyData*> datas;
// };
class MyCommands
{
private:
    MyFileIO *myFileIO;
public:
    TableCols *tc;
    void showDBs();
    bool createDB(std::string dbName);
    bool dropDB(std::string dbName);
    bool useDB(std::string dbName);
    void showTables();
    bool createTable(std::string tableName, TableCols *tableCols);
    bool dropTable(std::string tableName);
    bool insertData(std::string tableName, std::vector<MyData*> &data);
    void setMyData(int valNum, AllValue *val, MyData *data);
    void select(std::vector<std::string> *tableList);

    MyCommands()
    {
        myFileIO = new MyFileIO();
    }
    ~MyCommands()
    {
        delete myFileIO;
    }
};

#endif //MY_COMMANDS_H
