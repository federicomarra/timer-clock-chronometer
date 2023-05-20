# timer-clock-chronometer

<!-- all the badges are imported from img.shields.io -->
[![C++](https://img.shields.io/badge/-c++-black?logo=c%2B%2B&)](https://en.cppreference.com/w/)
[![GTests](https://img.shields.io/badge/tests-14%20passed%2C%200%20failed-important?logo=google&logoColor=white)](test)
[![GitHub last release](https://img.shields.io/github/v/release/federicomarra/timer-clock-chronometer)](https://github.com/federicomarra/timer-clock-chronometer/releases)
[![GitHub last commit](https://img.shields.io/github/last-commit/federicomarra/timer-clock-chronometer?cacheSeconds=3600)](https://github.com/federicomarra/timer-clock-chronometer/commits/master)
[![GitHub repo size](https://img.shields.io/github/repo-size/federicomarra/timer-clock-chronometer)](https://github.com/federicomarra/timer-clock-chronometer/tree/master)
[![License MIT](https://img.shields.io/github/license/federicomarra/timer-clock-chronometer?color=3da639)](https://opensource.org/licenses/MIT)

## Unifi Programmation C++ Laboratory
#### C++ Clock program with Timer and Chronometer features, all with multiple visualisation formats.

## Index
#### [How to run on your Terminal](#how-to-run-on-your-terminal-1)
#### [Instructions](#instructions-1)
#### [Timer](#timer-1)
#### [Clock](#clock-1)
#### [Chronometer](#chronometer-1)
#### [Tests](#tests-1)
#### [License](#mit-license)

## How to run on your Terminal

### Mac and Linux
1. Download [timer-clock-chronometer](cmake-build-debug/timer-clock-chronometer) trough terminal and run it.
2. Open your terminal, using `cd` navigate trough your folders until the one with the file just downloaded.
3. Run this instruction to make the file executable:
```
chmod +x timer-clock-chronometer
```
4. Open the file that now will be executable.

### Windows
1. Download the entire [project](https://github.com/federicomarra/timer-clock-chronometer/archive/refs/heads/master.zip)
2. Unzip it and open the project folder in your C++ IDE.
3. Build the project pressing `F7` or `Build` button.
4. Open [timer-clock-chronometer.exe](cmake-build-debug/timer-clock-chronometer.exe) in the folder named [cmake-build-debug](cmake-build-debug) trough terminal and run it.

## Instructions

Press `L` to switch language between English and Italian.

Press `ESC` to exit.

Press `H` to help.

|  INSTRUCTIONS   | TIMER | CLOCK | CHRONOMETER |
|:---------------:|:-----:|:-----:|:-----------:|
|      start      |  `S`  |       |     `V`     |
|      stop       |  `T`  |       |   `SPACE`   |
|      reset      |  `R`  |       |     `B`     |
|   change view   |  `W`  |  `K`  |     `N`     |
|     +  1 s      |  `↑`  |       |             |
|     -  1 s      |  `↓`  |       |             |
|     + 10 s      |  `→`  |       |             |
|     - 10 s      |  `←`  |       |             |
|     +  1 m      |  `1`  |       |             |
|     -  1 m      |  `2`  |       |             |
|     +  5 m      |  `5`  |       |             |
|     +  1 h      |  `6`  |       |             |
|     -  1 h      |  `7`  |       |             |

## Timer

### Setting

The timer is set by default to 10 s, but it can be changed by pressing the keys `↑` or `↓`, to add or subtract 1 second, `→` or `←` to add or subtract 10 seconds.

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

All the unit tests are in the folder [`test`](test) and are written using [`Google Test library`](https://github.com/google/googletest).

In  the **Test** files we use `TEST(TestSuiteName, TestName)` to make a single test.
<br>
Otherwise, in the **Test Fixture** files it is possible to make multiple tests using the same data configuration by `TEST_F(TestFixtureName, TestName)`.

In the test files [`TimerTest.cpp`](#timertest-in-timertestcpp), [`TimerTestFixture.cpp`](#timertestfixture-in-timertestfixturecpp), 
[`ChronoTest.cpp`](#chronotest-in-chronotestcpp) and [`ChronoTestFixture.cpp`](#chronotestfixture-in-chronotestfixturecpp) files we make use of:

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

All the documentation use is in [`primer.md`](test/lib/googletest/docs/primer.md) and [`advanced.md`](test/lib/googletest/docs/advanced.md) files.


### TimerTest in [`TimerTest.cpp`](test/TimerTest.cpp)

#### 1. TimerDefaultConstructor
This test checks if the default constructor initializes correctly to 0 seconds.

#### 2. TimerCorrectWorking
This test checks if an object of the class `Timer` works correctly with a duration set to 5 seconds.


### TimerTestFixture in [`TimerTestFixture.cpp`](test/TimerTestFixture.cpp)

##### 3. TimerDuration
At first this test checks that the duration can't be set less than or equal to zero seconds (-10:0) and can be set greater to zero seconds (1:10),
then it checks if the duration can be set correctly to 5 seconds.
It starts the timer and then try to set the duration to 10 seconds, but the timer can't be set while running, so it trows `bad_function_call` exception.
Then it iss checked if after 1 second the duration is less than 5 seconds (set before), and if the duration is greater than 0 seconds.

##### 4. StartTimer
This test checks at first that the timer can't start if not set before. 
Then the timer is set to 5 seconds, and the variable `start` is set to hte value of start of the timer.
After the timer starts, it is checked that the timer is running and that the variable `start` is less than the current time.    

##### 5. StopTimer

##### 6. ResetRunningTimer

##### 7. ResetNonRunningTimer

##### 8. TimerStringDuration


### ChronoTest in [`ChronoTest.cpp`](test/ChronoTest.cpp)


##### 9. ChronoDefaultConstructor

##### 10. ChronoCorrectWorking


### ChronoTestFixture in [`ChronoTestFixture.cpp`](test/ChronoTestFixture.cpp)


##### 11. StartChrono

##### 12. StopChrono

##### 13. ResetRunningChrono

##### 14. ResetNonRunningChrono


### Run of all the tests in [`runAllTest.cpp`](test/runAllTest.cpp)

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