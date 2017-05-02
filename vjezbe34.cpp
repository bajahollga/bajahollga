 	
										//binarne citanje:
ifstream is("banke.bin", ios_base::binary);
int n; //za int
in.read((char*)&n, sizeof(n));
//za stringove:
int n;
in.read((char*)&n, sizeof(n));  //citaj duljinu stringa
char* temp = new char[length];  //alociraj mem na hrpi
in.read(temp, n);    //procitaj znakove u mem
string s = string s(temp, n);  //string na stogu
delete[] temp;  //oslobodi mem
							//PRIMJER vektori citanje (vj1 zad 4)
struct banka
	{
		string ime;
		string broj;
	};

	banka ba;
	vector<banka>vektor;

string temp;

	while (true)
	{
		short duljina;

		if (!dat.read((char*)&duljina, sizeof(duljina))) {  //duljina stringa
			break;
		}


		char* pchar = new char[duljina];
		dat.read(pchar, duljina); //sad procita string u naziv;
		string naziv = string(pchar, duljina);
		delete[] pchar;

		int b = 7;   //nastavlja se, nije zapisano koliko je dugacak
		//vmbdi
		char* ppchar = new char[b];
		dat.read(ppchar, b); //duljina stringa
		string vmbdi = string(ppchar, b);

		delete[] ppchar;

		ba.ime = naziv;  //za vektor
		ba.broj = vmbdi; //za vektor
		
		vektor.push_back(ba); //za vektor
	}

	for (int i = vektor.size() - 1; i >= 0; i--)  //obrnuti  //za print vektora i strukture
	//for (int i = 0; i < vektor.size(); i++)
	{
		cout << vektor[i].ime << "; " << vektor[i].broj << endl;
		}

	dat.close();

										//binarne pisanje:
int broj =55; //za int
dat.write((char*)&broj, sizeof(broj));
//za stringove:								

string s = "Miro";

int length = s.length();//duljina u bajtovima
out.write((char*)&length, sizeof(length)); //pisi broj znakova stringa
out.write(s.c_str(), length);//upisi string
								//PRIMJER vektori pisanje (vj1, zad 4)
int n = vektor.size();
	//cout << n << endl;
	for (size_t i = 0; i < n; i++)
	{
		string novabanka = vektor[i].ime;
		short duljina = novabanka.length();

		out.write((char*)&duljina, sizeof(duljina)); //duljina stringa
		out.write(novabanka.c_str(), duljina);  //string ime


		string novibroj = vektor[i].broj;
		short duljina2 = 7;
		out.write(novibroj.c_str(), duljina2);  //string broj
	}
	out.close();




									//zadatak pravokutnici   		

void ucitaj(pravokutnik *pravokutnici, int length) {
	for (int i = 0; i < length; i++) {
		cout << "Unesite sirinu " << i + 1 << ". pravokutnika:";
		cin >> pravokutnici[i].sirina;
		cout << "Unesite visinu " << i + 1 << ". pravokutnika:";
		cin >> pravokutnici[i].visina;
	}
}

void upisi(pravokutnik *pravokutnici, int length, ofstream &os) {
	for (int i = 0; i < length; i++) {
		os << "P("<< pravokutnici[i].sirina << "," << pravokutnici[i].visina << ")=" << pravokutnici[i].povrsina() << endl;
	}
}
pravokutnik pravokutnici[5];
    int n = sizeof(pravokutnici) / sizeof(pravokutnik);


												//pomnozi primjer
razlomak::razlomak(int brojnik, int nazivnik) {
	this->_brojnik = brojnik;
	this->_nazivnik = nazivnik;
}

string razlomak::to_string() {
	stringstream ss;
	ss << this->_brojnik << "/" << this->_nazivnik;
	return ss.str();
}

