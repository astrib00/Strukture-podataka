#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

typedef struct clan* pozicija;

struct clan
{
	int broj;
	pozicija next;
};

void push(pozicija p) //u stogu i redu dodavanje novih elemenata vrsimo na kraj liste!!!
{
	pozicija temp = NULL;
	temp = (pozicija)malloc(sizeof(struct clan));

	temp->broj = rand() % (100 - 10 + 1) + 10; 

	while(p->next != NULL) //trebamo doc do kraja liste
		p = p->next;

	p->next = temp;
	temp->next = NULL;
}

int pop(pozicija p) //skidamo elemente s kraja vezane liste
{
	pozicija prev = NULL;
	int br = 0;

	prev = (pozicija)malloc(sizeof(struct clan));


	while(p->next != NULL)
	{
		prev = p;
		p = p->next;
	}

	if(p->next == NULL)
	{
		br = p->broj;
		prev->next = p->next;
		free(p);
	}
	return br;
}

int skiniRed(pozicija p) //skidamo elemente s pocetka vezane liste
{
	pozicija temp = NULL;
	int br = 0;

	temp = p->next;
	br = temp->broj;
	p->next = temp->next;
	free(temp);

	return br;
}

int main()
{
	char znak;
	int brstog = 0;
	int brred = 0;
	int i, j;
	struct clan head1; //head za stog
	struct clan head2; //head za red
	srand(time(0));
	head1.next = NULL;
	head2.next = NULL;

	printf("Ako zelite koristiti stog pritisnite S, a za red pritisnite R. \n");
	scanf(" %c", &znak);

	switch(toupper(znak))
	{
		case 'S':
			printf("Koliko elemanata zelite upisati u stog?\n");
			scanf("%d", &brstog);
			for(i=0;i<brstog+1;i++) //ako nije brstog+1 ispisati ce jedan element manje od broja kojeg smo unijeli
			{
				push(&head1);
			}
			printf("Ispis stoga: \n");
			for(i=0;i<brstog;i++) 
			{
				printf("%d ", pop(&head1));
			}
			break;

		case 'R':
			printf("Koliko elemanata zelite upisati u red?\n");
			scanf("%d", &brred);
			for(i=0;i<brred+1;i++) 
			{
				push(&head2);
			}
			printf("Ispis reda: \n");
			for(i=0;i<brred;i++) 
			{
				printf("%d ", skiniRed(&head2));
			}
			break;
	}

}
