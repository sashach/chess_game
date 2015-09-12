#include "knightmove.h"

KnightMove::KnightMove()
{

}

void KnightMove::SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player)
{
    SelectMoveOne(board, pos, 2, 1, player);
    SelectMoveOne(board, pos, 2, -1, player);
    SelectMoveOne(board, pos, -2, 1, player);
    SelectMoveOne(board, pos, -2, -1, player);
    SelectMoveOne(board, pos, 1, 2, player);
    SelectMoveOne(board, pos, 1, -2, player);
    SelectMoveOne(board, pos, -1, 2, player);
    SelectMoveOne(board, pos, -1, -2, player);
}
