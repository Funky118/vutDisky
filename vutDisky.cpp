#include <iostream>
#include <string>
using namespace std;
// "\" se musi psat jako \\ jinak je to escape sign (pr. \t, \a, \n ...)
const char *stringP = "start cmd /k net use P: \\\\ad.feec.vutbr.cz\\homes.id\\vutbr.cz\\203334 /USER:VUTBR\\";
const char *stringQ = "start cmd /k net use Q: \\\\deza.feec.vutbr.cz\\app /USER:VUTBR\\";
const char *stringR = "start cmd /k net use R: \\\\deza.feec.vutbr.cz\\doc /USER:VUTBR\\";
int main(){
	
	string a;
	char b;
	
	while(1)
	{
		cout << "Zadejte nazev disku: ";
		cin>>b;
		//Pro spravnou funkci getline() musime pouzit nasledujici metody
		cin.clear();
		cin.sync();
		/*equivalent if((b=='P'||b=='p')||...
						else
						Spatny nazev disku
		*/
		if((b!='P'&&b!='p')&&(b!='Q'&&b!='q')&&(b!='R'&&b!='r'))
		{
			cout << "Spatny nazev disku, mate na vyber z P,Q a R" << endl;
			continue;
		}
		
		cout << "Zadejte prihlasovaci jmeno: ";
		getline(cin,a);
		//Prikaz ktery se posle cmd pomoci system
		if(b=='P'||b=='p')
			a = stringP+a;
		else if(b=='Q'||b=='q')
			a = stringQ+a;
		else
			a = stringR+a;
		
		break;
	}

	//system nebere string, nutno pouzit metodu c_str (konvertuje string na const char*)
	system(a.c_str());
	
	return 0;
}
