#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct clan* pozicija;

struct clan
{
	int broj;
	pozicija next;
};

int push(pozicija head, pozicija temp) //temp je element kojeg dodajemo na stog
{
	if(temp == NULL || head == NULL)
	{
		printf("Unijeli ste neispravne argumente funkcije!!\n");
		return -1;
	}

	temp->next = head->next;
	head->next = temp;
	
	return 0;
}

int pop(pozicija head)
{
	pozicija tmp;

	if(head->next == NULL) //provjerimo je li stog prazan!
		return -1;

	tmp = head->next;
	head->next = tmp->next;
	free(tmp);

	return 0;
}

void ispis(pozicija p)
{
	if(p == NULL)
		printf("Stog je prazan!!!\n");

	while(p != NULL)
	{
		printf("%d", p->broj);
		p = p->next;
	}
}

int buffervelicina(FILE* fp)
{
	int velbuff = 0;

	fseek(fp, 0, SEEK_END); //pomocu fseek setamo po datoteci

	velbuff = ftell(fp); //ftell vraca velicinu izraza zapisanog u datoteci

	rewind(fp); //vraca pokazivac na pocetak datoteke

	return velbuff;
}

char* createBuff(FILE* fp)
{
	char* buffer;

	buffer = (char*)calloc(buffervelicina(fp) + 5, sizeof(char)); //prilikom alokacije buffera uvik dodat par znakova viska radi sigurnosti!!!

	fread(buffer, buffervelicina(fp), 1, fp); //kopiramo zapis iz datoteke u buffer
											  //fread(pokazivac na blok memorije di spremamo izraz, velicina pojedinog elementa, broj elemenata, odakle kopiramo izraz)
	return buffer;
}

float rezultatIzraza(pozicija head, char* str)
{
	int a;
	int read_offset = 0;
	float zn = 0;
	float rez = 0;
	char Operator;

	while(str != EOF)
	{
		a = sscanf(str, "%f%n", &zn, &read_offset);

		if(a == EOF)
			break;

		if(a == 1)
		{
			printf("Ucitan je broj %.3f", zn);
			push(head, novielement(zn));

			str += read_offset;
		}

		if(a == 0)
		{
			Operator = *(str + 1); //+1 zbog razmaka
			str += read_offset;

			printf("Ucitan je znak: %c", Operator);
		}

		ispis(head->next);
	}

	rez = head->next->broj;

	pop(head); //skinemo rezultat sa stoga odnosno zadnji clan

	return rez;
}

pozicija novielement(float br)
{
	pozicija temp; //novi element kojega stvorimo 

	temp = (pozicija)malloc(sizeof(clan));

	temp->broj = br; //dodijelimo mu vrijednost broja iz postfixa

	return temp;
}

float* operandi(pozicija p) //napravimo niz u kojem su operandi funkcije
{
	float* operandi = 0;
	pozicija newop= NULL; //novi operand

	if(p == NULL)
	{
		printf("Greska, argument neispravan!\n");
		return NULL;
	}

	else if(p->next == NULL || p->next->next == NULL)
	{
		printf("Nedovoljno argumenata!!\n");
		return NULL;
	}

	operandi = (float*)malloc(sizeof(float) * 2);

	*(operandi + 0) = p->next->broj;
	*(operandi + 1) = p->next->broj;

	pop(p);

	return operandi;
}

int operacija(pozicija head, float* operandi, char Operator)
{
	float x = 0, y = 0, rezltat = 0;

	y = *(operandi + 0);
	x = *(operandi + 1);

	if(operandi == NULL)
	{
		printf("Operand nije pronaden!!\n");
		return -1;
	}

	switch(Operator)
	{
	case '+': head->next->broj = x + y;
		break;
	case '-': head->next->broj = x - y;
		break;
	case'*': head->next->broj = x * y;
		break;
	case '/': head->next->broj = x / y;
		break;
	}
	return 0;
}

int main()
{
	FILE* fp;
	struct clan head;
	head.next = NULL;
	char* izraz;

	float rezultat = 0;

	fp = fopen("datoteka.txt", "r");

	if(fp == NULL)
	{
		printf("Datoteka nije otvorena!!!\n");
			return -1;
	}

	izraz = createBuff(fp); //postfix izraz iz datoteke zapisujemo u string

	rezultat = rezultatIzraza(&head, izraz);

	printf("Rezultat postfix izraza iz datoteke je: %.2f", rezultat);

	return 0;
}
