#include "Display.h"
#include <ncurses.h>
#include <locale.h>
#include <functional>

Display::Display() {
    timer = Timer();
    clock = Clock();
    chrono = Chronometer();
    terminate = false;
    help = false;
    ita = false;
}

void Display::init() {
    initscr();

    keypad(stdscr, true);
    nodelay(stdscr, true);

    timer.setDuration(5);

    termWidth = getmaxx(stdscr);
    termHeight = getmaxy(stdscr);
    height = 9;
    width = 25;

    timerWin = newwin(height, width, (termHeight - height * 2 - 2) / 2, (termWidth - width * 3 + 2) / 2);
    clockWin = newwin(height, width, (termHeight - height * 2 - 2) / 2, (termWidth - width * 3 + 2) / 2 + width - 1);
    chronoWin = newwin(height, width, (termHeight - height * 2 - 2) / 2, (termWidth - width * 3 + 2) / 2 + 2 * width - 2);
    instruction = newwin(height * 2, width * 3 - 2, (termHeight - height * 2 - 2) / 2 + height + 2, (termWidth - width * 3 + 2) / 2);
    refresh();

    do {
        update();
    } while (!terminate);

    endwin();
}

void Display::update() {
    checkKB();
    erase();

    werase(timerWin);
    werase(clockWin);
    werase(chronoWin);

    wborder(timerWin, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(clockWin, 0, 0, 0, 0, ACS_TTEE, ACS_TTEE, ACS_BTEE, ACS_BTEE);
    wborder(chronoWin, 0, 0, 0, 0, 0, 0, 0, 0);

    if (!ita) {
        mvwprintw(timerWin, 2, 10, "TIMER");
        mvwprintw(clockWin, 2, 10, "CLOCK");
        mvwprintw(chronoWin, 2, 7, "CHRONOMETER");
    } else {
        mvwprintw(timerWin, 2, 10, "TIMER");
        mvwprintw(clockWin, 2, 9, "OROLOGIO");
        mvwprintw(chronoWin, 2, 7, "CRONOMETRO");
    }

    if (timer.getDuration() == 0) {
        beep();
        if (!ita) {
            tmrTime = "OUT OF TIME";
        } else {
            tmrTime = "TEMPO SCADUTO";
        }
    } else {
        tmrTime = timer.getDurationString();
    }
    date = clock.getDate();
    time = clock.getTime();
    chrTime = chrono.getTimeString();
    chrMem = chrono.getMemoryString();

    mvwprintw(timerWin, 5, (width - tmrTime.length()) / 2, &tmrTime[0]);
    mvwprintw(clockWin, 4, (width - date.length()) / 2, &date[0]);
    mvwprintw(clockWin, 6, (width - time.length()) / 2, &time[0]);
    mvwprintw(chronoWin, 5, (width - chrTime.length()) / 2, &chrTime[0]);
//    mvwprintw(chronoWin, 6, (width - chrMem.length()) / 2, &chrMem[0]);

    if (help) {
        printFooter();
    } else {
        if (!ita) {
            mvwprintw(instruction, 0, 1, "Press  L  to switch language between English and Italian");
            mvwprintw(instruction, 1, 1, "Press ESC to exit");
            mvwprintw(instruction, 2, 1, "Press  F1 to help");
        } else {
            mvwprintw(instruction, 0, 1, "Premi  L  per cambiare lingua tra Inglese e Italiano");
            mvwprintw(instruction, 1, 1, "Premi ESC per uscire");
            mvwprintw(instruction, 2, 1, "Premi  F1 per l'aiuto");
        }
    }

    wrefresh(timerWin);
    wrefresh(chronoWin);
    wrefresh(clockWin);
    wrefresh(instruction);

    napms(50);
}

void Display::checkKB() {
    int ch = getch();

    switch(ch){
        case 27:         //exit
            terminate = true;
            break;
        case KEY_UP:    // +1s
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 1);
            }
            break;
        case KEY_DOWN:  // -1s
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 1);
            }
            break;
        case KEY_RIGHT: // +10s
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 10);
            }
            break;
        case KEY_LEFT:  // -10s
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 10);
            }
            break;
        case '1':       // +1m
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 60 );
            }
            break;
        case '2':       // +2m
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 120 );
            }
            break;
        case '7':       // -1m
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 60);
            }
            break;
        case '6':       // +1h
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 3600);
            }
            break;
        case '0':       // -1h
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 3600);
            }
            break;
        case 's':       // start timer
            try {
                timer.startTimer();
            }
            catch (bad_function_call e){
                printf("Timer not set");
                beep();
            }
            break;
        case 't':       // stop timer
            timer.stopTimer();
            break;
        case 'r':       // reset timer (it also stops it)
            timer.resetTimer();
            timer.stopTimer();
            break;
        case 'w':       // change timer view mode
            timer.setViewMode(timer.getViewMode()+1);
            break;
        case 'v':       // start chrono
            chrono.startChrono();
            break;
        case ' ':       // stop chrono
            chrono.stopChrono();
            break;
        case 'b':       // reset chrono
            chrono.resetChrono();
            break;
        case 'n':       // change chrono view mode
            chrono.setViewMode(chrono.getViewMode()+1);
            break;
        case 'k':       // change clock view mode
            clock.setViewMode(clock.getViewMode()+1, ita);
            break;
        case 'l':       // change language
            if (ita) {
                ita = false;
            } else {
                ita = true;
            }
            clock.setViewMode(clock.getViewMode(), ita);
            break;
        case KEY_F(1):  // help
            if (!help) {
                help = true;
                printFooter();
                clock.setViewMode(clock.getViewMode(), ita);
            } else {
                help = false;
            }
            break;
        default:
            break;
    }
}


