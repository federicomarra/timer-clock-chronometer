#include "Display.h"
#include <ncurses.h>
#include <functional>

Display::Display() {
    timer = Timer();
    clock = Clock();
    chrono = Chronometer();
    terminate = false;
    help = false;
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

    timerWin = newwin(height, width, (termHeight-height*2 - 2)/2, (termWidth - width*3 + 2)/2);
    clockWin = newwin(height, width, (termHeight-height*2 - 2)/2, (termWidth - width*3 + 2)/2 + width - 1);
    chronoWin = newwin(height, width, (termHeight-height*2 - 2)/2, (termWidth - width*3 +2)/2 + 2*width - 2);
    instruction = newwin(height*2, width*3-2, (termHeight-height*2 - 2)/2 + height + 2, (termWidth - width*3 + 2)/2);
    refresh();

    do{
        update();
    }while(!terminate);

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
    mvwprintw(timerWin, 2, 10, "TIMER");
    mvwprintw(clockWin, 2, 10, "CLOCK");
    mvwprintw(chronoWin, 2, 7, "CHRONOMETER");

    if(timer.getDuration() == 0){
        beep();
        tmrTime = "OUT OF TIME";
    }
    else {
        tmrTime = timer.getDurationString();
    }
    date = clock.getDate();
    time = clock.getTime();
    chrTime = chrono.getTimeString();
    chrMem = chrono.getMemoryString();

    mvwprintw(timerWin, 5, (width-tmrTime.length())/2, &tmrTime[0]);
    mvwprintw(clockWin, 4, (width-date.length())/2, &date[0]);
    mvwprintw(clockWin, 6, (width-time.length())/2, &time[0]);
    mvwprintw(chronoWin, 4, (width-chrTime.length())/2, &chrTime[0]);
    mvwprintw(chronoWin, 6, (width-chrMem.length())/2, &chrMem[0]);
    if(help){
        printFooterEn();
    }
    else{
        mvwprintw(instruction, 0, 1, "Press F1 for help");
        mvwprintw(instruction, 1, 1, "Premi F2 per l'aiuto");
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
        case 27:            //ESC KEY
            terminate = true;
            break;
        case KEY_UP:
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 1);
            }
            break;
        case KEY_DOWN:
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 1);
            }
            break;
        case KEY_RIGHT:
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 10);
            }
            break;
        case KEY_LEFT:
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 10);
            }
            break;
        case '1':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 60 );
            }
            break;
        case '2':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 120 );
            }
            break;
        case '7':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 60);
            }
            break;
        case '6':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 3600);
            }
            break;
        case '0':
            if(!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 3600);
            }
            break;
        case 's':
            try {
                timer.startTimer();
            }
            catch (bad_function_call e){
                printf("Timer not set");
                beep();
            }
            break;
        case 't':
            timer.stopTimer();
            break;
        case 'r':
            timer.resetTimer();
            break;
        case 'w':
            timer.setViewMode(timer.getViewMode()+1);
            break;
        case 'v':
            chrono.startChrono();
            break;
        case ' ':
            chrono.stopChrono();
            break;
        case 'b':
            chrono.resetChrono();
            break;
        case 'n':
            chrono.setViewMode(chrono.getViewMode()+1);
            break;
        case 'k':
            clock.setViewMode(clock.getViewMode()+1);
            break;
        case KEY_F(1):
            if (!help){
                help = true;
                printFooterEn();
            }
            else{
                help = false;
            }
            break;
        case KEY_F(2):
            if (!help){
                help = true;
                printFooterIt();
            }
            else{
                help = false;
            }
            break;
        default:
            break;
    }
}

