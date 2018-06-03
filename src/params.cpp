/*  Name: params.cpp
        Define, parse, check and return command line arguments
    Classes:
        params
    Dependencies:
       
*/

#include <iostream>
#include <iterator>
#include <string>
#if defined(WINDOWS)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem::v1;
#endif
#if defined(LINUX)
#include <filesystem>
namespace fs = std::filesystem:;
#endif

#include "boost/program_options.hpp"
namespace po = boost::program_options;

#include "params.hpp"

using namespace std;

static const string DESCRIPTION_TEXT = "Try to solve the given puzzle and print"
  " status or solution if it exists on stdout.\n"
  "Puzzle board is made of Rows x Columns cells.\n"
  "\tColumn is the horizontal dimension.\n"
  "\tRow is the vertical dimension.\n"
  "The puzzle can use the following pieces:\n"
  "- Square shape:\n"
  "\tXX\n"
  "\tXX\n"
  "- L right shape:\n"
  "\tXX\n"
  "\tX\n"
  "\tX\n"
  "- L left shape:\n"
  "\tXX\n"
  "\t X\n"
  "\t X\n"
  "- Bar shape:\n"
  "\tX\n"
  "\tX\n"
  "\tX\n"
  "\tX\n"
  "- Tee shape:\n"
  "\t X\n"
  "\tXXX\n"
  "- Step right shape:\n"
  "\t XX\n"
  "\tXX\n"
  "- Step left shape:\n"
  "\tXX\n"
  "\t XX\n"
  "The pieces can be flipped horizontally and vertically.\n";

Params::Params(int ac, char* av[])
{
  try {
    po::options_description globalOptions("Global options");
    globalOptions.add_options()
      ("help", DESCRIPTION_TEXT)
      (
        "verbose",
        po::bool_switch(&verbose_),
        "Print progress status on stdout (toggle)"
      )
      (
        "first",
        po::bool_switch(&first_),
        "Stop at first solution found (toggle)"
      )
      (
        "stats",
        po::bool_switch(&stats_),
        "Save puzzle solving statistics in CSV format (toggle)"
      );

    po::options_description imagesOptions("Images options");
    imagesOptions.add_options()
      (
        "images",
        po::bool_switch(&images_),
        "Output solutions as png images (toggle)"
      )
      (
        "output-dir dir",
        po::value<fs::path>(&outputDir_)->default_value(fs::current_path()),
        "Directory where to output png images (default: application dir)"
      )
      (
        "cell-size #",
        po::value<int>(&cellSize_)->default_value(100),
        "Size in pixels of one cell of the board (default: 100)"
      )
      (
        "shape-color colorname",
        po::value<string>(&borderColor_)->default_value("Yellow"),
        "Color name (HTML) of the shape color (default: Yellow)"
      )
      (
        "fill-color colorname",
        po::value<string>(&fillColor_)->default_value("DarkMagenta"),
        "Color name (HTML) of the fill color (default: DarkMagenta)"
      );

    po::options_description boardOptions("Board options");
    boardOptions.add_options()
      ("rows #", po::value<int>(&rows_)->required(), "Number of board rows (mandatory)")
      (
        "columns #",
        po::value<int>(&columns_)->required(),
        "Number of board columns (mandatory)"
      );

    po::options_description piecesOptions("Pieces options");
    piecesOptions.add_options()
      (
        "square #",
        po::value<int>()->default_value(0),
        "Number of Square shape pieces (default: 0)"
      )
      (
        "l-right #",
        po::value<int>()->default_value(0),
        "Number of L right shape pieces (default: 0)"
      )
      (
        "l-left #",
        po::value<int>()->default_value(0),
        "Number of L left shape pieces (default: 0)"
      )
      (
        "bar #",
        po::value<int>()->default_value(0),
        "Number of Bar shape pieces (default: 0)"
      )
      (
        "tee #",
        po::value<int>()->default_value(0),
        "Number of T shape pieces (default: 0)"
      )
      (
        "step-right #",
        po::value<int>()->default_value(0),
        "Number of Step right shape pieces (default: 0)"
      )
      (
        "step-left #",
        po::value<int>()->default_value(0),
        "Number of Step left shape pieces (default: 0)"
      );

    po::options_description options("Available options");
    options.add(globalOptions);
    options.add(imagesOptions);
    options.add(boardOptions);
    options.add(piecesOptions);

    po::variables_map vm;        
    po::store(po::parse_command_line(ac, av, options), vm);
    po::notify(vm);    
  }
  catch(exception& e) {
  }
  catch(...) {
  }
}

Params::~Params()
{
}

