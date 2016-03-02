#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QLabel>
#include <ui_mainwindow.h>

const QString statusCol = "COL: %1";
const QString statusRow = "ROW: %1";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExit_triggered();
    void on_textEdit_textChanged();
    void on_textEdit_cursorPositionChanged();
    void on_actionInformation_triggered();
private:
    QLabel * colLabel;
    QLabel * rowLabel;
    bool mModified;
    QString mFileName;

    bool suggestSave(void);
    void updateTitle(void);
    void closeEvent(QCloseEvent * event);

    Ui::MainWindow * ui;

};

#endif // MAINWINDOW_H
