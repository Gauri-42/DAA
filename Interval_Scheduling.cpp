#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to store intervals
struct Interval {
    int start;
    int end;
};

// Comparator function to sort by finishing time
bool compare(Interval a, Interval b) {
    return a.end < b.end;
}

int main() {
    int n;

    cout << "Enter number of intervals: ";
    cin >> n;

    vector<Interval> intervals(n);

    cout << "Enter start and end time of each interval:\n";
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].start >> intervals[i].end;
    }

    // Step 1: Sort intervals by ending time
    sort(intervals.begin(), intervals.end(), compare);

    vector<Interval> selected;

    // Step 2: Select first interval
    selected.push_back(intervals[0]);

    int lastEnd = intervals[0].end;

    // Step 3: Select non-overlapping intervals
    for (int i = 1; i < n; i++) {
        if (intervals[i].start >= lastEnd) {
            selected.push_back(intervals[i]);
            lastEnd = intervals[i].end;
        }
    }

    // Output selected intervals
    cout << "\nSelected Intervals:\n";
    for (auto interval : selected) {
        cout << "[" << interval.start << ", "
             << interval.end << "]\n";
    }

    cout << "\nMaximum number of non-overlapping intervals = "
         << selected.size() << endl;

    return 0;
}