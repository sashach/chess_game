#include "pawnmove.h"
#include "onemove.h"
#include "chessboard.h"

PawnMove::PawnMove()
{

}

void PawnMove::SelectPossibleMove(ChessBoard & board, QPoint & pos, const int player)
{
    auto get_end_y = [player, pos, board] (const int step) -> int {
        int k = (player == PLAYER_ONE) ? 1 : -1;
        int end_y = pos.y() + k * step;

        if(end_y < 0) end_y = 0;
        if(end_y >= ChessBoard::MAX_ROWS) end_y = ChessBoard::MAX_ROWS - 1;

        return end_y;
    };

    int col = pos.x();
    int row = pos.y();

    int row1 = get_end_y(1);

    if(board.IsFreeCell(row1, col))
        board.SetSelectedCell(row1, col, true);

    int capture_col = col - 1;
    if( capture_col >= 0 ) {
        if(board.IsNotFreeAndNotMine(row1, capture_col, player))
            board.SetSelectedCell(row1, capture_col, true);
    }
    capture_col = col + 1;
    if( capture_col < ChessBoard::MAX_ROWS ) {
        if(board.IsNotFreeAndNotMine(row1, capture_col, player))
            board.SetSelectedCell(row1, capture_col, true);
    }

    int row2 = get_end_y(2);
    if(board.IsFreeCell(row2, col)) {
        if(board.GetPiece(row, col) == PiecesManager::PIECE_WHITE_PAWN) {
            if( row == 1 ) {
                board.SetSelectedCell(row2, col, true);
            }
        }
        else if( row == 6 ) {
            board.SetSelectedCell(row2, col, true);
        }
    }
}
