#include "mainwindow.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    centralWidget = new QWidget(this);

    this->setCentralWidget( centralWidget );

    QVBoxLayout * mainLayout = new QVBoxLayout(centralWidget);
    lineEdit = new QLineEdit();
    mainLayout->addWidget(lineEdit);
    QPushButton * buttonA = new QPushButton(tr("Add \"A\""));
    QPushButton * buttonB = new QPushButton(tr("Add \"B\""));
    QPushButton * buttonC = new QPushButton(tr("Add \"C\""));
    QPushButton * buttonClear = new QPushButton(tr("Clear"));
    mainLayout->addWidget(buttonA);
    mainLayout->addWidget(buttonB);
    mainLayout->addWidget(buttonC);
    mainLayout->addWidget(buttonClear);

    connect(buttonA, SIGNAL(clicked()), this, SLOT(buttonAClicked()));
    connect(buttonB, SIGNAL(clicked()), this, SLOT(buttonBClicked()));
    connect(buttonC, SIGNAL(clicked()), this, SLOT(buttonCClicked()));
    connect(buttonClear, SIGNAL(clicked()), this, SLOT(buttonClearClicked()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::addChar(QChar ch)
{
    lineEdit->setText(lineEdit->text().append(ch));
}

void MainWindow::buttonAClicked(void)
{
    addChar('A');
}

void MainWindow::buttonBClicked(void)
{
    addChar('B');
}

void MainWindow::buttonCClicked(void)
{
    addChar('C');
}

void MainWindow::buttonClearClicked(void)
{
    lineEdit->clear();
}
