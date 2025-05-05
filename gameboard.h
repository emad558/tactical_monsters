#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMap>
#include <utility>
#include "clickabletile.h"

class GameBoard : public QMainWindow
{
    Q_OBJECT
public:
    enum Player { Player1, Player2 };
    enum GameState { PlacingUnit, SelectingUnit, SelectingDestination };

    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();

private slots:
    void onTileClicked(int row, int col);

private:
    char data[11][11];
    void handleUnitPlacement(int row, int col);
    void handleUnitSelection(QList<QGraphicsItem*> items, int row, int col);
    void handleUnitMovement(QList<QGraphicsItem*> items, int row, int col);
    void highlightMovementTiles(int startRow, int startCol, int range);
    void highlightPlacementTiles();
    void clearHighlights();
    void resetMovementState();
    void moveUnitTo(ClickableTile* unit, int newRow, int newCol);
    bool isOwnUnit(ClickableTile* unit);
    bool isValidPosition(int row, int col) const;
    bool isMovementAllowed(int row, int col);
    void switchTurns();
    void updateTurnIndicator();

    QGraphicsScene *scene;
    Player currentPlayer;
    GameState currentState;
    bool isUnitSelected;
    QString selectedUnitType;
    QString selectedUnitImagePath;
    ClickableTile* selectedUnitTile;
    QPointF originalPosition;

    QMap<QString, QString> unitImagePaths;
    QMap<int, QMap<int, std::pair<QString, ClickableTile*>>> unitsOnBoard;
};

#endif // GAMEBOARD_H
