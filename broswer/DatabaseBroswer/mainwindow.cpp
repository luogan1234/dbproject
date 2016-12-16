#include <QTableWidget>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // program starts here
    createButton = ui->createButton;
    openButton = ui->openButton;

    connect(createButton, SIGNAL(clicked(bool)), this, SLOT(createDatabase()));
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
    connect(mainTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(editRecord(int,int)));
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
    hBoxLayout3->addWidget(runButton);
    hBoxLayout3->addWidget(openScriptButton);
    QPlainTextEdit* textEdit = new QPlainTextEdit;
    QTableWidget* resultTable = new QTableWidget(5, 5);
    resultTable->setHorizontalHeaderLabels(mainHeader);
    resultTable->setFixedHeight(180);
    QLineEdit* lineEdit = new QLineEdit;
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
    delete ui;
}

void MainWindow::createDatabase() {

}

void MainWindow::openDatabase() {

}

void MainWindow::editRecord(int row, int column) {
    qDebug("%d %d", row, column);
}
