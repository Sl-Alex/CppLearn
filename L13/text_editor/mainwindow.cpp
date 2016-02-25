#include "mainwindow.h"
#include "helpdialog.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QToolBar>
#include <QPixmap>
#include <QIcon>
#include <QFileDialog>
#include <QTextStream>
#include <QKeySequence>
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mModified = false;
    mFileName = "";

    textEdit = new QTextEdit(this);
    this->setCentralWidget( textEdit );
    textEdit->setWordWrapMode(QTextOption::NoWrap);

    fileMenu = menuBar()->addMenu(tr("&File"));
    newAction = fileMenu->addAction(tr("&New"), this, SLOT(onNew()),QKeySequence::New);
    newAction->setStatusTip(tr("Create a new text document"));
    openAction = fileMenu->addAction(tr("&Open..."), this, SLOT(onOpen()),QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing text document"));
    saveAction = fileMenu->addAction(tr("&Save"), this, SLOT(onSave()), QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current document"));
    saveAsAction = fileMenu->addAction(tr("Save &As..."), this, SLOT(onSaveAs()),QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save current document under different name"));
    fileMenu->addSeparator();
    closeAction = fileMenu->addAction(tr("E&xit"), this, SLOT(onClose()), QKeySequence::Close);
    closeAction->setStatusTip(tr("Exit from the program"));
    helpAction = menuBar()->addAction(tr("&Help..."), this, SLOT(onHelp()));
    helpAction->setStatusTip(tr("Show help"));

    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));

    QToolBar *toolbar = addToolBar("main toolbar");

    QPixmap pix(assetsPath.arg("page_add.png"));
    toolbar->addAction(QIcon(pix),"New",this,SLOT(onNew()));
    pix.load(assetsPath.arg("page_save.png"));
    toolbar->addAction(QIcon(pix), "Save",this, SLOT(onSave()));
    toolbar->setFloatable(false);
    toolbar->setMovable(false);
    toolbar->addSeparator();
    colLabel = new QLabel();
    rowLabel = new QLabel();
    statusBar()->addPermanentWidget(colLabel,0);
    statusBar()->addPermanentWidget(rowLabel,0);
    colLabel->setText(statusCol.arg(0));
    rowLabel->setText(statusRow.arg(0));

    setWindowTitle(tr("Simple Text Editor"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if (suggestSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

bool MainWindow::suggestSave(void)
{
    if (mModified)
    {
        int ret = QMessageBox::warning(this, tr("Text Editor"),
                                       tr("Current document has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel,
                                       QMessageBox::Save);

        if (ret == QMessageBox::Cancel)
            return false;

        if (ret == QMessageBox::Save)
        {
            onSave();
            // Check if everything is saved
            if (mModified)
                return false;
        }
    }
    return true;
}

void MainWindow::onClose()
{
    close();
}

void MainWindow::onNew(void)
{
    if (suggestSave())
    {
        textEdit->clear();
        mModified = false;
        mFileName = "";
    }
}

/// @todo Implement saving procedure
void MainWindow::onSave(void)
{
    if (mFileName.isEmpty())
        mFileName = QFileDialog::getSaveFileName(this,tr("Save File"),"textfile.txt","");

    if (mFileName.isEmpty() == false)
    {
        QFile file(mFileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            if (file.flush() == false)
            {
                QMessageBox::warning(this, tr("Error"), "Cannot save text", QMessageBox::Ok, QMessageBox::Ok);
            }
            else
            {
                // Successful write
                mModified = false;
            }
            // Close anyway
            file.close();
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), "Cannot be opened for write!!!", QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

void MainWindow::onSaveAs(void)
{
    QString oldFileName = mFileName;
    bool oldModified = mModified;
    mFileName = "";
    mModified = true;
    onSave();
    // If case of save failure
    if (mModified)
    {
        // Restore old state
        mModified = oldModified;
        mFileName = oldFileName;
    }
}

void MainWindow::onTextChanged(void)
{
    mModified = true;
}

void MainWindow::onCursorPositionChanged(void)
{
    colLabel->setText(statusCol.arg(textEdit->textCursor().columnNumber()));
    rowLabel->setText(statusRow.arg(textEdit->textCursor().blockNumber()));
}

void MainWindow::onHelp(void)
{
    HelpDialog dlg(this);
    dlg.exec();
}

void MainWindow::onOpen(void)
{
    QMessageBox::warning(this, tr("Error"), "Cannot be opened for write!!!", QMessageBox::Ok, QMessageBox::Ok);
}