void razlomak::pomnozi(int n) {
	this->_brojnik *= n;

}





											//3.zadatak, 1.vjezbe -citaj iz csv                                                                

		string temp;
		getline(dat, temp);//prvi red

		while (getline(dat,temp))
		{

			string naziv;
			getline(dat, naziv, ';');
			cout << naziv << ';';

			string sifra;
			getline(dat, sifra, ';');
			cout << sifra << ';';

			double zbroj = 0;

			for (int i = 0; i < 48; i++) //ima 48 brojeva + jos jedan zadnji
			{
				string brojevi;
				getline(dat, brojevi, ';');
				zbroj += atof(brojevi.c_str());
			}
			
			//jos zadnji ostao
			string zadnji;
			getline(dat, zadnji);
			zbroj+= atof(zadnji.c_str());

			cout <<fixed<< zbroj << endl;
		}

										
										//2.vjezbe 1.zadatak tocke
#include <iostream>
#include <iomanip>
#include <fstream>
#include "tocka.h"
#include "high_res_timer.h"

using namespace std;

tocka* pripremi_polje_tocki(int n) {
	tocka* tocke = new tocka[n];
	for (int i = 0; i < n; i++) {
		tocke[i].inicijaliziraj(i, i);
	}
	return tocke;
}

int main() {
//def tip podatka za cuvanje o tockama. napravi polje
	hr_timer timer;

	int nr = 1000;
	nr = 10000;
	nr = 20000;
	nr = 100000;

	tocka *tocke = pripremi_polje_tocki(nr);

	ofstream os("udaljenosti.txt");
	if (!os) {
		cout << "Nije moguce stvoriti datoteku" << endl;
		return 1;
	}
    //setprecision(12) - to je odgovor na pitanje kako rijesiti problem s datotekom (nepreciznost, bez tocke)
	//ali bolje je koristiti fixed - ne treba iomanip import!
    start_hr_timer(timer);
	for (int i = 0; i < nr; i++) {
		double d = tocke[i].udaljenost_od_ishodista();
		os << "d(" << tocke[i].dohvati_x() << ", " << tocke[i].dohvati_y() << ") = " << setprecision(12) << d << endl;
	}

	stop_hr_timer(timer);
	cout << "Proteklo je " << get_elapsed_time_microsec(timer) / 1000 << "ms" << endl;
	os.close();

	delete[] tocke;

	return 0;
}
#ifndef _TOCKA_H_
#define _TOCKA_H_

class tocka {
private:
	int x;
	int y;
public:
	void inicijaliziraj(int x, int y);
	double udaljenost_od_ishodista();
	int dohvati_x();
	int dohvati_y();
};

#endif
#include <cmath>
#include "tocka.h"

using namespace std;

void tocka::inicijaliziraj(int x, int y) {
	this->x = x;
	this->y = y;
}

double tocka::udaljenost_od_ishodista() {
	return sqrt(pow(x, 2) + pow(y, 2));
}


int tocka::dohvati_x() {
	return this->x;
}
int tocka::dohvati_y() {
	return this->y;
}
											//quick sort i bubble sort
#include <iostream>
#include <ctime>
#include "high_res_timer.h"
#include "funkcije_za_sortiranje.h"

using namespace std;

int generate_random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int* kreiraj_polje(int n) {

    srand(time(nullptr));
	int* polje = new int[n];
	for (int i = 0; i < n; i++) {
		polje[i] = generate_random(1, 1000);
	}

	return polje;
}

int* kopiraj_polje(int *polje, int n) {

	int* kopija = new int[n];
	for (int i = 0; i < n; i++) {
		kopija[i] = polje[i];
	}
	return kopija;
}




int main() {

    //cout << rand() << endl;
	int n = 1000;
	n = 10000;
	n = 20000;

	int* brojevi1 = kreiraj_polje(n);
	int* brojevi2 = kopiraj_polje(brojevi1, n);

	hr_timer timer;

    start_hr_timer(timer);
    quick_sort(brojevi1, n);
    stop_hr_timer(timer);

    cout << "Quick sort:" << fixed << get_elapsed_time_microsec(timer) / 1000 << " ms" << endl;


    start_hr_timer(timer);
	bubble_sort(brojevi2, n);
	stop_hr_timer(timer);

	cout << "Bubble sort:" << fixed << get_elapsed_time_microsec(timer) / 1000 << " ms" << endl;

	delete[] brojevi1;
	delete[] brojevi2;


	return 0;
}
										//2.vjezbe, 3 zadatak
								//studenti, polje, slucjna vrijednost od do

