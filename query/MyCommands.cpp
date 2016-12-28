#include "MyCommands.h"

using namespace std;

void MyCommands::showDBs()
{
	vector<string> dbname;
    myFileIO->showDB(dbname);
    int len = dbname.size();
    if(len == 0) 
    	cout << "No database" << endl;
    else{
    	for(int i = 0; i < len; ++i)
    		cout << dbname[i] << " ";
    	cout << endl;
    }
}

void MyCommands::showDBs(vector<string> &dbNames) {
    myFileIO->showDB(dbNames);
}

bool MyCommands::createDB(string dbname)
{
    bool ret = myFileIO->createDB(dbname);
    if(!ret) cout << "Fail to create database " << dbname << endl;
    return ret;
}

bool MyCommands::dropDB(string dbname)
{
    bool ret = myFileIO->dropDB(dbname);
    return ret;
}

bool MyCommands::useDB(string dbname)
{
    bool ret = myFileIO->useDB(dbname);
    if(!ret) cout << "Fail to use database " << dbname << " No such database" << endl;
    return ret;
}

void MyCommands::showTables()
{
	vector<string> tableName;
    myFileIO->getTables(tableName);
    int len = tableName.size();
    if(len == 0) 
    	cout << "No table" << endl;
    else{
    	for(int i = 0; i < len; ++i)
    		cout << tableName[i] << " ";
    	cout << endl;
    }
}

void MyCommands::showTables(vector<string>& tableNames) {
    myFileIO->getTables(tableNames);
}

bool MyCommands::createTable(string tableName, TableCols *tableCols)
{
    if(tableCols != 0) {
        tableCols->setOrder();
    }
	bool ret = myFileIO->createTable(tableName, tableCols->toString());
	if(!ret) cout << "Fail to create table " << tableName << endl;
	return ret;
}

bool MyCommands::addCheck(MyCol *myCol, std::vector<AllValue*> *v, int dataType, int dataWide)
{
    //check the type and wide of each value
    //只支持string类型的数据
    int len = v->size();
    if(len < 0) return false;
    bool cBN = myCol->canBeNull;
    myCol->canBeNull = false;
    for (int i = 0; i < len; ++i)
    {
        switch((*v)[i]->kind){
            case 1:
                cout << "Check Error: Only char and varchar are supported" << endl;
                return false;
                break;
            case 2:
                if(dataType == 1 || dataType == 2){
                    if((*v)[i]->strVal.size() <= dataWide)
                        myCol->addWordList((*v)[i]->strVal);
                    else{
                        cout << "Check Error: DataWide Error" << endl;
                        cout << (*v)[i]->strVal << " " << dataWide << endl;
                        return false;
                    }
                }else{
                    cout << "Check Error: Type different" << endl;
                    return false;
                }
                break;
            case 3:
                if(cBN)
                    myCol->canBeNull = true;
                else{
                    cout << "Check Error: Can not be Null" << endl;
                    return false;
                }
                break;
            default:
                return false;
        }
    }
    return true;
}

MyCol* MyCommands::createForeignKey(std::string myColName, std::string tableName, std::string colName)
{
    MyTable *myTable = myFileIO->getTable(tableName);
    if(myTable == 0){
        cout << "No such table" << endl;
        return 0;
    }
    int num, offset;
    MyCol *myCol = myTable->cols.getByName(colName, num, offset);
    if(myCol == 0){
        cout << "No such col" << endl;
        return 0;
    }
    if(myCol->isPrimary == false){
        cout << "your target is not primary key";
        return 0;
    }   
    MyCol *thisCol = new MyCol(myCol->type,myCol->len,false,myCol->canBeNull,myColName,colName,false);
    return thisCol;
}

bool MyCommands::dropTable(string tableName)
{
	bool ret = myFileIO->dropTable(tableName);
    return ret;
}

bool MyCommands::insertData(string tableName, vector<vector<AllValue*>*> &data)
{
    MyTable *myTable = myFileIO->getTable(tableName);
    if(myTable == 0) return false;
    vector<MyData*> myData;
    int len = data.size();
    for (int i = 0; i < len; ++i)
    {
        MyData *d = new MyData(myTable->cols);
        int len2 = myTable->cols.cols.size();
        bool hasSet = true;
        for (int j = 0; j < len2; ++j)
        {
            hasSet = setMyData(j, &(myTable->cols), (*data[i])[j], d);
            if(!hasSet) break;
        }
        if(hasSet) myData.push_back(d);
    }
    bool ret = myTable->insertData(myData);
    return ret;
}

