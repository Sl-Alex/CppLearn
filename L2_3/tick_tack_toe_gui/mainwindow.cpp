#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardmodel.h"
#include "aiplayer.h"
#include "humanplayer.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pBoard = NULL;
    pPlayer1 = NULL;
    pPlayer2 = NULL;
}

MainWindow::~MainWindow()
{
    delete pBoard;
    delete ui;
}

void MainWindow::on_sizeSpin_valueChanged(int arg1)
{
    ui->winSpin->setMaximum(arg1);
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableView->setModel(NULL);
    if (pBoard) delete pBoard;
    if (pPlayer1) delete pPlayer1;
    if (pPlayer2) delete pPlayer2;
    if (ui->p1Human->isChecked())
        pPlayer1 = new HumanPlayer();
    else
        pPlayer1 = new AiPlayer();
    if (ui->p2Human->isChecked())
        pPlayer2 = new HumanPlayer();
    else
        pPlayer2 = new AiPlayer();
    int size = ui->sizeSpin->value();
    int winLevel = ui->winSpin->value();
    pBoard = new BoardModel(size, winLevel);
    pPlayer1->setBoard(pBoard);
    pPlayer2->setBoard(pBoard);
    pPlayer1->setValue(BoardModel::VAL_X);
    pPlayer2->setValue(BoardModel::VAL_O);
    ui->tableView->setModel(pBoard);
    for (int i = 0; i < size; i++)
    {
        ui->tableView->setColumnWidth(i,ui->tableView->width()/size);
        ui->tableView->setRowHeight(i,ui->tableView->height()/size);
    }
    pCurPlayer = pPlayer1;
    ui->statusLabel->setText("Ready to play");
    oldState = BoardModel::ST_ACTIVE;
}

// Click or "Enter" on the cell
void MainWindow::on_tableView_pressed(const QModelIndex &index)
{
    if (pCurPlayer->makeMove(index.column(),index.row()))
    {
        ui->tableView->repaint();
        if (pBoard->getState() == BoardModel::ST_ACTIVE)
        {
            if ( pCurPlayer == pPlayer1 )
                pCurPlayer = pPlayer2;
            else
                pCurPlayer = pPlayer1;
        }
    }
    if (pBoard->getState() == oldState) return;
    oldState = pBoard->getState();

    if (oldState == BoardModel::ST_ACTIVE) return;

    switch (oldState)
    {
        case BoardModel::ST_WIN_NONE:
            ui->statusLabel->setText("Nobody wins");
        break;
        case BoardModel::ST_WIN_X:
            ui->statusLabel->setText("Player 1 wins");
        break;
        case BoardModel::ST_WIN_O:
            ui->statusLabel->setText("Player 2 wins");
        break;
        default:
            ui->statusLabel->setText("Unknown state");
    }
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    on_tableView_pressed(index);
}
