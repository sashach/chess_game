#include "chessgamestorage.h"
#include "chessboardmodel.h"
#include <QFile>

ChessGameStorage::ChessGameStorage()
    :
      FileName("saved_game")
{
}

void ChessGameStorage::SetFileName(const QString & name)
{
    FileName = name;
}

void ChessGameStorage::saveGame()
{
    // Used saving of data structures in a file for avoiding extra dependencies
    // I'd better use the google::protobuf serialisation

    QFile file(FileName);

    try {
        file.open(QFile::WriteOnly);
        for(auto it : ChessBoardModel::Instance().GetMoveHistory()) {
            file.write(reinterpret_cast <char *> (&it), sizeof(OneMove));
        }
        file.close();

        emit recordIOMessage(QString("File was saved."));
    }
    catch (...) {
        emit recordIOMessage(QString("Error in saving file."));
    }
}

void ChessGameStorage::loadGame()
{
    QFile file(FileName);
    if(!file.exists()) {
        emit recordIOMessage(QString("File was no found"));
        return;
    }

    try {
        ChessBoardModel & model = ChessBoardModel::Instance();

        file.open(QFile::ReadOnly);
        while (!file.atEnd()) {
            OneMove m;
            file.read(reinterpret_cast <char *> (&m), sizeof(OneMove));
            model.GetMoveHistory().insert(m.num_move, m);
        }
        file.close();

        if (model.GetMoveHistory().empty())
            emit recordIOMessage(QString("Record file is empty or is not exists"));
        else
            emit recordIOMessage(QString("Record Prapared. Total %1 moves").arg(model.GetMoveHistory().size()));
    }
    catch (...) {
        emit recordIOMessage(QString("Error in opening file"));
    }
}

