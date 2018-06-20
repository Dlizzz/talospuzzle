

#include <iostream>

#include "params.h"
#include "piecesbag.h"
#include "piecesset.h"
#include "puzzle.h"
#include "errors.h"

using namespace std;

#if defined(_DEBUG)
void exit_handler() noexcept {
    cout << "Press a key to close...";
    cin.ignore();
}
#endif 

int main(int ac, char* av[]) {
#if defined(_DEBUG)
    // Avoid closing the console at the end of execution
    atexit(exit_handler);
#endif 

    Params params;
    try {
        // Read the parameters from command line
        if (! params.readParams(ac, av)) {
            params.printHelp();
            exit(EXIT_SUCCESS);
        }
        // Create the puzzle from parameters
        Puzzle puzzle(params);

        // Solve the puzzle
        puzzle.solve();

        // Print the solutions
        puzzle.printSolutions();
    }
    catch (ErrorParams& e) {
        cout << e.what() << "\n";
        params.printHelp(false);
        exit(EXIT_FAILURE);
    }
}


