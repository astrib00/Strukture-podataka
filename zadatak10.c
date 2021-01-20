#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define size 35

typedef struct cvor* pozicija;
struct cvor //struktura za stablo
{
	char string[size];
	pozicija lijevo;
	pozicija desno;
};

typedef struct stog* pozicija_stog;
struct stog //struktura za stog
{
	pozicija stablo;  
	pozicija_stog next;
};

pozicija_stog Push(pozicija_stog pos, pozicija cv) //argumenti su head element i element kojeg dodajemo na stog
{
	pozicija_stog tmp;

	if(pos == NULL) {
		printf("Pokazivac na stogu nije valjan, nesipravan argument!\n");
	return NULL;
	}

	tmp = (pozicija_stog)malloc(sizeof(struct stog)); //alokacija novog elementa
	tmp->stablo = cv; //adresu ovog cvora cini clan strukture stog
	tmp->next = pos->next;
	pos->next = tmp;

	return pos;
}

pozicija Pop(pozicija_stog pos)
{
	pozicija_stog tmp;
	pozicija vrijednost;

	if( NULL == pos)
	{
		printf("Prazan stog!\n");
		return NULL;
	}
	else {
		tmp = pos->next;
		pos->next = tmp->next;
		vrijednost = tmp->stablo;
		free(tmp);
	}
	return vrijednost;
}

int velicinaBuffera(FILE* fp)
{
	int velicina = 0;

	fseek(fp, 0, SEEK_END);

	velicina = ftell(fp);

	rewind(fp);
	
	return velicina;
}

char* napraviBuffer(FILE* fp)
{
	char* buffer;

	buffer = (char*)calloc(velicinaBuffera(fp) + 2, sizeof(char)); //+2 dodajemo sigurnosti radi
	
	fread(buffer, velicinaBuffera(fp), 1, fp);
	
	return buffer;
}

pozicija napraviCvor(char* val)
{
	pozicija tmp;

	tmp = (pozicija)malloc(sizeof(struct cvor));
	tmp->lijevo = NULL;
	tmp->desno = NULL;

	strcpy(tmp->string, val);
	
	return tmp;
}

void printInOrder(pozicija pos, char* str)
{
	if(NULL == pos)
		return;

	printInOrder(pos->lijevo, str);
	printf("%s  ", pos->string);
	strcat(str, " ");
	strcat(str, pos->string);
	printInOrder(pos->desno, str);
}

pozicija dodajDjecu(pozicija root, pozicija lijevo, pozicija desno)
{
	root->lijevo = lijevo; //u lijevom i desnom djetetu su operandi
	root->desno = desno;

	return root; //u root cvoru se nalaze operatori
}

int operatori(char znak)
{
	if(znak == '+' || znak == '-' || znak == '*' || znak == '/')
		return 1; 
	else
		return 0;
}

pozicija racunajIzraz(char* izraz)
{
	char* token;
	pozicija noviCvor, novoStablo, tmp, operCvor; //cvor operatora
	pozicija lijevo, desno, vrh; //vrh stoga
	struct stog _stog;
	pozicija _root = (pozicija)malloc(sizeof(struct cvor));

	_stog.next = NULL;
	token = strtok(izraz, " ");
	while(NULL != token) {
		if(isdigit(*token)) 
		{
			noviCvor = napraviCvor(token);
			Push(&_stog, noviCvor);
		}
		else if (operatori(*token))
		{
			operCvor = napraviCvor(token);
			_root = operCvor;
			lijevo = Pop(&_stog);
			desno = Pop(&_stog);
			dodajDjecu(operCvor, lijevo, desno);
			Push(&_stog, _root);
		}

		token = strtok(NULL, " ");
	}
	return _root;
}

int main()
{
	FILE* out; //ulazna datoteka, u nju spremamo
	FILE* in; //izlazna datoteka, iz nje citamo
	int brojac = 0; //velicina izraza iz datoteke
	char* buffer;
	pozicija root;
	char* infix = (char*)calloc(brojac + 8, sizeof(char));

	in = fopen("ulazna.txt", "r");
	if(NULL == in) {
		printf("Datoteka nije uspjesno otvorena!\n");
			return -1;
	}

	brojac = velicinaBuffera(in);
	buffer = napraviBuffer(in);
	printf("Postfix izraz ucitan iz datoteke: %s \n", buffer);

	root = racunajIzraz(buffer);
	fclose(in);
	printInOrder(root, infix); //pretvaramo postfix u infix
	printf("Infix izraz pretvoren iz postfixa: %s\n", infix);

	out = fopen("izlazna.txt", "w");
		if(NULL == out) {
			printf("Datoteka nije uspjesno otvorena!!!\n");
			return -1;
		}
	fwrite(infix, 1, brojac, out);
	fclose(out);

	return 0;
}
