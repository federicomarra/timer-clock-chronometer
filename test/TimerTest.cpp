#include  "gtest/gtest.h"
#include "../Timer.h"

TEST(TimerTest, TimerDefaultConstructor) {      // TEST 1
    Timer t;
    ASSERT_FALSE(t.isRunning());    // ASSERT_FALSE(condition) -> OK IF condition == false
    ASSERT_EQ(t.getDuration(), 0);  // ASSERT_EQ(actual, expected) -> OK IF actual == expected
    ASSERT_EQ(t.getViewMode(), 0);
}

TEST(TimerTest, TimerCorrectWorking) {          // TEST 2
    Timer t;
    ASSERT_TRUE(t.setDuration(5));

    time_point<steady_clock> start = steady_clock::now();
    ASSERT_TRUE(t.startTimer());

    while (t.getDuration() > 0) {}

    time_point<steady_clock> end = steady_clock::now();

    ASSERT_NEAR(duration_cast<milliseconds>(end - start).count(), 5 * 1000, 125);   // ASSERT_NEAR(actual, expected, tolerance) -> OK IF actual == expected ± tolerance
}