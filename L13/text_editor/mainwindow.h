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
    void onNew(void);
    void onSave(void);
    void onSaveAs(void);
    void onClose(void);
    void onTextChanged(void);
    void onHelp(void);
private:
    QTextEdit * textEdit;
    QMenu *fileMenu;
    QAction *helpAction;
    QAction *closeAction;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    bool mModified;
    QString mFileName;

    bool suggestSave(void);
    void closeEvent(QCloseEvent * event);
};

#endif // MAINWINDOW_H
