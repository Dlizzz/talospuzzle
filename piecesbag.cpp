#include <iostream>

#include "piece.h"
#include "piecesbag.h"

using namespace std;

std::ostream& operator<<(std::ostream& out, const PiecesBag& bag) {
    for (auto& piece : bag) { out << piece.second; }
    return out;
}

PiecesBag piecesBag {
    {"l-right", { "L Right", "DarkOrange", 4, {
        {1, 1},
        {1, 0},
        {1, 0}
    }}},
    {"l-left", { "L Left", "Tomato", 4, {
        {1, 1},
        {0, 1}, 
        {0, 1}
    }}},
    {"step-right", { "Step Right", "Lime", 2, {
        {0, 1, 1},
        {1, 1, 0}
    }}},
    {"step-left", { "Step Left", "SpringGreen", 2, {
        {1, 1, 0},
        {0, 1, 1}
    }}},
    {"square", { "Square", "Crimson", 1, { 
        {1, 1}, 
        {1, 1} 
    }}}, 
    {"bar", { "Bar", "DarkViolet", 2, {
        {1, 1, 1, 1}
    }}},
    {"tee", { "Tee", "Cyan", 4, {
        {0, 1, 0},
        {1, 1, 1}
    }}}
};
