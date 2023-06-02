#include "Display.h"
#include <functional>
#include <ncurses.h>
#include <locale.h>     // setlocale for Unicode Codify

Display::Display() {
    timer = Timer();
    clock = Clock();
    chrono = Chronometer();
    terminate = false;
    help = false;
    ita = false;
    unicode = false;
}

void Display::init() {
    initscr();

    keypad(stdscr, true);
    nodelay(stdscr, true);

    timer.setDuration(10);

    termWidth = getmaxx(stdscr);
    termHeight = getmaxy(stdscr);
    height = 9;
    width = 25;
    instructionHeight = height * 2 - 1;
    instructionWidth = width * 3 - 2;

    timerWin = newwin(height, width, (termHeight - height * 2 - 2) / 2, (termWidth - width * 3 + 2) / 2);
    clockWin = newwin(height, width, (termHeight - height * 2 - 2) / 2, (termWidth - width * 3 + 2) / 2 + width - 1);
    chronoWin = newwin(height, width, (termHeight - height * 2 - 2) / 2, (termWidth - width * 3 + 2) / 2 + 2 * width - 2);
    instruction = newwin(instructionHeight, instructionWidth, (termHeight - height * 2 - 2) / 2 + height, (termWidth - width * 3 + 2) / 2);
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
    werase(instruction);

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
    mvwprintw(chronoWin, 4, (width - chrTime.length()) / 2, &chrTime[0]);
    mvwprintw(chronoWin, 6, (width - chrMem.length()) / 2, &chrMem[0]);

    if (help) {
        printHelp();
    } else {
        if (!ita) {
            mvwprintw(instruction, 1, width / 3, "Press  L  to switch language between English and Italian");
            mvwprintw(instruction, 2, width / 3, "Press ESC to exit");
            mvwprintw(instruction, 3, width / 3, "Press  H  to help");
            if (getmaxy(stdscr) < height * 2 - 2 + termHeight / 2) {    // if terminal too small
                mvwprintw(instruction, 4, width / 3, "Expand vertically the terminal to see the help");
            }
        } else {
            mvwprintw(instruction, 1, width / 3, "Premi  L  per cambiare lingua tra Inglese e Italiano");
            mvwprintw(instruction, 2, width / 3, "Premi ESC per uscire");
            mvwprintw(instruction, 3, width / 3, "Premi  H  per l'aiuto");
            if (getmaxy(stdscr) < height * 2 - 2 + termHeight / 2) {    // termHeight < endWin=heightWin+beginWin
                mvwprintw(instruction, 4, width / 3, "Espandi verticalmente il terminale per vedere l'aiuto");
            }
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

    switch (ch) {

        // GENERAL
        case 27:        // ESC key ~ exit
            terminate = true;
            break;
        case 'l':       // switch language eng-ita
            switchIta();       // update display language
            break;
        case 'h':       // show help
            if (!help) {
                help = true;
                printHelp();
            } else {
                help = false;
            }
            break;
        /*
        case 'u':       // switch unicode
            (unicode ? unicode = false : unicode = true);
            break;
        */
            // TIMER
        case 's':       // start timer
            try {
                timer.startTimer();
            }
            catch (bad_function_call e) {
                printf("Timer not set");
                beep();
            }
            break;
        case 't':       // stop timer
            timer.stopTimer();
            break;
        case 'r':       // reset timer (it also stops it)
            timer.resetTimer();
            break;
        case 'w':       // change timer view mode
            timer.setViewMode(timer.getViewMode() + 1);
            break;
        case KEY_UP:    // +1s
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 1);
            }
            break;
        case KEY_DOWN:  // -1s
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 1);
            }
            break;
        case KEY_RIGHT: // +10s
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 10);
            }
            break;
        case KEY_LEFT:  // -10s
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 10);
            }
            break;
        case '1':       // +1m
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 60);
            }
            break;
        case '2':       // -1m
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 60);
            }
            break;
        case '5':       // +5m
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 300);
            }
            break;
        case '6':       // +1h
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() + 3600);
            }
            break;
        case '7':       // -1h
            if (!timer.isRunning()) {
                timer.setDuration(timer.getDuration() - 3600);
            }
            break;

            // CHRONO
        case 'v':       // start chrono
            chrono.startChrono();
            break;
        case ' ':       // stop chrono
            chrono.stopChrono();
            break;
        case 'b':       // reset chrono (if running it makes a lap, it does not also stop)
            chrono.resetChrono();
            break;
        case 'n':       // change chrono view mode
            chrono.setViewMode(chrono.getViewMode() + 1);
            break;

            // CLOCK
        case 'k':       // change clock view mode
            clock.setViewMode(clock.getViewMode() + 1);
            break;

            // if a non-recognized key is pressed
        default:
            break;
    }
}


