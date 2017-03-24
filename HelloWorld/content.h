#ifndef CONTENT_H
#define CONTENT_H

#include <QStackedWidget>
#include <QPushButton>
#include "datainsertion.h"

class WelcomeInterface: public QLabel
{
    Q_OBJECT
public:
    WelcomeInterface(QWidget *parent = 0);

};

class Content : public QStackedWidget
{
    Q_OBJECT

public:
    Content(QWidget *parent = 0);
    DataInsertion *insertionPage;
    WelcomeInterface *welcomePage;
private:

};


#endif // CONTENT_H
