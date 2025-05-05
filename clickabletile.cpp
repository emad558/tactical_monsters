#include "clickabletile.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

ClickableTile::ClickableTile(const QPixmap &pixmap, int row, int col, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(pixmap, parent), row(row), col(col)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

void ClickableTile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit tileClicked(row, col);
    }
    QGraphicsPixmapItem::mousePressEvent(event);
}
