#include "gtest/gtest.h"
#include "../Chronometer.h"
#include <thread>
#include <functional>

class ChronoTestFixture : public ::testing::Test {

protected:
    void SetUp() override {
        c = Chronometer();
    }

    Chronometer c;
};

TEST_F(ChronoTestFixture, StartChrono) {                    // TEST 11
    time_point<steady_clock> start = steady_clock::now();

    ASSERT_TRUE(c.startChrono());
    ASSERT_TRUE(c.isRunning());
    ASSERT_FALSE(c.startChrono());
    ASSERT_GT(c.getStart(), start);
    ASSERT_LT(c.getStart(), steady_clock::now());
    ASSERT_EQ(c.getMemory(), 0);    // memory empty
    ASSERT_EQ(c.getMemoryString(), "---");

    std::this_thread::sleep_for(1s);

    ASSERT_NEAR(c.getTime(), 10, 1);
}

TEST_F(ChronoTestFixture, StopChrono) {                     // TEST 12
    c.startChrono();
    std::this_thread::sleep_for(1s);

    ASSERT_TRUE(c.stopChrono());
    ASSERT_FALSE(c.stopChrono());
    ASSERT_FALSE(c.isRunning());
    ASSERT_GT(c.getTime(), 0);
    ASSERT_NEAR(c.getTime(), 10, 1);
    ASSERT_EQ(c.getMemory(), 0);    // memory empty
    ASSERT_EQ(c.getMemoryString(), "---");
}

TEST_F(ChronoTestFixture, ResetRunningChrono) {             // TEST 13
    c.startChrono();
    std::this_thread::sleep_for(1s);
    time_point<steady_clock> reset = steady_clock::now();

    ASSERT_TRUE(c.isRunning());
    c.resetChrono();
    ASSERT_TRUE(c.isRunning());

    std::this_thread::sleep_for(2s);
    ASSERT_EQ(c.getTime(), 20);
    ASSERT_NE(c.getMemory(), 0);
    ASSERT_NE(c.getMemoryString(), "---");
    ASSERT_EQ(c.getMemory(), 10);
    c.setViewMode(0);
    ASSERT_EQ(c.getMemoryString(), "0:00:01.0");
    c.setViewMode(1);
    ASSERT_EQ(c.getMemoryString(), "1.0 s");
    c.setViewMode(2);
    ASSERT_EQ(c.getMemoryString(), "1.0 s");

    ASSERT_GT(c.getStart(), reset);
    ASSERT_TRUE(c.isRunning());
}

TEST_F(ChronoTestFixture, ResetNonRunningChrono) {          // TEST 14
    c.startChrono();
    std::this_thread::sleep_for(1s);
    c.resetChrono();
    std::this_thread::sleep_for(1s);
    ASSERT_NE(c.getTime(), 0);
    ASSERT_NE(c.getMemory(), 0);
    ASSERT_NE(c.getMemoryString(), "---");
    c.stopChrono();

    ASSERT_FALSE(c.isRunning());
    c.resetChrono();
    ASSERT_FALSE(c.isRunning());

    ASSERT_EQ(c.getTime(), 0);
    ASSERT_EQ(c.getMemory(), 0);
    ASSERT_EQ(c.getMemoryString(), "---");
    ASSERT_FALSE(c.isRunning());
}

