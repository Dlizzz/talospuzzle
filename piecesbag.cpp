#include <iostream>
#include "piecesbag.h"

using namespace std;

std::ostream& operator<<(std::ostream &out, const PiecesBag &bag) {
    for (auto piece : bag) out << piece.second;
    return out;
}

PiecesBag piecesBag {
    {"l-right", { "L Right", "LR", 4, {
        {1, 1},
        {1, 0},
        {1, 0}
    }}},
    {"l-left", { "L Left", "LL", 4, {
        {1, 1},
        {0, 1}, 
        {0, 1}
    }}},
    {"step-right", { "Step Right", "SR", 2, {
        {0, 1, 1},
        {1, 1, 0}
    }}},
    {"step-left", { "Step Left", "SL", 2, {
        {1, 1, 0},
        {0, 1, 1}
    }}},
    {"square", { "Square", "SQ", 1, { 
        {1, 1}, 
        {1, 1} 
    }}}, 
    {"bar", { "Bar", "BA", 2, {
        {1, 1, 1, 1}
    }}},
    {"tee", { "Tee", "TE", 4, {
        {0, 1, 0},
        {1, 1, 1}
    }}}
};
