#include "gameboard.h"
#include <QLabel>
#include <QPixmap>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>
#include <iostream>
#include <fstream>

void GameBoard::onTileClicked(int row, int col)
{
    QList<QGraphicsItem*> items = scene->items(QPointF(
        col * 96 * 0.75,
        row * 81 + (col % 2 == 1 ? 81 / 2 : 0)
        ));

    switch(currentState) {
    case PlacingUnit:
        handleUnitPlacement(row, col);
        break;
    case SelectingUnit:
        handleUnitSelection(items, row, col);
        break;
    case SelectingDestination:

        if (selectedUnitTile != nullptr) {
            handleUnitMovement(items, row, col);
        }
        break;
    }
}

void GameBoard::handleUnitPlacement(int row, int col)
{
    int dataRow = row;
    int dataCol = col / 2;
    char tileData = (col % 2 == 0) ? data[dataRow*2 + 1][dataCol*2 + 1]
                                   : data[dataRow*2 + 2][dataCol*2 + 2];


    bool isOwned = (currentPlayer == Player1 && tileData == '1') ||
                   (currentPlayer == Player2 && tileData == '2');

    if (!isOwned) {
        qDebug() << "فقط می‌توانید روی خانه‌های خودتان سرباز قرار دهید!";
        return;
    }


    if (unitsOnBoard.contains(row) && unitsOnBoard[row].contains(col)) {
        qDebug() << "خانه قبلاً occupied است!";
        return;
    }

    QPixmap unitImg(selectedUnitImagePath);
    if (unitImg.isNull()) {
        unitImg = QPixmap("images/default_unit.png").scaled(96, 96);
    }

    ClickableTile *unit = new ClickableTile(unitImg.scaled(96, 81), row, col);
    unit->setPos(col * 96 * 0.75, row * 81 + (col % 2 == 1 ? 81 / 2 : 0));
    scene->addItem(unit);
    connect(unit, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

    unitsOnBoard[row][col] = std::make_pair(selectedUnitType, unit);
    isUnitSelected = false;
    currentState = SelectingUnit;
    clearHighlights();
    switchTurns();
}

void GameBoard::highlightPlacementTiles()
{
    clearHighlights();

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 9; c++) {

            int dataRow = r;
            int dataCol = c / 2;
            char tileData = (c % 2 == 0) ? data[dataRow*2 + 1][dataCol*2 + 1]
                                         : data[dataRow*2 + 2][dataCol*2 + 2];

            bool isOwned = (currentPlayer == Player1 && tileData == '1') ||
                           (currentPlayer == Player2 && tileData == '2');

            if (isOwned && (!unitsOnBoard.contains(r) || !unitsOnBoard[r].contains(c))) {
                ClickableTile* highlight = new ClickableTile(
                    QPixmap("image/place_highlight.jpg").scaled(96, 96),
                    r, c
                    );
                highlight->setPos(c * 96 * 0.75, r * 81 + (c % 2 == 1 ? 81 / 2 : 0));
                highlight->setZValue(-1);
                highlight->setIsHighlight(true);
                scene->addItem(highlight);
            }
        }
    }
}

void GameBoard::handleUnitSelection(QList<QGraphicsItem*> items, int row, int col)
{
    if (!items.isEmpty()) {
        ClickableTile* item = dynamic_cast<ClickableTile*>(items.first());
        if (item && isOwnUnit(item)) {
            selectedUnitTile = item;
            originalPosition = item->pos();
            currentState = SelectingDestination;
            highlightMovementTiles(row, col, 2);
            qDebug() << "Selected unit at:" << row << col;

            return;
        }
    }

    if (isUnitSelected && currentState == PlacingUnit) {
        handleUnitPlacement(row, col);
    }
}

void GameBoard::handleUnitMovement(QList<QGraphicsItem*> items, int row, int col)
{
    if (selectedUnitTile == nullptr) {
        qDebug() << "No unit selected for movement!";
        return;
    }

    bool isHighlighted = false;
    QPointF targetPos(col * 96 * 0.75, row * 81 + (col % 2 == 1 ? 81 / 2 : 0));

    for (auto item : scene->items(targetPos)) {
        if (auto tile = dynamic_cast<ClickableTile*>(item)) {
            if (tile->isHighlight()) {
                isHighlighted = true;
                break;
            }
        }
    }

    if (!isHighlighted) {
        qDebug() << "حرکت به این خانه مجاز نیست!";
        return;
    }

    moveUnitTo(selectedUnitTile, row, col);
    resetMovementState();
    switchTurns();
    qDebug() << "سرباز به موقعیت (" << row << "," << col << ") منتقل شد";
}

