#include "bishopmove.h"

BishopMove::BishopMove()
{

}

void BishopMove::SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player)
{
    SelectMoveLine(board, pos, 1, 1, player);
    SelectMoveLine(board, pos, 1, -1, player);
    SelectMoveLine(board, pos, -1, 1, player);
    SelectMoveLine(board, pos, -1, -1, player);
}