bool MyCommands::setMyData(int valNum, TableCols *tc, AllValue *val, MyData *data)
{
    MyCol* myCol;
    MyValue value;
    int num,offset;
    myCol=tc->getByCol(valNum,num,offset);
    switch (val->kind){
        case 1:
            if(myCol->type != 0){
                cout << "Set Data Error: Type Error1" << endl;
                return false;
            }else{
                MyData::format(val->intVal, myCol, value);
                break;
            }
            
        case 2:
            if(myCol->type != 1 && myCol->type != 2){
                cout << "Set Data Error: Type Error2" << endl;
                return false;
            }else if(val->strVal.size() > myCol->len){
                cout << val->strVal << endl;
                cout << "Set Data Error: Wide Error" << endl;
                return false;
            }else if(myCol->wordList.size() > 0 && !(myCol->isInWordList(val->strVal))){
                cout << "Set Data Error: Not In Check Error" << endl;
                return false;
            }else{
                MyData::format(val->strVal, myCol, value);
                break; 
            }
            
        case 3:
            if(myCol->canBeNull == false){
                cout << "Set Data Error: Can not be Null" << endl;
                return false;
            }else{
                MyData::format("", myCol, value, true);
                break;
            }
    }
    data->setValue(num, offset, myCol, value);
    return true;
}

void MyCommands::select(std::vector<std::string> *tableList)
{
    vector<vector<MyData*>*> allRes;
    basicSelect(tableList, 1, allRes);
}

void MyCommands::selectSelector(std::vector<Selector*> *s, std::vector<std::string> *tableList)
{
    selector = s;
    vector<vector<MyData*>*> allRes;
    basicSelect(tableList, 2, allRes);
}

void MyCommands::showMyDatasCol(std::vector<MyData*> datas, TableCols *tc, int index, int colLen)
{
    //如果index=-1，显示datas的所有列；否则显示datas的对应index位置的列
    MyCol* myCol;
    MyValue value;
    int num,offset;
    if(index != -1){
        myCol=tc->getByCol(index,num,offset);
        int len = datas.size();
        for(int l = 0; l < len; ++l){
            datas[l]->getValue(num,offset,myCol,value);
            value.print();
        }
    }else{
        int len = datas.size();
        for (int i = 0; i < len; ++i)
        {
            for(int j = 0; j < colLen; ++j){
                myCol=tc->getByCol(j,num,offset);
                datas[i]->getValue(num,offset,myCol,value);
                value.print();
            }  
        }
    }
}

void MyCommands::deleteWhere(std::string tableName, std::vector<WhereClause*> *where)
{
    MyTable *myTable;
    myTable = myFileIO->getTable(tableName);
    int len = where->size();
    vector<WhereClause*> res;
    res.clear();
    for (int i = 0; i < len; ++i)
    {
        WhereClause *w = (*where)[i];
        if(w->leftCol->tableNameIsNot(tableName)) {
            cout << "Wrong Table" << endl;
            continue;
        }
        if(w->rightValKind == 2 && w->rightCol2->tableNameIsNot(tableName)){
            cout << "Wrong Table" << endl;
            continue;
        }
        res.push_back(w);
    }
    Constraints con(&res, &(myTable->cols), 1);
    if(myTable->deleteData(&con));
    else 
        cout << "Fail to delete" << endl;
}

void MyCommands::selectWhere(std::vector<std::string> *tableList, std::vector<WhereClause*> *w)
{
    where = w;
    vector<vector<MyData*>*> allRes;
    basicSelect(tableList, 3, allRes);
}

void MyCommands::selectSelectorWhere(vector<Selector*> *s, vector<string> *tableList, vector<WhereClause*> *w)
{
    selector = s;
    where = w;
    vector<vector<MyData*>*> allRes;
    basicSelect(tableList, 4, allRes);
}

