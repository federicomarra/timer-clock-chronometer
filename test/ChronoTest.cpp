#include "gtest/gtest.h"
#include "../Chronometer.h"
#include <thread>
#include <functional>

TEST(ChronoTest, ChronoDefaultConstructor) {
    Chronometer c;

    ASSERT_FALSE(c.isRunning());
    ASSERT_EQ(c.getTime(), 0);
    ASSERT_EQ(c.getMemoryString(), "---");
    ASSERT_EQ(c.getViewMode(), 0);
    ASSERT_EQ(c.getTimeString(), "0:00:00.0");
}

TEST(ChronoTest, ChronoCorrectWorking) {
    Chronometer c;
    c.startChrono();
    std::this_thread::sleep_for(2s);
    c.stopChrono();

    ASSERT_NEAR(c.getTime(), 20, 0.5);

    c.startChrono();
    std::this_thread::sleep_for(1s);
    c.stopChrono();

    ASSERT_NEAR(c.getTime(), 30, 0.5);

    c.startChrono();
    c.resetChrono();
    std::this_thread::sleep_for(1s);
    c.stopChrono();

    ASSERT_NEAR(c.getTime(), 10, 0.5);
}