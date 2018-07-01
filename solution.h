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
    bool operator==(const Solution& solution) const ;
    void print(int offset) const;
    friend class Puzzle;

private:
    std::unique_ptr<Matrix> _board;
    bool _printable;
    void _makeSolutionBoard();
    void _makeSolutionBoard(PiecesSet& piecesSet);
};
