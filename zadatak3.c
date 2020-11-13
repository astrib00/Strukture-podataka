#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* pozicija;


struct osoba
{
	char ime[60];
	char prezime[60];
	int godina;
	pozicija next;
};

void unosP(pozicija);
void ispis(pozicija);
void unosK(pozicija);
void pronadi(pozicija);
void brisi(pozicija);
void dodajIza(pozicija);
void dodajIspred(pozicija);
void sortirajPrezime(pozicija);
int uDatoteku(pozicija);
int izDatoteke(pozicija);

int main() 
{
	struct osoba head;
	struct osoba headDat;
	head.next = NULL;
	headDat.next = NULL;
	
	unosP(&head);
	unosP(&head);
	ispis(head.next);
	unosK(&head);
	ispis(head.next);
	pronadi(&head);
	brisi(&head);
	ispis(head.next);
	dodajIza(&head);
	ispis(head.next);
	dodajIspred(&head);
	ispis(head.next);
	sortirajPrezime(&head);
	ispis(head.next);
	uDatoteku(&head);
	izDatoteke(&headDat);
	ispis(head.next);
}

void unosP(pozicija P)
{
	pozicija temp;

	temp = (pozicija)malloc(sizeof(struct osoba)); //cinimo novu strukturu

	printf("Unesite podatke osobe.\n");
	scanf("%s	%s	%d", temp->ime, temp->prezime, &temp->godina);

	temp->next = P->next; //slazemo pokazivace
	P->next = temp; 
}

void ispis(pozicija P)
{
	printf("Ispis:\n");
	while(P != NULL) {
		printf("%s	%s	%d\n", P->ime, P->prezime, P->godina);
		P = P->next; //setamo po listi
	}
}

void unosK(pozicija P)
{
	pozicija temp = NULL;
	temp = (pozicija)malloc(sizeof(struct osoba));

	printf("Unesite podatke za osobu koju zelite unijeti na kraj liste.\n");
	scanf("%s	%s	%d", temp->ime, temp->prezime, &temp->godina);

	while(P->next != NULL) //idemo do kraja liste
		P = P->next;

	P->next = temp;
	temp->next = NULL;
}

void pronadi(pozicija P)
{
	char prezime[60]; //prezime koje zelimo pronaci

	printf("Unesite prezime koje trazite.\n");
	scanf("%s", prezime);

	while(P->next != NULL && strcmp(prezime, P->prezime) != 0) // ako pronademo prezime strcmp daje vrijednost 0
	{
		P = P->next;
	}

	if(strcmp(prezime, P->prezime) == 0) //prezime nadeno
		printf("Trazeno prezime je: %s	%s	%d\n",P->ime, P->prezime, P->godina);
	else 
		printf("Trazeno prezime ne postoji u listi!!!\n");

}

void brisi(pozicija P)
{
	pozicija prev;
	char prezime[50];

	prev = (pozicija)malloc(sizeof(struct osoba)); //sluzi za oznacavanje clana koji prethodi trazenom clanu

	printf("Unesite prezime osobe koju zelite ukloniti.\n");
	scanf("%s", prezime);

	while(P->next != NULL && strcmp(prezime, P->prezime) != 0)
	{
			prev = P; //spremanje trenutnog clana, clan koji prethodi trazenom clanu(u slucaju da dodemo do trazenog clana)
			P = P->next; //idemo na sljedeci clan
	}

	if(strcmp(prezime, P->prezime) == 0) //ako smo nasli prezime
	{
		prev->next = P->next;
		free(P); // oslobadamo memoriju odabranog clana
	}
	else 
		printf("Trazeno prezime ne postoji u listi!!!\n");
}

void dodajIza(pozicija P)
{
	char prezime[50];
	pozicija temp;

	printf("Unesite prezime izad kojega zelite unijeti novu osobu.\n");
	scanf("%s", prezime);

	while(P->next != NULL && strcmp(prezime, P->prezime) != 0)
		P = P->next;

	if(strcmp(prezime, P->prezime) == 0)
	{
		temp = (pozicija)malloc(sizeof(struct osoba)); //alociramo memoriju za unos novog clana u listu
		printf("Unesite podatke nove osobe!\n");
		scanf("%s	%s	%d", temp->ime, temp->prezime, &temp->godina);
		
		temp->next = P->next; // slazemo pokazivace
		P->next = temp;
	}
	else
		printf("Uneseno prezime ne postoji!!!\n");
}

void dodajIspred(pozicija P)
{
	pozicija prev; //oznaka za prethodni clan trazenog clana
	char prezime[50];
	pozicija temp; // oznaka za novi clan kojeg dodajemo

	prev = (pozicija)malloc(sizeof(struct osoba));//alokacija memorije u koju spremamo podatke o prethodnom clanu

	printf("Unesite prezime osobe ispred koje zelite upisatu drugu osobu.\n");
	scanf("%s", prezime);

	while(P->next != NULL && strcmp(prezime, P->prezime) != 0)
	{
			prev = P; //spremanje trenutnog clana
			P = P->next; //idemo na sljedeci clan
	}

	if(strcmp(prezime, P->prezime) == 0) //nasli trazeno prezime
	{
		temp = (pozicija)malloc(sizeof(struct osoba));
		printf("Unesite podatke nove osobe!\n");
		scanf("%s	%s	%d", temp->ime, temp->prezime, &temp->godina);

		temp->next = prev->next;
		prev->next = temp;
	}
	else 
		printf("Trazeno prezime ne postoji u listi!!!\n");
}

void sortirajPrezime(pozicija P)
{
	pozicija prev, end, temp, i;

	end = NULL;

	while(P->next != end)
	{
		prev = P;
		i = P->next;

		while(i->next != end)
		{
			if(strcmp(i->prezime, i->next->prezime) > 0) //usporedujemo dva susjedna clana po prezimenu
			{
				temp = i->next;
				prev->next = temp;
				i->next = temp->next;
				temp->next = i;
				i = temp;
			}

			prev = i;
			i = i->next;
		}

		end = i;
	}
}

int uDatoteku(pozicija P)
{
	FILE* fp = NULL;

	fp = fopen("listaljudi.txt", "w");

	if(fp == NULL)
	{
		printf("Datoteka nije otvorena!\n");
		return -1;
	}

	while (P != NULL)
	{
		fprintf(fp, "%s	%s	%d", P->ime, P->prezime, P->godina);
		P = P->next;
	}

	printf("Podaci upisani u datoteku!!!\n");
	fclose(fp);
	return 0;
}

int izDatoteke(pozicija P)
{
	FILE* fp = NULL;
	
	pozicija novi;

	fp = fopen("listaljudi.txt" , "r");

	if(fp == NULL) //provjeravamo je li datoteka uspjesno otvorena
	{
		printf("Datoteka se nije otvorila!!!");
		return -1;
	}

	while(!feof(fp))
	{

		novi = (pozicija)malloc(sizeof(struct osoba));
		fscanf(fp, "%s	%s	%d" , novi->ime, novi->prezime, novi->godina);

		novi->next = P->next; //unos se vrsi na kraj liste
		P->next = novi;
		P = novi;

	}

	printf("Kraj unosa iz datoteke!");
	return 0;
}

