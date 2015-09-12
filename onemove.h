#ifndef ONEMOVE
#define ONEMOVE

#include <QMap>
#include "piecesmanager.h"

enum {
    PLAYER_ONE = 1,
    PLAYER_TWO = 2,
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

    typedef QMap <int, OneMove> Map;
};


#endif // ONEMOVE