void GameBoard::highlightMovementTiles(int startRow, int startCol, int range)
{
    clearHighlights();

    for (int r = -range; r <= range; r++) {
        for (int c = -range; c <= range; c++) {
            if (abs(r + c) <= range) {
                int newRow = startRow + r;
                int newCol = startCol + c;

                if (isValidPosition(newRow, newCol) &&
                    (!unitsOnBoard.contains(newRow) || !unitsOnBoard[newRow].contains(newCol))) {


                    qreal x = newCol * 96 * 0.75;
                    qreal y = newRow * 81;
                    if (newCol % 2 == 1) y += 81 / 2;

                    ClickableTile* highlight = new ClickableTile(
                        QPixmap("image/highlight.jpg").scaled(96, 96),
                        newRow, newCol
                        );
                    highlight->setPos(x, y);
                    highlight->setZValue(-1);
                    highlight->setIsHighlight(true);
                    scene->addItem(highlight);
                }
            }
        }
    }
}

void GameBoard::clearHighlights()
{
    QList<QGraphicsItem*> items = scene->items();
    for (auto item : items) {
        if (auto tile = dynamic_cast<ClickableTile*>(item)) {
            if (tile->isHighlight()) {
                scene->removeItem(tile);
                delete tile;
            }
        }
    }
}

void GameBoard::resetMovementState()
{
    clearHighlights();
    currentState = SelectingUnit;
    selectedUnitTile = nullptr;
}

void GameBoard::moveUnitTo(ClickableTile* unit, int newRow, int newCol)
{

    qreal x = newCol * 96 * 0.75;
    qreal y = newRow * 81;
    if (newCol % 2 == 1) y += 81 / 2;


    unit->setPos(x, y);
    unit->setZValue(1);


    QString unitType = unitsOnBoard[unit->getRow()][unit->getCol()].first;
    unitsOnBoard[newRow][newCol] = std::make_pair(unitType, unit);
    unitsOnBoard[unit->getRow()].remove(unit->getCol());

    unit->setRow(newRow);
    unit->setCol(newCol);
}

bool GameBoard::isOwnUnit(ClickableTile* unit)
{
    auto& unitData = unitsOnBoard[unit->getRow()][unit->getCol()];
    QString unitType = unitData.first;
    return (currentPlayer == Player1 && unitType.startsWith("P1")) ||
           (currentPlayer == Player2 && unitType.startsWith("P2"));
}

bool GameBoard::isValidPosition(int row, int col) const
{
    return row >= 0 && row < 5 && col >= 0 && col < 9;
}

bool GameBoard::isMovementAllowed(int row, int col)
{
    for (auto item : scene->items(QPointF(
        col * 96 * 0.75,
        row * 81 + (col % 2 == 1 ? 81 / 2 : 0)
             ))) {
        if (auto tile = dynamic_cast<ClickableTile*>(item)) {
            if (tile->isHighlight()) return true;
        }
    }
    return false;
}

void GameBoard::switchTurns()
{
    currentPlayer = (currentPlayer == Player1) ? Player2 : Player1;
    updateTurnIndicator();
    qDebug() << "Turn switched to:" << currentPlayer;
}

void GameBoard::updateTurnIndicator()
{

}

