#include<stdlib.h>
#include<stdio.h>

typedef struct broj* pozicija;

struct broj
{
	int br;
	pozicija next;
};

void unos(pozicija);
void ispis(pozicija);
void unija(pozicija, pozicija, pozicija);
void presjek(pozicija, pozicija, pozicija);

int main() 
{
	int n = 0;
	int m = 0;
	int i, j;
	/*struct broj L1;
	struct broj L2;
	struct broj Ru;
	struct broj Rp; */
	struct broj headRp; //head element liste u koju upisujemo rezultat presjeka 
	struct broj head1;
	struct broj head2;
	struct broj headRu; //head element liste u koju upisujemo rezultat unije
	head1.next = NULL;
	head2.next = NULL;
	headRu.next = NULL;
	headRp.next = NULL;

	printf("UNOS MORA BITI SORTIRAN RASTUCE(prvi broj najmanji, zadnji najveci)!!!\n");
	printf("Unos se vrsi na kraj liste!!!\n");
	printf("Koliko elemenata zelite unijeti u prvu listu?\n");
	scanf("%d", &n);

	printf("Unesite elemente prve liste.\n");
	for(i=0;i<n;i++)
	{
		unos(&head1);
	}

	printf("Koliko elemenata zelite unijeti u drugu listu?\n");
	scanf("%d", &m);

	printf("Unesite elemente druge liste.\n");
	for(j=0;j<m;j++)
	{
		unos(&head2);
	}
	ispis(head1.next); //ispis liste L1
	printf("\n");
	ispis(head2.next); //ispis liste L2
	puts("");
	puts("");

	unija(head1.next, head2.next, &headRu);
	ispis(headRu.next); //ispis unije

	puts("");
	puts("");

	presjek(head1.next, head2.next, &headRp);
	ispis(headRp.next); //ispis presjeka
}

void unos(pozicija p)
{
	pozicija temp = NULL;
	temp = (pozicija)malloc(sizeof(struct broj));

	printf("Unesite broj kojeg zelite upisati na kraj liste.\n");
	scanf("%d", &temp->br);

	while(p->next != NULL)
	{
		p = p->next;
	}

	p->next = temp;
	temp->next = NULL;
}

void ispis(pozicija p)
{
	while(p != NULL)
	{
		printf("%d ", p->br);
		p = p->next;
	}
}

void unija(pozicija p1, pozicija p2, pozicija pr)
{
	pozicija temp;

	while(p1 != NULL && p2 != NULL)
	{
		if(p1->br < p2->br)
		{
			temp = (pozicija)malloc(sizeof(struct broj));
			temp->br = p1->br;

			temp->next = pr->next;
			pr->next = temp;

			p1 = p1->next;
			pr = pr->next;
		}

		else if(p1->br > p2->br)
		{
			temp = (pozicija)malloc(sizeof(struct broj));
			temp->br = p2->br;

			temp->next = pr->next;
			pr->next = temp;

			p2 = p2->next;
			pr = pr->next;
		}

		else if(p1->br == p2->br)
		{
			temp = (pozicija)malloc(sizeof(struct broj));
			temp->br = p1->br;

			temp->next = pr->next;
			pr->next = temp;

			p1 = p1->next;
			p2 = p2->next;
			pr = pr->next;
		}
	}

	if(p1 != NULL) //ove dvije if strukture trebamo napisati 
					//zbog toga sto u gornjoj while petlji mozemo doc do kraja jedne liste 
					//prije nego do kraja druge liste pa trebamo pokriti takve slucajeve!!!
	{
		while(p1 != NULL)
		{
			temp = (pozicija)malloc(sizeof(struct broj));
			temp->br = p1->br;

			temp->next = pr->next;
			pr->next = temp;

			p1 = p1->next;
			pr = pr->next;
		}
	}

	if(p2 != NULL)
	{
		while(p2 != NULL)
		{
			temp = (pozicija)malloc(sizeof(struct broj));
			temp->br = p2->br;

			temp->next = pr->next;
			pr->next = temp;

			p2 = p2->next;
			pr = pr->next;
		}
	}
}

void presjek(pozicija p1, pozicija p2, pozicija pr)
{
	pozicija temp;

	while(p1 != NULL && p2 != NULL)
	{
		if(p1->br < p2->br)
		{
			p1 = p1->next;
		}

		else if(p2->br < p1->br)
		{
			p2 = p2->next;
		}

		else if(p1->br == p2->br) //upisujemo samo one elemente koji imaju jednake vrijednosti
		{
			temp = (pozicija)malloc(sizeof(struct broj));
			temp->br = p1->br;

			temp->next = pr->next;
			pr->next = temp;

			p1 = p1->next;
			p2 = p2->next;
			pr = pr->next;
		}
	}
}
