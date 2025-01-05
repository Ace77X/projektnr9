#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>

using namespace std;

void szukanie(int n, int* tabx, int* taby){
	int *index = new int[n];
	double odleglosc=0;
	
	for (int i =0; i<n;i++){
		index[i]=-1;
	}	
		for (int i = 0; i<n;i++){
			double minodleglosc=10000;
			int in=-1;
			for (int j = 0; j<n; j++){			
				if (j!=i){
				odleglosc = (tabx[i] - tabx[j]) * (tabx[i] - tabx[j]) + (taby[i] - taby[j]) * (taby[i] - taby[j]);
				if (odleglosc < minodleglosc) {
					minodleglosc = odleglosc;
					in=j;				
					}
				}
			}
		index[i]=in;		
	}

	for (int i=0; i<n;i++){
		cout << index[i] << " ";
	}

}

int main(){
	int n;
	cout << "Wpisz ilosc punktow: " << endl;
	cin >> n;
	
	int *tabx = new int[n];
	int *taby = new int[n];
	
	srand(time(NULL));
	
	for(int i = 0; i<n; i++){
		tabx[i] = rand() % 10;
		taby[i] = rand() % 10;
	}
	
	for(int i = 0;i<n;i++){
		cout << tabx[i] << " ";
	}
	
	cout << endl;
	
	for(int i = 0;i<n;i++){
		cout << taby[i] << " ";
	}
	
	cout << endl;

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	szukanie(n,tabx, taby);	
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	
	cout << endl << "czas: " << time_span.count() << endl;
	
	return 0;
}