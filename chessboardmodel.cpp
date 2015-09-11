#include "chessboardmodel.h"
#include <QDebug>
#include <QFile>

ChessBoardModel::ChessBoardModel()
{
    FileName = "saved_game";
    Init();
}

ChessBoardModel & ChessBoardModel::Instance()
{
    static ChessBoardModel ChessBoardModelInstance;
    return ChessBoardModelInstance;
}

void ChessBoardModel::Init()
{
    CurrentPlayer = 0;
    CurrentMoveNum = 0;

    PrepareBoard();

    MoveHistory.clear();
}

void ChessBoardModel::PrepareBoard()
{
    memset(ChessBoard, 0, sizeof(OneCell) * MAX_ROWS * MAX_ROWS);
    ChessBoard[0][0].piece_type = PiecesManager::PIECE_WHITE_ROOK;
    ChessBoard[0][1].piece_type = PiecesManager::PIECE_WHITE_KNIGHT;
    ChessBoard[0][2].piece_type = PiecesManager::PIECE_WHITE_BISHOP;
    ChessBoard[0][3].piece_type = PiecesManager::PIECE_WHITE_KING;
    ChessBoard[0][4].piece_type = PiecesManager::PIECE_WHITE_QUEEN;
    ChessBoard[0][5].piece_type = PiecesManager::PIECE_WHITE_BISHOP;
    ChessBoard[0][6].piece_type = PiecesManager::PIECE_WHITE_KNIGHT;
    ChessBoard[0][7].piece_type = PiecesManager::PIECE_WHITE_ROOK;

    ChessBoard[7][0].piece_type = PiecesManager::PIECE_BLACK_ROOK;
    ChessBoard[7][1].piece_type = PiecesManager::PIECE_BLACK_KNIGHT;
    ChessBoard[7][2].piece_type = PiecesManager::PIECE_BLACK_BISHOP;
    ChessBoard[7][3].piece_type = PiecesManager::PIECE_BLACK_QUEEN;
    ChessBoard[7][4].piece_type = PiecesManager::PIECE_BLACK_KING;
    ChessBoard[7][5].piece_type = PiecesManager::PIECE_BLACK_BISHOP;
    ChessBoard[7][6].piece_type = PiecesManager::PIECE_BLACK_KNIGHT;
    ChessBoard[7][7].piece_type = PiecesManager::PIECE_BLACK_ROOK;

    for(int i = 0; i < 8; ++i) {
        ChessBoard[1][i].piece_type = PiecesManager::PIECE_WHITE_PAWN;
        ChessBoard[6][i].piece_type = PiecesManager::PIECE_BLACK_PAWN;
    }

    ClearSelection();
}

void ChessBoardModel::startNewGame()
{
    Init();

    CurrentPlayer = PLAYER_ONE;
    CurrentMoveNum = 1;

    CapturedWhite.clear();
    CapturedBlack.clear();

    emit currentPlayerChanged(CurrentPlayer, CurrentMoveNum);
}

PiecesManager::PiecesTypes ChessBoardModel::GetPieceForCell(const int row, const int col)
{
   if (row < 0 || col < 0 || row >= MAX_ROWS || col >= MAX_ROWS)
       return PiecesManager::PIECE_NONE;

   return ChessBoard[row][col].piece_type;
}

bool ChessBoardModel::IsSelectedCell(const int row, const int col)
{
   if (row < 0 || col < 0 || row >= MAX_ROWS || col >= MAX_ROWS)
       return false;

   return ChessBoard[row][col].selected;
}