void Display::printHelp() {
    // HELP TEXT
    if (!ita) {
        mvwprintw(instruction, 1, 1, "  INSTRUCTIONS   |      TIMER      |      CLOCK      |   CHRONOMETER   |");
        mvwprintw(instruction, 3, 1, "      start      |        S        |                 |        V        |");
        mvwprintw(instruction, 4, 1, "      stop       |        T        |                 |      SPACE      |");
        mvwprintw(instruction, 5, 1, "      reset      |        R        |                 |        B        |");
        mvwprintw(instruction, 6, 1, "   change view   |        W        |        K        |        N        |");
    } else {
        mvwprintw(instruction, 1, 1, "   ISTRUZIONI    |      TIMER      |     OROLOGIO    |   CRONOMETRO    |");
        mvwprintw(instruction, 3, 1, "     inizio      |        S        |                 |        V        |");
        mvwprintw(instruction, 4, 1, "      ferma      |        T        |                 |      SPAZIO     |");
        mvwprintw(instruction, 5, 1, "     resetta     |        R        |                 |        B        |");
        mvwprintw(instruction, 6, 1, "  cambia vista   |        W        |        K        |        N        |");
    }
    mvwprintw(instruction,     7, 1, "     +  1 s      |                 |                 |                 |");
    mvwprintw(instruction,     8, 1, "     -  1 s      |                 |                 |                 |");
    mvwprintw(instruction,     9, 1, "     + 10 s      |                 |                 |                 |");
    mvwprintw(instruction,    10, 1, "     - 10 s      |                 |                 |                 |");
    mvwprintw(instruction,    11, 1, "     +  1 m      |        1        |                 |                 |");
    mvwprintw(instruction,    12, 1, "     -  1 m      |        2        |                 |                 |");
    mvwprintw(instruction,    13, 1, "     +  5 m      |        5        |                 |                 |");
    mvwprintw(instruction,    14, 1, "     +  1 h      |        6        |                 |                 |");
    mvwprintw(instruction,    15, 1, "     -  1 h      |        7        |");

    // BORDERS
    wborder(instruction, 0, 0, 0, 0, 0, 0, 0, 0);

    mvwaddch(instruction, 0, width * 3 / 4, ACS_TTEE);      // draw top central cross
    mvwaddch(instruction, 0, width * 3 / 4 * 2, ACS_TTEE);
    mvwaddch(instruction, 0, width * 3 / 4 * 3, ACS_TTEE);

    for (int j = 1; j < instructionHeight - 2; j++) {
        if (j != 2) {                                       // draw vertical lines
            mvwaddch(instruction, j, width * 3 / 4, ACS_VLINE);
            mvwaddch(instruction, j, width * 3 / 4 * 2, ACS_VLINE);
            mvwaddch(instruction, j, width * 3 / 4 * 3, ACS_VLINE);
        } else {                                             // draw crux
            mvwaddch(instruction, j, width * 3 / 4, ACS_PLUS);
            mvwaddch(instruction, j, width * 3 / 4 * 2, ACS_PLUS);
            mvwaddch(instruction, j, width * 3 / 4 * 3, ACS_PLUS);
        }
    }
    mvwaddch(instruction, instructionHeight - 2, width * 3 / 4, ACS_VLINE);
    mvwaddch(instruction, instructionHeight - 2, width * 3 / 4 * 2, ACS_VLINE);
    // draw low central cross
    mvwaddch(instruction, instructionHeight - 1, width * 3 / 4, ACS_BTEE);
    mvwaddch(instruction, instructionHeight - 1, width * 3 / 4 * 2, ACS_BTEE);
    mvwaddch(instruction, instructionHeight - 3, width * 3 / 4 * 3, ACS_BTEE);
    for (int i = 1; i < instructionWidth - 1; i++) {
        if (i != width * 3 / 4 && i != width * 3 / 4 * 2 && i != width * 3 / 4 * 3) {
            mvwaddch(instruction, 2, i, ACS_HLINE);         // draw horizontal lines
            if (i > width * 3 / 4 * 2)
                mvwaddch(instruction, instructionHeight - 3, i, ACS_HLINE);
        } else {
            mvwaddch(instruction, 2, i, ACS_PLUS);
        }
    }
    mvwaddch(instruction, 2, 0, ACS_LTEE);
    mvwaddch(instruction, 2, instructionWidth - 1, ACS_RTEE);
    mvwaddch(instruction, instructionHeight - 3, width * 3 / 4 * 2, ACS_LTEE);
    mvwaddch(instruction, instructionHeight - 3l, instructionWidth - 1, ACS_RTEE);


    // draw arrows
    if (!unicode) {                      // no unicode arrows
        mvwaddch(instruction, 7, 27, ACS_UARROW);
        mvwaddch(instruction, 8, 27, ACS_DARROW);
        mvwaddch(instruction, 9, 27, ACS_RARROW);
        mvwaddch(instruction, 10, 27, ACS_LARROW);
    } else {                            // unicode arrows
        setlocale(LC_ALL, "");
        mvwaddch(instruction, 7, 27, L'\u2191');       // upArrow ↑
        mvwaddch(instruction, 8, 27, L'\u2193');       // downArrow ↓
        mvwaddch(instruction, 9, 27, L'\u2192');       // rightArrow →
        mvwaddch(instruction, 10, 27, L'\u2190');      // leftArrow ←
    }

    // credits
    mvwprintw(instruction, 15, 43, (!ita ? "Credits: Federico Marra " : "Crediti: Federico Marra "));

    // refresh
    wrefresh(instruction);
}


void Display::switchIta() {
    ita = !ita;
    clock.switchIta();      // update clock language
}