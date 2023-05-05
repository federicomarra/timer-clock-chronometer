#include "gtest/gtest.h"

#include "../Timer.h"
#include <thread>
#include <functional>

class TimerSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        t = Timer();
    }

    Timer t;
};

TEST_F(TimerSuite, Duration){
    ASSERT_FALSE(t.setDuration(0));

    int testDuration = 5;

    ASSERT_TRUE(t.setDuration(testDuration));
    ASSERT_EQ(t.getDuration(), testDuration);

    t.startTimer();
    std::this_thread::sleep_for(1s);

    ASSERT_THROW(t.setDuration(10), bad_function_call);
    ASSERT_LT(t.getDuration(), testDuration);
    ASSERT_GT(t.getDuration(), 0);
}

TEST_F(TimerSuite, StartTimer) {
    ASSERT_THROW(t.startTimer(), bad_function_call);
    t.setDuration(5);
    time_point<steady_clock> start = steady_clock::now();

    ASSERT_TRUE(t.startTimer());
    ASSERT_TRUE(t.isRunning());
    ASSERT_GE(t.getStart(), start);
    ASSERT_LE(t.getStart(), steady_clock::now());
    ASSERT_FALSE(t.startTimer());
}

TEST_F(TimerSuite, StopTimer){
    t.setDuration(20);
    int initialDuration = t.getDuration();
    t.startTimer();
    std::this_thread::sleep_for(1s);

    ASSERT_TRUE(t.stopTimer());
    ASSERT_FALSE(t.isRunning());
    ASSERT_LT(t.getDuration(), initialDuration);
    ASSERT_GT(t.getDuration(), 0);
    ASSERT_FALSE(t.stopTimer());

    t.setDuration(1);
    t.startTimer();
    std::this_thread::sleep_for(2s);
    ASSERT_FALSE(t.stopTimer());
}

TEST_F(TimerSuite, ResetRunningTimer){
    t.setDuration(5);
    t.startTimer();
    time_point<steady_clock> originalStart = t.getStart();
    t.resetTimer();

    ASSERT_GT(t.getStart(), originalStart);
}

TEST_F(TimerSuite, ResetNonRunningTimer){
    t.setDuration(5);
    t.startTimer();
    std::this_thread::sleep_for(1s);
    t.stopTimer();
    time_point<steady_clock> originalStart = t.getStart();
    t.resetTimer();

    ASSERT_GT(t.getStart(), originalStart);
}

TEST_F(TimerSuite, StringDuration){
    t.setViewMode(1);
    t.setDuration(1);
    ASSERT_EQ(t.getDurationString(), "1 s");
    t.setDuration(60+1);
    ASSERT_EQ(t.getDurationString(), "1 m, 1  s");
    t.setDuration(60*60+1);
    ASSERT_EQ(t.getDurationString(), "1 h, 0 m, 1 s");
    t.setDuration(60*60+1);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "1:00:01");
}