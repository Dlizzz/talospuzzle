#include <string>

#include "errors.h"

using namespace std;

static const string errorsPrefix = "Fatal - talospuzzle command line error: ";

ErrorParams::ErrorParams(const std::string& msg) noexcept: _msg(errorsPrefix) {
    _msg.append(msg);
}
ErrorParams::ErrorParams(const char* msg) noexcept: _msg(errorsPrefix)  {
    _msg.append(msg);
}
