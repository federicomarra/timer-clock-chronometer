#include "Chronometer.h"
#include <chrono>
#include <math.h>
#include <string>

using namespace std;
using namespace std::chrono;

const int Chronometer::secPerDay = 60 * 60 * 24;
const int Chronometer::secPerHour = 60 * 60;
const int Chronometer::secPerMin = 60;

Chronometer::Chronometer() {
    start = steady_clock::now();
    stored = ::duration<int>::zero();
    running = false;
    memory = ::duration<int>::zero();
    viewMode = 2;
}

const time_point<steady_clock> &Chronometer::getStart() const {
    return start;
}

string Chronometer::getTimeString() const {
    return stringify(getTime());
}

int Chronometer::getTime() const {
    int decisecs;
    if (running) {
        decisecs = (int) round((duration_cast<milliseconds>(steady_clock::now() - start) + stored).count() / 100.f);
    } else {
        decisecs = (int) round(stored.count() / 100.f);
    }
    return decisecs;
}

string Chronometer::getMemoryString() const {
    if (memory != duration<int>::zero()) {
        int decisecs = (int) round(memory.count() / 100.f);
        return stringify(decisecs);
    } else {
        return "---";
    }
}

bool Chronometer::isRunning() const {
    return running;
}

bool Chronometer::startChrono() {
    if (!running) {
        start = steady_clock::now();
        running = true;
        return true;
    }
    return false;
}

bool Chronometer::stopChrono() {
    if (running) {
        time_point<steady_clock> now = steady_clock::now();
        running = false;
        stored = stored + duration_cast<milliseconds>(now - start);
        return true;
    }
    return false;
}

void Chronometer::resetChrono() {
    time_point<steady_clock> now = steady_clock::now();
    stored = ::duration<int>::zero();
    if (running) {
        memory = duration_cast<milliseconds>(now - start);
        start = now;
    } else {
        memory = duration<int>::zero();
    }
}

string Chronometer::stringify(int deciseconds) const {
    int hours, minutes, seconds, decisecs;
    string s, temp;

    hours = deciseconds / (secPerHour * 10);
    minutes = (deciseconds - hours * secPerHour * 10) / (secPerMin * 10);
    seconds = (deciseconds - hours * secPerHour * 10 - minutes * secPerMin * 10) / 10;
    decisecs = deciseconds % 10;

    switch (viewMode) {
        case 1:
            if (hours) {
                s += to_string(hours) + " h, ";
            }
            if (hours || minutes) {
                s += to_string(minutes) + " m, ";
            }
            s += to_string(seconds) + "." + to_string(decisecs) + " s";
            break;
        case 2:
            s = to_string(hours);
            s += ":";
            s += ((temp = to_string(minutes)).length() == 2) ? temp : "0" + temp;
            s += ":";
            s += ((temp = to_string(seconds)).length() == 2) ? temp : "0" + temp;
            s += "." + to_string(decisecs);
            break;
        default:
            s = to_string(deciseconds / 10) + "." + to_string(deciseconds % 10) + " s";
    }
    if (s.length() % 2 == 0) {
        s.replace(s.find(" s"), 2, "  s");
    }
    return s;
}

int Chronometer::getViewMode() const {
    return viewMode;
}

void Chronometer::setViewMode(int vm) {
    viewMode = vm % 3;
}