bool ChessBoardModel::IsMyPiece(PiecesManager::PiecesTypes t)
{
    bool res = false;

    switch( t ) {
    case PiecesManager::PIECE_WHITE_KING:
    case PiecesManager::PIECE_WHITE_QUEEN:
    case PiecesManager::PIECE_WHITE_ROOK:
    case PiecesManager::PIECE_WHITE_BISHOP:
    case PiecesManager::PIECE_WHITE_KNIGHT:
    case PiecesManager::PIECE_WHITE_PAWN:
    {
        res = (CurrentPlayer == PLAYER_ONE);
    }
        break;

    case PiecesManager::PIECE_BLACK_KING:
    case PiecesManager::PIECE_BLACK_QUEEN:
    case PiecesManager::PIECE_BLACK_ROOK:
    case PiecesManager::PIECE_BLACK_BISHOP:
    case PiecesManager::PIECE_BLACK_KNIGHT:
    case PiecesManager::PIECE_BLACK_PAWN:
    {
        res = (CurrentPlayer == PLAYER_TWO);
    }
        break;

    default:
    {
    }
        break;
    }

    return res;
}

void ChessBoardModel::selectCell(const int row, const int col)
{
    PiecesManager::PiecesTypes current_piece = ChessBoard[row][col].piece_type;
    if( !IsFreeCell(row, col) && IsMyPiece(current_piece) ) {
        ClearSelection();

        ChessBoard[row][col].selected = true;

        CurrentMove.started = true;
        CurrentMove.player = CurrentPlayer;
        CurrentMove.piece_type = current_piece;
        CurrentMove.position_from = QPoint(col, row);
        CurrentMove.player = CurrentPlayer;

        SelectPossibleMove();
    }
    else if (CurrentMove.started && ChessBoard[row][col].selected) {
        ChessBoard[row][col].selected = true;
        CurrentMove.position_to = QPoint(col, row);

        ProcessMove(CurrentMove);

        CurrentMove.num_move = CurrentMoveNum;
        MoveHistory.insert(CurrentMoveNum, CurrentMove);
        ++CurrentMoveNum;

        CurrentMove.Reset();
        ClearSelection();
        SwitchCurrentPlayer();
    }
    else {
        ClearSelection();
        CurrentMove.Reset();
    }

    emit modelChanged();
}

void ChessBoardModel::ClearSelection()
{
    for(int row = 0; row < MAX_ROWS; ++row) {
        for(int col = 0; col < MAX_ROWS; ++col) {
            ChessBoard[row][col].selected = false;
        }
    }
}

void ChessBoardModel::clearBoard()
{
    for(int row = 0; row < MAX_ROWS; ++row) {
        for(int col = 0; col < MAX_ROWS; ++col) {
            ChessBoard[row][col].piece_type = PiecesManager::PIECE_NONE;
            ChessBoard[row][col].selected = false;
        }
    }
    CapturedBlack.clear();
    CapturedWhite.clear();
}

