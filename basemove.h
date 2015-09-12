#ifndef BASEMOVE_H
#define BASEMOVE_H

class ChessBoard;
class QPoint;

class BaseMove
{
public:
    BaseMove();
    virtual ~BaseMove() {}
    virtual void SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player) = 0;

protected:
    void SelectMoveLine(ChessBoard & board, QPoint & pos, const int d_row, const int d_col, const int player);
    void SelectMoveOne(ChessBoard & board, QPoint & pos, const int d_row, const int d_col, const int player);
};

#endif // BASEMOVE_H
