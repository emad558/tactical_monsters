#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>

class GameBoard : public QMainWindow {
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();
};

#endif // GAMEBOARD_H
