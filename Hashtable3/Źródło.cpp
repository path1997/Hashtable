#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
#include <iomanip>

class hashtable
{
private:
	long klucz;
	std::string lancuch;
	std::fstream plik;
	std::fstream plik1;
	std::string nazwa_pliku_odczyt;
	std::string nazwa_pliku_zapis;
	std::string komenda;
	std::string *tablicaString;
	int iloscPrzypadkow;
	int rozmiarTab;
	int poczatek;
	int koniec;

public:
	hashtable()
	{
		klucz = 0;
		lancuch = "";
		std::ifstream plik;
		nazwa_pliku_odczyt = "";
		nazwa_pliku_zapis = "";
		komenda = "";
		tablicaString = NULL;
		iloscPrzypadkow = 0;
		rozmiarTab = 0;
		poczatek = 0;
		koniec = 0;
	}

	hashtable(std::string nazwa_pliku_odczyt, std::string nazwa_pliku_zapis)
	{
		this->nazwa_pliku_odczyt = nazwa_pliku_odczyt;
		this->nazwa_pliku_zapis = nazwa_pliku_zapis;
	}

	void WczytajPlik()
	{
		std::cout << "Podaj nazwe pliku do odczytu: ";
		std::cin >> nazwa_pliku_odczyt;
		std::cout << "Podaj nazwe pliku do zapisu: ";
		std::cin >> nazwa_pliku_zapis;
		plik.open(nazwa_pliku_odczyt, std::ios::in);
		plik1.open(nazwa_pliku_zapis, std::ios::out | std::ios::app);
		if (plik.good() == true)
		{
			plik >> iloscPrzypadkow;

			for (int i = 0; i < iloscPrzypadkow; i++)
			{

				do {
					plik >> komenda;
					if (komenda == "size")
					{
						size();
					}
					else if (komenda == "add")
					{
						add();
					}
					else if (komenda == "print")
					{
						print();
					}
					else if (komenda == "delete")
					{
						delete_();
					}
					else {}

				} while (komenda != "stop");
				
				if (komenda == "stop")
				{
					delete[] tablicaString;
				}
			}
		}
	}

	void size()
	{
		plik >> rozmiarTab;
		tablicaString = new std::string[rozmiarTab];
		/*for (int i = 0; i < rozmiarTab; i++)
		{
			tablicaString[i] = "";
		}*/
		poczatek = rozmiarTab / 2;
		koniec = rozmiarTab / 2;

	}

	void delete_()
	{
		plik >> klucz;
		/*for (int i = 0; i < rozmiarTab; i++)
		{
			if (klucz == dajKlucz(i))
			{
				tablicaString[i] = "";
			}
		}*/
		int stala= klucz % rozmiarTab;
		int licznik = klucz % rozmiarTab;
		while (klucz != dajKlucz(licznik)) 
		{
			if (licznik >= stala)
			{
				licznik++;
				if (licznik-1 == rozmiarTab - 1) 
				{
					licznik = stala - 1;
				}
			}
			else if (licznik < stala) 
			{
				licznik--;
			}
		}
		
		tablicaString[licznik] = "";

		int zmiany=1;
		/*for (int j = 0; j < rozmiarTab; j++) {
			if (zmiany == 0)
			{
				break;
				std::cout << "stop";
			}
			else
			{
				zmiany = 0;
			}*/
			while(zmiany!=0)
			{

				zmiany = 0;

			for (int i = 0; i < rozmiarTab; i++)
			{
				if (tablicaString[i - 1] == "" && (i > (dajKlucz(i) % rozmiarTab)) && (tablicaString[i]!=""))
				{
					tablicaString[i-1] = tablicaString[i];
					tablicaString[i] = "";
					zmiany++;
				}
				if (tablicaString[rozmiarTab-i + 1] == "" && (rozmiarTab-i < (dajKlucz(rozmiarTab-i) % rozmiarTab)) && (tablicaString[rozmiarTab - i] != ""))
				{
					tablicaString[rozmiarTab-i + 1] = tablicaString[rozmiarTab-i];
					tablicaString[rozmiarTab-i] = "";
					zmiany++;
				}
				
			}
		}
	}

	void add()
	{
		plik >> klucz;
		plik >> lancuch;
		if (lancuch.length() <= 8)
		{
			std::stringstream strumien;
			strumien << klucz;
			std::string temp = strumien.str();
			temp += " ";
			temp += lancuch;
			int licznik = 0;
			/*for (int i = 0; i<lancuch.length(); i++) {
				licznik =licznik+ (int)lancuch[i];
			}*/
			licznik = klucz % rozmiarTab;
			if (tablicaString[licznik] == "")
			{
				tablicaString[licznik] = temp;
				if (poczatek==rozmiarTab/2 && koniec==rozmiarTab/2) {
					poczatek = licznik;
					koniec = licznik;
					//std::cout << poczatek << " " << koniec << std::endl;
				}
				else if (poczatek > licznik) {
					poczatek = licznik;
					//std::cout << poczatek << " " << koniec << std::endl;
				}
				else if (koniec < licznik) {
					koniec = licznik;
					//std::cout << poczatek << " " << koniec << std::endl;
				}
			}
			else
			{
				int znacznik = 1;
				for (int i = licznik + 1; i < rozmiarTab; i++)
				{
					if (tablicaString[i] == "")
					{
						tablicaString[i] = temp;
						znacznik = 0;
						if (koniec < i) {
							koniec = i;
							//std::cout << poczatek << " " << koniec << std::endl;
						}
						break;
					}
					else if (klucz == dajKlucz(i)) 
					{
						tablicaString[i] = temp;
						znacznik = 0;
						break;
					}
				}
				if (znacznik == 1)
				{
					for (int i = licznik - 1; i >= 0; i--)
					{
						if (tablicaString[i] == "")
						{
							tablicaString[i] = temp;
							znacznik = 0;
							if (poczatek > i) {
								poczatek = i;
								//std::cout << poczatek << " " << koniec << std::endl;
							}
							break;
						} else if (klucz == dajKlucz(i))
						{
							tablicaString[i] = temp;
							znacznik = 0;
							break;
						}
					}
				}
				if (znacznik == 1)
				{
					std::cout << "Brak miejsca w tablicy" << std::endl;
				}
			}
		}
		else
		{
			std::cout << "Za dlugi lancuch" << std::endl;
		}

	}

	void print()
	{
		for (int i = poczatek; i <= koniec; i++)
		{
			if (tablicaString[i] != "")
			{
				plik1 << i << " " << tablicaString[i] << std::endl;
			}
		}
		plik1 << std::endl;
	}

	int dajKlucz(int wiersz)
	{
		std::string klucz_temp="";
		int klucz_tab;
		for (int i = 0; i < (int)tablicaString[wiersz].length(); i++) 
		{
			if (tablicaString[wiersz][i] == ' ') 
			{
				break;
			}
			else 
			{
				klucz_temp += tablicaString[wiersz][i];
			}
		}
		std::istringstream(klucz_temp) >> klucz_tab;
		return klucz_tab;
	}

	~hashtable() 
	{
		plik.close();
		plik1.close();
	}

};

int main()
{

	hashtable test;
	test.WczytajPlik();

	return 0;
}