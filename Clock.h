#ifndef TIMER_CLOCK_CHRONOMETER_CLOCK_H
#define TIMER_CLOCK_CHRONOMETER_CLOCK_H


#include <string>

using namespace std;

class Clock {
public:
    Clock();

    string getTime() const;

    string getDate() const;

    int getViewMode() const;

    void setViewMode(int vm);

    bool isIta() const;

    void setIta(bool it);

    void switchIta();

private:
    int viewMode;
    bool ita;
};


#endif //TIMER_CLOCK_CHRONOMETER_CLOCK_H