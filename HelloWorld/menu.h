#pragma execution_character_set("utf-8")
#ifndef MENU_H
#define MENU_H
#include <QLayout>
#include <QPushButton>
#include "analyselist.h"
class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent = 0);
    QPushButton *startButton;
    QPushButton *analyseButton;
    QPushButton *assessButton;
    QPushButton *helpButton;

private:
    QHBoxLayout *layout;
public slots:
    void startButtonClick();
    void analyseButtonClick();
    void assessButtonClick();
    void helpButtonClick();
signals:
    void changeMenu(int);
    void changeContentInterface(int);

};

#endif // MENU_H
