#include <iostream>
#include <vector>
using namespace std;

long long normal_mul_count = 0;
long long normal_add_count = 0;

long long strassen_mul_count = 0;
long long strassen_add_count = 0;

/* -------- NORMAL MATRIX MULTIPLICATION -------- */

vector<vector<int>> normal_mul(const vector<vector<int>> &A, const vector<vector<int>> &B, int n) {

    vector<vector<int>> C(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++) {
                normal_mul_count++; // multiplication
                normal_add_count++; // addition
                C[i][j] += A[i][k] * B[k][j];
            }
    return C;
}

/* -------- STRASSEN MULTIPLICATION -------- */

vector<vector<int>> addMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B, int n) {

    vector<vector<int>> C(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            strassen_add_count++;
            C[i][j] = A[i][j] + B[i][j];
        }

    return C;
}

vector<vector<int>> subtractMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B, int n) {

    vector<vector<int>> C(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            strassen_add_count++;
            C[i][j] = A[i][j] - B[i][j];
        }

    return C;
}

vector<vector<int>> strassenMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B, int n) {

    if(n == 1) {
        vector<vector<int>> C(1, vector<int>(1));
        strassen_mul_count++;
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;

    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));

    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

    for(int i = 0; i < newSize; i++) {
        for(int j = 0; j < newSize; j++) {

            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    vector<vector<int>> M1 = strassenMultiply(
        addMatrix(A11, A22, newSize),
        addMatrix(B11, B22, newSize),
        newSize);

    vector<vector<int>> M2 = strassenMultiply(
        addMatrix(A21, A22, newSize),
        B11,
        newSize);

    vector<vector<int>> M3 = strassenMultiply(
        A11,
        subtractMatrix(B12, B22, newSize),
        newSize);

    vector<vector<int>> M4 = strassenMultiply(
        A22,
        subtractMatrix(B21, B11, newSize),
        newSize);

    vector<vector<int>> M5 = strassenMultiply(
        addMatrix(A11, A12, newSize),
        B22,
        newSize);

    vector<vector<int>> M6 = strassenMultiply(
        subtractMatrix(A21, A11, newSize),
        addMatrix(B11, B12, newSize),
        newSize);

    vector<vector<int>> M7 = strassenMultiply(
        subtractMatrix(A12, A22, newSize),
        addMatrix(B21, B22, newSize),
        newSize);

    vector<vector<int>> C11 = addMatrix(
        subtractMatrix(addMatrix(M1, M4, newSize), M5, newSize),
        M7, newSize);

    vector<vector<int>> C12 = addMatrix(M3, M5, newSize);
    vector<vector<int>> C21 = addMatrix(M2, M4, newSize);
    vector<vector<int>> C22 = addMatrix(subtractMatrix(addMatrix(M1, M3, newSize), M2, newSize),M6, newSize);

    vector<vector<int>> C(n, vector<int>(n));

    for(int i = 0; i < newSize; i++) {
        for(int j = 0; j < newSize; j++) {

            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
}

int main() {

    int n;
    cout << "Enter matrix size (power of 2): ";
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));

    cout << "Enter Matrix A:\n";
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter Matrix B:\n";
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> B[i][j];

    vector<vector<int>> C1 = normal_mul(A, B, n);
    vector<vector<int>> C2 = strassenMultiply(A, B, n);

    cout << "\nNormal Multiplication Result:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << C1[i][j] << " ";
        cout << endl;
    }

    cout << "\nStrassen Multiplication Result:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << C2[i][j] << " ";
        cout << endl;
    }

    cout << "\n---- OPERATION COUNT ----\n";

    cout << "\nNormal Multiplications: " << normal_mul_count;
    cout << "\nNormal Additions: " << normal_add_count;

    cout << "\n\nStrassen Multiplications: " << strassen_mul_count;
    cout << "\nStrassen Additions/Subtractions: " << strassen_add_count;


    return 0;
}