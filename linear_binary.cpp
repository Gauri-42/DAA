#include<iostream>
#include<vector>
using namespace std;

int comp_lin =0, comp_bin=0;
bool linear_search(vector<int> &arr,int n,int key){
    for (int i = 0; i< n; i++){
        comp_lin++;
        if (arr[i] == key){
            return true;
        }
    }
    return false;
}

void Bubble_sort(vector<int> &arr, int n){

    for(int i =0; i<n-1; i++){
        bool swapped =false;

        for(int j =0; j<n-1-i; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                swapped=true;
            }
        }

        if (!swapped){
            break;
        }
    }
}

bool binarySearchUtil(vector<int> &arr, int left, int right, int key) {

    if(left > right){
        return false;
    }

    int mid = left + (right - left) / 2;

    comp_bin++;
    if(arr[mid] == key)
        return true;

    comp_bin++;
    if(key < arr[mid])
        return binarySearchUtil(arr, left, mid - 1, key);

    else
        return binarySearchUtil(arr, mid + 1, right, key);
}

bool binary_search(vector<int> &arr, int key){
    int n = arr.size();
    Bubble_sort(arr,n);
    int left = 0;
    int right = n - 1;

    return binarySearchUtil(arr, left, right, key);
}

int main(){
    int n, key;
    cout<<"Enter the size of array: ";
    cin>>n;

    vector<int> arr(n);
    cout<<"Enter the elements of array: ";
    for(int i =0; i<n;i++){
        cin>>arr[i];
    }

    cout<<"Enter the element to search: ";
    cin>> key;

    cout<<"\nBINARY SEARCH RESULT\n";
    vector<int>arr_copy = arr;
    bool result = binary_search(arr_copy,key);
    if (!result) {
        cout<<"Element Not Found !!\n";
    }
    cout<<"Total Comparsions = "<<comp_bin<<"\n";

    cout<<"\nLINEAR SEARCH RESULT\n";
    result = linear_search(arr,n,key);
    if (!result) {
        cout<<"Element Not Found !!\n";
    }
    cout<<"Total Comparsions = "<<comp_lin<<"\n";

    return 0;
}