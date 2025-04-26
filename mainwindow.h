#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QLabel *backgroundLabel;
    QPushButton *button1;
    QPushButton *button2;
};

#endif // MAINWINDOW_H
