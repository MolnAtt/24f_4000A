#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

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
	int sorszam;
	int id;
	int magassag;
	string tipus;

	Fa(int sorszam, int id, int magassag, string tipus)
	{
		this->sorszam = sorszam;
		this->id = id;
		this->magassag = magassag;
		this->tipus = tipus;
	}

	Fa(int sorszam, vector<string> sortomb)
	{
		this->sorszam = stoi(sortomb[0]);
		this->id = stoi(sortomb[0]);
		this->magassag = stoi(sortomb[1]);
		this->tipus = sortomb[2];
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

	~Fa()
	{

	}

private:

};




int main()
{
	Fa::beolvas("4000A_fak.tsv");

}
