#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "chessboardform.h"
#include "piecesmanager.h"
#include "chessboardmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ChessBoardForm>("mymodule", 1, 0, "ChessBoard");

    QQmlApplicationEngine engine;

    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("chessBoardModel", &ChessBoardModel::Instance());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

