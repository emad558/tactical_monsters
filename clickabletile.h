#ifndef CLICKABLETILE_H
#define CLICKABLETILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class ClickableTile : public QGraphicsPixmapItem {
public:
    int row, col;

    ClickableTile(const QPixmap &pixmap, int row, int col);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CLICKABLETILE_H
