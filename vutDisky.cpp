#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#define CESTA	"C:\\vutDisky\\reg_info.txt"

using namespace std;
// "\" se musi psat jako \\ jinak je to escape sign (pr. \t, \a, \n ...)
const char *stringP = "start cmd /k net use P: \\\\ad.feec.vutbr.cz\\homes.id\\vutbr.cz\\";
const char *stringQ = "start cmd /k net use Q: \\\\deza.feec.vutbr.cz\\app /USER:VUTBR\\";
const char *stringR = "start cmd /k net use R: \\\\deza.feec.vutbr.cz\\doc /USER:VUTBR\\";
int main() {

	string user_name;
	string user_ID;

	string cmd_string;	// Prikaz posilany do cmd
	string a;			// Docasne uloziste stringu pri manupulaci se streamy
	char b;				// Docasne uloziste nazvu disku
	fstream file;		// Soubor s prihlasovacimi udaji

	file.open(CESTA, ios::in);

	// Kontrola, ze soubor existuje a zpracovavani jeho obsahu
	if (!file.is_open())
	{
		file.close();
		filesystem::create_directory("C:\\vutDisky");
		file.open(CESTA, ios::out);
		if (!file.is_open())
			throw exception("Soubor reg_info.txt nemohl byt otevren!");

		cout << "Prejete si ulozit prihlasovaci udaje na lokalni disk? (Y/N)	";
		while (a != "Y" && a != "y" && a != "N" && a != "n")
		{
			cin >> a;
		}

		cin.ignore();
		if (a == "Y" || a == "y")
		{
			/*Ulozeni do reg_info.dat*/
			file << "Y\n";
			cout << "\nVase ID: ";
			getline(cin, user_ID);
			file << user_ID << '\n';
			cout << "\nJmeno: ";
			getline(cin, user_name);
			file << user_name << '\n';
		}
		else
			// Ulozi nastaveni a priste se uz nepta
			file << "N\n";

		file.close();
		file.open(CESTA, ios::in);
	}

	file >> a;
	if (a == "N")
	{
	loop0:
		cout << "(Zvolili jste neukladat informace, nastaveni lze zmenit napsanim \"!\" )\n";
		while (1)
		{
			cout << "Zadejte nazev disku: ";
			cin >> b;
			// Jelikoz mixuji operator>> a getline(), musi se pouzit nasledujici metoda
			cin.ignore();
			if (b == '!')
			{
				file.close();
				file.open(CESTA, ios::trunc | ios::out);

				cout << "Prejete si ulozit prihlasovaci udaje na lokalni disk? (Y/N)	";
				cin >> a;
				while (a != "Y" && a != "y" && a != "N" && a != "n")
				{
					cin >> a;
				}

				cin.ignore();
				if (a == "Y" || a == "y")
				{
					/*Ulozeni do reg_info.dat*/
					file << "Y\n";
					cout << "\nVase ID: ";
					getline(cin, user_ID);
					file << user_ID << '\n';
					cout << "\nJmeno: ";
					getline(cin, user_name);
					file << user_name << '\n';
					file.close();
					file.open(CESTA, ios::in);
					goto loop1;					// Nepouzivejte goto, ja jsem jenom linej tohle prepsat do swich case
				}
				else
					// Ulozi nastaveni a priste se uz nepta
					file << "N\n";

				file.close();
				file.open(CESTA, ios::in);
				continue;
			}
			else if ((b != 'P' && b != 'p') && (b != 'Q' && b != 'q') && (b != 'R' && b != 'r'))
			{
				cout << "Spatny nazev disku, mate na vyber z P,Q a R" << endl;
				continue;
			}

			// Docasne ulozi jmeno a ID uzivatele
			cout << "Zadejte prihlasovaci jmeno: ";
			getline(cin, user_name);
			cout << "\nZadejte svoje VUT ID: ";
			getline(cin, user_ID);

			//Prikaz ktery se posle cmd pomoci system
			if (b == 'P' || b == 'p')
				cmd_string = stringP + user_ID + " /USER:VUTBR\\" + user_name;
			else if (b == 'Q' || b == 'q')
				cmd_string = stringQ + user_name;
			else
				cmd_string = stringR + user_name;

			break;
		}
	}
	else if (a == "Y")
	{
	loop1:
		cout << "(nastaveni lze zmenit napsanim \"!\")\n";
		while (1)
		{
			cout << "Zadejte nazev disku: ";
			cin >> b;
			cin.ignore();

			if (b == '!')
			{
				file.close();
				file.open(CESTA, ios::trunc | ios::out);

				cout << "Prejete si ulozit prihlasovaci udaje na lokalni disk? (Y/N)	";
				cin >> a;
				while (a != "Y" && a != "y" && a != "N" && a != "n")
				{
					cin >> a;
				}

				cin.ignore();
				if (a == "Y" || a == "y")
				{
					/*Ulozeni do reg_info.dat*/
					file << "Y\n";
					cout << "\nVase ID: ";
					getline(cin, user_ID);
					file << user_ID << '\n';
					cout << "\nJmeno: ";
					getline(cin, user_name);
					file << user_name << '\n';
				}
				else
				{
					// Ulozi nastaveni a priste se uz nepta
					file << "N\n";
					file.close();
					file.open(CESTA, ios::in);
					goto loop0;					// Nepouzivejte goto, ja jsem jenom linej tohle prepsat do swich case
				}

				file.close();
				file.open(CESTA, ios::in);
				continue;
			}
			else if ((b != 'P' && b != 'p') && (b != 'Q' && b != 'q') && (b != 'R' && b != 'r'))
			{
				cout << "Spatny nazev disku, mate na vyber z P,Q a R" << endl;
				continue;
			}

			// Vybere udaje ze souboru
			getline(file, user_ID);
			getline(file, user_ID);
			getline(file, user_name);

			//Prikaz ktery se posle cmd pomoci system
			if (b == 'P' || b == 'p')
				cmd_string = stringP + user_ID + " /USER:VUTBR\\" + user_name;
			else if (b == 'Q' || b == 'q')
				cmd_string = stringQ + user_name;
			else
				cmd_string = stringR + user_name;

			break;
		}
	}
	else
	{
		file.close();
		throw exception("Soubor reg_info.txt byl vygenerovan spatne!");
	}

	file.close();
	//system nebere string, nutno pouzit metodu c_str (konvertuje string na const char*)
	system(cmd_string.c_str());

	return 0;
}
