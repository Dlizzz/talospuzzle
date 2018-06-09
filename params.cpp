/*  Name: params.cpp
        Define, parse, check and return command line arguments
    Classes:
        Params
    Dependencies:
       
*/

#include <iostream>
#include <string>
#include <memory>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#pragma warning (push)
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#pragma warning (pop)
namespace po = boost::program_options;
namespace fs = boost::filesystem;

#include "params.h"
#include "errors.h"
#include "helpers.h"

using namespace std;

static const string DESCRIPTION_TEXT = "Description:\nTry to solve the given puzzle and print"
    " status or solution if it exists on stdout.\n"
    "Puzzle board is made of Rows x Columns cells.\n"
    "- Column is the horizontal dimension.\n"
    "- Row is the vertical dimension.\n"
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

static const string CAPTION = "talospuzzle.exe --rows # --columns # [options]\nAvailable options"; 

Params::Params() noexcept: _lineLenght(120), _descriptionLength(80) {
    _options = std::unique_ptr<po::options_description>(
        new po::options_description(CAPTION, _lineLenght, _descriptionLength)
    );
    _vm = std::unique_ptr<po::variables_map>(new po::variables_map);
}

bool Params::getParams(int ac, char* av[]) {
    try {
		// Global options group
        po::options_description globalOptions("Global options", _lineLenght, _descriptionLength);
        globalOptions.add_options()(
            "help", "Display this help text"
        )(
			"verbose",
			po::bool_switch()->default_value(false),
			"Print progress status on stdout (toggle)"
		)(
			"first",
			po::bool_switch()->default_value(false),
			"Stop at first solution found (toggle)"
		)(
			"stats",
			po::bool_switch()->default_value(false),
			"Save puzzle solving statistics in CSV format (toggle)"
		);

		// Images options group
		po::options_description imagesOptions("Images options", _lineLenght, _descriptionLength);
        imagesOptions.add_options()(
            "images",
            po::bool_switch()->default_value(false),
            "Output solutions as png images (toggle)"
            )(
                "output-dir",
                po::value<fs::path>()->default_value(fs::current_path())->notifier(
                    [](fs::path value) { if (not fs::is_directory(value)) throw ErrorParams(
                        string("--output-dir: ")
                        .append(value.string())
                        .append(" is not a directory")
                ); }
            ),
			"Directory where to output png images (default: application dir)"
		)(
			"cell-size",
			po::value<int>()->default_value(100)->notifier(
                [](int value) { if (value <= 0) throw ErrorParams(
                    "--cell-size must be greater than 0"
                ); }
            ),
			"Size in pixels of one cell of the board (default: 100)"
		)(
			"shape-color",
			po::value<string>()->default_value("Yellow")->notifier(
                [](string value) { if (not isValidHtmlColorName(value)) throw ErrorParams(
                    string("--shape-color: ")
                    .append(value)
                    .append(" is not a valid HTML color name")
                ); }
            ),
			"Color name (HTML) of the shape color (default: Yellow)"
		)(
			"fill-color",
			po::value<string>()->default_value("DarkMagenta")->notifier(
                [](string value) { if (not isValidHtmlColorName(value)) throw ErrorParams(
                    string("--fill-color: ")
                    .append(value)
                    .append(" is not a valid HTML color name")
                ); }
            ),
			"Color name (HTML) of the fill color (default: DarkMagenta)"
		);

		// Board options group
		po::options_description boardOptions("Board options", _lineLenght, _descriptionLength);
		boardOptions.add_options()(
			"rows",
            po::value<int>()->required()->notifier(
                [](int value) { if (value <= 0) throw ErrorParams(
                    "--rows must be greater than 0"
                ); }
            ),
			"Number of board rows (mandatory)"
		)(
			"columns",
            po::value<int>()->required()->notifier(
                [](int value) { if (value <= 0) throw ErrorParams(
                    "--columns must be greater than 0"
                ); }
            ),
			"Number of board columns (mandatory)"
		);

		// Pieces set options group
        po::options_description piecesOptions("Pieces options", _lineLenght, _descriptionLength);
		piecesOptions.add_options()(
			"square",
			po::value<int>()->default_value(0)->notifier(
                [](int value) { if (value < 0) throw ErrorParams(
                    "--square must be greater than or equal to 0"
                ); }
            ),
			"Number of Square shape pieces (default: 0)"
		)(
			"l-right",
			po::value<int>()->default_value(0)->notifier(
                [](int value) { if (value < 0) throw ErrorParams(
                    "--l-right must be greater than or equal to 0"
                ); }
            ),
			"Number of L right shape pieces (default: 0)"
		)(
            "l-left",
			po::value<int>()->default_value(0)->notifier(
                [](int value) { if (value < 0) throw ErrorParams(
                    "--l-left must be greater than or equal to 0"
                ); }
            ),
			"Number of L left shape pieces (default: 0)"
		)(
			"bar",
			po::value<int>()->default_value(0)->notifier(
                [](int value) { if (value < 0) throw ErrorParams(
                    "--bar must be greater than or equal to 0"
                ); }
            ),
			"Number of Bar shape pieces (default: 0)"
		)(
			"tee",
			po::value<int>()->default_value(0)->notifier(
                [](int value) { if (value < 0) throw ErrorParams(
                    "--tee must be greater than or equal to 0"
                ); }
            ),
			"Number of T shape pieces (default: 0)"
		)(
			"step-right",
			po::value<int>()->default_value(0)->notifier(
                [](int value) { if (value < 0) throw ErrorParams(
                    "--step-right must be greater than or equal to 0"
                ); }
            ),
			"Number of Step right shape pieces (default: 0)"
		)(
			"step-left",
			po::value<int>()->default_value(0)->notifier(
                [](int value) { if (value < 0) throw ErrorParams(
                    "--step-left must be greater than or equal to 0"
                ); }
            ),
			"Number of Step left shape pieces (default: 0)"
		);

        _options->add(boardOptions).add(piecesOptions).add(imagesOptions).add(globalOptions);

		po::store(po::parse_command_line(ac, av, *_options), *_vm);
        if (_vm->count("help")) return false;
		po::notify(*_vm);
        return true;
	}
	catch(po::error &e) {
        throw ErrorParams(e.what());
	}
}

void Params::printHelp() const {
	cout << *_options << "\n" << DESCRIPTION_TEXT << "\n";
}