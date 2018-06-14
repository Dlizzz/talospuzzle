#pragma once
#include <vector>

#include "params.h"
#include "board.h"
#include "piecesset.h"
#include "solution.h"

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
    std::vector<Solution> solutions;
};

