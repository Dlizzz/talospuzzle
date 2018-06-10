#include <string>

#include "errors.h"

using namespace std;

Errors::Errors(const string& msg) {
    _msg = "Fatal - talospuzzle command line error: ";
    _msg.append(msg);
}

Errors::Errors(const char* msg) {
    _msg = "Fatal - talospuzzle command line error: ";
    _msg.append(msg);
}
