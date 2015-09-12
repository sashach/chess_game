#ifndef BISHOPMOVE_H
#define BISHOPMOVE_H

#include "basemove.h"

class BishopMove : public BaseMove
{
public:
    BishopMove();
    virtual void SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player);
};

#endif // BISHOPMOVE_H
