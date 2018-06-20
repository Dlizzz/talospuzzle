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
    std::vector<std::pair<PiecesSet::iterator, Positions::iterator>>(solution),
    _board(make_unique<Matrix>(*solution._board)),
    _Id(solution._Id) {}

// Solutions are equal if at least one of their symetrical boards are equal
bool Solution::operator==(const Solution& solution) {

    if (*(this->_board) == *solution._board) { return true; }
    if (*(this->_board) == solution._board->symHorizontal()) { return true; }
    if (*(this->_board) == solution._board->symVertical()) { return true; }
    if (*(this->_board) == solution._board->symCentral()) { return true; }

    return false;
}

void Solution::_makeSolutionBoard(PiecesSet& piecesSet, int Id) {
    // Do nothing if board is not initialized
    if (!_board) { return; }
    
    _Id = Id;

    // Replace board by a zero initialized board
    _board = make_unique<Matrix>(_board->rows(), _board->columns());
        
    // Combine all the positions in the board. Each element of the board stores the index of the
    // corresponding piece to easily find the piece from the board
    for (auto& position : *this) {
        unsigned char pieceId = distance(piecesSet.begin(), position.first) + 1;
        _board->combine(position.second->times(pieceId));
    }
}

// Helper for list deduplication
bool areSolutionsEqual(const Solution& solutionA, const Solution& solutionB) {

    cout << solutionA._board->to_string() << endl;
    cout << solutionB._board->to_string() << endl;
    cout << solutionB._board->symHorizontal().to_string() << endl;
    cout << solutionB._board->symVertical().to_string() << endl;
    cout << solutionB._board->symCentral().to_string() << endl;
    cout << "----\n";

    if (*solutionA._board == *solutionB._board) { return true; }
    if (*solutionA._board == solutionB._board->symHorizontal()) { return true; }
    if (*solutionA._board == solutionB._board->symVertical()) { return true; }
    if (*solutionA._board == solutionB._board->symCentral()) { return true; }

    return false;
}

