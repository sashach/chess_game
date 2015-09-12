#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "basemove.h"

class PawnMove : public BaseMove
{
public:
    PawnMove();
    virtual void SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player);
};

#endif // PAWNMOVE_H
