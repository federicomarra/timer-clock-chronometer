#include <string>
#include "Clock.h"
#include <time.h>

using namespace std;

Clock::Clock() {
    viewMode = 2;
}

string Clock::getTime() const {
    time_t now = time(0);
    tm date = *localtime(&now);
    string s, temp;
    switch(viewMode){
        case 2:
            temp = to_string(date.tm_hour);
            s += (temp.length() == 1 ? ('0'+temp) : temp);
            temp = to_string(date.tm_min);
            s += ":" + (temp.length() == 1 ? ('0'+temp) : temp);
            temp = to_string(date.tm_sec);
            s += " :" + (temp.length() == 1 ? ('0'+temp) : temp);
            break;
        default:
            temp = to_string(date.tm_hour);
            s += (temp.length() == 1 ? ('0'+temp) : temp);
            temp = to_string(date.tm_min);
            s += ":" + (temp.length() == 1 ? ('0'+temp) : temp);
    }
    return s;
}

string Clock::getDate() const {
    time_t now = time(0);
    tm date = *localtime(&now);
    string s, temp;
    switch(viewMode){
        case 1:
            s += "'" + to_string(date.tm_year%100);
            temp = to_string(date.tm_mday);
            s += "/" + (temp.length() == 1 ? ('0'+temp) : temp);
            temp = to_string(date.tm_mon+1);
            s += "/" + (temp.length() == 1 ? ('0'+temp) : temp);
            break;
        case 2:
            switch (date.tm_wday){
                case 0:
                    s += "Dom";
                    break;
                case 1:
                    s += "Lun";
                    break;
                case 2:
                    s += "Mar";
                    break;
                case 3:
                    s += "Mer";
                    break;
                case 4:
                    s += "Gio";
                    break;
                case 5:
                    s += "Ven";
                    break;
                case 6:
                    s += "Sab";
                    break;
            }
            temp = to_string(date.tm_mday);
            s += ' ' + (temp.length() == 1 ? ('0'+temp) : temp) + ' ';
            switch (date.tm_mon){
                case 0:
                    s += "Gen";
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
                    s += "Mag";
                    break;
                case 5:
                    s += "Giu";
                    break;
                case 6:
                    s += "Lug";
                    break;
                case 7:
                    s += "Ago";
                    break;
                case 8:
                    s += "Set";
                    break;
                case 9:
                    s += "Ott";
                    break;
                case 10:
                    s += "Nov";
                    break;
                case 11:
                    s += "Dic";
                    break;
            }
            s += ' ' + to_string(1900 + date.tm_year);
            break;
        default:
            temp = to_string(date.tm_mday);
            s += temp.length() == 1 ? ('0'+temp) : temp;
            temp = to_string(date.tm_mon+1);
            s += "/" + (temp.length() == 1 ? ('0'+temp) : temp);
            s += "/'" + to_string(date.tm_year%100);
    }
    return s;
}

int Clock::getViewMode() const {
    return viewMode;
}

void Clock::setViewMode(int vm) {
    viewMode = vm%3;
}

