#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
#include <QGraphicsScene>

class GameBoard : public QMainWindow {
    Q_OBJECT
private:
    QGraphicsScene *scene;
    QString selectedUnit;
    QString currentPlayer = "P1";
private slots:
    void onTileClicked(int row, int col);
public:
    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();
};

#endif // GAMEBOARD_H
