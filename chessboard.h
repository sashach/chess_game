#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "piecesmanager.h"

class QPoint;

class ChessBoard
{
public:
    ChessBoard();

    enum {
        MAX_ROWS = 8,
    };

    void Prepare();
    void ClearSelection();

    PiecesManager::PiecesTypes GetPiece(const int row, const int col);
    PiecesManager::PiecesTypes GetPiece(const QPoint & pos);

    void SetPiece(const int row, const int col, const PiecesManager::PiecesTypes piece);
    void SetPiece(const QPoint & pos, const PiecesManager::PiecesTypes piece);

    bool IsSelectedCell(const int row, const int col);
    void SetSelectedCell(const int row, const int col, const bool selected);
    void Clear();

    bool IsFreeCell(const int row, const int col);

    bool IsMyPiece(const int row, const int col, const int player);
    bool IsNotFreeAndNotMine(const int row, const int col, const int player);

private:

    struct OneCell {
        PiecesManager::PiecesTypes piece_type;
        bool selected;
    };

    OneCell Board[MAX_ROWS][MAX_ROWS];

signals:

public slots:
};


#endif // CHESSBOARD_H
