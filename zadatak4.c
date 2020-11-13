#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct polinom* ppol; //pozicija polinoma

struct polinom
{
	int baza;
	int exp;
	ppol next;
};

typedef struct polinom clan;

int citajDat(FILE*, ppol, ppol); //cita iz datoteke
int ispis(ppol); //ispisuje listu polinoma
int ucitajPol(char*, ppol, ppol);
int velBuffer(FILE*); //racuna velicinu buffera
int zbroji(ppol, ppol, ppol);
int mnozi(ppol, ppol, ppol);
int zbrojiExp(ppol); //zbraja one polinome s istim eksponentom
int sortUnos(ppol, ppol);
int brisiListu(ppol); //funkcija brise listu iz memorije

int main()
{
	FILE* fp;

	clan p1_Head, p2_Head, rez_Head;

	p1_Head.next = NULL;
	p2_Head.next = NULL;
	rez_Head.next = NULL;

	fp = fopen("datoteka.txt", "r");

	if(fp == NULL)
	{
		printf("GRESKA!!!Datoteka nije otvorena.");
		return -1;
	}

	citajDat(fp, &p1_Head, &p2_Head);

	printf("Ispis prvog polinoma: ");
	ispis(p1_Head.next);

	printf("Ispis drugog polinoma: ");
	ispis(p2_Head.next);

	zbroji(p1_Head.next, p2_Head.next, &rez_Head);
	mnozi(p1_Head.next, p2_Head.next, &rez_Head);
	printf("Ispis prije slaganja\n");
	ispis(rez_Head.next);

	zbrojiExp(&rez_Head);
	printf("Ispis krajnjeg rezultata\n");
	ispis(rez_Head.next);

	brisiListu(&p1_Head); //oslobadamo memoriju
	brisiListu(&p2_Head);
	brisiListu(&rez_Head);

	return 0;

}

int citajDat(FILE* fp, ppol p1, ppol p2) //citamo iz datoteke
{
	int bufferVel = 0;
	ppol noviEl = NULL;
	char* buffer = NULL;
	int exp = 0, koef = 0, offset = 0, r=0; //pomocne varijable

	bufferVel = velBuffer(fp);

	buffer = (char*)calloc(bufferVel, sizeof(char)); //alocirmo memoriju za buffer
	fread(buffer, bufferVel, 1, fp);  //U buffer upisemo ono sto je u datoteci

	fclose(fp);

	printf("Ispis buffera: \n %s \n", buffer);

	offset = ucitajPol(buffer, p1, noviEl);
	buffer = (buffer + offset); //pomicemo pokazivac buffera
	
	ucitajPol(buffer, p2, noviEl);
	return 0;
}

int velBuffer(FILE* fp) //racunamo velicinu buffera 
{
	int velicina = 0;

	fseek(fp, 0, SEEK_END);
	velicina = ftell(fp);
	rewind(fp);

	printf("Duljina buffera: %d\n", velicina);
	return velicina;
}

int ucitajPol(char* buffer, ppol p, ppol noviEl)
{
	int koef, r, n, exp;
	int offset = 0; //sluzi za pomak u stringu
	ppol head = p;

	while(buffer != EOF)
	{
		r = sscanf(buffer, "%d %d\n", &koef, &exp, &n);

		if( r==EOF)
		{
			printf("Dosli na kraj datoteke!\n");
		}

		if(r==0)
		{
			printf("Greska!!!");
			break;
		}

		offset += n;
		buffer = (buffer + n);

		noviEl = (ppol)malloc(sizeof(clan)); //nova struktura

		noviEl->baza = koef;
		noviEl->exp = exp;

		sortUnos(noviEl, p);

		if (*buffer == '\n')
		{
			break;
		}
	}
	offset +=1;
	return offset;
}

int sortUnos(ppol noviEl, ppol p)
{
	ppol head = NULL;
	head = p;

	if(p->next == NULL)
	{
		noviEl->next = p->next;
		p->next = noviEl;
	}

	else
	{
		while(p->next != NULL && p->next->exp < noviEl->exp)
		{
			p = p->next;
		}
			noviEl->next = p->next;
			p->next = noviEl;
	}
	p=head;

	return 0;
}

