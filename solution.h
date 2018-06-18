#pragma once
#include <vector>
#include <memory>
#include <iterator>

#include "matrix.h"
#include "piecesset.h"

class Solution:
    public std::vector<std::pair<PiecesSet::iterator, Positions::iterator>> {
public:
    Solution();
    Solution(PiecesSet::iterator& pieceIt, Positions::iterator& positionIt, Matrix& board);
    Solution(const Solution& solution);
    bool operator==(const Solution& solution);
    friend bool equal(const Solution& solutionA, const Solution& solutionB);
    friend class Puzzle;

private:
    std::unique_ptr<Matrix> _board;
    int _Id;
    void _makeSolutionBoard();
};
