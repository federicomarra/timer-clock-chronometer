#ifndef ELABORATOTIMER_CLOCK_H
#define ELABORATOTIMER_CLOCK_H

#include <string>

using namespace std;

class Clock {
public:
    Clock();

    string getTime() const;
    string getDate() const;

    int getViewMode() const;
    void setViewMode(int vm);

private:
    int viewMode;
};


#endif //ELABORATOTIMER_CLOCK_H
