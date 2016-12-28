#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H

#include "../recmanage/MyFileIO.h"
#include "../recmanage/TableCols.h"
#include "../recmanage/MyTable.h"
#include "../recmanage/MyData.h"

class MyCommands
{
private:
    std::vector<Selector*> *selector;
    std::vector<WhereClause*> *where;
    void showMyDatasCol(std::vector<MyData*> datas, TableCols *tc, int index, int colLen);
    //index:w左边对应的列的索引 w:使用索引加速的语句
    void searchByIndex(WhereClause *w, MyIndex *index, MyTable *table, Constraints* con, std::vector<MyData*> &res);
    bool joinSearch(MyTable *table, std::vector<std::string> *tableList);
public:
    MyFileIO *myFileIO;
    void showDBs();
    void showDBs(vector<string> &dbNames);
    bool createDB(std::string dbName);
    bool dropDB(std::string dbName);
    bool useDB(std::string dbName);
    bool desc(std::string tableName);
    void showTables();
    void showTables(vector<string>& tableNames);
    bool createTable(std::string tableName, TableCols *tableCols);
    bool addCheck(MyCol *myCol, std::vector<AllValue*> *v, int dataType, int dataWide);
    MyCol* createForeignKey(std::string myColName, std::string tableName, std::string colName);
    bool createIndex(std::string tableName, std::string colName);
    bool createPrimaryKeyIndex(std::string tableName);
    bool dropIndex(std::string tableName, std::string colName);
    bool dropTable(std::string tableName);
    bool insertData(std::string tableName, std::vector<vector<AllValue*>*> &data);
    bool setMyData(int valNum, TableCols *tc, AllValue *val, MyData *data);
    void select(std::vector<std::string> *tableList);
    void selectSelector(std::vector<Selector*> *selector, std::vector<std::string> *tableList);
    void selectWhere(std::vector<std::string> *tableList, std::vector<WhereClause*> *where);
    void selectSelectorWhere(std::vector<Selector*> *selector, std::vector<std::string> *tableList, std::vector<WhereClause*> *where);
    void basicSelect(std::vector<std::string> *tableList, int kind, std::vector<std::vector<MyData*>*> &allRes);
    void deleteWhere(std::string tableName, std::vector<WhereClause*> *where);
    void update(string tableName, std::vector<SetClause*> *set, std::vector<WhereClause*> *where);

    MyCommands()
    {
        myFileIO = new MyFileIO();
    }
    ~MyCommands()
    {
        myFileIO->closeAll();
        delete myFileIO;
    }
};

#endif //MY_COMMANDS_H
