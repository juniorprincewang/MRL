#include "menu.h"

Menu::Menu(QWidget *parent)
    :QWidget(parent)
{
    layout = new QHBoxLayout(this);
    startButton = new QPushButton(QStringLiteral("开始"), this);
    analyseButton = new QPushButton(QStringLiteral("限量分析"), this);
    assessButton = new QPushButton(QStringLiteral("安全评估"), this);
    helpButton = new QPushButton(QStringLiteral("帮助"), this);
    layout->addWidget(startButton);
    layout->addWidget(analyseButton);
    layout->addWidget(assessButton);
    layout->addWidget(helpButton);

    layout->addStretch();

    QObject::connect(analyseButton, &QPushButton::clicked, this, &Menu::analyseButtonClick);
    QObject::connect(assessButton, &QPushButton::clicked, this, &Menu::assessButtonClick);
    QObject::connect(startButton, &QPushButton::clicked, this, &Menu::startButtonClick);
    QObject::connect(helpButton, &QPushButton::clicked, this, &Menu::helpButtonClick);
}


void Menu::analyseButtonClick()
{
    emit changeMenu(1);
    emit changeContentInterface(2);
}

void Menu::assessButtonClick()
{
    emit changeMenu(2);
    emit changeContentInterface(2);
}

void Menu::startButtonClick()
{
    emit changeMenu(0);
    emit changeContentInterface(0);
}
void Menu::helpButtonClick()
{
    emit changeMenu(3);
    emit changeContentInterface(1);
}
