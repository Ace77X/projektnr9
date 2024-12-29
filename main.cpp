#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int main(){

	int n=5;
	
	//cout << "Wpisz ilosc punktow: " << endl;
	//cin >> n;

	int tabx[n];// = {0,1,-2,-1,10};
	int taby[n];// = {0,2,-3,-10,9};
	
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
	
	double odleglosc=0;
	int index[5];
	
	for (int i =0; i<n;i++){
		index[i]=-1;
	}
	
	for (int i = 0; i<n;i++){
		double minodleglosc=10000;
		int in=-1;
		for (int j = 0; j<n; j++){			
			if (j!=i){
			odleglosc = sqrt(pow(tabx[i] - tabx[j],2) + pow(taby[i] - taby[j],2));
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

	
	return 0;
}