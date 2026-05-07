#include <iostream>
#include <vector>
using namespace std;

void printArray(vector<int> &arr, string name) {
    cout << name << " : ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

void countingSort(vector<int> &arr) {
    int n = arr.size();

    // Find maximum element
    int maxVal = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }

    // Create count array
    vector<int> count(maxVal + 1, 0);

    // Store count of each element
    for(int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    cout << "\nAfter counting frequency:" << endl;
    printArray(count, "C");

    // Modify count array (cumulative sum)
    for(int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    cout << "\nAfter cumulative sum:" << endl;
    printArray(count, "C");
    cout << "\n";

    // Output array
    vector<int> output(n);

    // Build output array (traverse from end for stability)
    for(int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;

        cout << "After placing element " << arr[i] << " :" << endl;
        printArray(output, "B");
        printArray(count, "C");
        cout << endl;
    }

    // Copy back to original array
    arr = output;
}

int main() {
    vector<int> arr; int n;
    cout<<"Enter the size of array :";
    cin>>n;

    arr.resize(n);
    cout<<"Enter the elements :";
    for(int i =0; i<n;i++){
        cin>>arr[i];
    }
    
    countingSort(arr);

    cout << "\nFinal Sorted Array: ";
    for(int num : arr)
        cout << num << " ";

    return 0;
}