#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

class Punkt {   // Klasa za pomoca ktorej zapisywane beda punkty przy zachowaniu obu wspolrzednych i oryginalnego indeksu
    public:
        double x;
        double y;
        double indeks;
};

double odleglosc(const Punkt& p1, const Punkt& p2) {   // Funkcja obliczajaca odleglosc tradycyjna metoda -> lepsza modularnosc kodu
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void sortX(Punkt* punkty, int lewa, int prawa) {  // Funkcja sortujaca po wspolrzednych X uzywajac polecenia sort z biblioteki algorithm
    sort(punkty + lewa, punkty + prawa + 1, [](const Punkt& a, const Punkt& b) {
        return a.x < b.x;
    });
}


double bruteForce(Punkt* punkty, int lewa, int prawa, int* index) {   // Funkcja obliczajaca indeksy najblizszych sasiadow
    double minOdle = numeric_limits<double>::infinity();  // Ustawienie zmiennej na wartosc inf
    for (int i = lewa; i <= prawa; i++) {
        double aktminOdle = numeric_limits<double>::infinity();
        int in = -1;
        
        for (int j = lewa; j <= prawa; j++) {  // ustalanie indeksu najblizszego sasiada 
            if (i != j) {
                double odleglosc1 = odleglosc(punkty[i], punkty[j]);
                if (odleglosc1 < aktminOdle) {
                    aktminOdle = odleglosc1;
                    in = j;
                }
            }
        }
        
        index[i] = in;
        minOdle = min(minOdle, aktminOdle);
    }
    return minOdle;
}

double scalanie(Punkt* punkty, int lewa, int mid, int prawa, int* index, double d) {
    vector<pair<Punkt, int> > granica;   // Stworzenie zbioru granica 
    double mediana = punkty[mid].x;
    

    for (int i = lewa; i <= prawa; i++) {    // "Wlozenie" do zbioru granica punktow ktore sie kwalifikuja na potencjalnie blizsze po drugiej stronie tej granicy
        if (abs(punkty[i].x - mediana) < d) {
            granica.push_back({punkty[i], i});
        }
    }

    sort(granica.begin(), granica.end(),    // Sortowanie po wspolrzednych Y zbioru granica
         [](const pair<Punkt, int>& a, const pair<Punkt, int>& b) {
             return a.first.y < b.first.y;
         });

    double minOdle = d;
    

    for (int i = 0; i < granica.size(); i++) {  // Ustalanie czy w zbiorze granica sa punkty blizsze niz ustalone wczesniej
        for (int j = i + 1; j < min(i + 8, (int)granica.size()); j++) {   // Skorzystanie z dowodu geometrycznego na to, ze nie moze byc wiecej niz 7 punktow ktore sa potencjalnie blizsze
            if (granica[j].first.y - granica[i].first.y >= minOdle) break; 
            
            double dist = odleglosc(granica[i].first, granica[j].first);
            if (dist < minOdle) {
                int idx1 = granica[i].second;
                int idx2 = granica[j].second;
                
                if (dist < odleglosc(punkty[idx1], punkty[index[idx1]])) {  // Podmienianie indeksow w tablicy wynikowej index jesli zachodzi taka potrzeba
                    index[idx1] = idx2;
                }
                if (dist < odleglosc(punkty[idx2], punkty[index[idx2]])) {
                    index[idx2] = idx1;
                }
                
                minOdle = dist;
            }
        }
    }
    
    return minOdle;
}

double podzial(Punkt* punkty, int lewa, int prawa, int* index) {  // Funkcja odpowiedzialna za podzial zbioru danych na mniejsze
    if (prawa - lewa + 1 <= 3) {
        return bruteForce(punkty, lewa, prawa, index);   // Podzial dokonuje sie az osiagniemy zbiory o ilosci elementow 3 i mniej
    }
    
    int srod = lewa + (prawa - lewa) / 2;
    
    double granlew = podzial(punkty, lewa, srod, index);   // Ustalenie granic
    double granpraw = podzial(punkty, srod + 1, prawa, index);
    
    return scalanie(punkty, lewa, srod, prawa, index, min(granlew, granpraw));   // Wywowalanie funkcji scalanie ktora zapewni ostateczny wynik
}

void sasiedzi(Punkt* punkty, int n, int* index) {    
    sortX(punkty, 0, n - 1);
    podzial(punkty, 0, n - 1, index);
}

void testy() {
	
	// Test 1: Prosty przypadek
    Punkt punkty[3] = {{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
    int index[3] = {-1, -1, -1};
    sasiedzi(punkty, 3, index);
    assert(index[0] == 1);
    assert(index[1] == 0 || index[1] == 2);
    assert(index[2] == 1);
    
    // Test 2: Punkty w linii poziomej
    Punkt punkty1[4] = {{0, 0, 0}, {1, 0, 1}, {2, 0, 2}, {3, 0, 3}};
    int index1[4] = {-1, -1, -1, -1};
    sasiedzi(punkty1, 4, index1);
    assert(index1[0] == 1);
    assert(index1[1] == 0 || index1[1] == 2);
    assert(index1[2] == 1 || index1[2] == 3);
    assert(index1[3] == 2);
    
    // Test 3: Jeden punkt
    Punkt punkty2[1] = {{0, 0, 0}};
    int index2[1] = {-1};
    sasiedzi(punkty2, 1, index2);
    assert(index2[0] == -1);
    
    cout << endl << "Test OK" << endl;
}

int main() {
	ifstream file("danedivide.txt");   // Obsluga otwierania pliku
    if (!file.is_open()) {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        return 1;
    }	
	
    int n;
    file >> n;
    //cout << "Wpisz ilosc punktow: " << endl;
    //cin >> n;
    
    if (n <= 0) {
        cout << "Liczba punktow musi byc dodatnia!" << endl;
        return 1;
    }
    
    int *tabx = new int[n];
    int *taby = new int[n];
    
    srand(time(NULL));
    
   /*for(int i = 0; i < n; i++) {
   		//cin >> tabx[i];
   		//cin >> taby[i];
        tabx[i] = rand() % 10;
        taby[i] = rand() % 10;
    }   */

	for(int i = 0; i<n; i++){   // Uzupelnienie tablic
		file >> tabx[i];
	}
	for(int i = 0; i<n; i++){
		file >> taby[i];
	}

    for(int i = 0;i<n;i++){
		cout << tabx[i] << " ";
	}
	
	cout << endl;
	
	for(int i = 0; i < n; i++){
		cout << taby[i] << " ";
	}
    cout << endl;
    
    Punkt* punkty = new Punkt[n];
    for (int i = 0; i < n; i++) {
        punkty[i].x = tabx[i];
        punkty[i].y = taby[i];
        punkty[i].indeks = i;
    }
    
	file.close();  // Zamkniecie pliku -> dane zostaly przepisane do tablic
    int* index = new int[n]; 

    auto t1 = chrono::high_resolution_clock::now();      
    sasiedzi(punkty, n, index);
    
    auto t2 = chrono::high_resolution_clock::now();
    
    int* ostindeks = new int[n];    // Nowa tablica ostindeks w ktorej bedzie przechowywany ostateczny wynik - w tablicy index wynik jest odpowiedni dla posortowanych punktow wzgledem x
    for(int i = 0; i < n; i++) {
        int ind = punkty[i].indeks;   // Powrot do oryginalnej kolejnosci osiagany jest za pomoca zapisanego wczesniej indeksu
        ostindeks[ind] = punkty[index[i]].indeks;
    }

      
    for(int i = 0; i < n ; i++){   // Wypisanie wyniku na ekran 
		cout << ostindeks[i] << " ";
	}

	testy();    // Wywolanie funkcji testujacej
    
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << endl << "czas: " << time_span.count() << endl;
    
    delete[] index;
    delete[] punkty;
    delete[] tabx;
    delete[] taby;
    
    return 0;
}