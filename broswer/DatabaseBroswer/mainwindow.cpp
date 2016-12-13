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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createDatabase() {
    createButton->setText("Test");
}
