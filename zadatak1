#include<stdio.h>
#include<stdlib.h>

typedef struct studenti
{
	char ime[80];
	char prezime[80];
	int bodovi; 
} stud;

int main()
{
	int brStud=0;
	int i=0;
	char zn;
	FILE* fp;
	stud* student;
	double relBod[80];
	int maxBod = 80;

	fp = fopen("popis.txt", "r");

	if(fp == NULL)
	{
		printf("GRESKA! Datoteka nije otvorena.");
		return 1;
	}

	while(!feof(fp))
	{
		zn = fgetc(fp);
		if(zn == '\n')
			brStud++; 
	}

	rewind(fp);

	printf("Broj studenata na popisu je: %d \n", brStud);

	student = (stud*)malloc(sizeof(stud) * brStud);

	while(!feof(fp))
	{
		fscanf(fp, "%s		%s		%d", student[i].ime, student[i].prezime, &student[i].bodovi);
		i++;
	}

	for(i=0;i<brStud;i++)
	{
		relBod[i] = ((double)student[i].bodovi / (double)maxBod) * 100;

	}

	for(i=0;i<brStud;i++)
	{
		printf("%s		%s		%d		%.2f\n", student[i].ime, student[i].prezime, student[i].bodovi, relBod[i]);
	}

	fclose(fp);

}
