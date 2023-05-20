#include "gtest/gtest.h"
#include "../Timer.h"
#include <thread>
#include <functional>

class TimerTestFixture : public ::testing::Test {

protected:
    void SetUp() override {
        t = Timer();
    }

    Timer t;
};

TEST_F(TimerTestFixture, TimerDuration) {
    int testDuration;
    for (testDuration = -10; testDuration <= 0; testDuration++) {
        ASSERT_FALSE(t.setDuration(testDuration));       // ASSERT_FALSE(condition) -> OK IF condition == false
    }
    for (testDuration = 1; testDuration <= 10; testDuration++) {
        ASSERT_TRUE(t.setDuration(testDuration));        // ASSERT_TRUE(condition) -> OK IF condition == true
        ASSERT_EQ(t.getDuration(), testDuration);        // ASSERT_EQ(actual, expected) -> OK IF actual == expected
    }

    testDuration = 5;
    t.setDuration(testDuration);
    ASSERT_EQ(t.getDuration(), testDuration);

    t.startTimer();
    std::this_thread::sleep_for(1s);

    ASSERT_THROW(t.setDuration(10),
                 bad_function_call);  // ASSERT_THROW(function, exception) -> OK IF function throws exception
    ASSERT_LT(t.getDuration(), testDuration);            // ASSERT_LT(val1, val2) -> OK IF val1 < val2
    ASSERT_GT(t.getDuration(), 0);                       // ASSERT_GT(val1, val2) -> OK IF val1 > val2
}

TEST_F(TimerTestFixture, StartTimer) {
    ASSERT_THROW(t.startTimer(), bad_function_call);
    t.setDuration(5);
    time_point<steady_clock> start = steady_clock::now();

    ASSERT_TRUE(t.startTimer());
    ASSERT_TRUE(t.isRunning());
    ASSERT_GE(t.getStart(), start);                      // ASSERT_GE(val1, val2) -> OK IF val1 ≥ val2
    ASSERT_LE(t.getStart(), steady_clock::now());        // ASSERT_LE(val1, val2) -> OK IF val1 ≤ val2
    ASSERT_FALSE(t.startTimer());
}

TEST_F(TimerTestFixture, StopTimer) {
    ASSERT_FALSE(t.isRunning());
    ASSERT_FALSE(t.stopTimer());
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

TEST_F(TimerTestFixture, ResetRunningTimer) {
    t.setDuration(5);
    t.startTimer();

    ASSERT_TRUE(t.isRunning());

    time_point<steady_clock> originalStart = t.getStart();
    t.resetTimer();

    ASSERT_GT(t.getStart(), originalStart);
    ASSERT_FALSE(t.isRunning());
}

TEST_F(TimerTestFixture, ResetNonRunningTimer) {
    ASSERT_FALSE(t.isRunning());
    t.setDuration(5);
    t.startTimer();
    std::this_thread::sleep_for(1s);
    t.stopTimer();
    time_point<steady_clock> originalStart = t.getStart();
    t.resetTimer();
    ASSERT_GT(t.getStart(), originalStart);
}

TEST_F(TimerTestFixture, TimerStringDuration) {
    t.setDuration(1);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "0:00:01");
    t.setViewMode(1);
    ASSERT_EQ(t.getDurationString(), "1 s");
    t.setViewMode(2);
    ASSERT_EQ(t.getDurationString(), "1 s");

    t.setDuration(10);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "0:00:10");
    t.setViewMode(1);
    ASSERT_EQ(t.getDurationString(), "10  s");
    t.setViewMode(2);
    ASSERT_EQ(t.getDurationString(), "10  s");

    t.setDuration(60 + 1);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "0:01:01");
    t.setViewMode(1);
    ASSERT_EQ(t.getDurationString(), "1 m, 1 s");
    t.setViewMode(2);
    ASSERT_EQ(t.getDurationString(), "61  s");

    t.setDuration(5 * 60);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "0:05:00");
    t.setViewMode(1);
    ASSERT_EQ(t.getDurationString(), "5 m, 0 s");
    t.setViewMode(2);
    ASSERT_EQ(t.getDurationString(), "300 s");

    t.setDuration(60 * 60 + 1);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "1:00:01");
    t.setViewMode(1);
    ASSERT_EQ(t.getDurationString(), "1 h, 0 m, 1 s");
    t.setViewMode(2);
    ASSERT_EQ(t.getDurationString(), "3601  s");

    t.setDuration(60 * 60 + 60 + 1);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "1:01:01");
    t.setViewMode(1);
    ASSERT_EQ(t.getDurationString(), "1 h, 1 m, 1 s");
    t.setViewMode(2);
    ASSERT_EQ(t.getDurationString(), "3661  s");

    t.setDuration(60 * 60 + 23 * 60 + 45);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "1:23:45");
    t.setViewMode(1);
    ASSERT_EQ(t.getDurationString(), "1 h, 23 m, 45 s");
    t.setViewMode(2);
    ASSERT_EQ(t.getDurationString(), "5025  s");

    t.setDuration(60 * 60 * 24);
    t.setViewMode(0);
    ASSERT_EQ(t.getDurationString(), "24:00:00");
    t.setViewMode(1);
    ASSERT_EQ(t.getDurationString(), "24 h, 0 m, 0 s");
    t.setViewMode(2);
    ASSERT_EQ(t.getDurationString(), "86400 s");
}