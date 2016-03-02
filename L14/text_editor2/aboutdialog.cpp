#include "aboutdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QVariant>

AboutDialog::AboutDialog(QWidget * parent)
   : QDialog(parent)
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QLabel * header = new QLabel("Some information");
    header->setProperty("isHeader", true);
    mainLayout->addWidget(header);
    QLabel * text = new QLabel(tr(
        "This is just a very simple text editor, which was created in order "
        "to practice a bit with some Qt classes. You can use it at your own "
        "risk. I'm not responsible if this software will burn your house, "
        " spend your money and format your hard disk :).\n\nGood luck!"));
    text->setWordWrap(true);
    mainLayout->addWidget(text);
    setWindowTitle("About editor");
}
