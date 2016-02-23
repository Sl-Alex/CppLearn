#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void buttonAClicked(void);
    void buttonBClicked(void);
    void buttonCClicked(void);
    void buttonClearClicked(void);
    void addChar(QChar ch);

private:
    QWidget *centralWidget;
    QLineEdit * lineEdit;
};

#endif // MAINWINDOW_H
