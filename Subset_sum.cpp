#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int target;
    cout << "Enter target sum: ";
    cin >> target;

    // DP table
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Base case
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {

            // Exclude current element
            dp[i][j] = dp[i - 1][j];

            // Include current element
            if (arr[i - 1] <= j) {
                dp[i][j] = dp[i][j] ||
                           dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    // Check result
    if (!dp[n][target]) {
        cout << "\nSubset with given sum does NOT exist.\n";
        return 0;
    }

    cout << "\nSubset with given sum exists.\n";

    // Backtracking to find selected elements
    vector<int> subset;

    int i = n;
    int j = target;

    while (i > 0 && j > 0) {

        // If value came from upper row,
        // current element not included
        if (dp[i - 1][j]) {
            i--;
        }

        // Otherwise element was included
        else {
            subset.push_back(arr[i - 1]);

            j = j - arr[i - 1];
            i--;
        }
    }

    cout << "\nSelected elements are:\n";

    for (int x : subset) {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}
