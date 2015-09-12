#ifndef KNIGHTMOVE_H
#define KNIGHTMOVE_H

#include "basemove.h"

class KnightMove : public BaseMove
{
public:
    KnightMove();
    virtual void SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player);
};

#endif // KNIGHTMOVE_H
