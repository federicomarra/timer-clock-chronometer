#include "gtest/gtest.h"
#include "../Chronometer.h"

TEST(ChronoTest, Constructor){
    Chronometer c;

    ASSERT_FALSE(c.isRunning());
    ASSERT_EQ(c.getTime(), 0);
    ASSERT_EQ(c.getMemoryString(), "---");
}