void ChessBoardModel::SelectPossibleMove()
{
    auto select_move_line = [this] (const int d_row, const int d_col) {
        int col = CurrentMove.position_from.x() + d_col;
        int row = CurrentMove.position_from.y() + d_row;

        while (col >= 0 && row >= 0 && col < MAX_ROWS && row < MAX_ROWS) {
            if(IsFreeCell(row, col)) {
                ChessBoard[row][col].selected = true;
            }
            else if(!IsMyPiece(ChessBoard[row][col].piece_type)) {
                ChessBoard[row][col].selected = true;
                break;
            }
            else {
                break;
            }

            col += d_col;
            row += d_row;
        }
    };

    auto select_move_one = [this] (const int d_row, const int d_col) {
        int col = CurrentMove.position_from.x() + d_col;
        int row = CurrentMove.position_from.y() + d_row;

        if (col >= 0 && row >= 0 && col < MAX_ROWS && row < MAX_ROWS) {
            if(IsFreeCell(row, col)) {
                ChessBoard[row][col].selected = true;
            }
            else if(!IsMyPiece(ChessBoard[row][col].piece_type)) {
                ChessBoard[row][col].selected = true;
            }
        }
    };

    switch (CurrentMove.piece_type) {
    case PiecesManager::PIECE_WHITE_KING:
    case PiecesManager::PIECE_BLACK_KING:
    {
        select_move_one(1, 0);
        select_move_one(-1, 0);
        select_move_one(0, 1);
        select_move_one(0, -1);
        select_move_one(1, 1);
        select_move_one(1, -1);
        select_move_one(-1, 1);
        select_move_one(-1, -1);
    }
        break;

    case PiecesManager::PIECE_WHITE_QUEEN:
    case PiecesManager::PIECE_BLACK_QUEEN:
    {
        select_move_line(1, 0);
        select_move_line(-1, 0);
        select_move_line(0, 1);
        select_move_line(0, -1);
        select_move_line(1, 1);
        select_move_line(1, -1);
        select_move_line(-1, 1);
        select_move_line(-1, -1);
    }
        break;

    case PiecesManager::PIECE_WHITE_ROOK:
    case PiecesManager::PIECE_BLACK_ROOK:
    {
        select_move_line(1, 0);
        select_move_line(-1, 0);
        select_move_line(0, 1);
        select_move_line(0, -1);
    }
        break;

    case PiecesManager::PIECE_WHITE_BISHOP:
    case PiecesManager::PIECE_BLACK_BISHOP:
    {
        select_move_line(1, 1);
        select_move_line(1, -1);
        select_move_line(-1, 1);
        select_move_line(-1, -1);
    }
        break;

    case PiecesManager::PIECE_WHITE_KNIGHT:
    case PiecesManager::PIECE_BLACK_KNIGHT:
    {
        select_move_one(2, 1);
        select_move_one(2, -1);
        select_move_one(-2, 1);
        select_move_one(-2, -1);
        select_move_one(1, 2);
        select_move_one(1, -2);
        select_move_one(-1, 2);
        select_move_one(-1, -2);
    }
        break;

    case PiecesManager::PIECE_WHITE_PAWN:
    case PiecesManager::PIECE_BLACK_PAWN:
    {
        auto get_end_y = [this] (const int step) -> int {
            int k = (CurrentPlayer == PLAYER_ONE) ? 1 : -1;
            int end_y = CurrentMove.position_from.y() + k * step;

            if(end_y < 0) end_y = 0;
            if(end_y >= MAX_ROWS) end_y = MAX_ROWS - 1;

            return end_y;
        };

        int row1 = get_end_y(1);
        int col = CurrentMove.position_from.x();

        if(IsFreeCell(row1, col))
            ChessBoard[row1][col].selected = true;

        int capture_col = col - 1;
        if( capture_col >= 0 ) {
            if(ChessBoard[row1][capture_col].piece_type && !IsMyPiece(ChessBoard[row1][capture_col].piece_type))
                ChessBoard[row1][capture_col].selected = true;
        }
        capture_col = col + 1;
        if( capture_col < MAX_ROWS ) {
            if(ChessBoard[row1][capture_col].piece_type && !IsMyPiece(ChessBoard[row1][capture_col].piece_type))
                ChessBoard[row1][capture_col].selected = true;
        }

        int row2 = get_end_y(2);
        if(IsFreeCell(row2, col)) {
            int row = CurrentMove.position_from.y();
            if(CurrentMove.piece_type == PiecesManager::PIECE_WHITE_PAWN) {
                if( row == 1 ) {
                    ChessBoard[row2][col].selected = true;
                }
            }
            else if( row == 6 ) {
                ChessBoard[row2][col].selected = true;
            }
        }
    }
        break;

    default:
    {
        ClearSelection();
    }
        break;
    }

}

void ChessBoardModel::ProcessMove(OneMove & move)
{
    if(ChessBoard[move.position_to.y()][move.position_to.x()].piece_type) {
        CurrentMove.captured_peace = ChessBoard[move.position_to.y()][move.position_to.x()].piece_type;

        switch( CurrentMove.captured_peace ) {
        case PiecesManager::PIECE_WHITE_KING:
        case PiecesManager::PIECE_WHITE_QUEEN:
        case PiecesManager::PIECE_WHITE_ROOK:
        case PiecesManager::PIECE_WHITE_BISHOP:
        case PiecesManager::PIECE_WHITE_KNIGHT:
        case PiecesManager::PIECE_WHITE_PAWN:
        {
            CapturedWhite.push_back(CurrentMove.captured_peace);
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
            CapturedBlack.push_back(CurrentMove.captured_peace);
            qSort(CapturedBlack);
        }
            break;

        default:
        {
        }
            break;
        }
    }

    ChessBoard[move.position_to.y()][move.position_to.x()].piece_type = move.piece_type;
    ChessBoard[move.position_from.y()][move.position_from.x()].piece_type = PiecesManager::PIECE_NONE;
}

