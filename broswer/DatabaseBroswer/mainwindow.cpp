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

    // to simplify code: fixed size
    setFixedSize(1243, 703);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createDatabase() {
    createButton->setText("Test");
}

void MainWindow::openDatabase() {
    openButton->setText("Test");
}
