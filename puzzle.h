#pragma once
#include <vector>

#include "params.h"
#include "board.h"
#include "piecesset.h"
#include "solution.h"

struct TreeNode {
    unsigned int pieceIdx;
    unsigned int positionIdx;
};

class Puzzle:
    private Board,
    private PiecesSet {
public:
    Puzzle(const Params& params);
    void solve();

private:
    const bool _verbose;
    const bool _first;
    const bool _stats;
    const int _treeDepth;
    void _crawlTree();
};

