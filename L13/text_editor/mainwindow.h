#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QTextEdit>

const QString assetsPath = "../text_editor/assets/%1";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void onExit(void);
private:
    QTextEdit * textEdit;
    QMenu *fileMenu;
    QAction *helpAction;
    QAction *exitAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    bool mModified;

    void closeEvent(QCloseEvent * event);
};

#endif // MAINWINDOW_H
