#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QWidget>

const QString helpImagePath = "../slot_machine/help%1.png";

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    HelpDialog(QWidget *parent = 0);

private:
};

#endif // HELPDIALOG_H