int ispis(ppol p)
{
	if( p == NULL)
	{
		printf("Lista je prazna!!!\n");
		return -1;
	}

	while(p!=NULL) //petlja vrti dok ne dode do zadnjeg clana liste
	{
		if(p->next == NULL)
		{
			printf("%dx^%d", p->baza, p->exp);
		}

		else
		{
			printf("%dx^%d + ", p->baza, p->exp);
		}

		p=p->next;
	}
	printf("\n");
	return 0;
}

int zbroji(ppol p1, ppol p2, ppol rez)
{
	ppol noviEl, rez_Head;
	rez_Head = rez;

	while(p1 != NULL && p2 !=NULL)
	{
		if(p1->exp < p2->exp)
		{
			noviEl=(ppol)malloc(sizeof(clan)); //dinamicki alociramo novi clan

		noviEl->exp = p1->exp;
		noviEl->baza = p1->baza;

		noviEl->next = rez->next;
		rez->next = noviEl;

		p1 = p1->next;
		rez = rez->next; 
		}
	

	else if(p1->exp > p2->exp)
	{
		noviEl = (ppol)malloc(sizeof(clan)); // novi clan

		noviEl->exp = p2->exp; //unosimo podatke
		noviEl->baza = p2->baza;

		noviEl->next = rez->next;
		rez->next = noviEl;

		p2 = p2->next;
		rez = rez->next;
		}

	else if(p1->exp == p2->exp)
	{
		noviEl = (ppol)malloc(sizeof(clan));

		noviEl->exp = p2->exp;
		noviEl->baza = p2->baza + p1->baza;

		noviEl->next = rez->next;
		rez->next=noviEl;

		p1=p1->next;
		p2=p2->next;
		rez=rez->next;
	}
	} //ako dodemo na kraj polinoma, tada na kraj liste unosimo preostale sortirane polinome

	if(p1 != NULL)
	{
		while(p1 != NULL)
		{
			noviEl=(ppol)malloc(sizeof(clan));

			noviEl->baza = p1->baza;
			noviEl->exp=p1->exp;

			noviEl->next = rez->next;
			rez->next=noviEl;

			p1= p1->next;
			rez = rez->next;
		}
	}

	if(p2!=NULL)
	{
		while(p2!=NULL)
		{
			noviEl = (ppol)malloc(sizeof(clan));

			noviEl->baza = p2->baza;
			noviEl->exp=p2->exp;

			noviEl->next = rez->next;
			rez->next = noviEl;

			p2=p2->next;
			rez=rez->next;
		}
	}
}

int mnozi(ppol p1, ppol p2, ppol rez)
{
		ppol noviel, rez_Head, p2start;

		rez_Head = rez;
		p2start = p2;

		if(p1==NULL || p2==NULL || rez==NULL)
		{
			printf("GRESKA!!!\n Jedan od pokazivaca je na NULL vrijednosti.\n");
				return -1;
		}

		while(p1!=NULL)
		{
			while(p2!=NULL)
			{
				noviel=(ppol)malloc(sizeof(clan));

				noviel->exp = (p1->exp + p2->exp);
				noviel->baza = (p1->baza*p2->baza);

				sortUnos(noviel, rez_Head);

				p2 = p2->next;
			}

			p1 = p1->next;
			p2=p2start;
		}
		return 0;
}

int zbrojiExp(ppol pHEAD)
{
	ppol prev, trenutni, sljed;

	prev = pHEAD;
	trenutni = pHEAD->next;
	sljed = trenutni->next;

	while(sljed != NULL)
	{
		if(trenutni->exp == sljed->exp)
		{
			sljed->baza += trenutni->baza;

			prev->next = sljed;
			free(trenutni);

			trenutni = sljed;
			sljed = sljed->next;
			prev = prev;
		}
		else
		{
			prev = trenutni;
			trenutni = sljed;
			sljed = sljed->next;
		}
	}
	return 0;
}

int brisiListu(ppol p)
{
	ppol prev;

	p = p->next;

	while(p!=NULL)
	{
		prev = p;
		p = p->next;

		free(prev);
	}

	return 0;
}
