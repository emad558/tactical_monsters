#ifndef CLICKABLETILE_H
#define CLICKABLETILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

// ارث‌بری چندگانه از QObject و QGraphicsPixmapItem
class ClickableTile : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT  // حتماً باید باشه برای استفاده از سیگنال‌ها

public:
    int row, col;

    ClickableTile(const QPixmap &pixmap, int row, int col);

signals:
    void tileClicked(int row, int col);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CLICKABLETILE_H
