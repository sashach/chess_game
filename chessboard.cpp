#include "chessboard.h"
#include "onemove.h"

ChessBoard::ChessBoard()
{

}

void ChessBoard::Prepare()
{
    memset(Board, 0, sizeof(OneCell) * MAX_ROWS * MAX_ROWS);
    Board[0][0].piece_type = PiecesManager::PIECE_WHITE_ROOK;
    Board[0][1].piece_type = PiecesManager::PIECE_WHITE_KNIGHT;
    Board[0][2].piece_type = PiecesManager::PIECE_WHITE_BISHOP;
    Board[0][3].piece_type = PiecesManager::PIECE_WHITE_KING;
    Board[0][4].piece_type = PiecesManager::PIECE_WHITE_QUEEN;
    Board[0][5].piece_type = PiecesManager::PIECE_WHITE_BISHOP;
    Board[0][6].piece_type = PiecesManager::PIECE_WHITE_KNIGHT;
    Board[0][7].piece_type = PiecesManager::PIECE_WHITE_ROOK;

    Board[7][0].piece_type = PiecesManager::PIECE_BLACK_ROOK;
    Board[7][1].piece_type = PiecesManager::PIECE_BLACK_KNIGHT;
    Board[7][2].piece_type = PiecesManager::PIECE_BLACK_BISHOP;
    Board[7][3].piece_type = PiecesManager::PIECE_BLACK_QUEEN;
    Board[7][4].piece_type = PiecesManager::PIECE_BLACK_KING;
    Board[7][5].piece_type = PiecesManager::PIECE_BLACK_BISHOP;
    Board[7][6].piece_type = PiecesManager::PIECE_BLACK_KNIGHT;
    Board[7][7].piece_type = PiecesManager::PIECE_BLACK_ROOK;

    for(int i = 0; i < 8; ++i) {
        Board[1][i].piece_type = PiecesManager::PIECE_WHITE_PAWN;
        Board[6][i].piece_type = PiecesManager::PIECE_BLACK_PAWN;
    }

    ClearSelection();
}

void ChessBoard::ClearSelection()
{
    for(int row = 0; row < MAX_ROWS; ++row) {
        for(int col = 0; col < MAX_ROWS; ++col) {
            Board[row][col].selected = false;
        }
    }
}

PiecesManager::PiecesTypes ChessBoard::GetPiece(const int row, const int col)
{
    if(row >= 0 && col >= 0 && row < MAX_ROWS && col < MAX_ROWS)
        return Board[row][col].piece_type;
    else
        return PiecesManager::PIECE_NONE;
}

PiecesManager::PiecesTypes ChessBoard::GetPiece(const QPoint & pos)
{
    return GetPiece(pos.y(), pos.x());
}

void ChessBoard::SetPiece(const int row, const int col, const PiecesManager::PiecesTypes piece)
{
    if(row >= 0 && col >= 0 && row < MAX_ROWS && col < MAX_ROWS)
        Board[row][col].piece_type = piece;
}

void ChessBoard::SetPiece(const QPoint & pos, const PiecesManager::PiecesTypes piece)
{
    SetPiece(pos.y(), pos.x(), piece);
}

bool ChessBoard::IsSelectedCell(const int row, const int col)
{
    if(row >= 0 && col >= 0 && row < MAX_ROWS && col < MAX_ROWS)
        return Board[row][col].selected;
    else
        return false;
}

void ChessBoard::SetSelectedCell(const int row, const int col, const bool selected)
{
    if(row >= 0 && col >= 0 && row < MAX_ROWS && col < MAX_ROWS)
        Board[row][col].selected = selected;
}

void ChessBoard::Clear()
{
    for(int row = 0; row < MAX_ROWS; ++row) {
        for(int col = 0; col < MAX_ROWS; ++col) {
            Board[row][col].piece_type = PiecesManager::PIECE_NONE;
            Board[row][col].selected = false;
        }
    }
}

bool ChessBoard::IsFreeCell(const int row, const int col)
{
    return (Board[row][col].piece_type == PiecesManager::PIECE_NONE);
}

bool ChessBoard::IsMyPiece(const int row, const int col, const int player)
{
    bool res = false;

    switch( GetPiece(row, col) ) {
    case PiecesManager::PIECE_WHITE_KING:
    case PiecesManager::PIECE_WHITE_QUEEN:
    case PiecesManager::PIECE_WHITE_ROOK:
    case PiecesManager::PIECE_WHITE_BISHOP:
    case PiecesManager::PIECE_WHITE_KNIGHT:
    case PiecesManager::PIECE_WHITE_PAWN:
    {
        res = (player == PLAYER_ONE);
    }
        break;

    case PiecesManager::PIECE_BLACK_KING:
    case PiecesManager::PIECE_BLACK_QUEEN:
    case PiecesManager::PIECE_BLACK_ROOK:
    case PiecesManager::PIECE_BLACK_BISHOP:
    case PiecesManager::PIECE_BLACK_KNIGHT:
    case PiecesManager::PIECE_BLACK_PAWN:
    {
        res = (player == PLAYER_TWO);
    }
        break;

    default:
    {
    }
        break;
    }

    return res;
}

bool ChessBoard::IsNotFreeAndNotMine(const int row, const int col, const int player)
{
    if(GetPiece(row, col))
        return !IsMyPiece(row, col, player);
    else
        return false;
}
