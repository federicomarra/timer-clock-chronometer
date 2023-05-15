#ifndef TIMER_CLOCK_CHRONOMETER_DISPLAY_H
#define TIMER_CLOCK_CHRONOMETER_DISPLAY_H


#include "Timer.h"
#include "Clock.h"
#include "Chronometer.h"
#include <ncurses.h>

class Display {
public:
    Display();

    void init();

    void update();

    void checkKB();

    void printHelp();

    void switchIta();

private:
    Timer timer;
    Clock clock;
    Chronometer chrono;

    WINDOW *timerWin = nullptr;
    WINDOW *clockWin = nullptr;
    WINDOW *chronoWin = nullptr;
    WINDOW *instruction = nullptr;

    int height = 0, width = 0, termWidth = 0, termHeight = 0, instructionHeight = 0, instructionWidth = 0;
    string tmrTime, chrTime, chrMem, time, date;
    bool terminate, help, ita, unicode;
};


#endif //TIMER_CLOCK_CHRONOMETER_DISPLAY_H