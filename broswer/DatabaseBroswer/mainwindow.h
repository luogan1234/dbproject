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
    void editRecord(int row, int column);

private:
    Ui::MainWindow *ui;
    // make them member variable
    QPushButton* createButton;
    QPushButton* openButton;

    QTabWidget* tabWidget;
};

#endif // MAINWINDOW_H
