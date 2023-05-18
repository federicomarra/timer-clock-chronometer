#include "Timer.h"
#include <chrono>
#include <cmath>
#include <functional>
#include <string>

using namespace std;
using namespace std::chrono;

const int Timer::secPerDay = 60 * 60 * 24;
const int Timer::secPerHour = 60 * 60;
const int Timer::secPerMin = 60;

Timer::Timer() {
    start = steady_clock::now();
    duration = ::duration < int > ::zero();
    running = false;
    viewMode = 0;
}

const time_point<steady_clock> &Timer::getStart() const {
    return start;
}

int Timer::getDuration() {
    if (!running) {
        return (int) round(duration.count() / 1000);
    } else {
        time_point<steady_clock> now = steady_clock::now();
        float r = ((duration - duration_cast<milliseconds>(now - start)).count() / 1000.f);
        int remaining = r >= 0 ? (int) ceil(r) : (int) floor(r);
        if (remaining < 0) {
            remaining = 0;
        }
        return remaining;
    }
}

bool Timer::setDuration(const unsigned int seconds) {
    if (!running) {
        if (seconds > 0 && seconds <= secPerDay) {
            duration = ::duration < int, milli > (seconds * 1000);
            return true;
        }
        return false;
    }
    throw bad_function_call();
}

bool Timer::isRunning() const {
    return running;
}

bool Timer::startTimer() {
    if (duration != ::duration < int > ::zero()) {
        if (!running || getDuration() < 0) {
            start = steady_clock::now();
            running = true;
            return true;
        }
        return false;
    }
    throw bad_function_call();  //Before starting timer you need to set duration
}

bool Timer::stopTimer() {
    if (running) {
        time_point<steady_clock> now = steady_clock::now();
        running = false;
        ::duration<int, milli> remaining = duration - duration_cast<seconds>(now - start);
        if (remaining.count() > 0) {
            duration = remaining;
            return true;
        }
        return false;
    }
    return false;
}

void Timer::resetTimer() {      // it resets but also stops
    start = steady_clock::now();
    stopTimer();
}

string Timer::getDurationString() {
    int hours, minutes;
    int seconds = getDuration();
    string s, temp;

    hours = seconds / secPerHour;
    minutes = (seconds - hours * secPerHour) / secPerMin;
    seconds = seconds - hours * secPerHour - minutes * secPerMin;

    switch (viewMode) {
        case 0:     // vm 0:  h:mm:ss
            s = to_string(hours);
            s += ":";
            s += ((temp = to_string(minutes)).length() == 2) ? temp : "0" + temp;
            s += ":";
            s += ((temp = to_string(seconds)).length() == 2) ? temp : "0" + temp;
            break;

        case 1:     // vm 1:  h h, mm m, ss s
            if (hours) {
                s += to_string(hours) + " h, ";
            }
            if (hours || minutes) {
                s += to_string(minutes) + " m, ";
            }
            s += to_string(seconds) + " s";
            if (s.length() % 2 == 0 && getDuration() < 60) {
                s.replace(s.find(" s"), 2, "  s");
            }

            break;

        default:    // vm 2:  ssssss s
            s = to_string(getDuration()) + " s";
            if (s.length() % 2 == 0) {
                s.replace(s.find(" s"), 2, "  s");
            }
    }
    return s;
}

int Timer::getViewMode() const {
    return viewMode;
}

void Timer::setViewMode(int vm) {
    viewMode = vm % 3;
}
