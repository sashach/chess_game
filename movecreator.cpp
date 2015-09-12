#include "movecreator.h"
#include "kingmove.h"
#include "rookmove.h"
#include "queenmove.h"
#include "bishopmove.h"
#include "knightmove.h"
#include "pawnmove.h"

MoveCreator::MoveCreator()
{

}

BaseMove * MoveCreator::CreateMove(PiecesManager::PiecesTypes t)
{
    BaseMove *move = nullptr;

    switch (t) {
    case PiecesManager::PIECE_WHITE_KING:
    case PiecesManager::PIECE_BLACK_KING:
        move = new KingMove();
        break;
    case PiecesManager::PIECE_WHITE_QUEEN:
    case PiecesManager::PIECE_BLACK_QUEEN:
        move = new QueenMove();
        break;
    case PiecesManager::PIECE_WHITE_ROOK:
    case PiecesManager::PIECE_BLACK_ROOK:
        move = new RookMove();
        break;
    case PiecesManager::PIECE_WHITE_BISHOP:
    case PiecesManager::PIECE_BLACK_BISHOP:
        move = new BishopMove();
        break;
    case PiecesManager::PIECE_WHITE_KNIGHT:
    case PiecesManager::PIECE_BLACK_KNIGHT:
        move = new KnightMove();
        break;
    case PiecesManager::PIECE_WHITE_PAWN:
    case PiecesManager::PIECE_BLACK_PAWN:
        move = new PawnMove();
        break;
    default:
        break;
    }

    return move;
}

