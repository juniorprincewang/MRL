#include "content.h"
#include <QPixmap>

Content::Content(QWidget *parent)
    : QStackedWidget(parent)
{
//    stack = new QStackedWidget(this);
    this->setFrameStyle(QFrame::Panel | QFrame::Raised);
    /*插入其他页面*/

    insertionPage = new DataInsertion(this);
    welcomePage = new WelcomeInterface(this);
    this->addWidget(welcomePage);
    this->addWidget(insertionPage);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);
}


WelcomeInterface::WelcomeInterface(QWidget *parent)
    :QLabel(parent)
{
    QPixmap pixmap(":/images/welcome");
    this->setPixmap(pixmap);
}



