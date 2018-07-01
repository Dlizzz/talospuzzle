#include <vector>
#include <memory>
#include <iterator>

#include "matrix.h"
#include "piecesset.h"
#include "solution.h"
#include "helpers.h"

using namespace std;

Solution::Solution():
    _board(make_unique<Matrix>()),
    _printable(false) {}

Solution::Solution(PiecesSet::iterator& pieceIt, Positions::iterator& positionIt, Matrix& board):
    vector<pair<PiecesSet::iterator, Positions::iterator>>(
        1, make_pair(pieceIt, positionIt)
    ),
    _board(make_unique<Matrix>(board)),
    _printable(false) {}

Solution::Solution(const Solution& solution):
    vector<pair<PiecesSet::iterator, Positions::iterator>>(solution),
    _board(make_unique<Matrix>(*solution._board)),
    _printable(solution._printable) {}

void Solution::print(int offset) const {
    // Do nothing if not printable
    if (!_printable) { return; }
    
    for (auto& row : *_board) {
        cout << string(offset, NOTHING);
        for (auto& element : row) {
            // Get the piece color, from element being the index of the piece  
            ColorValues color = next(this->begin(), element - 1)->first->getColor();
            coutColoredBlock(color);
        }
        cout << endl;
    }
}

void Solution::_makeSolutionBoard() {
    // Do nothing if board is not initialized
    if (!_board) { return; }
    
    // Replace board by a zero initialized board
    _board = make_unique<Matrix>(_board->rows(), _board->columns());
        
    // Combine all the positions in the board. Each element of the board stores the index of the
    // corresponding piece to easily find the piece from the board
    for (auto& position : *this) {
        // Encode the piece Id in the board to help for solutions list deduplication
        unsigned char factor = position.first->getId();
        _board->combine(position.second->times(factor));
    }
}

void Solution::_makeSolutionBoard(PiecesSet& piecesSet) {
    // Do nothing if board is not initialized
    if (!_board) { return; }
    
    // Replace board by a zero initialized board
    _board = make_unique<Matrix>(_board->rows(), _board->columns());
        
    // Combine all the positions in the board. Each element of the board stores the index of the
    // corresponding piece to easily find the piece from the board
    for (auto& position : *this) {
        // Encode the piece Index in the board to help for solutions drawing
        unsigned char factor = distance(piecesSet.begin(), position.first) + 1;
        _board->combine(position.second->times(factor));
    }

    // The solution is now printable
    _printable = true;
}

// Solutions are equal if at least one of their symetrical or rotated boards are equal
bool Solution::operator==(const Solution& solution) const  {
    Matrix matrixA = *(this->_board);
    
    Matrix matrixB = *solution._board;
    if (matrixA == matrixB) { return true; }
    matrixB = matrixB.rot90();
    if (matrixA == matrixB) { return true; }
    matrixB = solution._board->symHorizontal();
    if (matrixA == matrixB) { return true; }
    matrixB = solution._board->symVertical();
    if (matrixA == matrixB) { return true; }
    matrixB = matrixB.symHorizontal();
    if (matrixA == matrixB) { return true; }
    matrixB = matrixB.rot90();
    if (matrixA == matrixB) { return true; }

    return false;
}

