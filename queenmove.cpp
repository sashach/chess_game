#include "queenmove.h"

QueenMove::QueenMove()
{

}

void QueenMove::SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player)
{
    SelectMoveLine(board, pos, 1, 0, player);
    SelectMoveLine(board, pos, -1, 0, player);
    SelectMoveLine(board, pos, 0, 1, player);
    SelectMoveLine(board, pos, 0, -1, player);
    SelectMoveLine(board, pos, 1, 1, player);
    SelectMoveLine(board, pos, 1, -1, player);
    SelectMoveLine(board, pos, -1, 1, player);
    SelectMoveLine(board, pos, -1, -1, player);
}
