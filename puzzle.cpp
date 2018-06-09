#include "puzzle.h"
#include "piecesbag.h"
#include "board.h"
#include "piecesset.h"
#include "params.h"

using namespace std;

puzzle::puzzle(const Params& params): 
    Board(params.getRows(), params.getColumns()),
    PiecesSet(piecesBag, params) {}
