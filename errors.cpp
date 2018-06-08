#include <string>

#include "errors.h"

using namespace std;

ErrorParams::ErrorParams(const string &msg) {
    _msg = "Fatal - talospuzzle command line error: ";
    _msg.append(msg);
}

ErrorParams::ErrorParams(const char* msg) {
    _msg = "Fatal - talospuzzle command line error: ";
    _msg.append(msg);
}

const char* ErrorParams::what() { return _msg.c_str(); }