void Display::printFooter() {   // no unicode arrows
    mvwprintw(instruction,      0, 1, "_________________________________________________");
    if (!ita) {
        mvwprintw(instruction,  1, 1, "| INSTRUCTIONS | TIMER |  CLOCK   | CHRONOMETER |");
        mvwprintw(instruction,  2, 1, "|     exit     |  ESC  |   ESC    |     ESC     |");
        mvwprintw(instruction,  3, 1, "|    start     |   S   |          |      V      |");
        mvwprintw(instruction,  4, 1, "|     stop     |   T   |          |    SPACE    |");
        mvwprintw(instruction,  5, 1, "|    reset     |   R   |          |      B      |");
        mvwprintw(instruction,  6, 1, "| change view  |   W   |    K     |      N      |");
        mvwprintw(instruction,  7, 1, "|    +  1 s    |  UP   |          |             |");
        mvwprintw(instruction,  8, 1, "|    -  1 s    | DOWN  |          |             |");
        mvwprintw(instruction,  9, 1, "|    + 10 s    | RIGHT |          |             |");
        mvwprintw(instruction, 10, 1, "|    - 10 s    | LEFT  |          |             |");
        mvwprintw(instruction, 11, 1, "|    +  1 m    |   1   |          |             |");
        mvwprintw(instruction, 12, 1, "|    +  2 m    |   2   |          |             |");
        mvwprintw(instruction, 13, 1, "|    -  1 m    |   7   |          |             |");
        mvwprintw(instruction, 14, 1, "|    +  1 h    |   6   |          |             |");
        mvwprintw(instruction, 15, 1, "|    -  1 h    |   0   |          |             |");
        mvwprintw(instruction, 17, 50, "Credits: Federico Marra");
    } else {
        mvwprintw(instruction,  1, 1, "|  ISTRUZIONI  | TIMER | OROLOGIO | CRONOMETRO  |");
        mvwprintw(instruction,  2, 1, "|    uscita    |  ESC  |   ESC    |     ESC     |");
        mvwprintw(instruction,  3, 1, "|    inizio    |   S   |          |      V      |");
        mvwprintw(instruction,  4, 1, "|    ferma     |   T   |          |    SPAZIO   |");
        mvwprintw(instruction,  5, 1, "|   resetta    |   R   |          |      B      |");
        mvwprintw(instruction,  6, 1, "| cambia vista |   W   |    K     |      N      |");
        mvwprintw(instruction,  7, 1, "|    +  1 s    |  SU   |          |             |");
        mvwprintw(instruction,  8, 1, "|    -  1 s    |  GIU' |          |             |");
        mvwprintw(instruction,  9, 1, "|    + 10 s    |  DX   |          |             |");
        mvwprintw(instruction, 10, 1, "|    - 10 s    |  SN   |          |             |");
        mvwprintw(instruction, 11, 1, "|    +  1 m    |   1   |          |             |");
        mvwprintw(instruction, 12, 1, "|    +  2 m    |   2   |          |             |");
        mvwprintw(instruction, 13, 1, "|    -  1 m    |   7   |          |             |");
        mvwprintw(instruction, 14, 1, "|    +  1 h    |   6   |          |             |");
        mvwprintw(instruction, 15, 1, "|    -  1 h    |   0   |          |             |");
        mvwprintw(instruction, 17, 50, "Crediti: Federico Marra");
    }
    wrefresh(instruction);
}

