#include <string>

#include "errors.h"

using namespace std;

static const string errorParamsPrefix = "Fatal - talospuzzle command line error: ";
static const string errorStatsPrefix = "Warning - talospuzzle statistics file error: ";
static const string errorImagesPrefix = "Warning - talospuzzle images error: ";


ErrorBase::ErrorBase(const std::string& msg) noexcept:
    _msg(msg) {}

ErrorBase::ErrorBase(const char* msg) noexcept:
    _msg(msg) {}

ErrorParams::ErrorParams(const std::string& msg) noexcept: 
    ErrorBase(errorParamsPrefix) {
    _msg.append(msg);
}
ErrorParams::ErrorParams(const char* msg) noexcept: 
    ErrorBase(errorParamsPrefix)  {
    _msg.append(msg);
}

ErrorStats::ErrorStats(const std::string& msg) noexcept: 
    ErrorBase(errorStatsPrefix) {
    _msg.append(msg);
}
ErrorStats::ErrorStats(const char* msg) noexcept: 
    ErrorBase(errorStatsPrefix)  {
    _msg.append(msg);
}

ErrorImages::ErrorImages(const std::string& msg) noexcept: 
    ErrorBase(errorImagesPrefix) {
    _msg.append(msg);
}
ErrorImages::ErrorImages(const char* msg) noexcept: 
    ErrorBase(errorImagesPrefix)  {
    _msg.append(msg);
}
