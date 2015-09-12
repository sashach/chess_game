TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    chessboardform.cpp \
    piecesmanager.cpp \
    chessboardmodel.cpp \
    chessgamestorage.cpp \
    basemove.cpp \
    chessboard.cpp \
    kingmove.cpp \
    queenmove.cpp \
    rookmove.cpp \
    bishopmove.cpp \
    knightmove.cpp \
    pawnmove.cpp \
    movecreator.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    chessboardform.h \
    piecesmanager.h \
    chessboardmodel.h \
    chessgamestorage.h \
    onemove.h \
    basemove.h \
    chessboard.h \
    kingmove.h \
    queenmove.h \
    rookmove.h \
    bishopmove.h \
    knightmove.h \
    pawnmove.h \
    movecreator.h

