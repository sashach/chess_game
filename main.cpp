#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "chessboardform.h"
#include "chessboardmodel.h"
#include "chessgamestorage.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ChessBoardForm>("mymodule", 1, 0, "ChessBoard");

    QQmlApplicationEngine engine;

    ChessGameStorage storage;

    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("chessBoardModel", &ChessBoardModel::Instance());
    ctx->setContextProperty("chessGameStorage", &storage);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

