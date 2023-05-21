#ifndef TIMER_CLOCK_CHRONOMETER_CHRONOMETER_H
#define TIMER_CLOCK_CHRONOMETER_CHRONOMETER_H


#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

class Chronometer {
public:
    Chronometer();

    const time_point<steady_clock> &getStart() const;

    string getTimeString() const;

    int getTime() const;

    int getMemory() const;

    string getMemoryString() const;

    bool isRunning() const;

    int getViewMode() const;

    void setViewMode(int vm);

    bool startChrono();

    bool stopChrono();

    void resetChrono();

private:
    time_point<steady_clock> start;
    ::duration<int, milli> stored;
    bool running;
    ::duration<int, milli> memory;
    int viewMode;

    static const int secPerDay, secPerHour, secPerMin;

    string stringify(int deciseconds) const;
};


#endif //TIMER_CLOCK_CHRONOMETER_CHRONOMETER_H