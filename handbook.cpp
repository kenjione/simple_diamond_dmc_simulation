#include "handbook.h"
#include <cstdlib>
#include <fstream>
#include <regex>
#include "handbookerror.h"

Handbook *Handbook::__instance = 0;

Handbook *Handbook::instance() {
    if (!__instance) {
        throw HandbookError("Handbook is not initialized");
    }

    return __instance;
}

Handbook::Handbook(const char *configFileName) {
    if (__instance) {
        throw HandbookError("Handbook can be initialized just one time");
    }

    std::fstream configFile(configFileName);

    if (!configFile.is_open()) {
        throw HandbookError("Cannot open configuration file");
    }

    std::regex commentRegexp(R"(^\s*#)");
    std::regex sectionRegexp(R"(^\[(.+)\])");
    std::regex variableRegexp(R"(\s*(\w+)\s*=\s*([\d\.e-]+)\s*)");

    try {
        VarVal *currentSection = 0;

        std::string line;
        while (std::getline(configFile, line)) {
            if (std::regex_match(line, commentRegexp)) continue;

            std::cmatch matches;
            if (std::regex_match(line.c_str(), matches, sectionRegexp)) {
                std::string sectionName = matches[1].str();
                currentSection = &_values[sectionName];
            } else if (std::regex_match(line.c_str(), matches, variableRegexp)) {
                if (currentSection) {
                    std::string variable = matches[1].str();
                    double value = atof(matches[2].str().c_str());
                    (*currentSection)[variable] = value;
                } else {
                    throw HandbookError("Variable is not in section", line.c_str());
                }
            }
        }
    } catch (std::regex_error &error) {
        throw HandbookError("Regex error", error.what());
    }

    __instance = this;
}

double Handbook::value(const char *sectionName, const char *variableName) const {
    auto sectionPair = _values.find(sectionName);
    if (sectionPair != _values.end()) {
        auto variablePair = sectionPair->second.find(variableName);
        if (variablePair != sectionPair->second.end()) {
            return variablePair->second;
        }
    }

    throw HandbookError("Variable not found", sectionName, variableName);
    return 0;
}
