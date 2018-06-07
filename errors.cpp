#include <exception>
#include <string>

#include "errors.h"

using namespace std;

ErrorParams::ErrorParams(string &msg) {
    _msg.append(msg);
}

ErrorParams::ErrorParams(const char* msg) {
    _msg.append(msg);
}

const char* ErrorParams::what() { return _msg.c_str(); }
