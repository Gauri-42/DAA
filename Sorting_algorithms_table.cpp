#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector> 
#include<iomanip>

using namespace std;

long long Insertion_Sort(vector<int> & arr){
    long long comparisons = 0;
    int n = arr.size();

    for(int i = 1; i<n; i++){
        int j = i-1;
        int key = arr[i];

        while(j>=0){
            comparisons++;
            if(arr[j]>key){
                arr[j+1]=arr[j];
                j--;
            }
            else{
                break;
            }
        }
        arr[j+1]=key;
    }
    return comparisons;
}

long long Selection_Sort(vector<int> & arr){
    long long comparisons = 0;
    int n = arr.size();

    for(int i = 0; i<n-1;i++){
        int min_index = i;

        for(int j = i+1;j<n;j++){
            comparisons++;
            if(arr[j]<arr[min_index]){
                min_index=j;
            }
        }

        if(i!=min_index){
            swap(arr[i],arr[min_index]);
        }
    }
    return comparisons;
}

long long Bubble_sort(vector<int> & arr){
    long long comparisons = 0;
    int n = arr.size();

    for(int i =0; i<n-1; i++){
        bool swapped =false;

        for(int j =0; j<n-1-i; j++){
            comparisons++;
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                swapped=true;
            }
        }

        if (!swapped){
            break;
        }
    }
    return comparisons;
}

long long merge(vector<int> &arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;
    long long comparisons = 0;

    while (i <= mid && j <= right) {
        comparisons++;
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
        }
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++) {
        arr[left + k] = temp[k];
    }

    return comparisons;
}

long long Merge_Sort(vector<int> &arr, int left, int right) {
    long long comparisons = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        comparisons += Merge_Sort(arr, left, mid);
        comparisons += Merge_Sort(arr, mid + 1, right);
        comparisons += merge(arr, left, mid, right);
    }

    return comparisons;
}

long long partition(vector <int> &arr, int low, int high, long long & comparisons){
    int pivot = arr[high];
    int i =low-1;

    for(int j =low; j<high;j++){
        comparisons++;
        if(arr[j]<pivot){
            i++;
            swap(arr[j],arr[i]);
        }
    }

    swap(arr[i+1],arr[high]);
    return i+1;
}

long long Quick_Sort(vector<int> &arr, int low, int high){
    long long comparisons =0;

    if(low <high){
        long long part_comp = 0;
        int q = partition(arr,low,high,part_comp);
        comparisons+=part_comp;

        comparisons+=Quick_Sort(arr,low,q-1);
        comparisons+=Quick_Sort(arr,q+1,high);
    }

    return comparisons;
}

long long heapify(vector <int> &arr, int n, int i){
    long long comparisons = 0;

    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < n){
        comparisons++;
        if(arr[left] > arr[largest]){
            largest = left;
        }
    }

    if(right < n){
        comparisons++;
        if(arr[right] > arr[largest]){
            largest = right;
        }
    }

    if (largest != i){
        swap(arr[i],arr[largest]);
        comparisons += heapify(arr, n, largest);
    }

    return comparisons;

}

long long Heap_Sort(vector<int> &arr){
    long long comparisons = 0;
    int n =arr.size();

    //Build heap
    for(int i = n/2 - 1; i>=0; i--){
        comparisons+=heapify(arr, n, i);
    }

    //Extract elements
    for(int i = n -1; i>0;i--){
        swap(arr[0],arr[i]);
        comparisons+=heapify(arr,i,0);
    }

    return comparisons;
}

