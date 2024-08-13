#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct turing {
	char pod;
	struct turing* pret;
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
	printf("Test primer [5/5]: deljivost zadatog broja sa 8\n");
	printf("Mentor: dr Branko Malesevic, vanredni profesor\n");
	printf("Student: Nemanja Karapetrovic [broj indeksa: ****/****]\n");
	printf("Napomena: Potrebno je da se ulazna datoteka zove ulaz5.txt i da se nalazi gde i izvorni fajl Special_Turing_Machine_5.c .\n");
	printf("Vreme: %s", ctime(&vreme));
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	puts("");
}

Turing* ucitavanje(Turing* lst) {
	FILE* p;
	Turing* novi, * posl = NULL;
	char pod1;
	p = fopen("ulaz5.txt", "r");
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
			novi->pret = posl;
		}
		posl = novi;
	}
	fclose(p);
	return lst;
}

Turing* obrada(Turing* lst, int* deljiv) {
	Turing* glava;
	glava = lst;
	bool iskoci = false;
	int q1 = 0, q2 = 0, q3 = 0, q4 = 0; /* Indikator: qi=0, program je bio u q1 stanju
													  qi=0, program nije bio u q1 stanju  */


													  /* Stranje q0 => f(q0,b)=(q-,b,+1);
																	   f(q0,0)=(q1,0,+1);
																	   f(q0,1)=(q1,1,+1);   */


	while (glava->pod == ' ') {
		glava = glava->sled;  // Ova petlja ce pozicionirati pokazivac glava na krajnji levi znak 1.
	}

	/* Stranje q0 => f(q0,b)=(q-,b,+1);
					 f(q0,0)=(q1,0,+1);
					 f(q0,1)=(q1,1,+1); */

	if (glava->pod == ' ') {
		printf("ERROR!!!\n");  // q- stanje
		if (glava->pod == ' ') glava->pod = ' ';
		glava = glava->sled;
		exit(1); // exit jer ako pocetak nije dobar, nema sta da se radi.
	}
	else { /*   f(q0,0)=(q1,0,+1);
				f(q0,1)=(q1,1,+1);    */

		if (glava->pod == '0') {
			glava->pod = '0';
			glava = glava->sled;
		}
		else {
			glava->pod = '1';
			glava = glava->sled;
		}
	}


	/* Stranje q1 => f(q1,b)=(q2,b,-1);
					 f(q1,0)=(q1,0,+1);
					 f(q1,1)=(q1,1,+1);   */

					 // f(q1,b)=(q2,b,-1);

	while ((q1 != 1 || q2 != 1 || q3 != 1 || q4 != 1) && !iskoci) { // Argument deljiv je prosledjen kao false.
		if (q1 == 0 && q2 == 0 && q3 == 0 && q4 == 0) {
			if (q1 == 0) {
				if (glava->pod == ' ') {
					glava->pod = ' ';
					glava = glava->pret;
					q1 = 1;
				}
				else { /* f(q1,0)=(q1,0,+1)
						 f(q1,1)=(q1,1,+1) */
					if (glava->pod == '0') {
						glava->pod = '0';
						glava = glava->sled;
					}
					else {
						glava->pod = '1';
						glava = glava->sled;
					}
				}
			}

			/* Stranje q2 => f(q2,b)=(q-,b,+1);
							 f(q2,0)=(q3,0,-1);
							 f(q2,1)=(q-,1,+1);   */

							 /* f(q2,b)=(q-,b,+1);
								f(q2,1)=(q-,1,+1);  */
			if (q1 == 1 && q2 == 0 && q3 == 0 && q4 == 0) {
				if (glava->pod == ' ' || glava->pod == '1') {
					//q- stanje
					if (glava->pod == ' ') glava->pod = ' ';
					if (glava->pod == '1') glava->pod = '1';
					glava = glava->sled;
					iskoci = true;
				}
				else { //f(q2,0)=(q3,0,-1); 
					glava->pod = '0';
					glava = glava->pret;
					q2 = 1;
				}

			}
			/* Stranje q3 => f(q3,b)=(q-,b,+1);
							 f(q3,0)=(q4,0,-1);
							 f(q3,1)=(q-,1,+1); */



							 /* f(q3,b)=(q-,b,+1);
								f(q3,1)=(q-,1,+1); */

			if (q1 == 1 && q2 == 1 && q3 == 0 && q4 == 0) {
				if (glava->pod == ' ' || glava->pod == '1') {
					//q- stanje
					if (glava->pod == ' ') glava->pod = ' ';
					if (glava->pod == '1') glava->pod = '1';
					glava = glava->sled;
					iskoci = true;
				}
				else { //f(q3,0)=(q4,0,-1); 
					glava->pod = '0';
					glava = glava->pret;
					q3 = 1;
				}
			}

			/* Stranje q4 => f(q4,b)=(q-,b,+1);
							 f(q4,0)=(q+,0,+1);
							 f(q4,1)=(q-,1,+1); */



							 /* f(q4,b)=(q-,b,+1);
								f(q4,1)=(q-,1,+1); */

			if (q1 == 1 && q2 == 1 && q3 == 1 && q4 == 0) {
				if (glava->pod == ' ' || glava->pod == '1') {
					//q- stanje
					if (glava->pod == ' ') glava->pod = ' ';
					if (glava->pod == '1') glava->pod = '1';
					glava = glava->sled;
					iskoci = true;
				}
				else { //f(q4,0)=(q+,0,+1); 
					glava->pod = '0';
					glava = glava->sled;
					q4 = 1;

				}
			}

			if (q4 == 1 && !iskoci) {
				*deljiv = true;

			}

		}
	}
	return lst;
}
void ispis(Turing* lst, bool deljiv) {
	Turing* tek;
	FILE* p;
	char izbor = 'a', izbor1;
	for (tek = lst; tek->pod != ' '; tek = tek->sled); // Petlja pozicionira pokazivac tek na mesto prvog simbola koji nije blanko znak.



	printf("Program:\n");

	printf("f(q0,b)=(q-,b,+1)\n");
	printf("f(q0,0)=(q1,0,+1)\n");
	printf("f(q0,1)=(q1,1,+1)\n");

	printf("f(q1,b)=(q2,b,-1)\n");
	printf("f(q1,0)=(q1,0,+1)\n");
	printf("f(q1,1)=(q1,1,+1)\n");

	printf("f(q2,b)=(q-,b,+1)\n");
	printf("f(q2,0)=(q3,0,-1)\n");
	printf("f(q2,1)=(q-,1,+1)\n");

	printf("f(q3,b)=(q-,b,+1)\n");
	printf("f(q3,0)=(q4,0,-1)\n");
	printf("f(q3,1)=(q-,1,+1)\n");

	printf("f(q4,b)=(q-,b,+1)\n");
	printf("f(q4,0)=(q+,0,+1)\n");
	printf("f(q4,1)=(q-,1,-1)\n");

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
		p = fopen("izlaz5.txt", "w");
		if (p == NULL) {
			printf("Neuspesno kreiranje datoteke!!!\n");
			exit(1);
		}
		if (deljiv) {
			fprintf(p, "%s", "Zadati broj je deljiv sa 8.\n");
			fclose(p);

		}
		else {
			fprintf(p, "%s", "Zadati broj nije deljiv sa 8.\n");
			fclose(p);
		}


	}

	if (deljiv) {
		printf("Zadati broj je deljiv sa 8.\n");
	}
	else {
		printf("Zadati broj nije deljiv sa 8.\n");
	}

	if (izbor1 == '1') printf("Vasa datoteka je uspesno formirana. Njen naziv je izlaz5.txt. Nalazi se na adresi izvornog fajla TuringMachine5.c .\n");


	puts(" ");
	puts(" ");
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
	bool deljiv = false;
	time_t pocetak, kraj;
	time(&pocetak);
	podaci();
	lst = ucitavanje(lst);
	lst = obrada(lst, &deljiv);
	ispis(lst, deljiv);
	lst = obrisi(lst);
	time(&kraj);
	printf("Vreme rada programskog dela obrade do ovog trenutka je %.2lf sekund(i,e).\n", difftime(kraj, pocetak));
	printf("Hvala sto ste koristili ovaj program!\n");
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	puts("---------------------------------------------------------------------------------------------------------------------------------");
	system("pause");
	return 0;
}