void MyCommands::basicSelect(std::vector<std::string> *tableList, int kind, vector<vector<MyData*>*> &allRes)
{
    std::vector<MyTable*> myTbs;
    std::vector<TableCols*> tcs;
    myTbs.clear();
    tcs.clear();
    MyTable *myTable;
    int len = tableList->size();
    for (int i = 0; i < len; ++i)
    {
        myTable = myFileIO->getTable((*tableList)[i]);
        myTbs.push_back(myTable);
        tcs.push_back(&(myTable->cols));
    }
    vector<MyData*> *res;
    allRes.clear();
    Constraints *con;
    if(kind == 1 || kind == 2 || kind == 5){
        con = new Constraints();
        for (int i = 0; i < len; ++i)
        {
            res = new vector<MyData*>;
            res->clear();
            myTbs[i]->searchData(con, *res);
            allRes.push_back(res);
        }
    }
    if(kind == 3 || kind == 4){
        int w_len = where->size();
        for (int j = 0; j < len; ++j)
        {
            vector<WhereClause*> whereRes;
            // WhereClause *specialWhere = 0;
            whereRes.clear();
            bool flag = true, join = false;
            bool canUseIndex = false;
            WhereClause *indexWhere = 0;
            MyIndex *myIndex = 0;
            for (int i = 0; i < w_len; ++i)
            {
                WhereClause *w = (*where)[i];
                if(w->rightValKind == 2){
                    join = true;
                }
                if(w->leftCol->tableNameIsNot((*tableList)[j])) {
                    flag = false;
                    canUseIndex = false;
                    myIndex = 0;
                    break;
                }
                int colID1 = myTbs[j]->getColID((*where)[i]->leftCol->colName);
                if(colID1 == -1){
                    flag = false;
                    canUseIndex = false;
                    myIndex = 0;
                    break;
                }else if(!canUseIndex){
                    myIndex = myTbs[j]->getIndex(colID1);
                    if(myIndex != 0){
                        canUseIndex = true;
                        indexWhere = (*where)[i];
                    }
                }
                whereRes.push_back(w);
            }
            res = new vector<MyData*>;
            res->clear();
            if(flag){
                con = new Constraints(&whereRes, tcs[j], 1);
                if(canUseIndex){
                    cout << "CAN USE INDEX" << endl;
                    //searchByIndex(indexWhere, myIndex, myTbs[j], con, *res);
                }
                if(join){
                    joinSearch(myTbs[j], tableList);
                    return;
                }else 
                    myTbs[j]->searchData(con, *res);
                
            }
            allRes.push_back(res);
        }
    }
   
    if(kind == 2 || kind == 4){
        int s_len = selector->size();
        for (int i = 0; i < s_len; ++i)
        {
            if((*selector)[i]->hasTableName){
                for (int j = 0; j < len; ++j)
                {
                    if ((*tableList)[j] == (*selector)[i]->tableName)
                    {
                        std::vector<MyCol> &col = myTbs[j]->cols.cols;
                        int len3 = col.size(), index = -1;
                        for (int m = 0; m < len3; ++m)
                        {
                            if(col[m].name == (*selector)[i]->colName){
                                index = m;
                                break;
                            }
                        }
                        if(index > -1){
                            cout << (*selector)[i]->tableName << "." << (*selector)[i]->colName << ":" << endl;
                            showMyDatasCol(*(allRes[j]), &(myTable->cols), index, len3);
                        }
                        break;
                    }
                }
            }else{
                for (int j = 0; j < len; ++j)
                {
                    std::vector<MyCol> &col = myTbs[j]->cols.cols;
                    int len3 = col.size(), index = -1;
                    for (int m = 0; m < len3; ++m)
                    {
                        if(col[m].name == (*selector)[i]->colName){
                            index = m;
                            break;
                        }
                    }
                    if(index > -1){
                        cout << (*selector)[i]->colName << ":" << endl;
                        showMyDatasCol(*(allRes[j]), &(myTbs[j]->cols), index, len3);
                    }
                }
            }
        }
    }
    if(kind == 1 || kind == 3){
        for (int i = 0; i < len; ++i)
        {
            int len2 = myTbs[i]->cols.cols.size();
            for (int j = 0; j < len2; ++j)
            {
                cout << myTbs[i]->cols.cols[j].name << " ";
            }
            cout << endl;
            showMyDatasCol(*(allRes[i]), &(myTbs[i]->cols), -1, len2);
        }
    }
}

