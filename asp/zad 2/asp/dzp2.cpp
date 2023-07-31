//resenje otporno na greske
//racionalno koriscenje resursa
//Ako uvedes pretpostavku koja je ogranicavajuca, to povlaci negativne poene

#include <iostream>
#include <string>
#include <limits>
#include <queue>
#include <stack> 

using namespace std;

//Креирање празне структуре података за граф задатих димензија (постоје чворови графа, али не постоје гране																													
void kreirajgraf(int**& graf, int dim) {
	graf = new int* [dim];
	for (int i = 0; i < dim; i++) {
		graf[i] = new int[dim];
		for (int j = 0; j < dim; j++) {
			graf[i][j] = 10000;
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
	else cout << "Graf je prazan" << endl;
}

//Додавање и уклањање гране између два чвора у графу											
void dodajgranu(int** graf, int dim, int pocetni, int krajnji,int tezina) {
	if (graf) {
		if ((graf[pocetni - 1][krajnji - 1] !=10000) && (graf[krajnji - 1][pocetni - 1] != 10000)) {
			cout << "Grana koju zelite da dodate vec postoji" << endl;
		}
		else {
			graf[pocetni - 1][krajnji - 1] = tezina;
			graf[krajnji - 1][pocetni - 1] = tezina;
		}
	}
	else cout << "Graf u koji zelite da dodate granu nije kreiran!" << endl;
}		

void uklonigranu(int** graf, int dim, int pocetni, int krajnji) {
	if (graf) {
		if ((graf[pocetni][krajnji] == 10000) && (graf[krajnji][pocetni] == 10000)) {
			cout << "Grana koju zelite da uklonite ne postoji" << endl;
		}
		else {
			graf[pocetni][krajnji] = 10000;
			graf[krajnji][pocetni] = 10000;
		}
	}
	else cout << "Graf iz kog zelite da uklonite granu nije kreiran!" << endl;
}

//Kopija grafa
int** kopiraj(int** graf, int dim) {
	int** tempgraf = new int* [dim];
	for (int i = 0; i < dim; i++) {
		tempgraf[i] = new int[dim];
		for (int j = 0; j < dim; j++) {
			tempgraf[i][j] = graf[i][j];
		}
	}
	return tempgraf;
}

//Brisanje grafa
void brisi(int**& graf, int dim) {
	for (int i = 0; i < dim; i++) {
		delete[] graf[i];
	}
	delete[] graf;
	graf = nullptr;
}

//Додавање чвора у граф и уклањање чвора из графа
void dodajcvor(int**& graf, int& dim) {
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

void uklonicvor(int**& graf, int& dim, int x) {
	if (graf) {
		if (x > dim) {
			cout << "Trazeni cvor ne postoji!" << endl;
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

// Print the queue (pomocna test funkcija)
void showq(queue<int> gq){
	queue<int> g = gq;
	while (!g.empty()) {
		cout << '\t' << g.front();
		g.pop();
	}
	cout << '\n';
}

//posetimo sve cvorove bilo kojim algoritmom obilaska
//ako na kraju ostane neki neposecen cvor, graf je nepovezan
bool povezan(int** graf, int dim) {
	//flagovi posecenosti
	int* flags = new int[dim];
	for (int i = 0; i < dim; i++) {
		flags[i] = 0;
	}
	//nasumicno odaberes prvi cvor i setujes ga da je obradjen
	int tekuci = rand() % dim;
	flags[tekuci - 1] = 1;
	//stavis tekuci cvor u red
	queue<int> redic;
	redic.push(tekuci);

	while (!redic.empty()) {
		tekuci = redic.front();
		redic.pop();
		//za sve susede cvora v: poseti sve NEPOSECENE susede i stavi ih u red
		for (int j = 0; j < dim; j++) {					//za sve susede cvora tekuci
			if (graf[tekuci - 1][j] != 10000) {			//ako je sused (postoji grana)
				if (flags[j] == 0) {					//ako je uz to i neposecen
					// poseti ga i stavi u red
					flags[j] = 1;
					redic.push(j+1);
				}
			}
		}
	}

	for (int i = 0; i < dim; i++) {
		if (flags[i] == 0) {
			delete[] flags;
			return false;
		}
	}
	delete[] flags;
	return true;
}

int Primov(int** &graf, int dim) {
	//prvo provera da li je graf povezan
	if ((povezan(graf, dim)) == false) {
		cout << endl<< "Uneli ste nepovezan graf";
		return 0;
	}
	else {
		int cena = 0;

		int* flags = new int[dim];
		for (int i = 0; i < dim; i++) {
			flags[i] = 0;
		}

		int tekuci = 0;	//
		//nasumicno odaberes prvi cvor i setujes ga da je obradjen
		tekuci = rand() % dim;
		flags[tekuci] = 1;	

		int brojac = dim - 1;
		while (brojac) {
			//iz skupa obradjenih cvorova, nadji granu najmanje tezine, koja povezuje jedan cvor iz skupa obradjenih sa jednim iz skupa neobradjenih
			int min = 100000;
			int neobradjen = 0;
			int obradjen = 0;
			for (int i = 0; i < dim; i++) {						//prolazi kroz sve cvorove da nadje one obradjene (i)
				if (flags[i] == 1) {							//pronadjen je obradjen cvor (i)
					for (int j = 0; j < dim; j++) {				//prolazi kroz sve cvorove da nadje neobradjene (j)
						if (graf[i][j] != 10000) {				//neobradjeni cvor ima granu s jednim od obradjenih
							if (graf[i][j] < min) {				//pronadjen je novi minimum
								min = graf[i][j];
								neobradjen = j;
								obradjen = i;
							}
						}
					}
				}
			}
			//dodas nadjeni minimum u sumu
			cena += min;
			//setujes cvor kao obradjen
			flags[neobradjen] = 1;
			//uklonis pronadjenu minimalnu granu iz matrice
			uklonigranu(graf, dim, obradjen, neobradjen);			

			brojac--;
		}
		delete[] flags;
		return cena;
	}
}

void Djikstra(int** &graf, int* &d, int* &t, int dim, int v) {
	int x = v - 1;
	int* flags = new int[dim];
	for (int i = 0; i < dim; i++) {
		flags[i] = 0;
	}
	flags[x] = 1;
												 
	for (int i = 0; i < dim; i++) {				
		d[i] = graf[x][i];
		if (d[i] == 0) {
			d[i] = 10000;
		}
		d[x] = 10000;
	}
	
	for (int i = 0; i < dim; i++) {
		if (graf[x][i] != 10000) {						
			t[i] = v;
		}
		else t[i] = 0;		
		t[x]=0;										
	}
					
	for (int k = 1; k < dim; k++) {
	//nadjes min rastojanje u vektoru d[], ali takvo da cvor nije obradjen
		int min = 10000;
		int mincvor = -1;
		for (int i = 0; i < dim; i++) {
			if (flags[i] != 1) {
				if (d[i] < min) {
					min = d[i];
					mincvor = i+1;
				}
			}
		}
		if (mincvor == -1) return;
	//nadjeni cvor dodas u obradjene
		flags[mincvor - 1] = 1;
	//prolazis kroz sve preostale neobradjene cvorove i gledas mozes li da smanjih rastojanja
	//kad nadjes da moze da se smanji, update tabele prethodnika
		for (int j = 0; j < dim; j++) {
			if (flags[j] != 1) {
				if ((d[mincvor-1]+graf[mincvor-1][j])<=d[j] ) {		
					d[j] = d[mincvor-1] + graf[mincvor-1][j];
					t[j] = mincvor;
				}
			}
		}
	}
}

//Print the stack (pomocna test funkcija)
void showstack(stack <int> s){
	while (!s.empty())
	{
		cout << '\t' << s.top();
		s.pop();
	}
	cout << '\n';
}

void putevi(int cv,int v, string& put, int& brojp, int** grafsvi, int** grafizg, int* trace, int &ukupp) {
	stack<int> s;
	brojp = 0;
	ukupp = 0;
	put = "";
	s.push(cv + 1);
	int preth = cv + 1;					
	int citajlok = cv;
	int procitan = trace[citajlok];
	int nastavi = 1; 
	while (nastavi) {
		if (procitan == 0) {
			nastavi=0;	
		}
		else {
			if (grafizg[preth - 1][procitan - 1] == 10000) {
				brojp++;
			}
			ukupp += grafsvi[preth - 1][procitan - 1];			
			s.push(procitan);
			preth = procitan;							
			citajlok = procitan - 1;
			procitan = trace[citajlok];
		}
	}
	//na steku se nalaze cvorovi u poretku, sad ih samo skini sa steka i ubaci u string
	int indeks = 0;
	while (!s.empty()) {
		if (indeks != 0) { put += "-"; }
		indeks = s.top();
		if (indeks == v) {
			put += 'V';
		}
		else {
			put += to_string(indeks);
		}
		s.pop();
	}
}


int main() {
	int** graf = nullptr;
	int** grafsvi = nullptr;
	int** grafizgradjeni = nullptr;
	int dim = 0;
	int x = -1;
	int pocetni = -1;
	int krajnji = -1;
	int tezina = 0;
	int V = -1;
	int* gsd = nullptr;
	int* gst = nullptr;
	int* gid = nullptr;
	int* git = nullptr;
	string putsvi, putizg;
	int brojpsvi = 0, brojpizg = 0;
	int broj = 0;

	int op = 0;
	int dalje = 1;
	int dalje1 = 1;
	int dalje2 = 1;

	while (op != 3) {
		cout << endl;
		cout << "Unesite redni broj operacije koju zelite da izvrsite nad grafom: " << endl;
		cout << "1. Stvaranje i ispis metroa" << endl;
		cout << "2. Pronalazenje najkrace rute za vatrogasna kola" << endl;
		cout << "3. Kraj rada" << endl;
		cin >> op;

		switch (op) {
		case 1:
			cout << "Unesite potrebne informacije o metrou:" << endl;
			cout << "broj kljucnih lokacija:";
			cin >> dim;
			kreirajgraf(graf, dim);
			while (dalje == 1) {
				cout << "Unesite indekse lokacija koje je moguce povezati: ";
				cin >> pocetni >> krajnji;
				if (pocetni == krajnji) {
					cout << "Ne mozete povezati grad sam sa sobom!" << endl;
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje;
				}
				else if (pocetni <= 0 || krajnji <= 0 || pocetni > dim || krajnji > dim) {
					cout << "Uneli ste nepostojecu vrednost cvora" << endl;
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje;
				}
				else {
					cout << "Unesite cenu puta izmedju te dve lokacije: ";
					cin >> tezina;
					dodajgranu(graf, dim, pocetni, krajnji, tezina);
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje;
				}
			}
			cout << "Minimalna cena metroa je:";
			cout << endl << (Primov(graf, dim)) << endl;
			brisi(graf, dim);
			break;
		case 2:
			//Unos dimenzija ako ne postoje vec
			if (!dim) {
				cout << "Unesite broj lokacija: " << endl;
				cin >> dim;
			}
			//kreiranje dva tipa grafa
			kreirajgraf(grafsvi, dim);
			kreirajgraf(grafizgradjeni, dim);
			//Unos v
			cout << "Unesite indeks parkiralista vozila: ";
			cin >> V;
			if (V <= 0 || V > dim) {
				cout << "Uneli ste nepostojecu lokaciju " << endl;
				break;
			}
			//unos puteva u obe vrste matrice
			while (dalje1 == 1) {
				cout << "Unesite lokacije izmedju kojih postoji izgradjen put: ";
				cin >> pocetni >> krajnji;
				if (pocetni == krajnji) {
					cout << "Ne mozete povezati grad sam sa sobom!" << endl;
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje1;
				}
				else if (pocetni <= 0 || krajnji <= 0 || pocetni > dim || krajnji > dim) {
					cout << "Uneli ste nepostojecu vrednost cvora" << endl;
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje1;
				}
				else {
					cout << "Unesite duzinu puta izmedju te dve lokacije: ";
					cin >> tezina;
					dodajgranu(grafsvi, dim, pocetni, krajnji, tezina);
					dodajgranu(grafizgradjeni, dim, pocetni, krajnji, tezina);
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje1;
				}
			}
			while (dalje2 == 1) {
				cout << "Unesite lokacije izmedju kojih je moguce izgraditi put: ";
				cin >> pocetni >> krajnji;
				if (pocetni == krajnji) {
					cout << "Ne mozete povezati grad sam sa sobom!" << endl;
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje2;
				}
				else if (pocetni <= 0 || krajnji <= 0 || pocetni > dim || krajnji > dim) {
					cout << "Uneli ste nepostojecu vrednost cvora" << endl;
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje2;
				}
				else {
					cout << "Unesite duzinu puta izmedju te dve lokacije: ";
					cin >> tezina;
					dodajgranu(grafsvi, dim, pocetni, krajnji, tezina);
					cout << "Zelite li da unesete jos lokacija? Unesite 1 za nastavak, bilo sta drugo za prekid: ";
					cin >> dalje2;
				}
			}

			//formiranje d i t
			gsd = new int[dim];
			gst = new int[dim];
			gid = new int[dim];
			git = new int[dim];
			Djikstra(grafsvi, gsd, gst, dim, V);
			Djikstra(grafizgradjeni, gid, git, dim, V);

			//ispis putanja
			cout << "Najkrace putanje su: " << endl;
			for (int i = 0; i < dim; i++) {
				if (i != (V - 1)) {
					cout << "Najkraci put za lokaciju " << (i + 1) << ":  ";
					if (gsd[i] == gid[i]) {
						putevi(i, V, putsvi, brojpsvi, grafsvi, grafizgradjeni, gst, broj);
						putevi(i, V, putizg, brojpizg, grafsvi, grafizgradjeni, git, broj);
						if (brojpizg < brojpsvi) {
							cout << "Ukupna duzina puta: " << broj << endl;
							cout << putizg << " broj neizgradjenih puteva: " << brojpizg << endl;
							cout << putsvi << " broj neizgradjenih puteva: " << brojpsvi << endl;
						}
						else if (brojpizg > brojpsvi) {
							cout << "Ukupna duzina puta: " << broj << endl;
							cout << putsvi << " broj neizgradjenih puteva: " << brojpsvi << endl;
							cout << putizg << " broj neizgradjenih puteva: " << brojpizg << endl;
						}
						else if (brojpizg == brojpsvi) {
							cout << "Ukupna duzina puta: " << broj << endl;
							cout << putsvi << " broj neizgradjenih puteva: " << brojpsvi << endl;
						}

					}
					else if (gsd[i] > gid[i]) {
						putevi(i, V, putizg, brojpizg, grafsvi, grafizgradjeni, git, broj);
						//ispisuje se za matricu izgradjenih
						cout << "Ukupna duzina puta: " << broj << endl;
						cout << putizg << " broj neizgradjenih puteva: " << brojpizg << endl;
					}
					else if (gsd[i] < gid[i]) {
						putevi(i,V, putsvi, brojpsvi, grafsvi, grafizgradjeni, gst, broj);
						//ispisuje se za matricu svih
						cout << "Ukupna duzina puta: " << broj << endl;
						cout << putsvi << " broj neizgradjenih puteva: " << brojpsvi << endl;
					}
				}
			}
			brisi(grafsvi, dim);
			brisi(grafizgradjeni, dim);
			delete[]gst;
			delete[]git;
			delete[]gsd;
			delete[]gid;
			break;
		case 3:
			exit(1);
		default:
			cout << "Uneli ste nepostojeci redni broj operacije. Ponovite unos";
			break;
		}
	}
}