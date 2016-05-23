#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "bookparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pBookTable = new BookTableModel(0);
    ui->tableView->setModel(pBookTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    modified = false;
}

MainWindow::~MainWindow()
{
    delete pBookTable;
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    /// @todo Ask for unsaved data
    close();
}

/// @brief Open text file with data
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open data file"), QDir::currentPath(), tr("Text file (*.txt);;Any file (*.*)"));

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Warning, "File open error","Can't open file for reading").exec();
        return;
    }

    pBookTable->clear();
    while (!file.atEnd()) {
        Book book;
        QString line = file.readLine();
        if (BookParser::parseLine(line,&book))
        {
            pBookTable->add(&book);
        }
        else
        {
            //@todo Can't parse line
        }
    }
    file.close();
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    ui->idEdit->setText(pBookTable->data(index.child(index.row(),0)).toString());
    ui->authorsEdit->setText(pBookTable->data(index.child(index.row(),1)).toString());
    ui->titleEdit->setText(pBookTable->data(index.child(index.row(),2)).toString());
    ui->publisherEdit->setText(pBookTable->data(index.child(index.row(),3)).toString());
    ui->yearEdit->setText(pBookTable->data(index.child(index.row(),4)).toString());
    ui->codeEdit->setText(pBookTable->data(index.child(index.row(),5)).toString());
    ui->borrowedEdit->setText(pBookTable->data(index.child(index.row(),6)).toString());
}
