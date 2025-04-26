#include "mainwindow.h"
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>
#include "gameboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Central widget to hold everything
    QWidget *central = new QWidget(this);
    this->setCentralWidget(central);

    // Background image
    backgroundLabel = new QLabel(central);
    backgroundLabel->setPixmap(QPixmap("bg.png").scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->lower();  // Push it to the back

    // Two buttons
    button1 = new QPushButton("Button 1", central);
    button2 = new QPushButton("Button 2", central);

    button1->setStyleSheet("font-size: 18px; padding: 10px;");
    button2->setStyleSheet("font-size: 18px; padding: 10px;");

    // Layout for buttons
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();
    layout->addWidget(button1, 0, Qt::AlignCenter);
    layout->addWidget(button2, 0, Qt::AlignCenter);
    layout->addStretch();


    connect(button1,&QPushButton::clicked , this,[this](){
        GameBoard* board = new GameBoard();
        board->show();
        this->hide();


    });
    central->setLayout(layout);
}
