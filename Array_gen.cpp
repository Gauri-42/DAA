#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<algorithm>

using namespace std;

void randomShuffle(vector<int>& arr){
    for(int i = arr.size() -1; i> 0; i--){
        int j = rand() % (i+1);
        swap(arr[i],arr[j]);
    }
}

int main() {
    ofstream fout("Input_arrays.txt");

    int base_count = 100;           //100 original arrays
    fout<<base_count*10<<endl;      //1000 (total arrays)

    for(int id = 1; id<=base_count; id++){
        int n = rand() % 1000 + 1;           // size of each array is between 1 to 1000
        
        vector<int> base(n);
        for(int i = 0; i<n; i++){
            base[i] = rand() % 1000 + 1;
        }

        // 8 random shuffles

        for(int k = 0; k<8; k++){
            vector<int> temp = base;
            randomShuffle(temp);

            fout<< id << " R " << n << endl;
            for (int x : temp){
                fout<< x <<" ";
            }
            fout<< endl;
        }

        // Ascending Order

        vector<int> asc = base;
        sort(asc.begin(),asc.end());
        fout<< id <<" A "<< n <<endl;
        for(int x: asc){
            fout<< x <<" ";
        }
        fout<<endl;

        // Descending Order

        vector<int> des = base;
        sort(des.begin(),des.end(),greater<int>());
        fout<<id<<" D "<<n<<endl;
        for(int x: des){
            fout<<x<<" ";
        }
        fout<< endl;
    }

    fout.close();
    cout<<"1000 arrays are generated and stored in the file";

    return 0;
}