#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Subject {
    string name;
    int periodsPerWeek;
    int assigned = 0;
};

int main() {
    int workingDays, periodsPerDay, numSubjects;

    cout << "=== Timetable Generator ===\n\n";

    cout << "Enter number of working days per week: ";
    cin >> workingDays;

    cout << "Enter number of periods per day: ";
    cin >> periodsPerDay;

    int totalSlots = workingDays * periodsPerDay;

    cout << "Enter number of subjects: ";
    cin >> numSubjects;

    vector<Subject> subjects(numSubjects);
    int totalPeriodsRequested = 0;

    for (int i = 0; i < numSubjects; i++) {
        cout << "\nSubject " << (i + 1) << " name: ";
        cin >> subjects[i].name;
        cout << "Periods per week for " << subjects[i].name << ": ";
        cin >> subjects[i].periodsPerWeek;
        totalPeriodsRequested += subjects[i].periodsPerWeek;
    }

    if (totalPeriodsRequested != totalSlots) {
        cout << "\nWarning: total requested periods (" << totalPeriodsRequested
             << ") do not match total available slots (" << totalSlots
             << " = " << workingDays << " days x " << periodsPerDay << " periods).\n";
        cout << "The generator will fill as many periods as possible and leave the rest as \"Free\".\n";
    }

    vector<vector<string>> table(workingDays, vector<string>(periodsPerDay, "Free"));

    vector<string> dayNames = {"Monday", "Tuesday", "Wednesday", "Thursday",
                                "Friday", "Saturday", "Sunday"};

    for (int d = 0; d < workingDays; d++) {
        for (int p = 0; p < periodsPerDay; p++) {
            sort(subjects.begin(), subjects.end(), [](const Subject &a, const Subject &b) {
                int remA = a.periodsPerWeek - a.assigned;
                int remB = b.periodsPerWeek - b.assigned;
                return remA > remB;
            });

            string lastSubject = (p > 0) ? table[d][p - 1] : "";
            bool placed = false;

            for (auto &s : subjects) {
                if (s.assigned < s.periodsPerWeek && s.name != lastSubject) {
                    table[d][p] = s.name;
                    s.assigned++;
                    placed = true;
                    break;
                }
            }

            if (!placed) {
                for (auto &s : subjects) {
                    if (s.assigned < s.periodsPerWeek) {
                        table[d][p] = s.name;
                        s.assigned++;
                        placed = true;
                        break;
                    }
                }
            }
        }
    }

    cout << "\n\n===== Generated Timetable =====\n\n";

    cout << "Day/Period\t";
    for (int p = 0; p < periodsPerDay; p++) {
        cout << "P" << (p + 1) << "\t";
    }
    cout << "\n";

    for (int d = 0; d < workingDays; d++) {
        string label = (d < (int)dayNames.size()) ? dayNames[d] : ("Day" + to_string(d + 1));
        cout << label << "\t";
        for (int p = 0; p < periodsPerDay; p++) {
            cout << table[d][p] << "\t";
        }
        cout << "\n";
    }

    cout << "\n===== Subject Allocation Summary =====\n";
    for (auto &s : subjects) {
        cout << s.name << ": " << s.assigned << " / " << s.periodsPerWeek << " periods placed\n";
    }

    return 0;
}
