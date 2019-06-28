#include <iostream>

using namespace std;

int N;

int read_int() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

void read_credits(int* &C) {
    for (int i=0; i<N; i++) {
        C[i] = read_int();
    }
}

int binarySearchLeft(int* &Arr, int l, int r, int x) { 
    int mid = l + (r - l)/2;
    if (r > l) {
        if (Arr[mid] == x) return mid;
        if (Arr[mid] > x) return binarySearchLeft(Arr, l, mid-1, x);
        return binarySearchLeft(Arr, mid+1, r, x);
    }
    else if (r==l) {
        if ((Arr[mid] > x)&&(mid>0)) {
            return mid-1;
        }
        return mid;
    }
    else {
        return r;
    }
}

int binarySearchRight(int* &Arr, int l, int r, int x) { 
    int mid = l + (r - l)/2;
    if (r > l) {
        if (Arr[mid] == x) return mid;
        if (Arr[mid] < x) return binarySearchRight(Arr, l, mid-1, x);
        return binarySearchRight(Arr, mid+1, r, x);
    }
    else if (r==l) {
        if ((Arr[mid] < x)&&(mid>0)) {
            return mid-1;
        }
        return mid;
    }
    else {
        return r;
    }
}

void find_left(int* &A, int* &LeftSteps) {
    int *Left;
    Left = new int [N];

    int len = 1;
    Left[0] = A[0];
    LeftSteps[0] = 1;

    for(int i=1; i<N; i++) {
        if (A[i] > Left[0]) {
            if (A[i] > Left[len-1]) {
                len++;
                Left[len-1] = A[i];
            }
            else {
                int mid = binarySearchLeft(Left, 0, len-1, A[i]);
                if ((A[i] != Left[mid])&&(A[i] < Left[mid+1])) {                    
                    Left[mid+1] = A[i];
                }
            }
        }
        else {
            Left[0] = A[i];
        }
        LeftSteps[i] = len;
    }
}

void find_right(int* &A, int* &RightSteps) {
    int *Right;
    Right = new int [N];

    int len = 1;
    Right[0] = A[N-1];
    RightSteps[N-1] = 1;

    for(int i=N-2; i>=0; i--) {
        if (A[i] < Right[0]) {
            if (A[i] < Right[len-1]) {
                len++;
                Right[len-1] = A[i];
            }
            else {
                int mid = binarySearchRight(Right, 0, len-1, A[i]);
                if ((A[i] != Right[mid])&&(A[i] > Right[mid+1])) {
                    Right[mid+1] = A[i];
                }
            }
        }
        else {
            Right[0] = A[i];
        }
        RightSteps[i] = len;
    }
}

int find_max(int* &Left, int* &Right) {
    int max = Right[0];
    int sum;

    for(int i=0; i<N-1; i++) {
        sum = Left[i] + Right[i+1];
        if (sum>max) max = sum;
    }

    return max;
}

int main(void) {
    N = read_int();
    int *C;
    C = new int [N];

    read_credits(C);

    int *LeftSteps;
    LeftSteps = new int [N];

    find_left(C, LeftSteps);

    int *RightSteps;
    RightSteps = new int [N];

    find_right(C, RightSteps);

    int max = find_max(LeftSteps, RightSteps);

    cout << max << endl;

    delete [] C;
    delete [] LeftSteps;
    delete [] RightSteps;

    return 0;
}