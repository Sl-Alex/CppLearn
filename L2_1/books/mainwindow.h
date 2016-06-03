#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "booktablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    BookTableModel * pBookTable;
    bool modified;
};

#endif // MAINWINDOW_H
