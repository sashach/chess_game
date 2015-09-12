#include "kingmove.h"

KingMove::KingMove()
{

}

void KingMove::SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player)
{
    SelectMoveOne(board, pos, 1, 0, player);
    SelectMoveOne(board, pos, -1, 0, player);
    SelectMoveOne(board, pos, 0, 1, player);
    SelectMoveOne(board, pos, 0, -1, player);
    SelectMoveOne(board, pos, 1, 1, player);
    SelectMoveOne(board, pos, 1, -1, player);
    SelectMoveOne(board, pos, -1, 1, player);
    SelectMoveOne(board, pos, -1, -1, player);
}
