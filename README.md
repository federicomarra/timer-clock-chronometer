# timer-clock-chronometer

![GitHub repo size](https://img.shields.io/github/repo-size/federicomarra/timer-clock-chronometer?color=55&label=project%20size&logo=55&logoColor=55%20B)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Programmation Laboratory  C++ Unifi

##### C++ Clock program with Timer and Chronometer features, all with multiple visualisation formats.

# Instructions

Press  `L`  to switch language between English and Italian.

Press `ESC` to exit.

Press `H`  to help.

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

# Timer

### Setting

The timer is set by default to 10 s, but it can be changed by pressing the keys `↑` or `↓`, to add or subtract 1 second, `→` or `←` to add or subtract 10 seconds.

Press `1` or `2` to add or subtract 1 minute, `5` to add 5 minutes,  `6` or `7` to add or subtract 1 hour.
 
### Start, Stop and Reset

The timer can be started by pressing `S`, stopped by pressing `T` and reset by pressing `R`.

### Formats

The timer can be displayed in different formats by pressing `W`.

The default format is **0**, but you can switch between these following formats:

| View Mode |         Time          |  Time Example   |
|:---------:|:---------------------:|:---------------:|
|   **0**   |     `h`:`mm`:`ss`     |     1:23:45     |
|   **1**   | `h` h, `mm` m, `ss` s | 1 h, 23 m, 45 s |
|   **2**   |       `sssss` s       |     5025 s      |

# Clock

### Formats

The timer can be displayed in different formats by pressing `K`.

The default format is **0**, but you can switch between these following formats:

| View Mode |          Date           |       Time        |  Date Example   | Time Example |
|:---------:|:-----------------------:|:-----------------:|:---------------:|:------------:|
|   **0**   | `wdd` `dd` `mmm` `yyyy` |  `hh`:`mm`:`ss`   | Tue 02 May 2023 |   14:03:24   |
|   **1**   |    `yyyy`-`mm`-`dd`     | `hh`:`mm` AM / PM |   2023-05-02    |   02:03 PM   |
|   **2**   |     `dd`/`mm`/`yyyy`    |     `hh`:`mm`     |   02/05/2023    |    14:03     |

# Chronometer

### Start, Stop, Reset and Lap

The chronometer can be started by pressing `V`, stopped by pressing `SPACE` and reset by pressing `B` (if stopped).

If the chronometer is running, you can add a lap by pressing `B`.

### Formats

The timer can be displayed in different formats by pressing `N`.

The default format is **0**, but you can switch between these following formats:

| View Mode |         Time          |  Time Example   |
|:---------:|:---------------------:|:---------------:|
|   **0**   |  `hh`:`mm`:`ss`.`DS`  |   1:23:45.39    |
|   **1**   | `h` h, `mm` m, `ss` s | 1 h, 23 m, 45 s |
|   **2**   |     `sssss`.`DS` s    |    5025.39 s    |

## MIT License

MIT License

Copyright (c) 2023 federicomarra

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