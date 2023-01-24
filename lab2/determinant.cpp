#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

#define dim 20

void gcf(long long mat[dim][dim], long long temp[dim][dim], long long p, long long q, long long n){
	long long i=0, j=0;
	for (long long row = 0; row < n; row++) {
		for (long long col = 0; col < n; col++) {			
			if (row != p && col != q) {
				temp[i][j++] = mat[row][col];
				if (j == n - 1) {
					j = 0;
					i++;
				}
			}
		}
	}
}

long long det(long long mat[dim][dim], long long n) {
	long long D = 0; 
	if (n == 1)
		return mat[0][0];

	long long temp[dim][dim]; 
	long long sign = 1; 

	for (long long f = 0; f < n; f++) {
		gcf(mat, temp, 0, f, n);
		D += sign * mat[0][f]
			* det(temp, n - 1);
		sign = -sign;
	}
	return D;
}

int main() {
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);
    
        auto start = high_resolution_clock::now();
    long long N;
    long long mat[dim][dim];
    long long val[dim];
    
    cin>>N;

    for(long long i=0;i<N;i++){
        for(long long j=0; j<N; j++){
            cin>>mat[i][j];
        }
        cin>>val[i];
    }
    
    cout << "Input:" << endl;
    for(long long i=0;i<N;i++){
        for(long long j=0;j<N;j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
    
    cout << endl;
    cout << "Output:" << endl;
    cout<<det(mat,N)<<endl;

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << "Time taken by function: "
    //      << duration.count() << " microseconds" << endl;
	return 0;
}

