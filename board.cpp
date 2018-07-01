#include "board.h"
#include <sstream>
#include <iomanip>

using namespace std;

Board::Board(unsigned int ro, unsigned int co) noexcept: 
    boardRows(ro), 
    boardColumns(co),
    boardId() {

    stringstream id;
    id << setw(2) << setfill('0');
    id << boardRows;
    id << setw(2) << setfill('0');
    id << boardColumns;
    
    boardId = id.str();
}

