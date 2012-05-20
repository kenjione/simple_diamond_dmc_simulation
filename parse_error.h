/*
 * parse_error.h
 *
 *  Created on: 30.05.2011
 *      Author: newmen
 */

#ifndef PARSE_ERROR_H_
#define PARSE_ERROR_H_

#include <string>

class ParseError {
public:
    ParseError(const char *message) : _message(message) { }
    virtual ~ParseError() {}

    virtual const char *getMessage() const { return _message.c_str(); }

protected:
    ParseError() {}

private:
    std::string _message;
};

#endif /* PARSE_ERROR_H_ */
