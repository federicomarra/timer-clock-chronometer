# timer-clock-chronometer

<!-- all the badges are imported from img.shields.io -->
[![C++](https://img.shields.io/badge/-c++-black?logo=c%2B%2B&)](https://cplusplus.com)
[![GTests](https://img.shields.io/badge/tests-14%20passed%2C%200%20failed-important?logo=google&logoColor=white)](test)
[![GitHub last release](https://img.shields.io/github/v/release/federicomarra/timer-clock-chronometer)](https://github.com/federicomarra/timer-clock-chronometer/releases)
[![GitHub last commit](https://img.shields.io/github/last-commit/federicomarra/timer-clock-chronometer?cacheSeconds=3600)](https://github.com/federicomarra/timer-clock-chronometer/commits/master)
[![GitHub repo size](https://img.shields.io/github/repo-size/federicomarra/timer-clock-chronometer)](https://github.com/federicomarra/timer-clock-chronometer/tree/master)
[![License MIT](https://img.shields.io/github/license/federicomarra/timer-clock-chronometer?color=3da639)](https://opensource.org/licenses/MIT)

## Unifi Programmation C++ Laboratory

#### C++ Clock program with Timer and Chronometer features, all with multiple visualisation formats.

## Index

[How to run on your Terminal](#how-to-run-on-your-terminal)

[Instructions](#instructions)

[Timer](#timer)

[Clock](#clock)

[Chronometer](#chronometer)

[Tests](#tests)

[License](#mit-license)

## How to run on your Terminal

### Mac and Linux ![macOS](https://img.shields.io/badge/macOS-000000?&logo=macos) ![Linux](https://img.shields.io/badge/Linux-FCC624?&logo=linux&logoColor=black)

1. Download [timer-clock-chronometer](cmake-build-debug/timer-clock-chronometer) trough terminal and run it.
2. Open your terminal, using `cd` navigate through your folders until the one with the file just downloaded.
3. To make the file executable run this instruction:

```
chmod +x timer-clock-chronometer
```

4. Open the file that now will be executable.

### Windows ![Windows](https://img.shields.io/badge/Windows-0078D6?&logo=windows&logoColor=white)

1. Download the
   entire [repository](https://github.com/federicomarra/timer-clock-chronometer/archive/refs/heads/master.zip)
2. Unzip it and open the project folder in your C++ IDE.
3. Build the project pressing `F7` or `Build` button.
4. Open [timer-clock-chronometer.exe](cmake-build-debug/timer-clock-chronometer.exe) in the folder
   named [cmake-build-debug](cmake-build-debug) trough terminal and run it.

## Instructions

Press `L` to switch language between English and Italian.

Press `ESC` to exit.

Press `H` to help.

| INSTRUCTIONS | TIMER | CLOCK | CHRONOMETER |
|:------------:|:-----:|:-----:|:-----------:|
|    start     |  `S`  |       |     `V`     |
|     stop     |  `T`  |       |   `SPACE`   |
|    reset     |  `R`  |       |     `B`     |
| change view  |  `W`  |  `K`  |     `N`     |
|    +  1 s    |  `↑`  |       |             |
|    -  1 s    |  `↓`  |       |             |
|    + 10 s    |  `→`  |       |             |
|    - 10 s    |  `←`  |       |             |
|    +  1 m    |  `1`  |       |             |
|    -  1 m    |  `2`  |       |             |
|    +  5 m    |  `5`  |       |             |
|    +  1 h    |  `6`  |       |             |
|    -  1 h    |  `7`  |       |             |

## Timer

### Setting

The timer is set by default to 10 s, but it can be changed by pressing the keys `↑` or `↓`, to add or subtract 1
second, `→` or `←` to add or subtract 10 seconds.

Press `1` or `2` to add or subtract 1 minute, `5` to add 5 minutes,  `6` or `7` to add or subtract 1 hour.

### Start, Stop and Reset

The timer can be started by pressing `S`, stopped by pressing `T` and reset by pressing `R`.

### Formats

The timer can be displayed in different formats by pressing `W`.

The default format is **0**, but you can switch between these following formats:

| View mode |         Time          |  Time example   |
|:---------:|:---------------------:|:---------------:|
|   **0**   |     `h`:`mm`:`ss`     |     1:23:45     |
|   **1**   | `h` h, `mm` m, `ss` s | 1 h, 23 m, 45 s |
|   **2**   |       `sssss` s       |     5025 s      |

## Clock

### Formats

The timer can be displayed in different formats by pressing `K`.

The default format is **0**, but you can switch between these following formats:

| View mode |          Date           |       Time        |  Date example   | Time example |
|:---------:|:-----------------------:|:-----------------:|:---------------:|:------------:|
|   **0**   | `wdd` `dd` `mmm` `yyyy` |  `hh`:`mm`:`ss`   | Tue 02 May 2023 |   14:03:24   |
|   **1**   |    `yyyy`-`mm`-`dd`     | `hh`:`mm` AM / PM |   2023-05-02    |   02:03 PM   |
|   **2**   |    `dd`/`mm`/`yyyy`     |     `hh`:`mm`     |   02/05/2023    |    14:03     |

## Chronometer

### Start, Stop, Reset and Lap

The chronometer can be started by pressing `V`, stopped by pressing `SPACE` and reset by pressing `B` (if stopped).

If the chronometer is running, you can add a lap by pressing `B`.

### Formats

The timer can be displayed in different formats by pressing `N`.

The default format is **0**, but you can switch between these following formats:

| View mode |         Time          |  Time example   |
|:---------:|:---------------------:|:---------------:|
|   **0**   |  `hh`:`mm`:`ss`.`ds`  |   1:23:45.39    |
|   **1**   | `h` h, `mm` m, `ss` s | 1 h, 23 m, 45 s |
|   **2**   |    `sssss`.`ds` s     |    5025.39 s    |

## Tests

|    Test Suite     | Tests passed | Tests failed | Tests total |
|:-----------------:|:------------:|:------------:|:-----------:|
|     TimerTest     |      2       |      0       |      2      |
| TimerTestFixture  |      6       |      0       |      6      |
|    ChronoTest     |      2       |      0       |      2      |
| ChronoTestFixture |      4       |      0       |      4      |
|     **Total**     |      14      |      0       |     14      |

All the unit tests are in the folder [`test`](test) and are written
using [`Google Test library`](https://github.com/google/googletest).

In the **Test** files we use `TEST(TestSuiteName, TestName)` to make a single test.
<br>
Otherwise, in the **Test Fixture** files it is possible to make multiple tests using the same data configuration
by `TEST_F(TestFixtureName, TestName)`.

In the test
files [`TimerTest.cpp`](#timertest-in-timertestcpp), [`TimerTestFixture.cpp`](#timertestfixture-in-timertestfixturecpp),
[`ChronoTest.cpp`](#chronotest-in-chronotestcpp)
and [`ChronoTestFixture.cpp`](#chronotestfixture-in-chronotestfixturecpp) files we make use of:

|               Fatal assertion               |         Test passed if         |
|:-------------------------------------------:|:------------------------------:|
|          `ASSERT_TRUE(condition);`          |       condition == true        |
|         `ASSERT_FALSE(condition);`          |       condition == false       |
|       `ASSERT_EQ(actual, expected);`        |       actual == expected       |
|       `ASSERT_NE(actual, expected);`        |       actual != expected       |
|          `ASSERT_LT(val1, val2);`           |          val1 < val2           |
|          `ASSERT_LE(val1, val2);`           |          val1 ≤ val2           |
|          `ASSERT_GT(val1, val2);`           |          val1 > val2           |
|          `ASSERT_GE(val1, val2);`           |          val1 ≥ val2           |
| `ASSERT_NEAR(actual, expected, tolerance);` | actual == expected ± tolerance |
|    `ASSERT_THROW(function, exception);`     |   function throws exception    |

All the documentation use is in [`primer.md`](test/lib/googletest/docs/primer.md)
and [`advanced.md`](test/lib/googletest/docs/advanced.md) files.

### TimerTest in [`TimerTest.cpp`](test/TimerTest.cpp)

#### 1. TimerDefaultConstructor

This test checks if the default constructor initializes correctly `running` to false, `duration` to 0 seconds
and `viewMode` to 0.

#### 2. TimerCorrectWorking

This test checks if the timer works correctly with a duration set to 5 seconds.

### TimerTestFixture in [`TimerTestFixture.cpp`](test/TimerTestFixture.cpp)

##### 3. TimerDuration

At first this test checks that the duration can't be set less than or equal to zero seconds (from -10 to 0) and can be
set greater to zero seconds (from 1 to 10), then it checks if the duration can be set correctly to 5 seconds.
It starts the timer and then try to set the duration to 10 seconds, but the timer can't be set while running, so it
trows `bad_function_call` exception.
Then it iss checked if after 1 second the duration is less than 5 seconds (set before), and if the duration is greater
than 0 seconds.

##### 4. StartTimer

This test checks at first that the timer can't start if not set before.
Then the timer is set to 5 seconds, and the `start` variable is set to the current time.
After the timer starts, it is checked that the timer is running and that the starting time is greater or equal to
the `start` variable and less or equal to the current time.
In the end it is checked that a running timer can't be started again.

##### 5. StopTimer

This test checks at first that the timer can't stop if not set before.
Then the timer is set to 20 seconds, and the `initialDuration` variable is set to the current duration set before.
After the timer starts and is stopped after 1 second, it is checked that the timer is not running and that the duration
of the time is less than the `initialDuration` variable and greater than 0.
In the end it is checked that a non-running timer can't be stopped again.

##### 6. ResetRunningTimer

This test checks at first set the timer to 5 seconds, makes it start and checks that is running.
Then the `originalStart` variable is set to the timer start time. The timer is reset and it is checked that the timer
start time is greater than the `originalStart` variable and that timer is not running anymore (because when a running
timer reset, it also stops).

##### 7. ResetNonRunningTimer

This test checks at first set the timer to 5 seconds, makes it start and stops it after 1 second.
Then the `originalStart` variable is set to the timer start time. The timer resets and it is checked that the timer
start time is greater than the `originalStart` variable.

##### 8. TimerStringDuration

This test checks if the duration string obtained from the function `getDurationString()` is equal to the different
durations in all the three different `viewMode`: `0`, `1`and `2`.<br>
It is checked for these durations: _1s_, _10s_, _1m_, _10m_, _1h 1s_, _1h 1m 1s_, _1h 23m 45s_, _24h_.

### ChronoTest in [`ChronoTest.cpp`](test/ChronoTest.cpp)

##### 9. ChronoDefaultConstructor

This test checks if the default constructor initializes correctly `running` to false, chronometer time to 0 seconds,
memory time to 0 and `viewMode` to 0.

##### 10. ChronoCorrectWorking

This test checks if the chronometer works correctly. It is maked start and after 2s stop. Then it checks if the time is
near 2s (with a tolerance of 1 ds) and memory is empty.<br>
After it is make start again and stopped after 1s. Then it checks if the time is near 3s (2s + 1s) and memory is still
empty.<br>
In the end the chronometer resets and it is checked if the time is 0s and memory is empty. Then it starts and while
running after 4s it is reset (if running it laps), and after 2s it is stopped. It is checked if the time is near 2s
(with a tolerance of 1 ds) and memory is not empty but 4s.

### ChronoTestFixture in [`ChronoTestFixture.cpp`](test/ChronoTestFixture.cpp)

##### 11. StartChrono

This test checks at first a variable called `start` is set to current time, then when the chronometer is made start,
`running` is true and cannot be started again.<br>
Then it is checked that the chronometer starting time is greater than the `start` variable and less than the current
time, it is also checked if the memory is empty.<br>
In the end it is checked that chronometer time is non-zero.

##### 12. StopChrono



##### 13. ResetRunningChrono



##### 14. ResetNonRunningChrono



### Run of all the tests in [`runAllTest.cpp`](test/runAllTests.cpp)

In this file we run all the tests of the previous files.

## MIT License

Copyright © 2023 [federicomarra](https://github.com/federicomarra)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.