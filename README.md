# timer-clock-chronometer

[![GitHub Repo Size](https://img.shields.io/github/repo-size/federicomarra/timer-clock-chronometer?color=20B2AA)](https://github.com/federicomarra/timer-clock-chronometer/tree/master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Unifi Programmation C++ Laboratory

##### C++ Clock program with Timer and Chronometer features, all with multiple visualisation formats.

# How to run on your Terminal

### Mac and Linux
1. Download [timer-clock-chronometer](cmake-build-debug%2Ftimer-clock-chronometer) trough terminal and run it.
2. Open your terminal, using `cd` navigate trough your folders until the one with the file just downloaded.
3. Run the instruction `chmod +x timer-clock-chronometer` to make the file executable (<a onclick="copyToClipboard('chmod +x timer-clock-chronometer')">click here to copy</a>).

<script>
   function copyToClipboard(text) {
   var tempInput = document.createElement("textarea");
   tempInput.value = text;
   document.body.appendChild(tempInput);
   tempInput.select();
   document.execCommand("copy");
   document.body.removeChild(tempInput);
   }
   </script>

4. Open the file that now will be executable.

### Windows
1. Download the entire [project](https://github.com/federicomarra/timer-clock-chronometer/archive/refs/heads/master.zip)
2. Unzip it and open the project folder in your C++ IDE.
3. Build the project pressing `F7` or `Build` button.
4. Open [timer-clock-chronometer.exe](cmake-build-debug%2Ftimer-clock-chronometer.exe) in the folder named [cmake-build-debug](cmake-build-debug) trough terminal and run it.

# Instructions

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

# Timer

### Setting

The timer is set by default to 10 s, but it can be changed by pressing the keys `↑` or `↓`, to add or subtract 1 second, `→` or `←` to add or subtract 10 seconds.

Press `1` or `2` to add or subtract 1 minute, `5` to add 5 minutes,  `6` or `7` to add or subtract 1 hour.
 
### Start, Stop and Reset

The timer can be started by pressing `S`, stopped by pressing `T` and reset by pressing `R`.

### Formats

The timer can be displayed in different formats by pressing `W`.

The default format is **0**, but you can switch between these following formats:

| View Mode |         Time          |  Time example   |
|:---------:|:---------------------:|:---------------:|
|   **0**   |     `h`:`mm`:`ss`     |     1:23:45     |
|   **1**   | `h` h, `mm` m, `ss` s | 1 h, 23 m, 45 s |
|   **2**   |       `sssss` s       |     5025 s      |

# Clock

### Formats

The timer can be displayed in different formats by pressing `K`.

The default format is **0**, but you can switch between these following formats:

| View Mode |          Date           |       Time        |  Date example   | Time example |
|:---------:|:-----------------------:|:-----------------:|:---------------:|:------------:|
|   **0**   | `wdd` `dd` `mmm` `yyyy` |  `hh`:`mm`:`ss`   | Tue 02 May 2023 |   14:03:24   |
|   **1**   |    `yyyy`-`mm`-`dd`     | `hh`:`mm` AM / PM |   2023-05-02    |   02:03 PM   |
|   **2**   |    `dd`/`mm`/`yyyy`     |     `hh`:`mm`     |   02/05/2023    |    14:03     |

# Chronometer

### Start, Stop, Reset and Lap

The chronometer can be started by pressing `V`, stopped by pressing `SPACE` and reset by pressing `B` (if stopped).

If the chronometer is running, you can add a lap by pressing `B`.

### Formats

The timer can be displayed in different formats by pressing `N`.

The default format is **0**, but you can switch between these following formats:

| View Mode |         Time          |  Time example   |
|:---------:|:---------------------:|:---------------:|
|   **0**   |  `hh`:`mm`:`ss`.`ds`  |   1:23:45.39    |
|   **1**   | `h` h, `mm` m, `ss` s | 1 h, 23 m, 45 s |
|   **2**   |    `sssss`.`ds` s     |    5025.39 s    |

## MIT License

MIT License

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