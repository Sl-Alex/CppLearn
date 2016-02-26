#include "mainwindow.h"
#include "aboutdialog.h"
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
    aboutAction = menuBar()->addAction(tr("&About..."), this, SLOT(onAbout()));
    aboutAction->setStatusTip(tr("Show about window"));

    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));

    QToolBar *toolbar = addToolBar(tr("Main toolbar"));

    QPixmap pix(assetsPath.arg("page_add.png"));
    toolbar->addAction(QIcon(pix),"New",this,SLOT(onNew()));
    toolbar->addSeparator();
    pix.load(assetsPath.arg("folder_page.png"));
    toolbar->addAction(QIcon(pix), "Open",this, SLOT(onOpen()));
    pix.load(assetsPath.arg("page_save.png"));
    toolbar->addAction(QIcon(pix), tr("Save"),this, SLOT(onSave()));
    toolbar->setFloatable(false);
    toolbar->setMovable(false);
    colLabel = new QLabel();
    rowLabel = new QLabel();
    statusBar()->addPermanentWidget(colLabel,0);
    statusBar()->addPermanentWidget(rowLabel,0);
    colLabel->setText(statusCol.arg(0));
    rowLabel->setText(statusRow.arg(0));

    updateTitle();
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
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
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
    updateTitle();
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
                QMessageBox::warning(this, tr("Error"), tr("Cannot save text"), QMessageBox::Ok, QMessageBox::Ok);
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
            QMessageBox::warning(this, tr("Error"), tr("Cannot open for write"), QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    updateTitle();
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
    updateTitle();
}

void MainWindow::onTextChanged(void)
{
    if (mModified)
        return;

    mModified = true;
    updateTitle();
}

void MainWindow::onCursorPositionChanged(void)
{
    colLabel->setText(statusCol.arg(textEdit->textCursor().columnNumber()));
    rowLabel->setText(statusRow.arg(textEdit->textCursor().blockNumber()));
}

void MainWindow::onAbout(void)
{
    AboutDialog dlg(this);
    dlg.exec();
}

void MainWindow::onOpen(void)
{
    if (suggestSave() == false)
        return;

    mModified = false;

    mFileName = QFileDialog::getOpenFileName(this,tr("Open File"),"","");

    if (mFileName.isEmpty() == false)
    {
        QFile file(mFileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            textEdit->clear();
            QByteArray ba = file.readAll();
            textEdit->setText(QString(ba));
            mModified = false;
            file.close();
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Cannot open for read"), QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    updateTitle();
}

void MainWindow::updateTitle(void)
{
    if (mFileName.isEmpty())
    {
        setWindowTitle(tr("Simple Text Editor"));
        return;
    }

    QFileInfo fi(mFileName);
    QString title = "";
    if (mModified)
        title = "*";
    title = title.append(fi.fileName()).append(" - ").append(fi.absolutePath());
    setWindowTitle(title);

}
