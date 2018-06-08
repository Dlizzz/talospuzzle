#pragma once

class Board {
public:
    Board(int ro, int co) noexcept;

protected:
    int rows;
    int columns;
};
