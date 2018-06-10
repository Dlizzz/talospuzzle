#pragma once
#include <vector>

#include "board.h"
#include "piecesset.h"
#include "params.h"

class Puzzle:
    private Board,
    private PiecesSet {
public:
    Puzzle(const Params& params);
    void solve();

private:
    bool _verbose = false;
    bool _first = false;
    bool _stats = false;
};

