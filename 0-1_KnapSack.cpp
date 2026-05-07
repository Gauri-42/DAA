#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n), value(n);

    // Input weights
    cout << "Enter weights:\n";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    // Input values
    cout << "Enter values:\n";
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    int W;
    cout << "Enter capacity of knapsack: ";
    cin >> W;

    // DP table initialization (all 0)
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {

            int exclude = dp[i - 1][w];

            int include = 0;
            if (weight[i - 1] <= w) {
                include = value[i - 1] + dp[i - 1][w - weight[i - 1]];
            }

            dp[i][w] = max(include, exclude);
        }
    }

    // Print maximum value
    cout << "\nMaximum value = " << dp[n][W] << endl;

    // 🔥 Backtracking to find selected items
    vector<int> selected;
    int i = n, w = W;

    while (i > 0 && w > 0) {

        // If item was included
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i - 1);   // store index

            w = w - weight[i - 1];       // reduce capacity
            i = i - 1;
        }
        else {
            i = i - 1;   // skip item
        }
    }

    // Reverse to get correct order
    reverse(selected.begin(), selected.end());

    // Print selected items
    cout << "\nSelected items (index, weight, value):\n";
    for (int idx : selected) {
        cout << idx << " -> "
             << weight[idx] << " "
             << value[idx] << endl;
    }

    return 0;
}