# dbproject

|,#,$ 将用作在存储数据和表格式时的保留字符

注意设置程序的运行目录，用于指定数据库位置

索引和记录管理写在了一起

主键不能为NULL，NULL比其他任何内容都小，两个NULL比较时相等

簇集索引是唯一索引，否则太难处理了，放弃

一般操作流程：
根据逻辑表达式确定需要查询的索引，通过MyTable获取索引并查找确定可能项目（如果有必要查索引的话，很多时候暴力就好了）
构建Constraints和Updates类，用来直接判定数据满足要求和更新数据（如果需要用到的话）
调用MyTable相关函数进行操作
我尽量把接口多搞了些，也减少了使用时需要额外考虑的事情

MyData使用请用new创建指针使用，为了统一delete减少内存泄漏

有非簇集唯一索引时插入数据，我会先去掉与索引重复的再插入

批量插入数据时，如果插入的数据之间有重复，请自行先去重，否则结果会出问题

UpdateData函数会把满足条件的数据定长的直接改好，变长的先拿出来改好再插回去，如果修改后会发生重复就会出错
UpdateDataSafe函数会把满足条件的数据先都拿出来，改好再一条条插回去，重复的就直接丢弃，这样和标准数据库做法一样
（我在没唯一索引时会直接调用UpdateData，速度快点）

isUnique函数只判断非簇集唯一索引，簇集索引在插入时会去重




以下是操作的建议调用函数：
CREATE DATABASE orderDB;
MyFileIO::createDB
与已有数据库重名返回false，成功创建返回true

DROP DATABASE orderDB;
MyFileIO::dropDB()
有该数据库并成功删除返回true，否则返回false

SHOW DATABASES;
MyFileIO::showDB()
返回true，同时修改传入的vector<string>保存所有数据库名称

USE orderDB;
MyFileIO::useDB()
有该数据库并成功切换返回true，否则返回false

SHOW TABLES;
MyFileIO::getTables()
返回true，同时修改传入的vector<string>保存当前数据库的所有表

CREATE TABLE customer(
id int(10) NOT NULL,
name char(25) NOT NULL,
gender char(1) NOT NULL,
PRIMARY KEY(id)
);
新建若干MyCol，看MyCol的构造函数
比如第一个id列(TYPE_INT, 10, true, false, "id")
新建TableCols，调用若干addCol()，最后调用setOrder()
MyFileIO::createTable()
与已有数据表重复返回false，否则返回true
一些列如果有限制需要MyCol::addWordList()
外键需要在构造时传入
PRIMARY KEY这个需要建立不可以删除的非空簇集索引


DROP TABLE customer;
MyFileIO::dropTable()
有该数据表并成功删除返回true，否则返回false
同时会删除相关的所有索引

DESC customer;
MyTable::getColNum()
MyTable::getColType()返回值形如COL_NULL之类的
MyTable::getColName()

INSERT INTO customer VALUES (300001, ‘CHAD CABELLO’, ‘F’);
参考tests.cpp中的例子
先tc=MyTable.cols
创建一个MyData对象myData，用tc作为构造函数参数
每次获取一列的num,offset和myCol
调用MyData::format()构造value
myData.setValue(num,offset,myCol,value);
调用MyTable::insertData()
批量插入基于没有唯一索引的条件，否则要先去重或一条条插入
已经处理了部分列限制词选择的情况，也会做外键插入的情况
TableCols::getAllForeignKey()获取当前数据表的所有外键，先判断好外键情况再插入


INSERT INTO orders VALUES (315000,200001,’eight’);
同上

DELETE FROM publisher WHERE state=’CA’;
如果能利用索引，则先用MyIndex::findData()找到可能的数据页和项（RID）位置
对于RID集合做逻辑运算
建立Constraints，用于判定一个MyData是否符合要求
调用MyTable::deleteData()选择直接删或者删指定的数据
MyTable::getAllForeignKey()获取指向当前数据表的所有外键，把他们中相关的数据也要删除（这里要递归处理，因此底层不直接做，暂时不考虑做）

UPDATE book SET title=’Nine Times Nine’ WHERE authors=’Anthony Boucher’;
如果能利用索引，则先用MyIndex::findData()找到可能的数据页和项（RID）位置
对于RID集合做逻辑运算
建立Constraints、Updates用于更新一个MyData（可以存一系列colID和目标value，用setValue更新）
调用MyTable::updateDataSafe()二选一
使用的前提是数据表没有外键且没有外键指向它，否则建议先find再delete，删除相关外键数据，把find到的数据更新好再判断外键并插入


SELECT * FROM publisher WHERE nation=’CA’;
利用索引
建立Constraints
调用MyTable::searchData()或MyTable::getData()

SELECT title FROM book WHERE authors is null;
同上

SELECT book.title,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8;
同上

CREATE INDEX customer(name);
MyTable::getColID()
返回-1说明没有索引才能创建索引
MyTable::createIndex()

DROP INDEX customer(name);
MyTable::getColID()
MyTable::dropIndex()

CREATE TABLE customer (
id int(10) NOT NULL,
name char(25) NOT NULL,
gender char(1) NOT NULL,
CHECK (gender in(‘F’,’M’)),
PRIMARY KEY (id)
);
使用MyCol::addwordList()增加限制，使用MyCol::isInWordList()检查是否属于候选词

外键相关函数补充：
外键由底层支持，仅考虑插入时的情况
TableCols::getAllForeignKey()这个是返回所有外键
MyTable::getAllForeignKey()这个是返回所有指向该数据表主键的外键