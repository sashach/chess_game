#include "basemove.h"
#include "chessboard.h"
#include <QPoint>

BaseMove::BaseMove()
{

}

void BaseMove::SelectMoveLine(ChessBoard & board, QPoint & pos, const int d_row, const int d_col, const int player)
{
    int col = pos.x() + d_col;
    int row = pos.y() + d_row;

    while (col >= 0 && row >= 0 && col < ChessBoard::MAX_ROWS && row < ChessBoard::MAX_ROWS) {
        if(board.IsFreeCell(row, col)) {
            board.SetSelectedCell(row, col, true);
        }
        else if(!board.IsMyPiece(row, col, player)) {
            board.SetSelectedCell(row, col, true);
            break;
        }
        else {
            break;
        }

        col += d_col;
        row += d_row;
    }
}

void BaseMove::SelectMoveOne(ChessBoard & board, QPoint & pos, const int d_row, const int d_col, const int player)
{
    int col = pos.x() + d_col;
    int row = pos.y() + d_row;

    if (col >= 0 && row >= 0 && col < ChessBoard::MAX_ROWS && row < ChessBoard::MAX_ROWS) {
        if(board.IsFreeCell(row, col)) {
            board.SetSelectedCell(row, col, true);
        }
        else if(!board.IsMyPiece(row, col, player)) {
            board.SetSelectedCell(row, col, true);
        }
    }
}
