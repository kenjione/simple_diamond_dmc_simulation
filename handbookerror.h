#ifndef HANDBOOKERROR_H
#define HANDBOOKERROR_H

#include <string>

class HandbookError
{
public:
    HandbookError(const char *message);
    HandbookError(const char *message, const char *line);
    HandbookError(const char *message, const char *section, const char *variable);

    const char *message() const { return _message.c_str(); }

private:
    std::string _message;
};

#endif // HANDBOOKERROR_H
