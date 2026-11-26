#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>				// log idő alatt keres, de szépen rendez (piros-fekete keresőfákkal / AVL fákkal dolgozik)
#include <unordered_map> // C# Dictionary // konstans idő alatt keres, kupis (hasítótáblákkal dolgozik)

using namespace std;

vector<string> feldarabol(string sor, char elvalasztojel) {
    stringstream ss(sor);   // a sor stringből csinalunk egy stream-et, amin végig lehet majd menni.
    string mezo;            // ebbe fogjuk tölteni a beolvasott dolgokat, ezek lesznek most a mezök.
    vector<string> result;   // ide gyujtjuk a mezőket, ezt adjuk majd vissza.

    while (getline(ss, mezo, elvalasztojel)) { // Addig menjen az olvasas, amig lehet. A getline valójában ad vissza értéket: Azt, hogy van-e még értelme folytatni az olvasást. Hamisat ad vissza, ha a végére ért.
        result.push_back(mezo); // a beolvasott mezőt betesszük a mezők közé.
    }
    return result;
}

class Fa
{
public:
	int sorszam; // ez az, ami nullától számozódik, és a fájlban elfoglalt hely
	int id;
	int magassag;
	string tipus;
	static map<int, int> id_to_sorszam;

	Fa(int sorszam, int id, int magassag, string tipus)
	{
		this->sorszam = sorszam;
		this->id = id;
		this->magassag = magassag;
		this->tipus = tipus;
	}

	Fa(int sorszam, vector<string> sortomb)
	{
		this->sorszam = sorszam;
		this->id = stoi(sortomb[0]);
		this->magassag = stoi(sortomb[1]);
		this->tipus = sortomb[2];
		Fa::id_to_sorszam[this->id] = this->sorszam; // rögzítjük a fa létrehozásakor azt is, hogy a központi nyilvántartásban milyen id alapján lehet a sorszámát megtalálni. 
	}

	static vector<Fa> beolvas(string fajlnev) {
		ifstream file(fajlnev); // a fájl megnyitása olvasásra.
		string sor;
		vector<Fa> fak;			// ez lesz az, amit visszaadunk.
		
		getline(file, sor); // 1️ fejléc sor kihagyása, hiszen ez a ciklus előtt van, mindenképpen lefut. 
		int i = 0;
		while (getline(file, sor)) // a getline pontosan akkor ad "hamis" értéket, ha a fájl végére értünk.
		{
			fak.push_back(Fa(i++, feldarabol(sor, '\t')));
		}

		return fak;
	}

	static vector<vector<int>> graf_beolvas(const string& fajlnev, const vector<Fa>& fak) {
		ifstream file(fajlnev);											// a fájl megnyitása olvasásra.
		string sor;
		vector<vector<int>> graf (fak.size(), vector<int>());			// ez lesz az, amit visszaadunk.

		getline(file, sor); 
		while (getline(file, sor)) 
		{
														// sor = "652\t608";
			vector<string> t = feldarabol(sor, '\t');	// t   = {"652", "608"}
			int id1 = stoi(t[0]);						// id1 = 652
			int id2 = stoi(t[1]);						// id1 = 608
			int sorszam1 = Fa::id_to_sorszam[id1];		// sorszam1 = 
			int sorszam2 = Fa::id_to_sorszam[id2];		// sorszam2 = 
			if (fak[sorszam1].magassag > fak[sorszam2].magassag)
			{
				graf[sorszam1].push_back(sorszam2);
			}
			else 
			{
				graf[sorszam2].push_back(sorszam1);
			}
		}

		return graf;
	}

private:

};


void graphviz(const vector<Fa>& fak,
	const vector<vector<int>>& graf)
{
	cout << "digraph G {" << endl;

	for (int i = 0; i < fak.size(); i++)
	{
		cout << "    " << fak[i].id << ";" << endl;

		for (int j : graf[i])
		{
			cout << "    " << fak[i].id
				<< " -> " << fak[j].id << ";" << endl;
		}
	}

	cout << "}" << endl;
}


map<int, int> Fa::id_to_sorszam; // így kap kezdőértéket a Fa osztályon belül deklarált statikus map. mainen kívül kell legyen!

int main()
{	
	vector<Fa> fak = Fa::beolvas("fak.tsv");
	vector<vector<int>>graf = Fa::graf_beolvas("kotelek.tsv", fak);

	graphviz(fak, graf);
}
