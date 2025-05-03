#include "clickabletile.h"
#include <QDebug>

ClickableTile::ClickableTile(const QPixmap &pixmap, int row, int col)
    : QGraphicsPixmapItem(pixmap), row(row), col(col) {
    setAcceptedMouseButtons(Qt::LeftButton);
}

void ClickableTile::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Tile clicked at: (" << row << "," << col << ")";
    emit tileClicked(row, col);

    // setPixmap(QPixmap(":/images/selected_tile.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QGraphicsPixmapItem::mousePressEvent(event);
}
