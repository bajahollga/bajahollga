 	
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










/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


POSITION lista_poljem::find(double min) {    //dodaj u listu, vraca prvi elemen cija dob je manja od zadane
	for (POSITION i = first(); i < end(); i++) {
		if (_elements[i - 1].ocekivanje < min) {
			return i;
		}
	}
	return end();
}
//POSITION position_found = lista.find(min);     //ucitava i uklanja iz liste
	//while (position_found != lista.end()) {
	//	lista.remove(position_found);
	//	//cout << position_found << endl;
	//	position_found = lista.find(min);
	//}

	//dat.close();

	//for (POSITION i = lista.first(); i < lista.end(); i = lista.next(i)) {
	//	ELTYPE element;
	//	if (lista.read(i, element)) {
	//		cout << element.drzava << "(" << element.ocekivanje << ")" << endl;
	//	}
	//}


									//1.4 vjezbe //ubaci random brojeve u dinam
#include <iostream>
#include <ctime>
#include "lista_dinamicka.h"
#include "high_res_timer.h"

using namespace std;

int random(int min, int max) {
	return rand() % (max - min + 1) + min;
}


int main() {
	srand(time(nullptr));

	lista_dinamicka lista;
	hr_timer timer;

	start_hr_timer(timer);
	for (int i = 0; i < 100000; i++) {
		ELTYPE broj = random(1, 100);
		lista.insert(broj, lista.first());
	}

	double suma = 0;
	int nr_elem = 0;
	for (POSITION i = lista.first(); i != lista.end(); i = lista.next(i)) {
		ELTYPE broj;
		lista.read(i, broj);
		suma += broj;
		nr_elem++;
	}

	stop_hr_timer(timer);

	cout << "Prosjek brojeva: " << suma / nr_elem << endl;
	cout << "Vrijeme potrebno: " << get_elapsed_time_microsec(timer)/1000 << endl;
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

										//2.5.vjezbe stog
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "stog_dinamicki.h"

using namespace std;


int main() {

	stog_dinamicki stog;

	string naredba;
	string temp;
	string rijec;
	string na_vrh_stoga;
	stringstream ss;



	cout << "Unesi naredbu  (ADD rijec, UNDO ili EXIT)  "<< endl;
	while (getline(cin,naredba))
	{
		cout << "Unesi naredbu  (ADD rijec, UNDO ili EXIT)  " << endl;

		if (naredba=="UNDO")
		{
			stog.pop(temp);  //vraca element s vrha i brise ga
		}
		else if (naredba == "EXIT")
		{
			break;
		}
		
		else {	
			ss.str(""); //ocisti stringstream
			ss.clear();

			ss << naredba;
			getline(ss, temp, ' ');//naredbu u smece
			getline(ss, rijec);  //rijec u string rijec

			ss.str("");//ocisti stringstream
			ss.clear();

			//sad rijec u bacvu:
			ss << na_vrh_stoga << " " << rijec;


			stog.push(ss.str());  //utrpaj u stog iz bacve


		}

		cout << "--> ";
		stog.top(na_vrh_stoga);
		cout << na_vrh_stoga << endl;
		
		
		/*f (stog.top(na_vrh_stoga))
		{
			cout << na_vrh_stoga << endl;
		}
		else
		{
			cout << endl;
		}*/
		

	}


	return 0;
}
											//5.vj  5 zad- red
											//upis slanje ili kraj
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "red_dinamicki.h"

using namespace std;

int odabir() {
	system("cls");
	cout << "Odaberi: " << endl;
	cout << "1: upis novog broja" << endl;
	cout << "2: slanje u dat" << endl;
	cout << "3: kraj" << endl;
	int opcija;
	cin >> opcija;
	return opcija;

}

bool slanje(red_dinamicki &red, ofstream &out) {

	while (!red.is_empty())
	{
		ELTYPE element;
		red.dequeue(element);
		out << element << endl;
	}

	return true;
}


int main() {
	ofstream out("output.txt");
	if (!out)
	{
		cout << "Greska" << endl;
		return 404;
	}
	//u petlji nudi opcije:
	//			upis novog broja
	//			slanje u datoteku
	//			kraj rada
	red_dinamicki red;

	bool dalje = true;
	do
	{
		int n = odabir();
		if (n==1)//upis
		{
			cout << "Upisi broj" << endl;
			ELTYPE broj;
			cin >> broj;
			red.enqueue(broj);
		}


		else if (n==2)//slanje
		{
			slanje(red, out); //upisat ce i vratit true da se moze vrtit dalje

		}
		else
		{
			dalje = false;
		}

	} while (dalje);
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									//bin. stabla 6. vj, zad 1    impl. poljem
	#include <iostream>
#include "binarno_stablo.h"
using namespace std;

//    78
//  1   14
//     15  99
//itd

int main() {
	//ima 31 cvor, promijenit capacity

	binarno_stablo stablo;

	stablo.create(78); //to je root

	//78 ima djecu 1 i 14

	POSITION root = stablo.root(); //kazemo koja je pozicija
	stablo.insert_left(root, 1); //koje je lijevo dijete
	stablo.insert_right(root, 14);  //koje je desno dijete
	
	//1 nema djece, idemo na 14
	POSITION p_14 = stablo.get_right_child(root);
	//broj 14 je desno dijete od rota
	stablo.insert_left(p_14, 15); //dodamo mu lijevo dijete
	stablo.insert_right(p_14, 99); //dodamo mu lijevo dijete

	//15 nema djece, idemo na 99
	POSITION p_99 = stablo.get_right_child(p_14);
	//broj 99 je desno dijete od 14
	stablo.insert_left(p_99, 3); //dodamo mu lijevo dijete
	stablo.insert_right(p_99, 4); //dodamo mu lijevo dijete

	//sad na 3
	POSITION p_3 = stablo.get_right_child(p_99);
	//broj 3 je lijevo dijete od 99
	stablo.insert_left(p_3, 29); //dodamo mu lijevo dijete
	stablo.insert_right(p_3, 67); //dodamo mu lijevo dijete

	//sad na 4
	POSITION p_4 = stablo.get_right_child(p_99);
	//broj 4 je desno dijete od 99
	//nema lijevo dijete
	stablo.insert_right(p_4, 11); //dodamo mu lijevo dijete


	stablo.print_tree(); //malo sam promijenio metodu da ne printa adrese ako nema broja

	return 0;
}
											//din. stablo  2.zadatak/6vj
	struct Osoba
{
	string ime;
	string prezime;
	Osoba(string ime, string prezime);
	Osoba();
};
	Osoba::Osoba(string ime, string prezime)
{
	this->ime = ime;
	this->prezime = prezime;
}

Osoba::Osoba()
{
}
	#include<iostream>
#include<string>
#include"binarno_stablo_dinamicko.h"
#include "Osoba.h"
using namespace std;


int main() {

	binarno_stablo stablo;

	ELTYPE ana("Ana", "Anic");
	ELTYPE juro("Juro", "Juric");
	ELTYPE iva("Iva", "Ivic");
	ELTYPE ferdo("Ferdo", "Ferdic");
	ELTYPE dino("Dino", "Dinic");
	ELTYPE ema("Ema", "Emic");

	stablo.create(ana);
	POSITION root = stablo.root();

	stablo.insert_left(root, juro);
	stablo.insert_right(root, iva);

	POSITION p_iva = stablo.get_right_child(root);
	stablo.insert_left(p_iva, ferdo);

	POSITION p_ferdo = stablo.get_left_child(p_iva);
	stablo.insert_left(p_ferdo, dino);
	stablo.insert_right(p_ferdo, ema);

	stablo.print_tree(stablo.root(), 0);

	return 0;
}
	////////////////////////////////////////////////////////////      
	//definicija cvora da sadrzi i pokazivac na roditelja				//promijeni da pokazuje parent
#ifndef _BINARNO_STABLO_H_
#define _BINARNO_STABLO_H_

#include <iostream>
#include <string>
#include "Osoba.h"

using namespace std;

typedef Osoba ELTYPE;

struct cvor;

typedef cvor* POSITION;

struct cvor {
	ELTYPE element;
	POSITION left_child;
	POSITION right_child;
	POSITION parent;
};

class binarno_stablo {
private:
	POSITION root_node;
	POSITION create_new_node(const ELTYPE& element);

public:
	void create(const ELTYPE& element);
	bool insert_left(const POSITION parent, const ELTYPE& element);
	bool insert_right(const POSITION parent, const ELTYPE& element);
	POSITION root();
	POSITION get_left_child(const POSITION parent);
	POSITION get_right_child(const POSITION parent);
	bool get_node(const POSITION pos, ELTYPE& element);
	void print_tree(const POSITION node, int level);
};

#endif	
	
	#include "binarno_stablo_dinamicko.h"
#include "Osoba.h"
#include <iostream>
using namespace std;

/*************** PRIVATNE METODE ****************/

POSITION binarno_stablo::create_new_node(const ELTYPE& element) {
	cvor* novi = new cvor;
	novi->element = element;
	novi->left_child = nullptr;
	novi->right_child = nullptr;
	novi->parent = nullptr;
	
	return novi;
}

/*************** JAVNE METODE ****************/

void binarno_stablo::create(const ELTYPE& element) {
	root_node = create_new_node(element);
}

bool binarno_stablo::insert_left(const POSITION parent, const ELTYPE& element) {
	if (parent->left_child != nullptr) {
		return false;
	}

	parent->left_child = create_new_node(element);
	parent->left_child->parent = parent;
	return true;
}

bool binarno_stablo::insert_right(const POSITION parent, const ELTYPE& element) {
	if (parent->right_child != nullptr) {
		return false;
	}

	parent->right_child = create_new_node(element);
	parent->right_child->parent = parent;
	return true;
}

POSITION binarno_stablo::root() {
	return root_node;
}

POSITION binarno_stablo::get_left_child(const POSITION parent) {
	return parent->left_child;
}

POSITION binarno_stablo::get_right_child(const POSITION parent) {
	return parent->right_child;
}

bool binarno_stablo::get_node(const POSITION pos, ELTYPE& element) {
	element = pos->element;
	return true;
}

void binarno_stablo::print_tree(const POSITION node, int level) {
	if (node == nullptr) { return; }

	ELTYPE element;
	if (get_node(node, element)) {
		for (int i = 0; i < level; i++) { cout << " "; }
		//cout << element.ime<<" "<<element.prezime<< endl; // TU MIJENJAJ ISPIS.
		cout << element.to_string()<< endl; // TU MIJENJAJ ISPIS.
	}

	print_tree(node->left_child, level + 3);
	print_tree(node->right_child, level + 3);
}
	
	
	
	struct Osoba
{
	string ime;
	string prezime;
	Osoba(string ime, string prezime);
	Osoba();

};
	#include "Osoba.h"

Osoba::Osoba(string ime, string prezime)
{
	this->ime = ime;
	this->prezime = prezime;
}

Osoba::Osoba()
{
}
		
	
	

int main() {

	binarno_stablo stablo;

	ELTYPE ana("Ana", "Anic");
	ELTYPE juro("Juro", "Juric");
	ELTYPE iva("Iva", "Ivic");
	ELTYPE ferdo("Ferdo", "Ferdic");
	ELTYPE dino("Dino", "Dinic");
	ELTYPE ema("Ema", "Emic");

	stablo.create(ana);
	POSITION root = stablo.root();

	stablo.insert_left(root, juro);
	stablo.insert_right(root, iva);

	POSITION p_iva = stablo.get_right_child(root);
	stablo.insert_left(p_iva, ferdo);

	POSITION p_ferdo = stablo.get_left_child(p_iva);
	stablo.insert_left(p_ferdo, dino);
	stablo.insert_right(p_ferdo, ema);

	stablo.print_tree(stablo.root(), 0);

	POSITION temp = stablo.get_right_child(p_ferdo);
	int n = 0;
	while (temp->parent !=nullptr)
	{
		n++;
		temp = temp->parent;
	}

	cout << "Dubina zadnjeg je: " << n << endl;

	return 0;
}	
	
	
	
	
	
	
	
	//vj.7 1.zad	//binarno stablo/inorder/pre/post
	#include <iostream>
#include "binarno_stablo.h"

using namespace std;

int main() {
	//								63
	//						32				70
	//				27			33					90
	//					30			50						92
	binarno_stablo stablo;
	stablo.create(63);
	
	POSITION root = stablo.root();
	stablo.insert_left(root, 32);
	stablo.insert_right(root, 70);
	
	POSITION node_32 = stablo.get_left_child(root);
	stablo.insert_left(node_32, 27);
	stablo.insert_right(node_32, 33);

	POSITION node_27 = stablo.get_left_child(node_32);
	stablo.insert_right(node_27, 30);

	POSITION node_33 = stablo.get_right_child(node_32);
	stablo.insert_right(node_33, 50);

	POSITION node_70 = stablo.get_right_child(root);
	stablo.insert_right(node_70, 90);

	POSITION node_90 = stablo.get_right_child(node_70);
	stablo.insert_right(node_90, 92);

	cout << "inorder (ovo se ponasa kao bst!):";
	stablo.inorder(root);
	cout << endl;
	cout << "preorder:";
	stablo.preorder(root);
	cout << endl;
	cout << "postorder:";
	stablo.postorder(root);
	cout << endl;

	return 0;
}
	
								//5.zad 7 vjezbe //u bst cuva podatke, da upise sifru i dal postoji
	
	
	
	#ifndef _DRZAVA_H_
#define _DRZAVA_H_
#include <string>
using namespace std;

struct drzava {
	string naziv;
	string sifra;
};

#endif

	#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "bst.h"

using namespace std;

bool ucitajdrzave(bst &bst, string naziv) {
	ifstream dat(naziv);
	if (!dat) {
		return false;
	}

	string line;
	getline(dat, line);
	while (getline(dat, line)) {
		ELTYPE drzava;
		stringstream ss(line);
		getline(ss, drzava.naziv, ';');
		getline(ss, drzava.sifra);
		bst.insert(drzava);
	}
	dat.close();
	return true;
}


int main() {

	bst bst;
	if (!ucitajdrzave(bst, "Drzave.csv")) {
		cout << "Nije moguce pristupiti datoteci" << endl;
		return 1;
	}

	cout << "Unesite sifru za pretragu:";
	ELTYPE drzava;
	getline(cin, drzava.sifra);
	if (bst.exists(drzava)) {
		cout << "drzava postoji" << endl;
	}
	else {
		cout << "drzava ne postoji" << endl;

	}

	return 0;
}

	////////////////////////////////////////////////////////////////////////////////////////////////
							//hrpa  //najveci se shifta gore , roditelj mora biti veci
	
	#include <iostream>
#include "heap.h"

using namespace std;

int main() {

    heap heap;

    heap.insert(42);
    heap.insert(27);
    heap.insert(16);
    heap.insert(7);
    heap.insert(19);
    heap.insert(10);
    heap.insert(66);

    while (!heap.is_empty()) {
        cout << heap.remove() << endl;
    }

    return 0;
}
								//3.zadatak  vj 8  drzave u hrpu. ispisi elemente
	#ifndef _DRZAVA_H_
#define _DRZAVA_H_

#include <string>

using namespace std;

struct Drzava {
	string naziv;
	string sifra;
};

#endif
	
	#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "heap.h"

using namespace std;



void ucitaj(heap &hrpa, ifstream &dat) {

	string line;
	getline(dat, line);
	while (getline(dat, line))
	{
		//cout << line << endl;
	stringstream ss;
	ss << line;


	ELTYPE drzava;
	getline(ss, drzava.naziv, ';');
	getline(ss, drzava.sifra);
	
	hrpa.insert(drzava);
	}
	
}

int main() {

	ifstream dat("Sifre_drzava.csv");
	if (!dat)
	{
		cout << "greska" << endl;
		return 404;
	}

	//u hrpu ubacivat iz ifstreama

	heap hrpa;
	//u hrpu iz strema, zgurat u metodu
	ucitaj(hrpa, dat);

	dat.close();

	//proc po hrpi  //while not empty

	while (!hrpa.is_empty())
	{
		ELTYPE el=hrpa.remove(); //ovako jer vraca nesto, ne moze kao na vjezbama prije

		cout << el.naziv << "; "<<el.sifra << endl;  //ispis je obruti

	}
	return 0;
}
	                  
	//cpp heap
	
	#include <string>
#include <iostream>
#include "heap.h"
using namespace std;

/**************** PRIVATNO ****************************/

POSITION heap::calc_left(POSITION parent) {
	return parent * 2 + 1;
}

POSITION heap::calc_right(POSITION parent) {
	return parent * 2 + 2;
}

POSITION heap::calc_parent(POSITION child) {
	return (child - 1) / 2;
}

bool heap::is_full() {
	return _next == CAPACITY;
}

void heap::reheapify_upward() {
	// Pomiči taj element prema vrhu hrpe.
	POSITION pos = _next;

	// Petlju vrtimo sve dok ne dođemo do korijena ili dok roditelj nije veći ili jednak djetetu.
	
	
	

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	while (pos > 0 && _elements[pos].sifra < _elements[calc_parent(pos)].sifra) {				//mijenjat u manje za 4.zadatak	(preko sifre ga mozemo nac //tu se raspao
		swap(_elements[pos], _elements[calc_parent(pos)]);

		pos = calc_parent(pos);
	}
}

void heap::reheapify_downward() {
	// Indeks trenutnog čvora roditelja, počinjemo s korijenom.
	POSITION pos = 0;
	
	// Radi sve dok je indeks roditelja na predzadnjem nivou.
	while (pos < _next / 2) {

		// Izračunaj indeks djeteta koje sadrži veći element.
		POSITION left_child = calc_left(pos);
		POSITION right_child = calc_right(pos);

		POSITION index_with_greater_value;

		// Moguće su tri situacije: nema djece, postoji lijevo dijete ili postoje oba djeteta.
		if (left_child >= _next && right_child >= _next) {
			return; // Nema djece.
		}
		else if (left_child < _next && right_child >= _next) {
			index_with_greater_value = left_child; // Postoji samo lijevo.
		}
		else { // Postoje oba djeteta pa uspoređujem koje je veće.
			
			
			   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (_elements[left_child].sifra < _elements[right_child].sifra) {			//mijenjat u manje za 4.zadatak					 //tu se raspao
				index_with_greater_value = left_child;
			}
			else {
				index_with_greater_value = right_child;
			}
		}

		// Zamijeni ako je u djetetu veći element.
		
		
		
		
		
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (_elements[pos].sifra > _elements[index_with_greater_value].sifra) {             	//mijenjat u manje za 4.zadatak	 //tu se raspao
			swap(_elements[pos], _elements[index_with_greater_value]);
		}
		else {
			// Inače je algoritam gotov, element je na svom mjestu.
			return;
		}

		// Nastavi zamjene u toj grani.
		pos = index_with_greater_value;
	}
}

/**************** JAVNO ****************************/

heap::heap() {
	_next = 0;
}

bool heap::is_empty() {
	return _next == 0;
}

void heap::insert(const ELTYPE& element) {
	if (is_full()) {
		throw string("Hrpa je puna!");
	}

	// Spremi element na sljedeće mjesto.
	_elements[_next] = element;

	reheapify_upward();

	// Označi da smo ubacili još jedan element.
	_next++;
}

ELTYPE heap::remove() {
	if (is_empty()) {
		throw string("Hrpa je prazna");
	}

	ELTYPE element_na_vrhu = _elements[0];

	// Označi da vadimo element.
	_next--;

	// Ako nismo obrisali korijen, presloži hrpu.
	if (_next > 0) {

		// Stavi zadnji element na mjesto korijena.
		_elements[0] = _elements[_next];

		// Presloži hrpu.
		reheapify_downward();
	}

	return element_na_vrhu;
}

									//vj8 zad 4 izmjenjeni 3.zad.
	#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "heap.h"

using namespace std;



void ucitaj(heap &hrpa, ifstream &dat) {

	string line;
	getline(dat, line);
	while (getline(dat, line))
	{
		//cout << line << endl;
		stringstream ss;
		ss << line;


		ELTYPE drzava;
		getline(ss, drzava.naziv, ';');
		getline(ss, drzava.sifra);

		hrpa.insert(drzava);
	}

}


int main() {

	ifstream dat("Sifre_drzava.csv");
	if (!dat)
	{
		cout << "greska" << endl;
		return 404;
	}

	//u hrpu ubacivat iz ifstreama

	heap hrpa;
	//u hrpu iz strema, zgurat u metodu
	ucitaj(hrpa, dat);

	dat.close();

	//proc po hrpi  //while not empty

	while (!hrpa.is_empty())
	{
		ELTYPE el = hrpa.remove(); //ovako jer vraca nesto, ne moze kao na vjezbama prije

		cout << el.naziv << "; " << el.sifra << endl;  //ispis je obruti

	}

	return 0;
}
	
	//cpp heap
	#include <string>
#include <iostream>
#include "heap.h"
using namespace std;

/**************** PRIVATNO ****************************/

POSITION heap::calc_left(POSITION parent) {
	return parent * 2 + 1;
}

POSITION heap::calc_right(POSITION parent) {
	return parent * 2 + 2;
}

POSITION heap::calc_parent(POSITION child) {
	return (child - 1) / 2;
}

bool heap::is_full() {
	return _next == CAPACITY;
}

void heap::reheapify_upward() {
	// Pomiči taj element prema vrhu hrpe.
	POSITION pos = _next;

	// Petlju vrtimo sve dok ne dođemo do korijena ili dok roditelj nije veći ili jednak djetetu.




	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	while (pos > 0 && _elements[pos].sifra < _elements[calc_parent(pos)].sifra) {			//mijenjat u manje(preko sifre ga mozemo nac //tu se raspao
		swap(_elements[pos], _elements[calc_parent(pos)]);

		pos = calc_parent(pos);
	}
}

void heap::reheapify_downward() {
	// Indeks trenutnog čvora roditelja, počinjemo s korijenom.
	POSITION pos = 0;

	// Radi sve dok je indeks roditelja na predzadnjem nivou.
	while (pos < _next / 2) {

		// Izračunaj indeks djeteta koje sadrži veći element.
		POSITION left_child = calc_left(pos);
		POSITION right_child = calc_right(pos);

		POSITION index_with_greater_value;

		// Moguće su tri situacije: nema djece, postoji lijevo dijete ili postoje oba djeteta.
		if (left_child >= _next && right_child >= _next) {
			return; // Nema djece.
		}
		else if (left_child < _next && right_child >= _next) {
			index_with_greater_value = left_child; // Postoji samo lijevo.
		}
		else { // Postoje oba djeteta pa uspoređujem koje je veće.


			   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (_elements[left_child].sifra < _elements[right_child].sifra) {			//mijenjat u manje						 //tu se raspao
				index_with_greater_value = left_child;
			}
			else {
				index_with_greater_value = right_child;
			}
		}

		// Zamijeni ako je u djetetu veći element.





		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (_elements[pos].sifra > _elements[index_with_greater_value].sifra) {                 //mijenjat u manje	 //tu se raspao
			swap(_elements[pos], _elements[index_with_greater_value]);
		}
		else {
			// Inače je algoritam gotov, element je na svom mjestu.
			return;
		}

		// Nastavi zamjene u toj grani.
		pos = index_with_greater_value;
	}
}

/**************** JAVNO ****************************/

heap::heap() {
	_next = 0;
}

bool heap::is_empty() {
	return _next == 0;
}

void heap::insert(const ELTYPE& element) {
	if (is_full()) {
		throw string("Hrpa je puna!");
	}

	// Spremi element na sljedeće mjesto.
	_elements[_next] = element;

	reheapify_upward();

	// Označi da smo ubacili još jedan element.
	_next++;
}

ELTYPE heap::remove() {
	if (is_empty()) {
		throw string("Hrpa je prazna");
	}

	ELTYPE element_na_vrhu = _elements[0];

	// Označi da vadimo element.
	_next--;

	// Ako nismo obrisali korijen, presloži hrpu.
	if (_next > 0) {

		// Stavi zadnji element na mjesto korijena.
		_elements[0] = _elements[_next];

		// Presloži hrpu.
		reheapify_downward();
	}

	return element_na_vrhu;
}

	
	
	
	
	
	
									//vj 8 zad 5 prioritetni red ubaci od 1-100
									//ispisi sve iz dinam reda
	#include <iostream>
#include "prioritetni_red.h"

using namespace std;

int main() {

	prioritetni_red red;
	for (int i = 1; i < 100; i++) {
		red.enqueue(i, i);
	}

	ELTYPE broj;
	while (red.dequeue(broj)) {
		cout << broj << endl;
	}

	return 0;
}
							//verzija da 200 prioritet ak je paran, 100 ako je neparan
	int main() {

	prioritetni_red red;
	for (int i = 1; i < 100; i++) {
		int priority;
		if (i % 2 == 0) {
			priority = 200;
		} else {
			priority = 100;
		}
		red.enqueue(i, priority);
	}

	ELTYPE broj;
	while (red.dequeue(broj)) {
		cout << broj << endl;
	}

	return 0;
}
	
