#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Binary search -> p(j) calculation
struct Jobs{
    int start;
    int finish;
    int weight;
};

// Computes p(j)
int compatiblejob(vector<Jobs>& jobs, int j){
    int low = 0;
    int high = j-1;
    while (low<=high){
        int mid = (low+high)/2;
        if (jobs[mid].finish <= jobs[j].start){
            if ((mid+1<=high) && (jobs[mid+1].finish <= jobs[j].start)){
                low = mid + 1;
            }
            else{
                return mid;
            }
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}

// main
int main(){
    int n;
    cout<<"Enter the number of jobs :";cin>>n;
    vector<Jobs> jobs(n);
    cout<<"-------Enter the attributes of each job-------"<<endl;

    for(int i=0; i<n; i++){
        cout<<"Enter the start time of job "<<i+1<<" : ";
        cin>>jobs[i].start;
    }
    for(int i=0; i<n; i++){
        cout<<"Enter the finish time of job "<<i+1<<" : ";
        cin>>jobs[i].finish;
    }
    for(int i=0; i<n; i++){
        cout<<"Enter the weight of job "<<i+1<<" : ";
        cin>>jobs[i].weight;
    }

    vector<int> p(n);
    // Sort jobs according to finish time
    sort(jobs.begin(),jobs.end(),[](Jobs a, Jobs b){
        return a.finish<b.finish;
    });

    // Computes p(j) for all j
    for(int j=0; j<n; j++){
        p[j] = compatiblejob(jobs, j);
    }

    // Memoization Array dp(n)
    vector<int> opt(n);
    opt[0] = jobs[0].weight;
    for(int j=1; j<n ;j++){
        int exclude = opt[j-1];
        int include = jobs[j].weight;
        if (p[j]!=-1){
            include += opt[p[j]];
        }
        opt[j] = max(include, exclude);
    }

    // Find-Solution
    vector<int> result;
    int j = n-1;
    while(j>=0){
        int include = jobs[j].weight;
        if (p[j]!=-1){
            include += opt[p[j]];
        }
        int exclude = (j>0) ? opt[j-1] : 0;
        if(include > exclude){
            result.push_back(j);
            j = p[j];
        }
        else{
            j = j-1;
        }
    }
    reverse(result.begin(), result.end());

    //Result display
    cout<<"-----Job Scheduling Table-----"<<endl;
    cout<<left
        << setw(10) << "Job"
        << setw(10) << "Start"
        << setw(10) << "Finish"
        << setw(10) << "P(j)"
        <<endl;
    cout<<"--------------------------------"<<endl;
    for (int i = 0; i < jobs.size(); i++) {
        cout << left
             << setw(10) << i
             << setw(10) << jobs[i].start
             << setw(10) << jobs[i].finish
             << setw(10) << p[i]
             << endl;
    }
    cout<<endl;
    cout<<"Maximum Obtainable Weight = "<<opt.back()<<endl;
    cout<<"Selected Jobs(Job, Start, Finish, Weight)"<<endl;
    for(int job : result){
        cout<<job<<"->";
        cout<<jobs[job].start<<" ";
        cout<<jobs[job].finish<<" ";
        cout<<jobs[job].weight<<" "<<endl;
    }
    return 0;
}
