#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QToolBar>
#include <QPixmap>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mModified = true;

    textEdit = new QTextEdit(this);
    this->setCentralWidget( textEdit );

    fileMenu = menuBar()->addMenu(tr("&File"));
    openAction = fileMenu->addAction(tr("&Open..."));
    saveAction = fileMenu->addAction(tr("&Save"));
    saveAsAction = fileMenu->addAction(tr("Save &As..."));
    fileMenu->addSeparator();
    exitAction = fileMenu->addAction(tr("E&xit"));
    exitAction->setStatusTip(tr("Exit from the program"));
    helpAction = menuBar()->addAction(tr("&Help..."));
    helpAction->setStatusTip(tr("Show help"));

    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExit()));

    QPixmap savepix(assetsPath.arg("disk.png"));

    QToolBar *toolbar = addToolBar("main toolbar");
    toolbar->addAction(QIcon(savepix), "Save");
    toolbar->setFloatable(false);
    toolbar->setMovable(false);
    toolbar->addSeparator();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if (mModified)
    {
        int ret = QMessageBox::warning(this, tr("Text Editor"),
                                       tr("The document has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel,
                                       QMessageBox::Save);

        if (ret == QMessageBox::Cancel)
            event->ignore();

        if (ret == QMessageBox::Save)
        {
            /// @todo implement saving procedure
        }
    }

    event->accept();
}

void MainWindow::onExit()
{
    close();
}
