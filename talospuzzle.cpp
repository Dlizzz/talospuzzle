

#include <iostream>

#include "params.h"
#include "piecesset.h"
#include "errors.h"

using namespace std;

#if defined(_DEBUG)
void exit_handler() noexcept {
    cout << "Press a key to close...";
    cin.ignore();
}
#endif 

int main(int ac, char* av[]) {
    Params params;

#if defined(_DEBUG)
    // Avoid closing the console at the end of execution
    atexit(exit_handler);
#endif 

    try {
        if (not params.getParams(ac, av)) {
            params.printHelp();
            exit(EXIT_SUCCESS);
        }
    }
    catch (ErrorParams &e) {
        cout << e.what() << "\n";
        exit(EXIT_FAILURE);
    }

    dumpPiecesBag();
}