GameBoard::GameBoard(QWidget *parent)
    : QMainWindow(parent), currentPlayer(Player1),
      currentState(SelectingUnit), isUnitSelected(false),
      selectedUnitTile(nullptr)
{
    this->setWindowTitle("Main Game Board");
    this->resize(1180, 820);

    // Initialize unit images
    unitImagePaths = {
        {"P1 Unit 1", "image/a1.jpg"},
        {"P1 Unit 2", "image/a2.jpg"},
        {"P2 Unit 1", "image/a3.jpg"},
        {"P2 Unit 2", "image/a3.jpg"}
    };

    scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setFixedSize(1180, 820);

    view->setRenderHint(QPainter::Antialiasing);
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    const int tileWidth = 96;
    const int tileHeight = 81;
    const int rows = 5;
    const int cols = 9;
    char data1[5][5];
    char data2[4][4];
    // char data[11][11];
    memset(data, 0, sizeof(data));
    std::cout << "asdasd" << std::endl;

    std::string myText;
    std::ifstream MyReadFile("grids/grid1.txt");
    int line = 0 ;
    int currLine1 = 0 ;
    int currLine2 = 0 ;



    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
            data[i][j] = 'r';
        }
    }

    while (getline (MyReadFile, myText)) {
        if(line%2 == 1){
            for(int ch=0 ; ch < 5; ch++){
                data1[currLine1][ch] = myText[ch*6 + 1];
                // data[currLine1*2][ch]
            }
            currLine1++;
        }else{
            if(line!=0 && line!=10){
                for(int ch=0 ; ch < 4; ch++){
                    data2[currLine2][ch] = myText[ch*6 + 4];
                }
                currLine2++;
            }

        }
        // std::cout << myText << std::endl;
        line++;
    }


    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {

            if(data1[i][j] == ' '){
                data[i*2 + 1][j*2 + 1] = 'e' ;
            }else if(data1[i][j] == '~'){
                data[i*2 + 1][j*2 + 1] = 'w' ;
            }else if(data1[i][j] == '1'){
                data[i*2 + 1][j*2 + 1] = '1' ;
            }else if(data1[i][j] == '2'){
                data[i*2 + 1][j*2 + 1] = '2' ;
            }else if(data1[i][j] == '#'){
                data[i*2 + 1][j*2 + 1] = 'r' ;
            }

            // data[i*2 + 1][j*2 + 1] = data1[i][j] ;
        }
    }


    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(data2[i][j] == ' '){
                data[i*2 + 2][j*2 + 2] = 'e' ;
            }else if(data2[i][j] == '~'){
                data[i*2 + 2][j*2 + 2] = 'w' ;
            }else if(data2[i][j] == '1'){
                data[i*2 + 2][j*2 + 2] = '1' ;
            }else if(data2[i][j] == '2'){
                data[i*2 + 2][j*2 + 2] = '2' ;
            }else if(data2[i][j] == '#'){
                data[i*2 + 2][j*2 + 2] = 'r' ;
            }
            // data[i*2 + 2][j*2 + 2] = data2[i][j] ;
        }
    }

    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {

            std::cout << data1[i][j] << " ";
        }
        std::cout << std::endl;
    }


    // for(int a = 0; a < 5; a++)
    // {
    //     for(int b = 0; b < 5; b++)
    //     {
    //         std::cout << data1[a][b] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for(int a = 0; a < 4; a++)
    // {
    //     for(int b = 0; b < 4; b++)
    //     {
    //         std::cout << data2[a][b] << " ";
    //     }
    //     std::cout << std::endl;
    // }


    QPixmap imgEmpty("image/polyg.png");
    QPixmap imgWater("image/water.jpg");
    QPixmap imgRock("image/rock.jpg");
    QPixmap imgP1("image/p1.jpg");
    QPixmap imgP2("image/p2.jpg");

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {





            // QPixmap pixmap("polyg.png");
            // QPixmap scaled = pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);


            int x = col * tileWidth * 0.75;
            int y = row * tileHeight;

            if (col % 2 == 1) {
                if(row == rows-1){
                    continue;
                }
                y += tileHeight / 2;

                if(data2[row][col/2] == '1'){
                    QPixmap scaled = imgP1.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data2[row][col/2] == '2'){
                    QPixmap scaled = imgP2.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);                    item->setPos(x, y);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    scene->addItem(item);
                }else if(data2[row][col/2] == '#'){
                    QPixmap scaled = imgRock.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data2[row][col/2] == '~'){
                    QPixmap scaled = imgWater.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data2[row][col/2] == ' '){
                    QPixmap scaled = imgEmpty.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }
                // }
            }else{
                if(data1[row][col/2] == '1'){
                    QPixmap scaled = imgP1.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data1[row][col/2] == '2'){
                    QPixmap scaled = imgP2.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data1[row][col/2] == '#'){
                    QPixmap scaled = imgRock.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data1[row][col/2] == '~'){
                    QPixmap scaled = imgWater.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data1[row][col/2] == ' '){
                    QPixmap scaled = imgEmpty.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    connect(item, &ClickableTile::tileClicked, this, &GameBoard::onTileClicked);

                    item->setPos(x, y);
                    scene->addItem(item);
                }
            }


        }
    }



    QVBoxLayout *player1Units = new QVBoxLayout;
    for (int i = 0; i < 5; ++i) {
        QString unitName = "P1 Unit " + QString::number(i + 1);
        QPushButton *unitButton = new QPushButton(unitName, this);
        unitButton->setFixedSize(100, 60);
        player1Units->addWidget(unitButton);

        connect(unitButton, &QPushButton::clicked, this, [=]() {
            if (currentPlayer == Player1) {
                selectedUnitType = unitName;
                selectedUnitImagePath = unitImagePaths.value(unitName, "image/p1.jpg");
                isUnitSelected = true;
                currentState = PlacingUnit;
                highlightPlacementTiles();
                qDebug() << "Ready to place:" << selectedUnitType;
            }
        });
    }

    QVBoxLayout *player2Units = new QVBoxLayout;
    for (int i = 0; i < 5; ++i) {
        QString unitName = "P2 Unit " + QString::number(i + 1);
        QPushButton *unitButton = new QPushButton(unitName, this);
        unitButton->setFixedSize(100, 60);
        player2Units->addWidget(unitButton);

        connect(unitButton, &QPushButton::clicked, this, [=]() {
            if (currentPlayer == Player2) {
                selectedUnitType = unitName;
                selectedUnitImagePath = unitImagePaths.value(unitName, "image/p2.jpg");
                isUnitSelected = true;
                currentState = PlacingUnit;
                highlightPlacementTiles();
                qDebug() << "Ready to place:" << selectedUnitType;
            }
        });
    }

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(player1Units);
    mainLayout->addWidget(view);
    mainLayout->addLayout(player2Units);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    view->setAlignment(Qt::AlignCenter);

}

GameBoard::~GameBoard() {

}
