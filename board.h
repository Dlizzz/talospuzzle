#pragma once

class Board {
public:
    Board(unsigned int ro, unsigned int co) noexcept;

protected:
    unsigned int boardRows;
    unsigned int boardColumns;
};
