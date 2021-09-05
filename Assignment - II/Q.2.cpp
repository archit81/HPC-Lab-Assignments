// vector-vector addition using shared clause

#include <omp.h> 
#include <bits/stdc++.h>
using namespace std;

int main()
{	
    int n = 5, i;
    vector<int> A = {1,2,3,4,5}, B = {10, 20, 30, 40, 50}, C(n);

	#pragma omp parallel num_threads(5) shared(n, i, A, B, C)
	{   
        for(i = 0; i < n; i++) {
            int tmp = i;
            C[tmp] = A[tmp] + B[tmp];
            stringstream ss;
            ss<<"Thread: "<<omp_get_thread_num()<<" processing element-"<<tmp<<'\n';
            cout<<ss.str();
        }        
	}


    cout<<"\ni\tA[i] + \tB[i] = \tC[i]\n";
    for(int i = 0; i < n; i++) {
        cout<<i<<"\t"<<A[i]<<"\t"<<B[i]<<"\t"<<C[i]<<"\n";
    }
}
