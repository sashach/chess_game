#ifndef CHESSBOARDMODEL_H
#define CHESSBOARDMODEL_H

#include <QObject>
#include "piecesmanager.h"
#include "onemove.h"
#include "chessboard.h"

class ChessBoardModel: public QObject
{
    Q_OBJECT
public:
    static ChessBoardModel & Instance();

    void Init();

    PiecesManager::PiecesTypes GetPieceForCell(const int row, const int col);
    bool IsSelectedCell(const int row, const int col);

    PiecesManager::PiecesVector & GetCapturedWhite();
    PiecesManager::PiecesVector & GetCapturedBlack();

    OneMove::Map & GetMoveHistory();

private:
    ChessBoardModel();
    void SelectPossibleMove();

    void ProcessMove(OneMove & move);
    void ProcessMoveBack(OneMove & move);
    void SwitchCurrentPlayer();
    void AddToCaptured(PiecesManager::PiecesTypes p);

    ChessBoard Board;
    OneMove CurrentMove;
    int CurrentPlayer, CurrentMoveNum;
    bool GameStarted;

    OneMove::Map MoveHistory;
    PiecesManager::PiecesVector CapturedBlack, CapturedWhite;

signals:
    void modelChanged();
    void currentPlayerChanged(const int id, const int move_num);
    void replayMoveChanged(const int move, const int size);

public slots:
    void selectCell(const int row, const int col);
    void startNewGame();
    void stopGame();
    void clearBoard();
    void prepareBoard();
    void prevStep();
    void nextStep();
};

#endif // CHESSBOARDMODEL_H