void MyCommands::update(string tableName, std::vector<SetClause*> *set, std::vector<WhereClause*> *where)
{
    MyTable *myTable = 0;
    myTable = myFileIO->getTable(tableName);
    if(myTable == 0) {
        cout << "No such table" << endl;
        return;
    }
    int len_set = set->size();
    int num, offset;
    for(int i = 0; i < set->size(); ++i){
        MyCol *myCol = myTable->cols.getByName((*set)[i]->colName, num, offset);
        bool deleteSetClause = false;
        if(myCol == 0){
            cout << "SetClause Error: No such Col" << endl;
            deleteSetClause = true;
        } else {
            AllValue *val = (*set)[i]->val;
            switch(val->kind){
            case 1:
                if(myCol->type != 0){
                    cout << "SetClause Error: Type Error" << endl;
                    deleteSetClause = true;
                }
                break;
            case 2:
                if(myCol->type != 1 && myCol->type != 2){
                    cout << "SetClause Error: Type Error" << endl;
                    deleteSetClause = true;
                }else if(val->strVal.size() > myCol->len){
                    cout << "SetClause Error: Type Error" << endl;
                    deleteSetClause = true;
                }else if(myCol->wordList.size() > 0 && !(myCol->isInWordList(val->strVal))){
                    cout << "SetClause Error: Not In Check Error" << endl;
                    deleteSetClause = true;
                }
                break;
            case 3:
                if(myCol->canBeNull == false){
                    cout << "SetClause Error: Can not be Null" << endl;
                    deleteSetClause = true;
                }
                break;
            }
        }
        if(deleteSetClause){
            std::vector<SetClause*>::iterator it = set->begin() + i;
            set->erase(it);
            i--;
        }
    }
    Constraints con(where, &(myTable->cols), 1);
    Updates upd(&(myTable->cols), set);
    if(myTable->updateDataSafe(&con, &upd) == false) 
        cout << "Fail To Update" << endl;
}

bool MyCommands::desc(string tbName)
{
    MyTable *myTable = 0;
    myTable = myFileIO->getTable(tbName);
    if(myTable == 0) {
        cout << "No such table" << endl;
        return false;
    }
    int colNum = myTable->getColNum();
    if(colNum == 0)
        cout << "No Col" << endl;
    for (int i = 0; i < colNum; ++i)
    {
        cout << "COLTYPE: ";
        switch (myTable->getColType(i)){
            case 0:
                cout << "NULL";
            case 1:
                cout << "PRI";
            case 2:
                cout << "UNI";
            case 3:
                cout << "MUL";
            default:
                cout << "ERROR";
        }
        cout << "\tDATATYPE: ";
        switch (myTable->getColDataType(i)){
            case 0:
                cout << "int";
                break;
            case 1:
                cout << "char";
                break;
            case 2:
                cout << "varchar";
                break;
        }
        cout << "\tCOLNAME: " << myTable->getColName(i) << endl;
    }
}

bool MyCommands::createIndex(std::string tableName, std::string colName)
{
    MyTable *myTable = 0;
    myTable = myFileIO->getTable(tableName);
    if(myTable == 0) {
        cout << "No such table" << endl;
        return false;
    }
    int colID = myTable->getColID(colName);
    if(colID == -1){
        cout << "No such col" << endl;
        return false;
    }
    bool res;
    if(myTable->cols.hasPrimaryKey() == colID){
        res = myTable->createIndex(colID,INDEX_CLUSTERED, false, false);
    } else
        res = myTable->createIndex(colID,INDEX_UNCLUSTERED, true, true);
    if(!res) cout << "Fail to create index" << endl;
    return res;
}

bool MyCommands::createPrimaryKeyIndex(std::string tableName)
{
    MyTable *myTable = 0;
    myTable = myFileIO->getTable(tableName);
    if(myTable == 0) {
        cout << "No such table" << endl;
        return false;
    }
    bool res = false;
    int colID = myTable->cols.hasPrimaryKey();
    if(colID != -1){
        res = myTable->createIndex(colID,INDEX_CLUSTERED, false, false);
    } else{
        cout << "Fail to create Index: No PrimaryKey" << endl;
    }
    if(!res) cout << "Fail to create index" << endl;
    return res;
}

bool MyCommands::dropIndex(std::string tableName, std::string colName)
{
    MyTable *myTable = 0;
    myTable = myFileIO->getTable(tableName);
    if(myTable == 0) {
        cout << "No such table" << endl;
        return false;
    }
    int colID = myTable->getColID(colName);
    if(colID == -1){
        cout << "No such col" << endl;
        return false;
    }
    if(myTable->cols.hasPrimaryKey() == colID){
        cout << "Index On PrimaryKey Can not be deleted" << endl;
        return false;
    }
    bool res = myTable->dropIndex(colID);
    if(!res) cout << "Fail to drop index" << endl;
    return res;
}

void MyCommands::searchByIndex(WhereClause *w, MyIndex *index, MyTable *table, Constraints* con, std::vector<MyData*> &res)
{
    std::vector<MyData*> fitIndex;
    int type1, type2;
    fitIndex.clear();
    res.clear();
    // index->findData(MyValue* value1, type1, MyValue* value2, type2, res);
}

