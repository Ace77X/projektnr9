#include <iostream>
#include <cmath>

using namespace std;

int main(){

	int n=5;
	
	//cout << "Wpisz ilosc punktow: " << endl;
	//cin >> n;

	int tabx[n] = {0,1,-2,-1,10};
	int taby[n] = {0,2,-3,-10,9};
	

	
	double odleglosc=0;
	//double odlegloscsq=0;
	double minodleglosc=10000;
	int index[2]={-1,-1};
	
	for (int i = 0; i<n;i++){
		for (int j = 1; j<n; j++){			
			if (j!=i){
			odleglosc = sqrt(pow(tabx[i] - tabx[j],2) + pow(taby[i] - taby[j],2));
			
			if (odleglosc < minodleglosc) {
				minodleglosc = odleglosc;
				index[0]=i;
				index[1]=j;
			}
		}
		}
	}

	if (minodleglosc < 0) {
		cout << "Blad w obliczeniach, odleglosc jest mniejsza niz 0." << endl;
	} else if (minodleglosc == 0){
		cout << "Odleglosc miedzy tymi samymi punktami jest rowna 0" << endl;
	} else {
		cout << minodleglosc << endl;
		cout << "Pomiedzy punktem " << index[0]+1 << " oraz punktem " << index[1]+1<< endl;
	}
	
	//cout << tabx[0] << " " << tabx[1] << " ";
	//odleglosc = sqrt(pow(tabx[0] - tabx[1],2) + pow(taby[0] - taby[1],2));
	//odlegloscsq = pow(tabx[0] - tabx[1],2) + pow(taby[0] - taby[1],2);
	//cout << odlegloscsq;
	
	return 0;
}