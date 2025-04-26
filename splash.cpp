#include "splash.h"
#include <QVBoxLayout>
#include <QPixmap>

SplashScreen::SplashScreen(QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("Splash Screen");

    imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap("splash.jpg").scaled(460, 215, Qt::KeepAspectRatio));

    startButton = new QPushButton("Start", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel, 0, Qt::AlignCenter);
    layout->addWidget(startButton, 0, Qt::AlignCenter);

    connect(startButton, &QPushButton::clicked, this, &SplashScreen::startClicked);
}
