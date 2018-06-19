#pragma once
#include <vector>
#include <list>
#include <memory>

#include "matrix.h"
#include "params.h"
#include "board.h"
#include "piecesset.h"
#include "solution.h"

class Puzzle:
    public Board,
    public PiecesSet {
public:
    Puzzle(const Params& params);
    void solve();
    void printSolutions();

private:
    const bool _verbose;
    const bool _first;
    const bool _stats;
    bool _solved;
    std::unique_ptr<std::list<Solution>> _solutions;
    void _crawlTree(Solution& solution, PiecesSet::iterator& nextPieceIt); 
    void _deduplicateSolutions();
};

