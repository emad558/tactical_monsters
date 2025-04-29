#include "gameboard.h"
#include <QLabel>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <fstream>
#include "clickabletile.h""

GameBoard::GameBoard(QWidget *parent)
    : QMainWindow(parent) {
    this->setWindowTitle("Main Game Board");

    this->resize(1180, 820);

    QGraphicsScene *scene = new QGraphicsScene(this);
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
    char data[11][11];

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
                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data2[row][col/2] == '2'){
                    QPixmap scaled = imgP2.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data2[row][col/2] == '#'){
                    QPixmap scaled = imgRock.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data2[row][col/2] == '~'){
                    QPixmap scaled = imgWater.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data2[row][col/2] == ' '){
                    QPixmap scaled = imgEmpty.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    item->setPos(x, y);
                    scene->addItem(item);
                }
                // }
            }else{
                if(data1[row][col/2] == '1'){
                    QPixmap scaled = imgP1.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data1[row][col/2] == '2'){
                    QPixmap scaled = imgP2.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data1[row][col/2] == '#'){
                    QPixmap scaled = imgRock.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data1[row][col/2] == '~'){
                    QPixmap scaled = imgWater.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    item->setPos(x, y);
                    scene->addItem(item);
                }else if(data1[row][col/2] == ' '){
                    QPixmap scaled = imgEmpty.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ClickableTile *item = new ClickableTile(scaled,row,col);
                    item->setPos(x, y);
                    scene->addItem(item);
                }
            }


        }
    }

    QVBoxLayout *player1Units = new QVBoxLayout;
    for (int i = 0; i < 5; ++i) {
        QPushButton *unitButton = new QPushButton("P1 Unit " + QString::number(i + 1));
        unitButton->setFixedSize(100, 60);
        player1Units->addWidget(unitButton);
    }

    QVBoxLayout *player2Units = new QVBoxLayout;
    for (int i = 0; i < 5; ++i) {
        QPushButton *unitButton = new QPushButton("P2 Unit " + QString::number(i + 1));
        unitButton->setFixedSize(100, 60);
        player2Units->addWidget(unitButton);
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
