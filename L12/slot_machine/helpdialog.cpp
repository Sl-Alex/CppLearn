#include <QtWidgets>

#include "helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent)
{
    QPixmap pix;
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    // Window options
    setWindowTitle(tr("Help"));

    QLabel * helpText = new QLabel(tr("The rules are very easy to understand and remember.\n"
                                      "At the start you have only 9 dollars. Each spin costs\n"
                                      "exactly 1 dollar. You can win a lot of money with several\n"
                                      "successful combinations (see below). You can spend as\n"
                                      "much money as you wish. Good luck!"));
    mainLayout->addWidget(helpText);
    // Header
    QGridLayout * rulesLayout = new QGridLayout();
    QLabel * header1Text = new QLabel(tr("RESULT"));
    QLabel * header2Text = new QLabel(tr("RULE"));
    QLabel * header3Text = new QLabel(tr("SCORES"));
    header1Text->setProperty("isHeader",true);
    header2Text->setProperty("isHeader",true);
    header3Text->setProperty("isHeader",true);

    rulesLayout->addWidget(header1Text,0,0);
    rulesLayout->addWidget(header2Text,0,1);
    rulesLayout->addWidget(header3Text,0,2);

    // Rule 1
    QHBoxLayout * rule1Pics = new QHBoxLayout();
    QLabel * rule1pic1 = new QLabel();
    QLabel * rule1pic2 = new QLabel();
    QLabel * rule1pic3 = new QLabel();
    pix.load(helpImagePath.arg(1));
    rule1pic1->setPixmap(pix);
    rule1pic2->setPixmap(pix);
    rule1pic3->setPixmap(pix);
    rule1Pics->addWidget(rule1pic1);
    rule1Pics->addWidget(rule1pic2);
    rule1Pics->addWidget(rule1pic3);
    QLabel * rule1Text = new QLabel(tr("3 identical pictures"));
    QLabel * rule1Result = new QLabel("10");
    rule1Result->setProperty("isStats", true);
    rulesLayout->addLayout(rule1Pics,1,0);
    rulesLayout->addWidget(rule1Text,1,1);
    rulesLayout->addWidget(rule1Result,1,2);

    // Rule 2
    QHBoxLayout * rule2Pics = new QHBoxLayout();
    QLabel * rule2pic1 = new QLabel();
    QLabel * rule2pic2 = new QLabel();
    pix.load(helpImagePath.arg(2));
    rule2pic1->setPixmap(pix);
    rule2pic2->setPixmap(pix);
    rule2Pics->addWidget(rule2pic1);
    rule2Pics->addWidget(rule2pic2);
    QLabel * rule2Text = new QLabel(tr("2 identical pictures"));
    QLabel * rule2Result = new QLabel("5");
    rule2Result->setProperty("isStats", true);
    rulesLayout->addLayout(rule2Pics,2,0,1,1,Qt::AlignLeft);
    rulesLayout->addWidget(rule2Text,2,1);
    rulesLayout->addWidget(rule2Result,2,2);

    // Rule 3
    QLabel * rule3pic = new QLabel();
    pix.load(helpImagePath.arg(3));
    rule3pic->setPixmap(pix);
    QLabel * rule3Text = new QLabel(tr("Each dollar"));
    QLabel * rule3Result = new QLabel("2");
    rule3Result->setProperty("isStats", true);
    rulesLayout->addWidget(rule3pic,3,0,1,1,Qt::AlignLeft);
    rulesLayout->addWidget(rule3Text,3,1);
    rulesLayout->addWidget(rule3Result,3,2);

    mainLayout->addLayout(rulesLayout);

    // Layout is done, set fixed size
    setFixedSize(sizeHint());
}
