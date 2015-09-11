#ifndef CHESSBOARDFORM_H
#define CHESSBOARDFORM_H

#include <QQuickPaintedItem>

class ChessBoardForm : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ChessBoardForm(QQuickItem * parent = 0);

    void paint(QPainter * painter);
    void mousePressEvent(QMouseEvent * event);

private:
    int GetCellLeftX(const int col);
    int GetCellTopY(const int row);

    int GetColForX(const int x);
    int GetRowForY(const int y);

    enum {
        CELL_WIDTH = 50,
    };

    int BaseX, BaseY;

signals:

public slots:
};

#endif // CHESSBOARDFORM_H
