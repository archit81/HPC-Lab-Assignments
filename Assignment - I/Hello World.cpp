#include <omp.h> 
#include <bits/stdc++.h>
using namespace std;

int main()
{	
	omp_set_num_threads(10);
	#pragma omp parallel
	{   
        stringstream ss;
        ss << "Hello World - 2018BTECS00088 from thread: "<<omp_get_thread_num()<<"\n";
		cout<<ss.str();
	}

}

// run the program using following command -
// g++ -o hello -fopenmp "Hello World.cpp"
// .\hello
