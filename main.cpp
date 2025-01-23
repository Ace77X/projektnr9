#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cassert>

using namespace std;

int* szukanie(int n, int* tabx, int* taby){
	int *index = new int[n];    // Deklaracja tablicy index
	double odleglosc=0;
	
	for (int i =0; i<n;i++){   // Uzupelnienie tablicy index wartosciami -1 aby miec pewnosc ze nie beda mialy wplyw na wynik
		index[i]=-1;
	}	
	for (int i = 0; i<n;i++){   // Obliczanie i zapisywanie indeksow najblizszych sasiadow
		double minodleglosc=numeric_limits<double>::infinity();
		int in=-1;
		for (int j = 0; j<n; j++){
			if (j!=i){
			odleglosc = (tabx[i] - tabx[j]) * (tabx[i] - tabx[j]) + (taby[i] - taby[j]) * (taby[i] - taby[j]);
			if (odleglosc < minodleglosc) {
				minodleglosc = odleglosc;
				in = j;				
				}
			}
		}
		index[i]=in;		
	}
	
	return index;
}

void testy() {   // Funkcja przeprowadzajaca testy przy uzyciu assert
    // Test 1: Prosty przypadek
    int tabx1[] = {0, 1, 2};
    int taby1[] = {0, 0, 0};
    int n1 = 3;
    int* wynik1 = szukanie(n1, tabx1, taby1);
    assert(wynik1[0] == 1);
    assert(wynik1[1] == 0 || wynik1[1] == 2);
    assert(wynik1[2] == 1);
    delete[] wynik1;

    // Test 2: Punkty w pionie
    int tabx2[] = {0, 0, 0};
    int taby2[] = {0, 1, 2};
    int n2 = 3;
    int* wynik2 = szukanie(n2, tabx2, taby2);
    assert(wynik2[0] == 1);
    assert(wynik2[1] == 0 || wynik2[1] == 2);
    assert(wynik2[2] == 1);
    delete[] wynik2;

    // Test 3: Jeden punkt
    int tabx3[] = {5};
    int taby3[] = {5};
    int n3 = 1;
    int* wynik3 = szukanie(n3, tabx3, taby3);
    assert(wynik3[0] == -1);
    delete[] wynik3;
	
	cout <<endl <<  "Test OK";
}


int main(){
	
	ifstream file("danebrute.txt");   // Obsluga otwierania pliku
    if (!file.is_open()) {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        return 1;
    }
	
	int n;
	file >> n;  // Pobieranie liczby punktow z pliku
	//cout << "Wpisz ilosc punktow: " << endl;
	//cin >> n;
	
	if (n <= 0) {
        cout << "Liczba punktow musi byc dodatnia!" << endl;
        return 1;
    }
    
	int *tabx = new int[n];   // Deklaracja tablic
	int *taby = new int[n];
	int *index;    // Deklaracja wskaznika do tablicy index, ktora jest stworzona w funkcji
	
	srand(time(NULL));
	
	for(int i = 0; i<n; i++){   // Uzupelnienie tablic
		//tabx[i] = rand() % 10;
		//taby[i] = rand() % 10;
		file >> tabx[i];
	}
	for(int i = 0; i<n; i++){
		file >> taby[i];
	}
	
	for(int i = 0;i<n;i++){   // Wypisanie tablic na ekran
		cout << tabx[i] << " ";
	}
	
	cout << endl;
	
	for(int i = 0;i<n;i++){
		cout << taby[i] << " ";
	}
	
	cout << endl;
	file.close();  // Zamkniecie pliku -> dane zostaly przepisane do tablic
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	index = szukanie(n,tabx, taby);	// Przypisanie wskaznika do tablicy "zwrotnej" z funkcji szukanie
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	
	for (int i=0; i<n;i++){  // Wypisanie wyniku na ekran
		cout << index[i] << " ";
	}
	
	testy();  // Wywolanie funkcji w ktorej wykonywane sa testy
	
	cout << endl << "czas: " << time_span.count() << endl;  // Wypisanie pomiaru czasu
	
	delete[] tabx;   // Usuniecie tablic z pamieci
	delete[] taby;
	
	return 0;
}