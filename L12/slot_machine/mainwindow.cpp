#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMenuBar>
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>
#include <QTimer>
#include <time.h>
#include "mainwindow.h"
#include "helpdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(0));

    mCoins = 9;

    centralWidget = new QWidget(this);

    this->setCentralWidget( centralWidget );

    fileMenu = menuBar()->addMenu(tr("&File"));
    exitAction = fileMenu->addAction(tr("E&xit"));
    exitAction->setStatusTip(tr("Exit from the program"));
    helpAction = menuBar()->addAction(tr("&Help..."));
    helpAction->setStatusTip(tr("Show help"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitSlot()));

    QLabel * moneyLabel = new QLabel(tr("MONEY"));
    QLabel * spinsLabel = new QLabel(tr("SPINS"));

    QFont font = moneyLabel->font();
    font.setPointSize(16);
    font.setBold(true);

    moneyLabel->setFont(font);
    spinsLabel->setFont(font);
    moneyLabel->setStyleSheet("color: #FE9A2E;");
    spinsLabel->setStyleSheet(moneyLabel->styleSheet());

    font.setPointSize(12);
    moneyText = new QLabel();
    moneyText->setNum(mCoins);
    moneyText->setStyleSheet("color: #40FF00;");
    moneyText->setFont(font);

    spinsText = new QLabel("0");
    spinsText->setStyleSheet(moneyText->styleSheet());
    spinsText->setFont(font);

    QPixmap pix;
    for (int i = 0; i < 3; ++i)
    {
        mState[i] = 0;
        pictures[i] = new QLabel();
        pix.load(imgPath.arg(mState[i]));
        pictures[i]->setPixmap(pix);
    }
    setStyleSheet("color: #E0E0E0; background: #303030;");

    spinButton = new QPushButton(tr("Make a spin!"));

    QVBoxLayout * mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout * statsLayout = new QHBoxLayout();
    QVBoxLayout * scoresLayout = new QVBoxLayout();
    QVBoxLayout * spinsLayout = new QVBoxLayout();
    QHBoxLayout * picturesLayout = new QHBoxLayout();

    QLabel * leftSide = new QLabel();
    QLabel * rightSide = new QLabel();
    pix.load(imgPath.arg(10));
    leftSide->setPixmap(pix);
    pix.load(imgPath.arg(11));
    rightSide->setPixmap(pix);

    scoresLayout->addWidget(moneyLabel,0,Qt::AlignLeft);
    scoresLayout->addWidget(moneyText,0,Qt::AlignLeft);
    spinsLayout->addWidget(spinsLabel,0,Qt::AlignRight);
    spinsLayout->addWidget(spinsText,0,Qt::AlignRight);
    picturesLayout->addWidget(leftSide,0);
    picturesLayout->addWidget(pictures[0],0);
    picturesLayout->addWidget(pictures[1],0);
    picturesLayout->addWidget(pictures[2],0);
    picturesLayout->addWidget(rightSide,0);
    picturesLayout->setContentsMargins(5,5,5,5);
    pictures[0]->setContentsMargins(0,0,1,0);
    pictures[1]->setContentsMargins(0,0,0,0);
    pictures[2]->setContentsMargins(1,0,0,0);
    picturesLayout->setSpacing(0);
    picturesLayout->setAlignment(Qt::AlignCenter);

    statsLayout->addLayout(scoresLayout,1);
    QLabel * moneyPicture = new QLabel();
    pix.load(imgPath.arg(12));
    moneyPicture->setPixmap(pix);
    statsLayout->addWidget(moneyPicture,0,Qt::AlignCenter);
    statsLayout->addLayout(spinsLayout,1);
    mainLayout->addLayout(statsLayout,1);
    mainLayout->addLayout(picturesLayout,1);
    mainLayout->addWidget(spinButton,1);

    spinButton->setStyleSheet(
"QPushButton {\
    border: 2px solid #404040;\
    border-radius: 6px;\
    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
        stop: 0 #808080, stop: 1 #606060);\
    min-width: 80px;\
}\
QPushButton:pressed {\
    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
        stop: 0 #606060, stop: 1 #909090);\
}\
QPushButton:!enabled{\
    color:#606060;\
    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
        stop: 0 #606060, stop: 1 #909090);\
}\
QPushButton:flat {\
    border: none; /* no border for a flat push button */\
}\
QPushButton:default {\
    border-color: navy; /* make the default button prominent */\
}");
    spinButton->setFixedHeight(40);

    menuBar()->setStyleSheet(
"QMenuBar{\
    color: #D0D0D0;\
    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\
        stop:0 #606060, stop:1 #303030);\
}\
QMenuBar::item {\
    spacing: 5px; /* spacing between menu bar items */\
    padding: 5px 5px;\
    background: transparent;\
    color: #E0E0E0;\
}\
QMenu::item:selected { /* when selected using mouse or keyboard */\
    background: #585858;\
}\
QMenu::item:pressed {\
    background: #888888;\
}\
QMenuBar::item:selected { /* when selected using mouse or keyboard */\
    background: #585858;\
}\
QMenuBar::item:pressed {\
    background: #888888;\
}");
    connect(spinButton, SIGNAL(clicked()), this, SLOT(makeSpin()));
    mAnimationTimer = new QTimer(this);
    mWinTimer = new QTimer(this);
    connect(mAnimationTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    connect(mWinTimer, SIGNAL(timeout()), this, SLOT(winAnimation()));
    setWindowTitle(tr("Slot machine game"));
    setFixedSize(sizeHint());
}

