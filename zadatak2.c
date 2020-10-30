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

int main() 
{
	struct osoba head;
	head.next = NULL;
	unosP(&head);
	unosP(&head);
	ispis(head.next);
	unosK(&head);
	ispis(head.next);
	pronadi(&head);
	brisi(&head);
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
	while(P->next != NULL) {
		printf("%s	%s	%d", P->ime, P->prezime, P->godina);
		P = P->next; //setamo po listi
	}
}

void unosK(pozicija P)
{
	pozicija temp;
	temp = (pozicija)malloc(sizeof(struct osoba));

	printf("Unesite podatke za tu osobu.\n");
	scanf("%s	%s	%d", temp->ime, temp->prezime, temp->godina);

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
		printf("Trazeno prezime je: %s	%s	%d",P->ime, P->prezime, P->godina);
	else 
		printf("Trazeno prezime ne postoji u listi!!!");

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
			prev = P; //spremanje trenutnog clana, clan koji prethodi trazenom clanu(u slucaju da dodemo do trazeog clana)
			P = P->next; //idemo na sljedeci clan
	}

	if(strcmp(prezime, P->prezime) == 0) //ako smo nasli prezime
	{
		prev->next = P->next;
		free(P); // oslobadamo memoriju odabranog clana
	}
	else 
		printf("Trazeno prezime ne postoji u listi!!!");
}
