#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Structure for an item
struct Item {
    int value;
    int weight;
};

// Comparator function to sort by value/weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;

    return r1 > r2;
}

int main() {
    int n;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
    }

    int capacity;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // Step 1: Sort items by value/weight ratio
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;

    cout << "\nSelected items:\n";

    // Step 2: Pick items greedily
    for (int i = 0; i < n; i++) {

        // If whole item can be taken
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;

            cout << "Took full item -> "
                 << "Value: " << items[i].value
                 << ", Weight: " << items[i].weight << endl;
        }

        // Take fraction of item
        else {
            double fraction = (double)capacity / items[i].weight;

            totalValue += items[i].value * fraction;

            cout << "Took "
                 << fixed << setprecision(2)
                 << fraction * 100
                 << "% of item -> "
                 << "Value: " << items[i].value
                 << ", Weight: " << items[i].weight << endl;

            capacity = 0;
            break;
        }
    }

    cout << "\nMaximum value in knapsack = "
         << fixed << setprecision(2)
         << totalValue << endl;

    return 0;
}
