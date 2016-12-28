#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>
#include <QInputDialog>
#include <iostream>
#include <sstream>
#include <QMessageBox>
#include "../../query/MyCommands.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openDatabase();
    void setUsingDb(QString dbName);
    void runSql();
    void refresh();

private:
    Ui::MainWindow *ui;
    // make them member variable
    QPushButton* openButton;
    QTableWidget* structureTable;

    QComboBox* comboBox;
    QTableWidget* mainTable;

    QTabWidget* tabWidget;
    MyCommands myCommands;
    string usingDb;
    string usingTable;

    QPlainTextEdit* textEdit;
    QPlainTextEdit* lineEdit;

    void select(vector<string> tableList);
};

#endif // MAINWINDOW_H
