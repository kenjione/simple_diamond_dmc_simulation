#ifndef TIMENUMBERSCURVESSAVER_H
#define TIMENUMBERSCURVESSAVER_H

#include "saver.h"
#include <deque>
#include <string>

class TimeNumberCurvesSaver : public Saver
{
public:
    TimeNumberCurvesSaver(const char *filename);

protected:
    void saveHeader(const std::deque<std::string> &names);
    void saveValuesLine(float time, const std::deque<int> &numbers);
};

#endif // TIMENUMBERSCURVESSAVER_H
