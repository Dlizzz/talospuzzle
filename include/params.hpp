// Header file for Class Params

#if !defined(_PARAMS_HPP)
#define _PARAMS_HPP

#include <string>
#include <unordered_map>
#if defined(WINDOWS)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem::v1;
#endif
#if defined(LINUX)
#include <filesystem>
namespace fs = std::filesystem:;
#endif


class Params
{
    public:
        Params();
        ~Params();
		void getParams(int ac, char* av[]);
  
    private:
        int rows_;                                        // # of rows of the board
        int columns_;                                     // # of columns of the board
        int cellSize_;                                    // size in pixels of a cell (square) of the board 
        bool verbose_;                                    // verbose output (toggle)
        bool first_;                                      // stop at firts solution found (toggle)
        bool stats_;                                      // save solving stats in csv file (toggle)
        bool images_;                                     // save png images of the solutions (toggle)
        std::string fillColor_;                           // HTML name of the fill color for the cells
        std::string shapeColor_;                          // HTML name of the border color for the cells  
        std::unordered_map<std::string, int> piecesSet_;  // # of each piece to solve the puzzle
        fs::path outputDir_;							  // directory where to save the png images
};

#endif // _PARAMS_HPP
