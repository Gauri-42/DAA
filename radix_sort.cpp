#include <iostream>
#include <vector>
using namespace std;

void printArray(vector<int> &arr) {
    for(int x : arr)
        cout << x << " ";
    cout << endl;
}

void count_sort(vector<int> &arr, int exp){
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for(int i = 0; i<n;i++){
        int digit = (arr[i]/exp) %10;
        count[digit]++;
    }

    for(int i = 1; i<10; i++){
        count[i]+=count[i-1];
    }

    for(int i = n-1; i >= 0; i --){
        int digit = (arr[i]/exp)%10;
        output[count[digit]-1] = arr[i];
        count[digit]--;
    }

    arr=output;
}

void radix_sort(vector<int> &arr){
    int n = arr.size();

    if(n == 0){
        return;
    }

    int max = arr[0];
    for(int i = 1; i<n ;i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }

    for(int exp = 1; max/exp >0 ;exp*=10){
        cout << "\nSorting by digit place (exp = " << exp << ")" << endl;
        count_sort(arr,exp);

        cout << "Array after this pass: ";
        printArray(arr);
    }

}

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    radix_sort(arr);

    cout << "Sorted array: ";
    for(int num : arr)
        cout << num << " ";

    return 0;
}