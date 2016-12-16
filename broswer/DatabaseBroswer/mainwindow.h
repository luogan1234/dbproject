#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createDatabase();
    void openDatabase();

private:
    Ui::MainWindow *ui;
    // make them member variable
    QPushButton* createButton;
    QPushButton* openButton;
};

#endif // MAINWINDOW_H
