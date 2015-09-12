#ifndef QUEENMOVE_H
#define QUEENMOVE_H

#include "basemove.h"

class QueenMove : public BaseMove
{
public:
    QueenMove();
    virtual void SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player);
};

#endif // QUEENMOVE_H
