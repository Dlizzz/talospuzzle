#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "piece.h"

using namespace std;

static unordered_map<string, Piece> piecesBag {
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
    {"step-let", { "Step Left", "SL", 2, {
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

/*
Dump piecesBag for testing
*/
void dumpPiecesBag() {
    for (auto piece : piecesBag) cout << piece.second;
}