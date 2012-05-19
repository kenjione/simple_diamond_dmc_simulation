/*
 * parse_params_error.h
 *
 *  Created on: 30.05.2011
 *      Author: newmen
 */

#ifndef PARSE_PARAMS_ERROR_H_
#define PARSE_PARAMS_ERROR_H_

#include <string>
#include <sstream>

#include "parse_error.h"

class ParseParamsError : public ParseError {
public:
    ParseParamsError(const char *message, const char *param) : ParseError(message), _param(param) { }

    const char *getMessage() const {
		std::stringstream message;
		message << ParseError::getMessage() << ": " << _param;
        return message.str().c_str();
	}

private:
	ParseParamsError();

private:
	std::string _param;
};

#endif /* PARSE_PARAMS_ERROR_H_ */