void ChessBoardModel::ProcessMoveBack(OneMove & move)
{
    ChessBoard[move.position_to.y()][move.position_to.x()].piece_type = PiecesManager::PIECE_NONE;
    if(move.captured_peace) {
        ChessBoard[move.position_to.y()][move.position_to.x()].piece_type = move.captured_peace;

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

    ChessBoard[move.position_from.y()][move.position_from.x()].piece_type = move.piece_type;
}

void ChessBoardModel::SwitchCurrentPlayer()
{
    CurrentPlayer = (CurrentPlayer == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
    emit currentPlayerChanged(CurrentPlayer, CurrentMoveNum);
}

bool ChessBoardModel::IsFreeCell(const int row, const int col)
{
    return (ChessBoard[row][col].piece_type == PiecesManager::PIECE_NONE);
}

void ChessBoardModel::saveGame()
{
    QFile file(FileName);

    try {
        file.open(QFile::WriteOnly);
        for(auto it : MoveHistory) {
            file.write(reinterpret_cast <char *> (&it), sizeof(OneMove));
        }
        file.close();

        emit recordIOMessage(QString("File was saved."));
    }
    catch (...) {
        emit recordIOMessage(QString("Error in saving file."));
    }
}

void ChessBoardModel::loadGame()
{
    clearBoard();
    PrepareBoard();
    CurrentMoveNum = 0;

    QFile file(FileName);
    if(!file.exists()) {
        emit recordIOMessage(QString("File was no found"));
        return;
    }

    try {
        file.open(QFile::ReadOnly);
        while (!file.atEnd()) {
            OneMove m;
            file.read(reinterpret_cast <char *> (&m), sizeof(OneMove));
            MoveHistory.insert(m.num_move, m);
        }
        file.close();

        if (MoveHistory.empty())
            emit recordIOMessage(QString("Record file is empty or is not exists"));
        else
            emit recordIOMessage(QString("Record Prapared. Total %1 moves").arg(MoveHistory.size()));
    }
    catch (...) {
        emit recordIOMessage(QString("Error in opening file"));
    }
}

void ChessBoardModel::prevStep()
{
    if(CurrentMoveNum < 1) {
        PrepareBoard();
        CurrentMoveNum = 0;
        return;
    }

    if(CurrentMoveNum < MoveHistory.size()) {
        CurrentMove = MoveHistory.value(CurrentMoveNum);
        ProcessMoveBack(CurrentMove);

        emit replayMoveChanged(CurrentMoveNum, MoveHistory.size());
        emit modelChanged();
    }

    --CurrentMoveNum;
}

void ChessBoardModel::nextStep()
{
    ++CurrentMoveNum;

    if(CurrentMoveNum >= MoveHistory.size())
        CurrentMoveNum = MoveHistory.size();

    if(CurrentMoveNum < MoveHistory.size()) {
        CurrentMove = MoveHistory.value(CurrentMoveNum);
        ProcessMove(CurrentMove);

        emit replayMoveChanged(CurrentMoveNum, MoveHistory.size());
        emit modelChanged();
    }
}

QVector <PiecesManager::PiecesTypes> & ChessBoardModel::GetCapturedWhite()
{
    return CapturedWhite;
}

QVector <PiecesManager::PiecesTypes> & ChessBoardModel::GetCapturedBlack()
{
    return CapturedBlack;
}

void ChessBoardModel::setFileName(const QString & str)
{
    FileName = str;
}
