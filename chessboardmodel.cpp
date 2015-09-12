#include "chessboardmodel.h"
#include "movecreator.h"
#include <QDebug>

ChessBoardModel::ChessBoardModel()
    :
      CurrentPlayer(0),
      CurrentMoveNum(0),
      GameStarted(false)
{
    Init();
}

ChessBoardModel & ChessBoardModel::Instance()
{
    static ChessBoardModel ChessBoardModelInstance;
    return ChessBoardModelInstance;
}

void ChessBoardModel::Init()
{
    Board.Prepare();
    MoveHistory.clear();
}

void ChessBoardModel::prepareBoard()
{
    Board.Prepare();
    CurrentMoveNum = 0;
}

void ChessBoardModel::startNewGame()
{
    Init();

    CurrentPlayer = PLAYER_ONE;
    CurrentMoveNum = 1;
    GameStarted = true;

    CapturedWhite.clear();
    CapturedBlack.clear();

    emit currentPlayerChanged(CurrentPlayer, CurrentMoveNum);
}

void ChessBoardModel::stopGame()
{
    GameStarted = false;
}

PiecesManager::PiecesTypes ChessBoardModel::GetPieceForCell(const int row, const int col)
{
   return Board.GetPiece(row, col);
}

bool ChessBoardModel::IsSelectedCell(const int row, const int col)
{
    return Board.IsSelectedCell(row, col);
}


void ChessBoardModel::selectCell(const int row, const int col)
{
    if(!GameStarted)
        return;

    if( Board.IsMyPiece(row, col, CurrentPlayer) ) {
        Board.ClearSelection();

        Board.SetSelectedCell(row, col, true);

        CurrentMove.started = true;
        CurrentMove.player = CurrentPlayer;
        CurrentMove.piece_type = Board.GetPiece(row,col);
        CurrentMove.position_from = QPoint(col, row);
        CurrentMove.player = CurrentPlayer;

        SelectPossibleMove();
    }
    else if (CurrentMove.started && Board.IsSelectedCell(row, col)) {
        Board.SetSelectedCell(row, col, true);
        CurrentMove.position_to = QPoint(col, row);

        ProcessMove(CurrentMove);

        CurrentMove.num_move = CurrentMoveNum;
        MoveHistory.insert(CurrentMoveNum, CurrentMove);
        ++CurrentMoveNum;

        CurrentMove.Reset();
        Board.ClearSelection();
        SwitchCurrentPlayer();
    }
    else {
        Board.ClearSelection();
        CurrentMove.Reset();
    }

    emit modelChanged();
}

void ChessBoardModel::clearBoard()
{
    Board.Clear();
    CapturedBlack.clear();
    CapturedWhite.clear();
}

void ChessBoardModel::SelectPossibleMove()
{
    MoveCreator creator;
    BaseMove * move = creator.CreateMove(CurrentMove.piece_type);
    if(move) {
        move->SelectPossibleMove(Board, CurrentMove.position_from, CurrentPlayer);
        delete move;
    }
    else {
        Board.ClearSelection();
    }
}

void ChessBoardModel::AddToCaptured(PiecesManager::PiecesTypes p)
{
    switch( p ) {
    case PiecesManager::PIECE_WHITE_KING:
    case PiecesManager::PIECE_WHITE_QUEEN:
    case PiecesManager::PIECE_WHITE_ROOK:
    case PiecesManager::PIECE_WHITE_BISHOP:
    case PiecesManager::PIECE_WHITE_KNIGHT:
    case PiecesManager::PIECE_WHITE_PAWN:
    {
        CapturedWhite.push_back(p);
        qSort(CapturedWhite);
    }
        break;

    case PiecesManager::PIECE_BLACK_KING:
    case PiecesManager::PIECE_BLACK_QUEEN:
    case PiecesManager::PIECE_BLACK_ROOK:
    case PiecesManager::PIECE_BLACK_BISHOP:
    case PiecesManager::PIECE_BLACK_KNIGHT:
    case PiecesManager::PIECE_BLACK_PAWN:
    {
        CapturedBlack.push_back(p);
        qSort(CapturedBlack);
    }
        break;

    default:
    {
    }
        break;
    }

}

void ChessBoardModel::ProcessMove(OneMove & move)
{
    if(Board.GetPiece(move.position_to)) {
        CurrentMove.captured_peace = Board.GetPiece(move.position_to);
        AddToCaptured(CurrentMove.captured_peace);
    }

    Board.SetPiece(move.position_to, move.piece_type);
    Board.SetPiece(move.position_from, PiecesManager::PIECE_NONE);
}

void ChessBoardModel::ProcessMoveBack(OneMove & move)
{
    Board.SetPiece(move.position_to, PiecesManager::PIECE_NONE);
    if(move.captured_peace) {
        Board.SetPiece(move.position_to, move.captured_peace);

        switch( CurrentMove.captured_peace ) {
        case PiecesManager::PIECE_WHITE_KING:
        case PiecesManager::PIECE_WHITE_QUEEN:
        case PiecesManager::PIECE_WHITE_ROOK:
        case PiecesManager::PIECE_WHITE_BISHOP:
        case PiecesManager::PIECE_WHITE_KNIGHT:
        case PiecesManager::PIECE_WHITE_PAWN:
        {
            for(auto it = CapturedWhite.begin(); it != CapturedWhite.end(); ++it){
                if (*it == move.captured_peace) {
                    it = CapturedWhite.erase(it);
                    break;
                }
            }
        }
            break;

        case PiecesManager::PIECE_BLACK_KING:
        case PiecesManager::PIECE_BLACK_QUEEN:
        case PiecesManager::PIECE_BLACK_ROOK:
        case PiecesManager::PIECE_BLACK_BISHOP:
        case PiecesManager::PIECE_BLACK_KNIGHT:
        case PiecesManager::PIECE_BLACK_PAWN:
        {
            for(auto it = CapturedBlack.begin(); it != CapturedBlack.end(); ++it){
                if (*it == move.captured_peace) {
                    CapturedBlack.erase(it);
                    break;
                }
            }
        }
            break;

        default:
        {
        }
            break;
        }
    }

    Board.SetPiece(move.position_from, move.piece_type);
}

void ChessBoardModel::SwitchCurrentPlayer()
{
    CurrentPlayer = (CurrentPlayer == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
    emit currentPlayerChanged(CurrentPlayer, CurrentMoveNum);
}

void ChessBoardModel::prevStep()
{
    CurrentMove = MoveHistory.value(CurrentMoveNum);
    ProcessMoveBack(CurrentMove);

    if(CurrentMoveNum < 1) {
        Board.Prepare();
        return;
    }
    else {
        --CurrentMoveNum;
    }

    emit replayMoveChanged(CurrentMoveNum, MoveHistory.size());
    emit modelChanged();
}

void ChessBoardModel::nextStep()
{
    if(CurrentMoveNum < MoveHistory.size()) {
        ++CurrentMoveNum;

        CurrentMove = MoveHistory.value(CurrentMoveNum);
        ProcessMove(CurrentMove);

        emit replayMoveChanged(CurrentMoveNum, MoveHistory.size());
        emit modelChanged();
    }
}

PiecesManager::PiecesVector & ChessBoardModel::GetCapturedWhite()
{
    return CapturedWhite;
}

PiecesManager::PiecesVector & ChessBoardModel::GetCapturedBlack()
{
    return CapturedBlack;
}

OneMove::Map & ChessBoardModel::GetMoveHistory()
{
    return MoveHistory;
}
