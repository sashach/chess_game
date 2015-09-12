#ifndef PIECESMANAGER_H
#define PIECESMANAGER_H

#include <QObject>
#include <QImage>
#include <QMap>

class PiecesManager: public QObject
{
    Q_OBJECT
public:
    PiecesManager();
    ~PiecesManager();

    enum PiecesTypes {
        PIECE_NONE = 0,
        PIECE_WHITE_KING,
        PIECE_WHITE_QUEEN,
        PIECE_WHITE_ROOK,
        PIECE_WHITE_BISHOP,
        PIECE_WHITE_KNIGHT,
        PIECE_WHITE_PAWN,
        PIECE_BLACK_KING,
        PIECE_BLACK_QUEEN,
        PIECE_BLACK_ROOK,
        PIECE_BLACK_BISHOP,
        PIECE_BLACK_KNIGHT,
        PIECE_BLACK_PAWN,
        PIECE_LAST
    };
    typedef QVector <PiecesManager::PiecesTypes> PiecesVector;

    void Init();
    QImage & GetImage(const PiecesTypes t);

private:
    QMap <PiecesTypes, QImage> PiecesImages;

signals:

public slots:
};



#endif // PIECESMANAGER_H