#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <string>

using namespace std;

class student {
private:
	string ime;
	string prezime;
	int god_rodjenja;
public:
	void inicijaliziraj(string ime, string prezime, int god_rodjenja);
	string to_string();
};
#endif
#include <sstream>
#include "student.h"

using namespace std;

void student::inicijaliziraj(string ime, string prezime, int god_rodjenja) {
	this->ime = ime;
	this->prezime = prezime;
	this->god_rodjenja = god_rodjenja;
}

string student::to_string() {
	stringstream ss;
	ss << ime << ", " << prezime << ", " << god_rodjenja;
	return ss.str();
}
#include <iostream>
#include <ctime>
#include "student.h"


int generate_random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void kreiraj_studente(student* polje, int n) {

	srand(time(nullptr));
	for (int i = 0; i < n; i++) {
		cout << "Unesite ime " << i + 1 << ". studenta:";
		string ime;
		getline(cin, ime);
		cout << "Unesite ime " << i + 1 << ". studenta:";
		string prezime;
		getline(cin, prezime);
		int god_rodjenja = generate_random(1961, 1997);
		polje[i].inicijaliziraj(ime, prezime, god_rodjenja);
	}
}

int main() {

	student polje[5];
	kreiraj_studente(polje, sizeof(polje) / sizeof(student));
	for (int i = 0; i < sizeof(polje) / sizeof(student); i++) {
		cout << polje[i].to_string() << endl;
	}

	return 0;
}


										//2.vjezbe, 4 zadatak     binarne
								//prepisi samo nazive u binarnu
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

void write_string(string line, ofstream &out) {
    short length = line.length();
    out.write((char*)&length, sizeof(length));
    out.write(line.c_str(), length);
}

string read_string(short length, ifstream &in) {
    char* temp = new char[length];
    in.read(temp, length);
    string s(temp, length);
    delete[] temp;
    return s;
}


int main() {

	ifstream is("Broj_znanstvenika_na_milijun_stanovnika.csv");
	ofstream os("nazivi_drzava.dat", ios_base::binary);

	if (!is || !os) {
		cout << "Unable to open file" << endl;
		return 1;
	}

	string line;
    //skip header
	getline(is, line);
	while (getline(is, line)) {
		stringstream ss(line);
		string naziv;
		getline(ss, naziv, ';');
		//cout << naziv << endl;
        write_string(naziv, os);
    }
	os.close();
	is.close();

    //checking
    ifstream bin("nazivi_drzava.dat", ios_base::binary);
    if (!bin) {
        cout << "nije moguce pristupiti datoteci" << endl;
        return 2;
    }
    while (true) {
        short length;
        if (!bin.read((char*)&length, sizeof(length))) {
            break;
        }
        string naziv = read_string(length, bin);
        cout << naziv << endl;
    }

    bin.close();
	return 0;
}
							//zadatak 5 vjezbe 2 prepisi nazive za koje nema podataka

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
using namespace std;

int main() {
	
	ifstream dat("Broj_znanstvenika_na_milijun_stanovnika.csv");
	if (!dat) {
		cout << "Greska pri otvaranju datoteke" << endl;
		return 1;
	}

	string temp;
	getline(dat, temp); 

	string naziv;
	
	bool nema_podataka;
	while (getline(dat, naziv, ';')) {
	
		// Provjera ima li u 10 godina ijedan podatak (čim nađem prvi, ne moram dalje tražiti).
		nema_podataka = true;
		for (int i = 0; i < 10; i++) {
			getline(dat, temp, ';');

			if (temp!="")
			{
				nema_podataka = false;
				break;
			}

		}
		getline(dat, temp); // Odbacim ostatak linije.

		if (nema_podataka) {
			cout << naziv << endl;
		}
	}

	dat.close();
	//string line;  //ili ovako
//getline(is, line);
//while (getline(is, line)) {
//
//	stringstream ss(line);
//	string naziv;
//	getline(ss, naziv, ';');
//
//	string temp;
//	bool nema_podataka = true;
//	for (int i = 0; i < 10; i++) {
//		stringstream converter;
//		getline(ss, temp, ';');
//		converter << temp;
//		int broj_znanstvenika;
//		if (converter >> broj_znanstvenika) {
//			nema_podataka = false;
//			break;
//		}
//	}
//
//
//	if (nema_podataka) {
//		cout << naziv << endl;
//	}
//}
//is.close();

	return 0;
}










