#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H

#include "../recmanage/MyFileIO.h"
struct MyType
{
    int dataType;
    int dataWide;
    MyType(int dataType, int dataWide):dataType(dataType), dataWide(dataWide)
    {};
    ~MyType();
};

class MyCommands
{
private:
    MyFileIO *myFileIO;
public:
    void showDBs();
    bool createDB(std::string dbName);
    bool dropDB(std::string dbName);
    bool useDB(std::string dbName);
    void showTables();
    bool createTable(std::string tableName, std::string tableFormat);
    bool dropTable(std::string tableName);
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
