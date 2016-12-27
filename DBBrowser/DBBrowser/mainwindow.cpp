#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../parser/tokens.h"
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* str);
extern int yyparse();
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // program starts here
    openButton = ui->openButton;

    connect(openButton, SIGNAL(clicked(bool)), this, SLOT(openDatabase()));

    tabWidget = ui->tabWidget;
    // remove the default tabs
    tabWidget->removeTab(0);
    tabWidget->removeTab(0);

    // initialize the content of the first tab
    QVBoxLayout* vBoxLayout1 = new QVBoxLayout;
    QHBoxLayout* hBoxLayout1 = new QHBoxLayout;
    hBoxLayout1->setAlignment(Qt::AlignLeft);
    QPushButton* createTableButton = new QPushButton("Create Table");
    QPushButton* editTableButton = new QPushButton("Edit Table");
    QPushButton* deleteTableButton = new QPushButton("Delete Table");
    hBoxLayout1->addWidget(createTableButton);
    hBoxLayout1->addWidget(editTableButton);
    hBoxLayout1->addWidget(deleteTableButton);
    QTableWidget* structureTable = new QTableWidget(10, 3);  // number 10 is depend on the amount of tables
    QStringList structureHeader;
    structureHeader << "Name" << "Type" << "Structure";
    structureTable->setHorizontalHeaderLabels(structureHeader);
    structureTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vBoxLayout1->addLayout(hBoxLayout1);
    vBoxLayout1->addWidget(structureTable);
    QWidget* tab1 = new QWidget;
    tab1->setLayout(vBoxLayout1);
    tabWidget->addTab(tab1, "Data Structure");

    // initialize the content of the second tab
    QVBoxLayout* vBoxLayout2 = new QVBoxLayout;
    QHBoxLayout* hBoxLayout2 = new QHBoxLayout;
    QLabel* label = new QLabel("Table:");
    QComboBox* comboBox = new QComboBox;
    comboBox->addItem("Customers");
    comboBox->addItem("Students");
    QPushButton* createRecordButton = new QPushButton("Create Record");
    QPushButton* deleteRecordButton = new QPushButton("Delete Record");
    hBoxLayout2->addWidget(label);
    hBoxLayout2->addWidget(comboBox);
    hBoxLayout2->addSpacerItem(new QSpacerItem(100, 0, QSizePolicy::Expanding));
    hBoxLayout2->addWidget(createRecordButton);
    hBoxLayout2->addWidget(deleteRecordButton);
    QTableWidget* mainTable = new QTableWidget(10, 5);  // not fixed
    QStringList mainHeader;
    mainHeader << "Name" << "id" << "Age" << "Gender" << "Grades";
    mainTable->setHorizontalHeaderLabels(mainHeader);
    mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vBoxLayout2->addLayout(hBoxLayout2);
    vBoxLayout2->addWidget(mainTable);
    QWidget* tab2 = new QWidget;
    tab2->setLayout(vBoxLayout2);
    tabWidget->addTab(tab2, "View Data");

    // initialize the content of the third tab
    QVBoxLayout* vBoxLayout3 = new QVBoxLayout;
    QHBoxLayout* hBoxLayout3 = new QHBoxLayout;
    hBoxLayout3->setAlignment(Qt::AlignLeft);
    QPushButton* runButton = new QPushButton("Run");
    QPushButton* openScriptButton = new QPushButton("Open Script");
    connect(runButton, SIGNAL(clicked(bool)), this, SLOT(runSql()));
    hBoxLayout3->addWidget(runButton);
    hBoxLayout3->addWidget(openScriptButton);
    textEdit = new QPlainTextEdit;
    QTableWidget* resultTable = new QTableWidget(5, 5);
    resultTable->setHorizontalHeaderLabels(mainHeader);
    resultTable->setFixedHeight(180);
    lineEdit = new QPlainTextEdit;
    lineEdit->setReadOnly(true);
    lineEdit->setFixedHeight(60);
    vBoxLayout3->addLayout(hBoxLayout3);
    vBoxLayout3->addWidget(textEdit);
    vBoxLayout3->addWidget(resultTable);
    vBoxLayout3->addWidget(lineEdit);
    QWidget* tab3 = new QWidget;
    tab3->setLayout(vBoxLayout3);
    tabWidget->addTab(tab3, "Execute SQL");
    // to simplify code: fixed size
    setFixedSize(1243, 703);

}

MainWindow::~MainWindow() {

}

void MainWindow::select(vector<string> tableList) {
    vector<vector<MyData*>*> allRes;
    myCommands.basicSelect(&tableList, 5, allRes);
    MyTable *myTable= myCommands.myFileIO->getTable(tableList[0]);
    if(myTable == 0){

    }
    TableCols *tc = &(myTable->cols);
    int colLen = tc->cols.size();
    MyCol* myCol;
    MyValue value;
    int num,offset;

    int len = allRes[0]->size();
    for (int i = 0; i < len; ++i)
    {
        for(int j = 0; j < colLen; ++j){
            myCol=tc->getByCol(j,num,offset);
            (*allRes[0])[i]->getValue(num,offset,myCol,value);
//            value.print();
            cout << i << " " << j << endl;
            switch(value.type){
                case TYPE_INT:
                    cout << *((int*)value.res) << endl;
                    break;
                case TYPE_CHAR:
                case TYPE_VARCHAR:
                    char* content = new char[value.dataLen + 1];
                    strncpy(content, value.res, value.dataLen);
                    content[value.dataLen] = '\0';
                    cout << content << endl;
                    break;
            }
        }
    }
}

void MainWindow::openDatabase() {
    vector<string> dbNames;
    myCommands.showDBs(dbNames);

    QInputDialog* dialog = new QInputDialog;
    dialog->setOption(QInputDialog::UseListViewForComboBoxItems);
    QStringList dbNamesList;
    foreach (string name, dbNames) {
        dbNamesList << name.c_str();
    }
    dialog->setComboBoxItems(dbNamesList);
    dialog->setLabelText("Select a database:");
    connect(dialog, SIGNAL(textValueSelected(QString)), this, SLOT(setUsingDb(QString)));
    dialog->show();
}

void MainWindow::setUsingDb(QString dbName) {
    usingDb = dbName.toStdString();
    myCommands.useDB(usingDb);
    vector<string> dbList;
    dbList.push_back("customer");
    select(dbList);
}

void MainWindow::runSql() {
    // redirection init
    stringstream streamBuffer;
    streambuf* old = cout.rdbuf(streamBuffer.rdbuf());

    // run sql sentences
    string sql = textEdit->toPlainText().toStdString();
    YY_BUFFER_STATE buffer = yy_scan_string(sql.c_str());
    yyparse();
    yy_delete_buffer(buffer);

    // redirect to info
    string info = streamBuffer.str();
    lineEdit->appendPlainText(info.c_str());
}
