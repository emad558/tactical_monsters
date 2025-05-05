#include "mainwindow.h"
#include <QPixmap>
#include <QVBoxLayout>
#include <QPushButton>
#include "gameboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1024, 768);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    backgroundLabel = new QLabel(centralWidget);
    backgroundLabel->setAlignment(Qt::AlignCenter);

    QPixmap bg("image/bg.jpg");
    if(bg.isNull()) {
        qDebug() << "Failed to load background image!";
    }
    backgroundLabel->setPixmap(bg);
    backgroundLabel->lower();

    QPushButton *button1 = new QPushButton("New Game", centralWidget);
    QPushButton *button2 = new QPushButton("Gallery", centralWidget);

    button1->setStyleSheet("font-size: 18px; padding: 10px; min-width: 200px;");
    button2->setStyleSheet("font-size: 18px; padding: 10px; min-width: 200px;");

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addStretch();
    layout->addWidget(button1, 0, Qt::AlignCenter);
    layout->addWidget(button2, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(button1, &QPushButton::clicked, this, [this](){
        GameBoard *board = new GameBoard();
        board->show();
        hide();
    });

    updateBackground();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

void MainWindow::updateBackground()
{
    if (backgroundLabel) {
        QPixmap original("image/bg.jpg");
        if (!original.isNull()) {
            QPixmap scaled = original.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            backgroundLabel->setPixmap(scaled);
            backgroundLabel->resize(size());
        }
    }
}
