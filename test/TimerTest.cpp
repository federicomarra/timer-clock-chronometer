#include  "gtest/gtest.h"

#include "../Timer.h"

TEST(TimerTest, TimerDefaultConstructor) {
    Timer t;
    ASSERT_FALSE(t.isRunning());
    ASSERT_EQ(t.getDuration(), 0);
}

TEST(TimerTest, TimerCorrectWorking){
    Timer t;
    t.setDuration(5);

    time_point<steady_clock> start = steady_clock::now();
    t.startTimer();

    while(t.getDuration() > 0){}

    time_point<steady_clock> end = steady_clock::now();

    ASSERT_NEAR(duration_cast<milliseconds>(end-start).count(), 5*1000, 125);
}