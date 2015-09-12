#ifndef ROOKMOVE_H
#define ROOKMOVE_H

#include "basemove.h"

class RookMove : public BaseMove
{
public:
    RookMove();
    virtual void SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player);

};

#endif // ROOKMOVE_H
