#include "piecesmanager.h"

PiecesManager::PiecesManager()
{
    Init();
}

PiecesManager::~PiecesManager()
{

}

PiecesManager & PiecesManager::Instance()
{
    static PiecesManager PiecesManagerInstance;
    return PiecesManagerInstance;
}

void PiecesManager::Init()
{
    PiecesImages.clear();

    for(int i = 0; i < PIECE_LAST; ++i) {
        QImage img;

        switch (i) {
        case PIECE_WHITE_KING:
            img.load(QString(":/pieces/king_white.png"));
            break;
        case PIECE_WHITE_QUEEN:
            img.load(QString(":/pieces/queen_white.png"));
            break;
        case PIECE_WHITE_ROOK:
            img.load(QString(":/pieces/rook_white.png"));
            break;
        case PIECE_WHITE_BISHOP:
            img.load(QString(":/pieces/bishop_white.png"));
            break;
        case PIECE_WHITE_KNIGHT:
            img.load(QString(":/pieces/knight_white.png"));
            break;
        case PIECE_WHITE_PAWN:
            img.load(QString(":/pieces/pawn_white.png"));
            break;
        case PIECE_BLACK_KING:
            img.load(QString(":/pieces/king_black.png"));
            break;
        case PIECE_BLACK_QUEEN:
            img.load(QString(":/pieces/queen_black.png"));
            break;
        case PIECE_BLACK_ROOK:
            img.load(QString(":/pieces/rook_black.png"));
            break;
        case PIECE_BLACK_BISHOP:
            img.load(QString(":/pieces/bishop_black.png"));
            break;
        case PIECE_BLACK_KNIGHT:
            img.load(QString(":/pieces/knight_black.png"));
            break;
        case PIECE_BLACK_PAWN:
            img.load(QString(":/pieces/pawn_black.png"));
            break;
        default:
            break;
        }

        PiecesImages.insert(static_cast <PiecesTypes> (i), img);
    }
}

QImage & PiecesManager::GetImage(const PiecesTypes t)
{
     return PiecesImages[t];
}
