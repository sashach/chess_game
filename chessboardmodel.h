#ifndef CHESSBOARDMODEL_H
#define CHESSBOARDMODEL_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "piecesmanager.h"

class ChessBoardModel: public QObject
{
    Q_OBJECT
public:
    static ChessBoardModel & Instance();

    void Init();

    struct OneCell {
        PiecesManager::PiecesTypes piece_type;
        bool selected;
    };

    PiecesManager::PiecesTypes GetPieceForCell(const int row, const int col);
    bool IsSelectedCell(const int row, const int col);

    enum {
        PLAYER_ONE = 1,
        PLAYER_TWO = 2,
        MAX_ROWS = 8,
    };

    struct OneMove {
        bool started;
        int num_move, player;
        PiecesManager::PiecesTypes piece_type, captured_peace;
        QPoint position_from, position_to;

        OneMove()
            :
              started(false),
              num_move(0),
              player(0),
              piece_type(PiecesManager::PIECE_NONE),
              captured_peace(PiecesManager::PIECE_NONE)
        {
        }

        void Reset()
        {
            started = false;
            num_move = 0,
            player = 0;
            piece_type = PiecesManager::PIECE_NONE;
            captured_peace = PiecesManager::PIECE_NONE;
            position_from = QPoint(0,0);
            position_to = QPoint(0,0);
        }

        OneMove (const OneMove & m)
            :
              started(m.started),
              num_move(m.num_move),
              player(m.player),
              piece_type(m.piece_type),
              captured_peace(m.captured_peace),
              position_from(m.position_from),
              position_to(m.position_to)
        {
        }

        const OneMove & operator = (const OneMove & m)
        {
            if (this != &m) {
                started = m.started;
                num_move = m.num_move;
                player = m.player;
                piece_type = m.piece_type;
                captured_peace = m.captured_peace;
                position_from = m.position_from;
                position_to = m.position_to;
            }
            return *this;
        }
    };

    QVector <PiecesManager::PiecesTypes> & GetCapturedWhite();
    QVector <PiecesManager::PiecesTypes> & GetCapturedBlack();

private:
    ChessBoardModel();
    void ClearSelection();
    void SelectPossibleMove();

    bool IsMyPiece(PiecesManager::PiecesTypes t);
    void ProcessMove(OneMove & move);
    void ProcessMoveBack(OneMove & move);
    void SwitchCurrentPlayer();
    bool IsFreeCell(const int row, const int col);
    void PrepareBoard();

    OneCell ChessBoard[MAX_ROWS][MAX_ROWS];
    OneMove CurrentMove;
    int CurrentPlayer, CurrentMoveNum;
    QString FileName;

    QMap <int, OneMove> MoveHistory;
    QVector <PiecesManager::PiecesTypes> CapturedBlack, CapturedWhite;

signals:
    void modelChanged();
    void currentPlayerChanged(const int id, const int move_num);
    void recordIOMessage(const QString & str);
    void replayMoveChanged(const int move, const int size);

public slots:
    void selectCell(const int row, const int col);
    void startNewGame();
    void clearBoard();
    void saveGame();
    void loadGame();
    void prevStep();
    void nextStep();
    void setFileName(const QString & str);
};

#endif // CHESSBOARDMODEL_H
