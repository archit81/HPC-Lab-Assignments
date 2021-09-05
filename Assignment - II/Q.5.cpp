// scalar-vector without work sharing construct

#include <omp.h> 
#include <bits/stdc++.h>
using namespace std;

int main()
{	
    int n = 10, Scalar = 10;
    vector<int> A = {1,2,3,4,5,6,7,8,9,10}, C(n);

	#pragma omp parallel num_threads(5)
	{   
        int id = omp_get_thread_num();
        int l = id*n/5, r = ((id+1)*n)/5;
        for(int i = l; i < r; i++) {
            C[i] = A[i] + Scalar;
            stringstream ss;
            ss<<"Thread: "<<omp_get_thread_num()<<" processing element-"<<i<<'\n';
            cout<<ss.str();
        }
	}

    
    cout<<"\ni\tA[i] + \tS = \tC[i]\n";
    for(int i = 0; i < n; i++) {
        cout<<i<<"\t"<<A[i]<<"\t"<<Scalar<<"\t"<<C[i]<<"\n";
    }
}