/*
void Display::printFooter() {   // unicode arrows
    setlocale(LC_ALL, "");      // Set the locale to support Unicode characters
    wchar_t* upArrow = L"\u2191";
    wchar_t* downArrow = 0x2193;
    wchar_t* rightArrow = 0x2192;
    wchar_t* leftArrow = 0x2190;
    mvwaddwstr(instruction,  7, 19, &upArrow);
    mvwaddwstr(instruction,  8, 19, &downArrow);
    mvwaddwstr(instruction,  9, 19, &rightArrow);
    mvwaddwstr(instruction, 10, 19, &leftArrow);
    mvwprintw(instruction,      0, 1, "_________________________________________________");
    if (!ita) {
        mvwprintw(instruction,  1, 1, "| INSTRUCTIONS | TIMER |  CLOCK   | CHRONOMETER |");
        mvwprintw(instruction,  2, 1, "|     exit     |  ESC  |   ESC    |     ESC     |");
        mvwprintw(instruction,  3, 1, "|    start     |   S   |          |      V      |");
        mvwprintw(instruction,  4, 1, "|     stop     |   T   |          |    SPACE    |");
        mvwprintw(instruction,  5, 1, "|    reset     |   R   |          |      B      |");
        mvwprintw(instruction,  6, 1, "| change view  |   W   |    K     |      N      |");

        mvwprintw(instruction,  7, 1, "|    +  1 s    |   ↑   |          |             |");
        mvwprintw(instruction,  8, 1, "|    -  1 s    |   ↓   |          |             |");
        mvwprintw(instruction,  9, 1, "|    + 10 s    |   →   |          |             |");
        mvwprintw(instruction, 10, 1, "|    - 10 s    |   ←   |          |             |");

        mvwprintw(instruction, 11, 1, "|    +  1 m    |   1   |          |             |");
        mvwprintw(instruction, 12, 1, "|    +  2 m    |   2   |          |             |");
        mvwprintw(instruction, 13, 1, "|    -  1 m    |   7   |          |             |");
        mvwprintw(instruction, 14, 1, "|    +  1 h    |   6   |          |             |");
        mvwprintw(instruction, 15, 1, "|    -  1 h    |   0   |          |             |");
        mvwprintw(instruction, 17, 50, "Credits: Federico Marra");
    } else {
        mvwprintw(instruction,  1, 1, "|  ISTRUZIONI  | TIMER | OROLOGIO | CRONOMETRO  |");
        mvwprintw(instruction,  2, 1, "|    uscita    |  ESC  |   ESC    |     ESC     |");
        mvwprintw(instruction,  3, 1, "|    inizio    |   S   |          |      V      |");
        mvwprintw(instruction,  4, 1, "|    ferma     |   T   |          |    SPAZIO   |");
        mvwprintw(instruction,  5, 1, "|   resetta    |   R   |          |      B      |");
        mvwprintw(instruction,  6, 1, "| cambia vista |   W   |    K     |      N      |");
        mvwprintw(instruction,  7, 1, "|    +  1 s    |   ↑   |          |             |");
        mvwprintw(instruction,  8, 1, "|    -  1 s    |   ↓   |          |             |");
        mvwprintw(instruction,  9, 1, "|    + 10 s    |   →   |          |             |");
        mvwprintw(instruction, 10, 1, "|    - 10 s    |   ←   |          |             |");
        mvwprintw(instruction, 11, 1, "|    +  1 m    |   1   |          |             |");
        mvwprintw(instruction, 12, 1, "|    +  2 m    |   2   |          |             |");
        mvwprintw(instruction, 13, 1, "|    -  1 m    |   7   |          |             |");
        mvwprintw(instruction, 14, 1, "|    +  1 h    |   6   |          |             |");
        mvwprintw(instruction, 15, 1, "|    -  1 h    |   0   |          |             |");
        mvwprintw(instruction, 17, 50, "Crediti: Federico Marra");
    }
    wrefresh(instruction);
}
*/