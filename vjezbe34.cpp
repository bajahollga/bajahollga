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
