#pragma once
#include <vector>

#include "board.h"
#include "piecesset.h"
#include "params.h"

class puzzle:
    private Board,
    private PiecesSet {
public:
    puzzle(const Params& params);
};

