#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMenu>
#include <QTimer>
#include <QPushButton>

const QString imgPath = "../slot_machine/img%1.png";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    QWidget *centralWidget;

    ~MainWindow();

private slots:
    void makeSpin();
    void showHelp();
    void updateAnimation();
    void winAnimation();
    void exitSlot();
private:

    QLabel * spinsText;
    QLabel * pictures[3];
    QLabel * moneyText;
    QPushButton * spinButton;

    QMenu *fileMenu;
    QAction *helpAction;
    QAction *exitAction;
    int mCoins;

    int mState[3];

    QTimer * mAnimationTimer;
    QTimer * mWinTimer;
};

#endif // MAINWINDOW_H
