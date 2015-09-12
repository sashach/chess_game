#include "chessboardform.h"
#include "piecesmanager.h"
#include "chessboardmodel.h"
#include "chessboard.h"
#include <QPainter>
#include <QDebug>

ChessBoardForm::ChessBoardForm(QQuickItem *parent)
    :
      QQuickPaintedItem(parent),
      BaseX(0),
      BaseY(0)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

void ChessBoardForm::paint(QPainter * painter)
{
    painter->fillRect(contentsBoundingRect(), Qt::transparent);

    BaseX = painter->viewport().width() / 2 - 200;
    BaseY = painter->viewport().height() - painter->viewport().y() - 100;

    QBrush black_brush(QColor(100, 100, 100), Qt::Dense3Pattern);
    QPen black_pen(QColor(100, 100, 100), Qt::SolidLine);
    QBrush white_brush(QColor(240, 240, 240), Qt::SolidPattern);

    for(int row = 0; row < 8; ++row) {
        int y = BaseY - row * CELL_WIDTH;
        for(int col = 0; col < 8; ++col) {
            QPen & pen = black_pen;
            QBrush & brush = ((row + col) % 2) ? white_brush : black_brush;

            int x = BaseX + col * CELL_WIDTH;

            painter->setPen(pen);
            painter->setBrush(brush);

            QRect cell(x, y, CELL_WIDTH, CELL_WIDTH);
            painter->drawRect(cell);
        }

        QPoint p(BaseX - 20, y + 30);
        painter->drawText(p, QString("%1").arg(row + 1));
    }

    for(int col = 0; col < 8; ++col) {
        QPoint p(BaseX + 20 + col * 50, BaseY + 70);
        QString str;
        switch (col) {
        case 0:
            str = "A";
            break;
        case 1:
            str = "B";
            break;
        case 2:
            str = "C";
            break;
        case 3:
            str = "D";
            break;
        case 4:
            str = "E";
            break;
        case 5:
            str = "F";
            break;
        case 6:
            str = "G";
            break;
        case 7:
            str = "H";
            break;
        default:
            break;
        }

        painter->drawText(p, str);
    }

    ChessBoardModel & model = ChessBoardModel::Instance();

    for(int row = 0; row < ChessBoard::MAX_ROWS; ++row) {
        for(int col = 0; col < ChessBoard::MAX_ROWS; ++col) {
            if(model.IsSelectedCell(row, col)) {
                painter->setBrush(QBrush(QColor(240, 240, 100), Qt::Dense2Pattern));
                painter->drawRect(GetCellLeftX(col) + 5, GetCellTopY(row) + 5, 40, 40);
            }

            QPoint p(GetCellLeftX(col) + 5, GetCellTopY(row) + 5);
            painter->drawImage(p, Pieces.GetImage(model.GetPieceForCell(row, col)));
        }
    }

    auto draw_captured = [this, painter](const int cap_x, QVector <PiecesManager::PiecesTypes> & v) {
        int cap_y = BaseY;
        for(auto it: v) {
            QPoint p(cap_x, cap_y);
            painter->drawImage(p, Pieces.GetImage(it));
            cap_y -= 40;
        }
    };

    draw_captured(BaseX - 70, model.GetCapturedWhite());
    draw_captured(BaseX + CELL_WIDTH * ChessBoard::MAX_ROWS + 30,
                  model.GetCapturedBlack());
}

int ChessBoardForm::GetCellLeftX(const int col)
{
     return BaseX + col * CELL_WIDTH;
}

int ChessBoardForm::GetCellTopY(const int row)
{
     return BaseY - row * CELL_WIDTH;
}

int ChessBoardForm::GetColForX(const int x)
{
    return round((x - BaseX) / CELL_WIDTH);
}

int ChessBoardForm::GetRowForY(const int y)
{
    if(BaseY > y)
        return 1 + round((BaseY - y) / CELL_WIDTH);
    else
        return 0;
}

void ChessBoardForm::mousePressEvent(QMouseEvent * event)
{
    ChessBoardModel::Instance().selectCell(GetRowForY(event->y()), GetColForX(event->x()));
    QQuickPaintedItem::mousePressEvent(event);
}
