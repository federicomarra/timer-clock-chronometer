#include "gtest/gtest.h"

#include "../Chronometer.h"
#include <thread>
#include <functional>

class ChronoSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        c = Chronometer();
    }

    Chronometer c;
};

TEST_F(ChronoSuite, StartChrono){
    time_point<steady_clock> start = steady_clock::now();

    ASSERT_TRUE(c.startChrono());
    ASSERT_TRUE(c.isRunning());
    ASSERT_FALSE(c.startChrono());
    ASSERT_GT(c.getStart(), start);
    ASSERT_LT(c.getStart(), steady_clock::now());
    ASSERT_EQ(c.getMemoryString(), "---");

    std::this_thread::sleep_for(1s);

    ASSERT_NE(c.getTime(), 0);
}

TEST_F(ChronoSuite, StopChrono){
    c.startChrono();
    std::this_thread::sleep_for(1s);

    ASSERT_TRUE(c.stopChrono());
    ASSERT_FALSE(c.stopChrono());
    ASSERT_FALSE(c.isRunning());
    ASSERT_NE(c.getTime(), 0);
    ASSERT_EQ(c.getMemoryString(), "---");
}

TEST_F(ChronoSuite, ResetRunningChrono){
    c.startChrono();
    std::this_thread::sleep_for(1s);
    time_point<steady_clock> reset = steady_clock::now();
    c.resetChrono();

    ASSERT_NE(c.getMemoryString(), "0.0 s");
    ASSERT_GT(c.getStart(), reset);
    ASSERT_TRUE(c.isRunning());
}

TEST_F(ChronoSuite, ResetNonRunningChrono){
    c.startChrono();
    std::this_thread::sleep_for(1s);
    c.resetChrono();
    std::this_thread::sleep_for(1s);
    c.stopChrono();
    c.resetChrono();

    ASSERT_EQ(c.getTime(), 0);
    ASSERT_EQ(c.getMemoryString(), "---");
    ASSERT_FALSE(c.isRunning());
}

