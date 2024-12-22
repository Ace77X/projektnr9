#include <iostream>
#include <cmath>

using namespace std;

class Punkt {
	
	public:
	int x;
	int y;
	Punkt(){
		x=0;
		y=0;
	}
	
	Punkt(int x0, int y0) : x(x0), y(y0){}
	
};


int main(){
	Punkt p1(5,2);
	Punkt p2(3,1);
		
	cout << p1.x << " " << p1.y << endl;
	cout << p2.x << " " << p2.y << endl;
	
	double odleglosc=0;
	//double odlegloscsq=0;
	odleglosc = sqrt((p1.x-p2.x)^2 + (p1.y - p2.y)^2);	
	//odlegloscsq = (p1.x-p2.x)^2 + (p1.y - p2.y)^2;
	if (odleglosc < 0 ) {
		cout << "Blad w obliczeniach, odleglosc jest mniejsza niz 0." << endl;
	} else if (odleglosc == 0 ){
		cout << "Odleglosc miedzy tymi samymi punktami jest rowna 0" << endl;
	} else {
		cout << odleglosc << endl;
	}
	
	return 0;
}