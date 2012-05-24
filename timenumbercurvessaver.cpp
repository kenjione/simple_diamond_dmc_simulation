#include "timenumbercurvessaver.h"

TimeNumberCurvesSaver::TimeNumberCurvesSaver(const char *filename) : Saver(filename) {}

void TimeNumberCurvesSaver::saveHeader(const std::deque<std::string> &names) {
    _outFile << "Time\tNumber\n"
             << "#";
    for (const std::string &name : names) _outFile << "\t" << name;
    _outFile << "\n";
}

void TimeNumberCurvesSaver::saveValuesLine(double time, const std::deque<int> &numbers) {
    _outFile.precision(12);
    _outFile << time;
    for (int number : numbers) _outFile << "\t" << number;
    _outFile << std::endl;
}
