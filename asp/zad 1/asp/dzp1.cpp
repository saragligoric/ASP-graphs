//resenje otporno na greske
//racionalno koriscenje resursa
//Ako uvedes pretpostavku koja je ogranicavajuca, to povlaci negativne poene

//sve operacije realizovati putem potprograma ciji je jedan argument pokazivac na strukturu podataka koja implementira graf sa kojim se radi

#include <iostream>

using namespace std;

//Креирање празне структуре података за граф задатих димензија (постоје чворови графа, али не постоје гране
void kreirajgraf(int** &graf, int dim) {
	graf = new int* [dim];
	for (int i = 0; i < dim; i++) {
		graf[i] = new int[dim];
		for (int j = 0; j < dim; j++) {
			graf[i][j] = 0;
		}
	}
};

//Испис репрезентације графа
void ispisigraf(int** graf, int dim) {
	if (graf) {
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				cout << graf[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	else cout << "Graf je prazan"<<endl;
}

//Додавање и уклањање гране између два чвора у графу
void dodajgranu(int** graf, int dim, int pocetni, int krajnji) {
	if (graf) {
		if ((graf[pocetni - 1][krajnji - 1] == 1) && (graf[krajnji - 1][pocetni - 1] == 1)) {
			cout << "Grana koju zelite da dodate vec postoji" << endl;
		}
		else {
			graf[pocetni - 1][krajnji - 1] = 1;
			graf[krajnji - 1][pocetni - 1] = 1;
		}
	}
	else cout << "Graf u koji zelite da dodate granu nije kreiran!" << endl;
}

void uklonigranu(int** graf, int dim, int pocetni, int krajnji) {
	if (graf) {
		if ((graf[pocetni - 1][krajnji - 1] == 0) && (graf[krajnji - 1][pocetni - 1] == 0)) {
			cout << "Grana koju zelite da uklonite ne postoji" << endl;
		}
		else {
			graf[pocetni - 1][krajnji - 1] = 0;
			graf[krajnji - 1][pocetni - 1] = 0;
		}
	}
	else cout << "Graf iz kog zelite da uklonite granu nije kreiran!" << endl;
}

//Kopija grafa
int** kopiraj(int** graf, int dim) {
	int** tempgraf = new int * [dim];
	for (int i = 0; i < dim; i++) {
		tempgraf[i] = new int [dim];
		for (int j = 0; j < dim; j++) {
			tempgraf[i][j] = graf[i][j];
		}
	}
	return tempgraf;
}

//Brisanje grafa
void brisi(int** &graf, int dim) {
	for (int i = 0; i < dim; i++) {
		delete[] graf[i];
	}
	delete[] graf;
	graf = nullptr;
}

//Додавање чвора у граф и уклањање чвора из графа
void dodajcvor(int** &graf, int &dim) {
	if (graf) {
		int** tempgraf = kopiraj(graf, dim);
		brisi(graf, dim);
		dim++;
		kreirajgraf(graf, dim);
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				if (i != (dim - 1) && j != (dim - 1)) {
					graf[i][j] = tempgraf[i][j];
				}
			}
		}
		brisi(tempgraf, dim - 1);
	}
	else cout << "Nije moguce dodati cvor jer ne postoji graf" << endl;
}

void uklonicvor(int** &graf, int& dim, int x) {
	if (graf) {
		if (x > dim) {
			cout << "Trazeni cvor ne postoji!"<<endl;
			return;
		}
		else {
			for (int i = 0; i < dim; i++) {
				for (int j = 0; j < dim; j++) {
					if (j >= x - 1) {
						graf[i][j] = graf[i][j + 1];
					}
				}
			}
			for (int i = 0; i < dim - 1; i++) {
				for (int j = 0; j < (dim - 1); j++) {
					if (i >= x - 1) {
						graf[i][j] = graf[i + 1][j];
					}
				}
			}
			dim--;
		}
	}
	else cout << "Graf iz kog zelite da uklonite cvor nije kreiran!" << endl;
}

int main() {
	int** graf=nullptr;
	int dim=0;
	int x = -1;
	int pocetni = -1;
	int krajnji = -1;

	int op=0;
	while (op != 8) {
		cout << endl;
		cout << "Unesite redni broj operacije koju zelite da izvrsite nad grafom: " << endl;
		cout << "1. Kreiranje grafa" << endl;
		cout << "2. Dodavanje cvora u graf" << endl;
		cout << "3. Uklanjanje cvora iz grafa" << endl;
		cout << "4. Dodavanje grane izmedju dva cvora" << endl;
		cout << "5. Uklanjanje grane izmedju dva cvora u grafu" << endl;
		cout << "6. Ispis grafa" << endl;
		cout << "7. Brisanje grafa" << endl;
		cout << "8. Kraj rada" << endl;
		cin >> op;

		switch (op) {
		case 1:
			cout << "Unesite broj cvorova koje zelite da ima graf: ";
			cin >> dim;
			kreirajgraf(graf, dim);
			break;
		case 2:
			dodajcvor(graf, dim);
			break;
		case 3:
			cout << "Unesite redni broj cvora koji zelite da uklonite: ";
			cin >> x;
			uklonicvor(graf, dim, x);
			break;
		case 4:
			cout << "Unesite brojeve cvorova koje zelite da povezete: ";
			cin >> pocetni >> krajnji;
			dodajgranu(graf, dim, pocetni, krajnji);
			break;
		
		case 5:
			cout << "Unesite brojeve cvorova izmedju kojih zelite da uklonite granu:";
			cin >> pocetni >> krajnji;
			uklonigranu(graf, dim, pocetni, krajnji);
			break;
		case 6:
			ispisigraf(graf, dim);
			break;
		case 7:
			brisi(graf, dim);
		case 8:
			exit(1);
		default:
			cout << "Uneli ste nepostojeci redni broj operacije. Ponovite unos";
			break;
		}
	}
}