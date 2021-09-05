// scalar-vector addition using shared clause

#include <omp.h> 
#include <bits/stdc++.h>
using namespace std;

int main()
{	
    int n = 5, Scalar = 10, i;
    vector<int> A = {1,2,3,4,5}, C(n);

	#pragma omp parallel num_threads(5) shared(n, i, A, Scalar)
	{   
        for(i = 0; i < n; i++) {
            int tmp = i;
            C[tmp] = A[tmp] + Scalar;
            stringstream ss;
            ss<<"Thread: "<<omp_get_thread_num()<<" processing element-"<<tmp<<'\n';
            cout<<ss.str();
        }
	}


    cout<<"\ni\tA[i] + \tS = \tC[i]\n";
    for(int i = 0; i < n; i++) {
        cout<<i<<"\t"<<A[i]<<"\t"<<Scalar<<"\t"<<C[i]<<"\n";
    }
}
