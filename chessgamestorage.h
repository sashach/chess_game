#ifndef CHESSGAMESTORAGE_H
#define CHESSGAMESTORAGE_H

#include <QObject>

class ChessGameStorage: public QObject
{
    Q_OBJECT
public:
    ChessGameStorage();

    void SetFileName(const QString & name);

private:
    QString FileName;

signals:
    void recordIOMessage(const QString & str);

public slots:
    void saveGame();
    void loadGame();
};

#endif // CHESSGAMESTORAGE_H
