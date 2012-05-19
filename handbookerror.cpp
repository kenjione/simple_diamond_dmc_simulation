#include "handbookerror.h"
#include <string>

HandbookError::HandbookError(const char *message) : ParseError(message) {}

HandbookError::HandbookError(const char *message, const char *line)
    : ParseError(std::string(std::string(message) + ": " + line).c_str()) {}

HandbookError::HandbookError(const char *message, const char *section, const char *variable)
    : ParseError(std::string(std::string(message) + ": " + section + "::" + variable).c_str()) {} // этажесть канешна :)