int main() {

        ifstream fin("Input_arrays.txt");
        ofstream fout("Output.txt");
        ofstream graph("Graph_Data.csv");

        int total_arrays;
        fin>>total_arrays;

        vector<long long> ins_best(101,0), ins_worst(101,0), ins_avg(101,0);
        vector<long long> sel_best(101,0), sel_worst(101,0), sel_avg(101,0);
        vector<long long> bub_best(101,0),bub_worst(101,0), bub_avg(101,0);
        vector<long long> mer_best(101,0), mer_worst(101,0), mer_avg(101,0);
        vector<long long> qui_best(101,0), qui_worst(101,0), qui_avg(101,0);
        vector<long long> hea_best(101,0), hea_worst(101,0), hea_avg(101,0);

        vector<int> array_size(101, 0);
        vector<int> random_count(101,0);

        for(int i =0; i<total_arrays; i++){
            int base_id,n;
            char type;
            fin >> base_id>> type >>n;

            array_size[base_id]=n;
            
            vector<int>arr(n);          //copies the array from file
            for(int j =0; j<n; j++){
                fin >> arr[j];
            }

            vector<int> temp;

            //Insertion Sort
            temp = arr;
            long long ic = Insertion_Sort(temp);
            if(type =='A'){
                ins_best[base_id] = ic;
            }
            else if(type == 'D'){
                ins_worst[base_id] = ic;
            }
            else{
                ins_avg[base_id] +=ic;
                random_count[base_id]++;
            }

            //Selection Sort
            temp = arr;
            long long sc = Selection_Sort(temp);
            if(type =='A'){
                sel_best[base_id] = sc;
            }
            else if(type == 'D'){
                sel_worst[base_id] = sc;
            }
            else{
                sel_avg[base_id] +=sc;
            }

            //Bubble Sort
            temp = arr;
            long long bc = Bubble_sort(temp);
            if(type =='A'){
                bub_best[base_id] = bc;
            }
            else if(type == 'D'){
                bub_worst[base_id] = bc;
            }
            else{
                bub_avg[base_id] +=bc;
            }

            // Merge Sort
            temp = arr;
            long long mc = Merge_Sort(temp, 0, n - 1);
            if (type == 'A') {
                mer_best[base_id] = mc;
            }
            else if (type == 'D') {
                mer_worst[base_id] = mc;
            }
            else {
                mer_avg[base_id] += mc;
            }

            // Quick Sort
            temp = arr;
            long long qc = Quick_Sort(temp, 0, n - 1);
            if(type =='A'){
                qui_best[base_id] = qc;
            }
            else if(type == 'D'){
                qui_worst[base_id] = qc;
            }
            else{
                qui_avg[base_id] += qc;
            }

            // Heap Sort
            temp = arr;
            long long hc = Heap_Sort(temp);
            if(type =='A'){
                hea_best[base_id] = hc;
            }
            else if(type == 'D'){
                hea_worst[base_id] = hc;
            }
            else{
                hea_avg[base_id] += hc;
            }
        }

    //--------------------Combined Tabular form----------------------
    fout << "COMBINED TABULAR ANALYSIS\n";
    fout << "====================================================================================================\n";
    fout << "Array\t\tCase\t\tInsertion\tSelection\t\tBubble\t\tMerge\t\tQuick\t\tHeap\n";
    fout << "----------------------------------------------------------------------------------------------------\n";

    graph << "ArrayNumber,"<<"ArraySize,"
      << "Ins_Best,Ins_Avg,Ins_Worst,"
      << "Sel_Best,Sel_Avg,Sel_Worst,"
      << "Bub_Best,Bub_Avg,Bub_Worst,"
      << "Mer_Best,Mer_Avg,Mer_Worst,"
      << "Qui_Best,Qui_Avg,Qui_Worst,"
      << "Heap_Best,Heap_Avg,Heap_Worst\n";

    for (int i = 1; i <= 100; i++) {

        fout << i << "\t\tBest\t\t"
             <<"\t"<< ins_best[i] << "\t\t"
             << "\t"<<sel_best[i] << "\t\t"
             << "\t"<<bub_best[i] << "\t\t"
             << "\t"<<mer_best[i] << "\t\t"
             << "\t"<<qui_best[i] << "\t\t"
             << "\t"<<hea_best[i] << endl;

        fout << "\t\tWorst\t\t"
             << "\t"<<ins_worst[i] << "\t\t"
             << sel_worst[i] << "\t\t"
             << "\t"<<bub_worst[i] << "\t\t"
             << "\t"<<mer_worst[i] << "\t\t"
             <<qui_worst[i] << "\t\t"
             << "\t\t"<<hea_worst[i] << endl;

        long long insA = (random_count[i] ? ins_avg[i] / random_count[i] : 0);
        long long selA = (random_count[i] ? sel_avg[i] / random_count[i] : 0);
        long long bubA = (random_count[i] ? bub_avg[i] / random_count[i] : 0);
        long long merA = (random_count[i] ? mer_avg[i] / random_count[i] : 0);
        long long quiA = (random_count[i] ? qui_avg[i] / random_count[i] : 0);
        long long heaA = (random_count[i] ? hea_avg[i] / random_count[i] : 0);

        fout << "\t\tAverage\t\t"
            << "\t" << insA << "\t\t"
            << selA << "\t\t"
            << "\t" << bubA << "\t\t"
            << "\t" << merA << "\t\t"
            <<quiA<<"\t\t"
            <<heaA<<endl;

        fout << "-----------------------------------------------------------------------------\n";

        graph << i << "," << array_size[i] << ","
            << ins_best[i] << "," << insA << "," << ins_worst[i] << ","
            << sel_best[i] << "," << selA << "," << sel_worst[i] << ","
            << bub_best[i] << "," << bubA << "," << bub_worst[i] << ","
            << mer_best[i] << "," << merA << "," << mer_worst[i] << ","
            << qui_best[i] << "," << quiA << "," << qui_worst[i] << ","
            << hea_best[i] << "," << heaA << "," << hea_worst[i] << "\n";

    }

    // ---------- Overall Average ----------

    long long total_ins = 0, total_sel = 0, total_bub = 0, total_mer=0,total_qui=0, total_hea =0;

    for (int i = 1; i <= 100; i++) {
        total_ins += (ins_avg[i] + ins_best[i] + ins_worst[i])/ (random_count[i]+2);
        total_sel += (sel_avg[i] + sel_best[i] + sel_worst[i])/ (random_count[i]+2);
        total_bub += (bub_avg[i] + bub_best[i] + bub_worst[i])/ (random_count[i]+2);
        total_mer += (mer_avg[i] + mer_best[i] + mer_worst[i])/ (random_count[i]+2);
        total_qui += (qui_avg[i] + qui_best[i] + qui_worst[i])/(random_count[i]+2);
        total_hea += (hea_avg[i] + hea_best[i] + hea_worst[i])/(random_count[i]+2);
    }

    fout << "\nOVERALL AVERAGE COMPARISONS\n";
    fout << "===========================\n";
    fout << "Insertion Sort : " << total_ins / 100 << endl;
    fout << "Selection Sort : " << total_sel / 100 << endl;
    fout << "Bubble Sort    : " << total_bub / 100 << endl;
    fout << "Merge Sort     : " << total_mer / 100 << endl;
    fout << "Quick Sort     : " << total_qui / 100 << endl;
    fout << "Heap Sort      : " << total_hea / 100 << endl;


    fin.close();
    fout.close();
    graph.close();

    cout << "Final tabular analysis completed successfully.\n";
    return 0;
}  