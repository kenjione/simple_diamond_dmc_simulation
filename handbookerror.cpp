#include "handbookerror.h"

HandbookError::HandbookError(const char *message) : _message(message) {}

HandbookError::HandbookError(const char *message, const char *line) : _message(message) {
    _message += ": " + std::string(line);
}

HandbookError::HandbookError(const char *message, const char *section, const char *variable) : _message(message) {
    _message += ": " + std::string(section) + "::" + std::string(variable);
}
