#ifndef CLICKABLETILE_H
#define CLICKABLETILE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class ClickableTile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ClickableTile(const QPixmap &pixmap, int row, int col, QGraphicsItem *parent = nullptr);

    int getRow() const { return row; }
    int getCol() const { return col; }
    void setRow(int newRow) { row = newRow; }
    void setCol(int newCol) { col = newCol; }
    bool isHighlight() const { return m_isHighlight; }
    void setIsHighlight(bool highlight) { m_isHighlight = highlight; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void tileClicked(int row, int col);

private:
    int row;
    int col;
    bool m_isHighlight = false;
};

#endif // CLICKABLETILE_H