bool MyCommands::joinSearch(MyTable *table, std::vector<std::string> *tableList)
{
    vector<Selector*> selectors;
    vector<int> whereChange;
    selectors.clear();
    whereChange.clear();
    int len_where = where->size();
    for (int i = 0; i < len_where; ++i)
    {
        if((*where)[i]->rightValKind == 2){
            whereChange.push_back(i);
            Selector *s = new Selector((*where)[i]->rightCol2->tableName, (*where)[i]->rightCol2->colName);
            selectors.push_back(s);
        }
    }
    if(selectors.size() == 0) return false;
    
    //use MyIndex when 2 tables join
    bool canUseIndex = false;
    MyIndex *myIndex = 0;
    int colID1 = table->getColID((*where)[whereChange[0]]->leftCol->colName);
    if(colID1 == -1){
        return false;
    }else{
        myIndex = table->getIndex(colID1);
        if(myIndex != 0){
            canUseIndex = true;
            cout << "Two Table Join Using Index" << endl;
        }
    }

    string tb2 = selectors[0]->tableName;
    std::vector<string> getTb2;
    getTb2.clear();
    getTb2.push_back(tb2);
    for (int i = 1; i < selectors.size(); ++i)
    {
        //2 tables join
        if(tb2 != selectors[i]->tableName) return false;
    }
    vector<vector<MyData*>*> resTb2;
    basicSelect(&getTb2, 5, resTb2);
    if(resTb2.size() == 0){
        return false;
    }
    std::vector<MyData*> *dataTb2 = resTb2[0];
    MyTable *tableTb2 = myFileIO->getTable(tb2);
    if(tableTb2 == 0) return false;

    std::vector<int> num, offset;
    std::vector<MyCol*> mycolTb2;
    MyCol* temp_col;
    int temp_num, temp_offset;
    num.clear();
    offset.clear();
    mycolTb2.clear();
    for (int i = 0; i < selectors.size(); ++i)
    {
        temp_col = tableTb2->cols.getByName(selectors[i]->colName, temp_num, temp_offset);
        if(temp_col == 0){
            cout << "Join Error: no such col" << endl;
            return false;
        }
        mycolTb2.push_back(temp_col);
        num.push_back(temp_num);
        offset.push_back(temp_offset);
    }
    Constraints *con = new Constraints(where, &(table->cols), 1);
    vector<vector<MyData*>*> allRes1, allRes2;
    allRes1.clear();
    allRes2.clear();
    for (int i = 0; i < dataTb2->size(); ++i)
    {
        for(int j = 0; j < selectors.size(); ++j){
            //change where
             MyValue value;
            (*dataTb2)[i]->getValue(num[j],offset[j],mycolTb2[j],value);
            WhereClause *temp_where = (*where)[whereChange[j]];
            switch(value.type){
                case 0: 
                    temp_where->rightValKind = 1;
                    temp_where->rightCol1 = *(int*) value.res;
                    break;
                case 1:
                case 2:
                    temp_where->rightValKind = 3;
                    temp_where->rightCol3 = (string) value.res;
                    break;
            }
        }
        
        vector<MyData*> *res = new vector<MyData*>;
        res->clear();
        if(canUseIndex){
            MyValue value_index1, value_index2;
            vector<pair<int,int> > pair_index;
            vector<MyData*> *res_index = new vector<MyData*>;
            pair_index.clear();
            res_index->clear();
            (*dataTb2)[i]->getValue(num[0],offset[0],mycolTb2[0],value_index1);
            (*dataTb2)[i]->getValue(num[0],offset[0],mycolTb2[0],value_index2);
            myIndex->findData(&value_index1,COMPARE_SMALLER_EQUAL,&value_index2,COMPARE_LARGER_EQUAL,pair_index);
            table->getData(pair_index, *res_index);
            int len_index = res_index->size();
            for (int ii = 0; ii < len_index; ++ii)
            {   
                if(con->checkData((*res_index)[ii]))
                    res->push_back((*res_index)[ii]);
            }
        }else 
            table->searchData(con, *res);
        if(res->size() > 0){
            allRes1.push_back(res);
        }
    }
    for (int i = 0; i < allRes1.size(); ++i)
    {
        showMyDatasCol(*(allRes1[i]), &(table->cols), -1, table->cols.cols.size());
    }
}
