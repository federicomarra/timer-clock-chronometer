#include "gtest/gtest.h"
#include "../Chronometer.h"
#include <thread>
#include <functional>

TEST(ChronoTest, ChronoDefaultConstructor) {
    Chronometer c;

    ASSERT_FALSE(c.isRunning());
    ASSERT_EQ(c.getTime(), 0);
    ASSERT_EQ(c.getMemory(), 0);
    ASSERT_EQ(c.getMemoryString(), "---");
    ASSERT_EQ(c.getViewMode(), 0);
}

TEST(ChronoTest, ChronoCorrectWorking) {
    Chronometer c;
    c.startChrono();
    std::this_thread::sleep_for(2s);
    c.stopChrono();

    ASSERT_NEAR(c.getTime(), 20, 1);
    ASSERT_EQ(c.getMemory(), 0);

    c.startChrono();
    std::this_thread::sleep_for(1s);
    c.stopChrono();

    ASSERT_NEAR(c.getTime(), 30, 1);    // 20 + 10 = 30 ds
    ASSERT_EQ(c.getMemory(), 0);

    c.resetChrono();

    ASSERT_EQ(c.getTime(), 0);
    ASSERT_EQ(c.getMemory(), 0);

    c.startChrono();
    std::this_thread::sleep_for(4s);
    c.resetChrono();
    std::this_thread::sleep_for(2s);
    c.stopChrono();

    ASSERT_NEAR(c.getTime(), 20, 1);
    ASSERT_NEAR(c.getMemory(), 40, 1);
}