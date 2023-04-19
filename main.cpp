#include <unistd.h>
#include <ncurses.h>

#include <iostream>
#include <thread>
#include "Timer.h"
#include "Chronometer.h"
#include "Clock.h"
#include "Display.h"
#include <string>

using namespace std;

int main() {
    Display d;
    d.init();

    return 0;
}