MainWindow::~MainWindow()
{

}

void MainWindow::makeSpin()
{
    if (mCoins > 0)
    {
        --mCoins;
    }
    moneyText->setNum(mCoins);

    spinButton->setEnabled(false);
    mAnimationTimer->start(30);

    static int i = 0;
    spinsText->setNum(++i);
}

void MainWindow::exitSlot()
{
    if (mCoins > 0)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Do you really want to exit?"));
        msgBox.setInformativeText(tr("You still have some money!\n"
                                     "You can spend'em all here! :)"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);

        int ret = msgBox.exec();
        if (ret != QMessageBox::Yes)
            return;
    }
    close();
}

void MainWindow::updateAnimation()
{
    static int spinCntMax[3] = {
        2+rand()%5,
        2+rand()%5,
        2+rand()%5
    };
    static int spinCnt[3] = {20,20,20};
    static int skip[3] = {5,5,5};

    bool done = true;
    QPixmap pix;
    for (int i = 0; i < 3; i++)
    {
        if (spinCnt[i] > spinCntMax[i])
        {
            int offset = 1+rand()%2;
            mState[i] += offset;
            mState[i] %= 10;
            --spinCnt[i];
        }
        else if (spinCnt[i] != 0)
        {
            if (skip[i] == 0)
            {
                mState[i]++;
                mState[i] %= 10;
                spinCnt[i]--;
                skip[i] = 5;
            }
            else
            {
                skip[i]--;
            }
        }
        if (spinCnt[i] != 0)
            done = false;
        pix.load(imgPath.arg(mState[i]));
        pictures[i]->setPixmap(pix);
    }

    if (done)
    {
        // Check if there is a successful combination
        bool win = false;
        if ((mState[0] == mState[1]) && (mState[1] == mState[2]))
        {
            mCoins += 10;
            win = true;

        }
        else if ((mState[0] == mState[1]) ||
                 (mState[1] == mState[2]) ||
                 (mState[2] == mState[0]))
        {
            mCoins += 2;
            win = true;
        }
        for (int i = 0; i < 3; ++i)
        {
            if (mState[i] == 5)
            {
                ++mCoins;
                win = true;
            }
        }
        if (win)
        {
            moneyText->setNum(mCoins);
            mWinTimer->start(150);
            /// @ToDo: animate
        }

        mAnimationTimer->stop();
        if (mCoins != 0)
            spinButton->setEnabled(true);
        for (int i = 0; i < 3; i++)
        {
            spinCnt[i] = 20;
            spinCntMax[i] = 2+rand()%5;
        }
    }
}

void MainWindow::showHelp()
{
    HelpDialog * dlg = new HelpDialog(this);
    dlg->show();
}

void MainWindow::winAnimation()
{
    static int cnt = 5;

    QFont font = moneyText->font();

    if (--cnt == 0)
    {
        cnt = 5;
        font.setPointSize(12);
        moneyText->setFont(font);
        mWinTimer->stop();
        return;
    }

    if (font.pointSize() != 16)
        font.setPointSize(16);
    else
        font.setPointSize(12);

    moneyText->setFont(font);
}
