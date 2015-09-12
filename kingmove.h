#ifndef KINGMOVE_H
#define KINGMOVE_H

#include "basemove.h"

class KingMove : public BaseMove
{
public:
    KingMove();
    virtual void SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player);
};

#endif // KINGMOVE_H