/*
void Display::printFooterEn() {
    mvwprintw(instruction, 0, 1, "TIMER | S : start, T : stop, R : reset, W : view, UP : +1s, DOWN : -1s");
    mvwprintw(instruction, 1, 1, "CLOCK |                        ");
    mvwprintw(instruction, 1, 41, "K : view");
    mvwprintw(instruction, 2, 1, "CHRONO | V : start, SPACE: stop, B : reset, N : change view");
    mvwprintw(instruction, 4, 1, "ESC : exit");
    mvwprintw(instruction, 6, 51, "Credit: Federico Marra");
    wrefresh(instruction);
}

void Display::printFooterIt() {
    mvwprintw(instruction, 0, 1, "TIMER | S : inizia, T : stop, R : reset, W : view, UP : +1s, DOWN : -1s");
    mvwprintw(instruction, 1, 1, "CLOCK | ");
    mvwprintw(instruction, 1, 41, "K : view");
    mvwprintw(instruction, 2, 1, "CHRONO | V : start, SPACE: stop, B : reset, N : change view");
    mvwprintw(instruction, 4, 1, "ESC : exit");
    mvwprintw(instruction, 6, 51, "Credit: Federico Marra");
    wrefresh(instruction);
}
*/



void Display::printFooterEn() {
    mvwprintw(instruction,  0, 1, "| INSTRUCTION | TIMER | CLOCK | CHRONOMETER |");
    mvwprintw(instruction,  1, 1, "|    exit     |  ESC  |  ESC  |     ESC     |");
    mvwprintw(instruction,  2, 1, "|    start    |   S   |       |      V      |");
    mvwprintw(instruction,  3, 1, "|    stop     |   T   |       |    SPACE    |");
    mvwprintw(instruction,  4, 1, "|    reset    |   R   |       |      B      |");
    mvwprintw(instruction,  5, 1, "| change view |   W   |   K   |      N      |");
    mvwprintw(instruction,  6, 1, "|    +  1 s   |  UP   |       |             |");
    mvwprintw(instruction,  7, 1, "|    -  1 s   | DOWN  |       |             |");
    mvwprintw(instruction,  8, 1, "|    + 10 s   | RIGHT |       |             |");
    mvwprintw(instruction,  9, 1, "|    - 10 s   | LEFT  |       |             |");
    mvwprintw(instruction, 10, 1, "|    +  1 m   |   1   |       |             |");
    mvwprintw(instruction, 11, 1, "|    +  2 m   |   2   |       |             |");
    mvwprintw(instruction, 12, 1, "|    -  1 m   |   7   |       |             |");
    mvwprintw(instruction, 13, 1, "|    +  1 h   |   6   |       |             |");
    mvwprintw(instruction, 14, 1, "|    -  1 h   |   0   |       |             |");
    mvwprintw(instruction, 16, 51, "Credit: Federico Marra");
    wrefresh(instruction);
}

void Display::printFooterIt() {
    mvwprintw(instruction,  0, 1, "| ISTRUZIONI | TIMER | OROLOGIO | CRONOMETRO |");
    mvwprintw(instruction,  1, 1, "|    uscita     |  ESC  |  ESC  |     ESC     |");
    mvwprintw(instruction,  2, 1, "|    inizio    |   S   |       |      V      |");
    mvwprintw(instruction,  3, 1, "|    ferma     |   T   |       |    SPACE    |");
    mvwprintw(instruction,  4, 1, "|    resetta    |   R   |       |      B      |");
    mvwprintw(instruction,  5, 1, "| cambia vista |   W   |   K   |      N      |");
    mvwprintw(instruction,  6, 1, "|    +  1 s   |  UP   |       |             |");
    mvwprintw(instruction,  7, 1, "|    -  1 s   | DOWN  |       |             |");
    mvwprintw(instruction,  8, 1, "|    + 10 s   | RIGHT |       |             |");
    mvwprintw(instruction,  9, 1, "|    - 10 s   | LEFT  |       |             |");
    mvwprintw(instruction, 10, 1, "|    +  1 m   |   1   |       |             |");
    mvwprintw(instruction, 11, 1, "|    +  2 m   |   2   |       |             |");
    mvwprintw(instruction, 12, 1, "|    -  1 m   |   7   |       |             |");
    mvwprintw(instruction, 13, 1, "|    +  1 h   |   6   |       |             |");
    mvwprintw(instruction, 14, 1, "|    -  1 h   |   0   |       |             |");
    mvwprintw(instruction, 16, 51, "Crediti: Federico Marra");
    wrefresh(instruction);
}