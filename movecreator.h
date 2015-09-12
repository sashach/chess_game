#ifndef MOVECREATOR_H
#define MOVECREATOR_H

#include "piecesmanager.h"
#include "basemove.h"

class MoveCreator
{
public:
    MoveCreator();
    BaseMove * CreateMove(PiecesManager::PiecesTypes t);
};

#endif // MOVECREATOR_H
