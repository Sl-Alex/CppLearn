#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "boardmodel.h"
#include "abstractplayer.h"

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
    void on_sizeSpin_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_tableView_pressed(const QModelIndex &index);

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    BoardModel * pBoard;
    AbstractPlayer * pPlayer1;
    AbstractPlayer * pPlayer2;
    AbstractPlayer * pCurPlayer;
    BoardModel::State oldState;
};

#endif // MAINWINDOW_H
