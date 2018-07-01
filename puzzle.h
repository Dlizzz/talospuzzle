#pragma once
#include <list>
#include <memory>
#include <ctime>

#include "matrix.h"
#include "params.h"
#include "board.h"
#include "piecesset.h"
#include "solution.h"

class Puzzle:
    public Board,
    public PiecesSet {
public:
    explicit Puzzle(const Params& params);
    void solve();
    void printSolutions();

private:
    const bool _verbose;
    const bool _first;
    const bool _stats;
    long long _combinationsCount;
    std::string _puzzleId;
    clock_t _solvingTime;
    std::unique_ptr<std::list<Solution>> _solutions;
    void _crawlTree(Solution& solution, PiecesSet::iterator& nextPieceIt); 
    void _deduplicateSolutions();
    void _printStats() const;
};

