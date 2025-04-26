#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class SplashScreen : public QWidget {
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);

signals:
    void startClicked();

private:
    QLabel *imageLabel;
    QPushButton *startButton;
};

#endif // SPLASH_H
