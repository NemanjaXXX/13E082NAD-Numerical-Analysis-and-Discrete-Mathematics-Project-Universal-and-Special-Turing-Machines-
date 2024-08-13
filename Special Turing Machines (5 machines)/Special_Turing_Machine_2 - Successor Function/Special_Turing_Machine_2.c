#include<stdio.h>
#include<time.h>
#include<stdlib.h>


typedef struct turing {
	char pod;
	struct turing* sled;
}Turing;

void podaci() {
	time_t vreme;
	time(&vreme);
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	printf("                                             Univerzitet u Beogradu\n");
	printf("                                         Elektrotehnicki fakultet Beograd\n");
	printf("                                           Bulevar kralja Aleksandra 73\n");
	puts(" ");
	printf("Predmet: Numericka analiza i diskretna matematika [13E082NAD]\n");
	printf("Razlog: predispitne obaveze\n");
	printf("Tema: Racunarska realizacija Turing-ove masine\n");
	printf("Test primer [2/5]: funkcija sledbenik\n");
	printf("Mentor: dr Branko Malesevic, vanredni profesor\n");
	printf("Student: Nemanja Karapetrovic [broj indeksa]: ****/****]\n");
	printf("Napomena: Potrebno je da se ulazna datoteka zove ulaz2.txt i da se nalazi gde i izvorni fajl Special_Turing_Machine_2.c .\n");
	printf("Vreme: %s", ctime(&vreme));
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	puts("");
}

Turing* ucitavanje(Turing* lst) {
	FILE* p;
	Turing* novi, * posl = NULL;
	char pod1;
	p = fopen("ulaz2.txt", "r");
	if (p == NULL) {
		printf("Otvaranje datoteke nije uspelo!\n");
		exit(1);

	}
	while (fscanf(p, "%c", &pod1) != EOF) {
		novi = malloc(sizeof(Turing));
		if (novi == NULL) {
			printf("Alokacija memorije nije uspela!\n");
			exit(1);
		}
		novi->pod = pod1;
		novi->sled = NULL;
		if (lst == NULL) {
			lst = novi;
		}
		else {
			posl->sled = novi;
		}
		posl = novi;
	}
	fclose(p);
	return lst;
}

Turing* obrada(Turing* lst) {
	Turing* glava;
	glava = lst;

	while (glava->pod == ' ') glava = glava->sled; // Petlja pozicionira glavu Turing-ove masine na krajnji levi simbol koji nije blanko znak.

	/*    q0 =>		f(q0,b)=(q-,b,+1)
					f(q0,1)=(q1,1,+1)

	*/
	if (glava->pod == ' ') {
		printf("ERROR!!!\n");
		glava->pod = ' ';
		glava = glava->sled;
	}
	else {
		glava->pod = '1';
		glava = glava->sled;
	}

	/*		q1 =>		f(q1,b)=(q+,1,+1)
						f(q1,1)=(q1,1,+1)

	*/



	while (glava->pod != ' ') {
		if (glava->pod == '1') {
			glava->pod = '1';
			glava = glava->sled;
		}
		glava = glava->sled;    // Pokazivac glava se pozicionirao na krajnju desnu poziciju.
	}

	return lst; //q+ stanje


}

void ispis(Turing* lst) {
	Turing* tek;
	FILE* p;
	char izbor = 'a', izbor1;



	printf("Program:\n");

	printf("f(q0,b)=(q-,b,+1)\n");
	printf("f(q0,1)=(q1,1,+1)\n");
	printf("f(q1,b)=(q+,1,+1)\n");
	printf("f(q1,1)=(q1,1,+1)\n");


	puts(" ");

	printf("Da li zelite da se kreira posebna datoteka u kojoj ce se nalaziti rezultat obrade ulazne datoteke? \n");
	printf("Molim Vas unesite izbor: 1-DA   0-NE\n");
	printf("Vas izbor: ");
	scanf("%c", &izbor);
	izbor1 = izbor;
	// Zastita od nekorektnog unosa.
	scanf("%c", &izbor);
	if (izbor != '\n') {
		while (izbor != '\n') {
			scanf("%c", &izbor);
			izbor1 = 'a'; // Da trazi ponovni unos za npr. 123 ako se to prvo unese.
		}
	}
	while (izbor1 != '1' && izbor1 != '0') {
		printf("Nekorektan unos!!!\n");
		printf("Molim Vas ponovo unesite svoj izbor: 1-DA 0-NE\n");
		while (izbor != '\n')scanf("%c", &izbor);
		printf("Vas izbor: ");
		scanf("%c", &izbor);
		izbor1 = izbor;
		scanf("%c", &izbor);
		while (izbor != '\n') {
			scanf("%c", &izbor);
			izbor1 = 'a'; // Da trazi ponovni unos za npr. 123.
		}
	}
	puts(" ");

	printf("Rezultat: ");
	if (izbor1 == '1') {
		p = fopen("izlaz2.txt", "w");
		if (p == NULL) {
			printf("Neuspesno kreiranje datoteke!!!\n");
			exit(1);
		}
		for (tek = lst; tek != NULL; tek = tek->sled) {
			fprintf(p, "%c", tek->pod);
			printf("%c", tek->pod);

		}
		fclose(p);
	}
	else {
		for (tek = lst; tek != NULL; tek = tek->sled) {
			printf("%c", tek->pod);
		}

	}
	puts(" ");
	if (izbor1 == '1') printf("Vasa datoteka je uspesno formirana. Njen naziv je izlaz2.txt. Nalazi se na adresi izvornog fajla TuringMachine2.c .\n");
}

Turing* obrisi(Turing* lst) {
	Turing* stari, * tek;
	tek = lst;
	while (tek != NULL) {
		stari = tek;
		tek = tek->sled;
		free(stari);
	}
	lst = NULL;
	return lst;
}

int main() {
	Turing* lst;
	lst = NULL;
	time_t pocetak, kraj;
	time(&pocetak);
	podaci();
	lst = ucitavanje(lst);
	lst = obrada(lst);
	ispis(lst);
	lst = obrisi(lst);
	time(&kraj);
	puts(" ");
	printf("Vreme rada programskog dela obrade do ovog trenutka je %.2lf sekund(i,e).\n", difftime(kraj, pocetak));
	printf("Hvala sto ste koristili ovaj program!\n");
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	system("pause");
	return 0;
}