#ifndef ELABORATOTIMER_DISPLAY_H
#define ELABORATOTIMER_DISPLAY_H


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

    void printFooterEn();

    void printFooterIt();

private:
    Timer timer;
    Clock clock;
    Chronometer chrono;

    WINDOW * timerWin = nullptr;
    WINDOW * clockWin = nullptr;
    WINDOW * chronoWin = nullptr;
    WINDOW * instruction = nullptr;
    int height = 0, width = 0, termWidth = 0, termHeight = 0;
    string tmrTime, chrTime, chrMem, time, date;
    bool help, ita;

    bool terminate;
};


#endif //ELABORATOTIMER_DISPLAY_H
