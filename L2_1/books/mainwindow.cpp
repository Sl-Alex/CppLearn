#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QModelIndex>

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

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.exec();
    if (dialog.selectedFiles().size() == 0)
        return;

    QString fileName = dialog.selectedFiles().at(0);

    if (fileName.isEmpty())
        return;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    db.open();
    QSqlQuery query;
    query.exec("CREATE TABLE books (id INTEGER PRIMARY KEY, bookID TEXT, authors TEXT, title TEXT, publisher TEXT, year INTEGER, code INTEGER, borrowed TEXT)");
    query.clear();
    query.prepare("INSERT INTO books (bookID, authors, title, publisher, year, code, borrowed)"
                  "VALUES (:bookID, :authors, :title, :publisher, :year, :code, :borrowed);");
    for (int i = 0; i < ui->tableView->model()->rowCount(); ++i)
    {
        QModelIndex idx = ui->tableView->model()->index(0,0);
        query.bindValue(":bookID",ui->tableView->model()->data(idx));
        query.bindValue(":authors",ui->tableView->model()->data(idx.child(idx.row(),1)));
        query.bindValue(":title",ui->tableView->model()->data(idx.child(idx.row(),2)));
        query.bindValue(":publisher",ui->tableView->model()->data(idx.child(idx.row(),3)));
        query.bindValue(":year",ui->tableView->model()->data(idx.child(idx.row(),4)));
        query.bindValue(":code",ui->tableView->model()->data(idx.child(idx.row(),5)));
        query.bindValue(":borrowed",ui->tableView->model()->data(idx.child(idx.row(),6)));

        query.exec();
    }
}
