# Timetable Generator (C++)

A simple console-based timetable generator written in C++. It takes the number
of working days per week, periods per day, and a list of subjects with their
required periods per week, then generates a weekly timetable avoiding the same
subject repeating in consecutive periods on the same day.

## Build

```bash
g++ -std=c++14 -Wall -o timetable.exe src/main.cpp
```

## Run

```bash
./timetable.exe
```

You will be prompted for:
- Number of working days per week
- Number of periods per day
- Number of subjects, and periods per week for each

The program prints the generated timetable grid and an allocation summary.
