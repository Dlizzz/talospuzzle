#include <vector>
#include <memory>
#include <iterator>

#include "matrix.h"
#include "piecesset.h"
#include "solution.h"

using namespace std;

Solution::Solution():
    _board(make_unique<Matrix>()) {}

Solution::Solution(PiecesSet::iterator& pieceIt, Positions::iterator& positionIt, Matrix& board):
    std::vector<std::pair<PiecesSet::iterator, Positions::iterator>>(
        1, make_pair(pieceIt, positionIt)
    ),
    _board(make_unique<Matrix>(board)) {}

Solution::Solution(const Solution& solution):
    _board(make_unique<Matrix>(*solution._board)) {}

// Solutions are equal if at least one of their symetrical boards are equal
bool Solution::operator==(const Solution& solution) {

    if (*(this->_board) == *solution._board) { return true; }
    if (*(this->_board) == solution._board->symHorizontal()) { return true; }
    if (*(this->_board) == solution._board->symVertical()) { return true; }
    if (*(this->_board) == solution._board->symCentral()) { return true; }

    return false;
}

void Solution::_makeSolutionBoard() {
    // Do nothing if board is not initialized
    if (!_board) { return; }
    if (_board->empty()) { return; }
    for (auto& row : *_board) {
        if (row.empty()) { return; }
    }

    // Replace board by a zero initialized board
    *_board = Matrix(_board->rows(), _board->columns);
    

    
    for (auto& position : solution) {
        unsigned char pieceId = distance(begin(), position.first) + 1;
        puzzleBoard.combine(position.second->times(pieceId));
    }
}

// Helper for list deduplication
bool equal(const Solution& solutionA, const Solution& solutionB) {

    if (*solutionA._board == *solutionB._board) { return true; }
    if (*solutionA._board == solutionB._board->symHorizontal()) { return true; }
    if (*solutionA._board == solutionB._board->symVertical()) { return true; }
    if (*solutionA._board == solutionB._board->symCentral()) { return true; }

    return false;
}

