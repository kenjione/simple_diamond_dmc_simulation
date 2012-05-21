#ifndef HANDBOOKERROR_H
#define HANDBOOKERROR_H

#include "parse_error.h"

class HandbookError : public ParseError
{
public:
    HandbookError(const char *message);
    HandbookError(const char *message, const char *line);
    HandbookError(const char *message, const char *section, const char *variable);
};

#endif // HANDBOOKERROR_H