//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//4.zadatak, 3.vjezbe
using namespace std;
int main() {
	ifstream dat("Life_expectancy.csv");
	if (!dat) {	cout << "Greska" << endl;	return 404;	}

	lista_poljem lista;
	string temp;
	getline(dat, temp); //prvi red u smece
	int brojac = 0;
	while (getline(dat, temp))
	{
		brojac++;
		stringstream ss; //bacva
		ss << temp;
		ELTYPE drzava;
		getline(ss, drzava.naziv, ';'); //naziv u strukturu

		string privremeni; //broj u strukturu
		getline(ss, privremeni, ';');

		if (!(drzava.dob = atof(privremeni.c_str())))
		{
			drzava.dob = 0;
		}
		lista.insert(drzava, lista.end());//trpat u listu
	}

	//printanje
	/*for (POSITION i = lista.first(); i < lista.end(); i=lista.next(i))
	{
		ELTYPE element;
		lista.read(i, element);
		cout << element.naziv << ", " << element.dob << endl;	}*/

	//racunaj prosjek
	double zbroj = 0;
	ELTYPE z_dob;
	for (POSITION i = lista.first(); i < lista.end(); i = lista.next(i))
	{
		lista.read(i, z_dob);
		zbroj += z_dob.dob;

	}
	cout << "Prosjek: " << zbroj / brojac << endl;
	
	string unos;

	bool dalje;
	do              //nek unosi naziv drzave i trazi
	{
		cout << "unesi naziv" << endl;
		getline(cin, unos);

		ELTYPE dummy;
		dummy.naziv = unos;

		POSITION nadjen = lista.find(dummy);

		if (nadjen != lista.end())
		{
			cout << "Drzava postoji" << endl;

			//pretrazi listu da nađemo dob
			lista.read(nadjen, dummy);//na poziciji npr. Croatia procitaj u stukturi
			cout << "Dob je: " << dummy.dob << endl;
			
		}
		else
		{
			cout << "nema je" << endl;
		}

		cout << "Dalje 1/0 " << endl;
		cin >> dalje;
		cin.ignore();
	} while (dalje == 1);


	dat.close();

	return 0;
}

                                                                      //5.zadatak 4 vjezbe

	lista_dinamicka lista;


	string temp;
	getline(dat, temp);//prvi red

	while ((getline(dat,temp)))
	{
		//cout << temp << endl;
		stringstream ss;
		ss << temp;//bacva

		string smece;
		ELTYPE drzava;
		getline(ss, drzava.naziv, ';');
		getline(ss, drzava.sifra, ';');

		getline(ss, smece);

		lista.insert(drzava, lista.first());

	}

	/*for (POSITION i = lista.first(); i != lista.end(); i=lista.next(i))
	{
		ELTYPE element;
		lista.read(i, element);
		cout << element.naziv << "; " << element.sifra << endl;
	}*/

	dat.close();

	//sad od korisnika ucitat slovo da 

	char slovo;
	cout << "Unesi slovo" << endl;
	cin >> slovo;

	for (POSITION i = lista.first(); i != lista.end(); i = lista.next(i))
	{
		ELTYPE element;
		lista.read(i, element);

		if (toupper(element.naziv[0]) == toupper(slovo))
		{
			cout << element.naziv << endl;		}	}
