#include <string>
#include "Clock.h"
#include <ctime>

using namespace std;

Clock::Clock() {
    viewMode = 0;
    ita = false;
}

string Clock::getTime() const {
    time_t now = time(0);
    tm date = *localtime(&now);
    string s, temp;
    switch (viewMode) {
        case 0:     // vm 0:  hh:mm:ss
            temp = to_string(date.tm_hour);
            s += (temp.length() == 1 ? ('0' + temp) : temp);
            temp = to_string(date.tm_min);
            s += ":" + (temp.length() == 1 ? ('0' + temp) : temp);
            temp = to_string(date.tm_sec);
            s += ":" + (temp.length() == 1 ? ('0' + temp) : temp);
            break;

        case 1:     // vm 1:  hh:mm AM/PM
            temp = to_string(date.tm_hour % 12);
            s += (temp.length() == 1 ? ('0' + temp) : temp);
            temp = to_string(date.tm_min);
            s += ":" + (temp.length() == 1 ? ('0' + temp) : temp);
            s += (date.tm_hour < 12 ? " AM" : " PM");
            break;

        default:    // vm 2:  hh:mm
            temp = to_string(date.tm_hour);
            s += (temp.length() == 1 ? ('0' + temp) : temp);
            temp = to_string(date.tm_min);
            s += ":" + (temp.length() == 1 ? ('0' + temp) : temp);
    }
    return s;
}

string Clock::getDate() const {
    time_t now = time(0);
    tm date = *localtime(&now);
    string s, temp;
    switch (viewMode) {
        case 0:   // vm 0:  wdd dd mmm yyyy
            switch (date.tm_wday) {     // week day
                case 0:
                    s += (ita ? "Dom" : "Sun");
                    break;
                case 1:
                    s += (ita ? "Lun" : "Mon");
                    break;
                case 2:
                    s += (ita ? "Mar" : "Tue");
                    break;
                case 3:
                    s += (ita ? "Mer" : "Wed");
                    break;
                case 4:
                    s += (ita ? "Gio" : "Thu");
                    break;
                case 5:
                    s += (ita ? "Ven" : "Fri");
                    break;
                case 6:
                    s += (ita ? "Sab" : "Sat");
                    break;
            }
            temp = to_string(date.tm_mday);
            s += ' ' + (temp.length() == 1 ? ('0' + temp) : temp) + ' ';
            switch (date.tm_mon) {      // month
                case 0:
                    s += (ita ? "Gen" : "Jan");
                    break;
                case 1:
                    s += "Feb";
                    break;
                case 2:
                    s += "Mar";
                    break;
                case 3:
                    s += "Apr";
                    break;
                case 4:
                    s += (ita ? "Mag" : "May");
                    break;
                case 5:
                    s += (ita ? "Giu" : "Jun");
                    break;
                case 6:
                    s += (ita ? "Lug" : "Jul");
                    break;
                case 7:
                    s += (ita ? "Ago" : "Aug");
                    break;
                case 8:
                    s += (ita ? "Set" : "Sep");
                    break;
                case 9:
                    s += (ita ? "Ott" : "Oct");
                    break;
                case 10:
                    s += "Nov";
                    break;
                case 11:
                    s += (ita ? "Dic" : "Dec");
                    break;
            }
            s += ' ' + to_string(1900 + date.tm_year);
            break;

        case 1:    // vm 1:  yyyy-mm-dd
            s += to_string(1900 + date.tm_year);
            temp = to_string(date.tm_mon + 1);
            s += "-" + (temp.length() == 1 ? ('0' + temp) : temp);
            temp = to_string(date.tm_mday);
            s += "-" + (temp.length() == 1 ? ('0' + temp) : temp);
            break;

        default:    // vm 2:  dd/mm/yyyy
            temp = to_string(date.tm_mday);
            s += (temp.length() == 1 ? ('0' + temp) : temp);
            temp = to_string(date.tm_mon + 1);
            s += "/" + (temp.length() == 1 ? ('0' + temp) : temp);
            s += "/" + to_string(1900 + date.tm_year);
    }
    return s;
}

int Clock::getViewMode() const {
    return viewMode;
}

void Clock::setViewMode(int vm, bool it) {
    viewMode = vm % 3;
    ita = it;
}