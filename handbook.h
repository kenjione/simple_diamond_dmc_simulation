#ifndef HANDBOOK_H
#define HANDBOOK_H

#include <map>
#include <string>
#include "int3.h"

class Handbook {
    typedef std::map<std::string, double> VarVal;

public:
    static Handbook *instance();

    Handbook(const char *configFileName);

    double value(const char *sectionName, const char *variableName) const;

private:
    static Handbook *__instance;

    std::map<std::string, VarVal> _values;
};

#endif /* HANDBOOK_H */
