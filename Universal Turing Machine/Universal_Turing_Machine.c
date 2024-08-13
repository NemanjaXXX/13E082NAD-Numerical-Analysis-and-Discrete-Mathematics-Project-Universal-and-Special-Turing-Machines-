#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

typedef struct turing {
	char pod;
	struct turing* pret;
	struct turing* sled;
}Turing;

typedef struct program {
	int q; // 1, 2, 3, ... ,n
	char uslov; // {1, b} V {0, 1, b}
	char sl_stanje_q_plus_ili_minus; // +, -, 1, 2, 3, ... ,n
	int sl_stanje_broj;
	char zamena;  // {1, b} V {0, 1, b}
	int pomeraj_glave; // +1 V -1
	struct program* pret;
	struct program* sled;
}Program;


void podaci() {
	time_t vreme;
	time(&vreme);
	puts("-----------------------------------------------------------------------------------------------------------------------------------------------------");
	puts("-----------------------------------------------------------------------------------------------------------------------------------------------------");
	printf("                                             Univerzitet u Beogradu\n");
	printf("                                         Elektrotehnicki fakultet Beograd\n");
	printf("                                           Bulevar kralja Aleksandra 73\n");
	puts(" ");
	printf("Predmet: Numericka analiza i diskretna matematika [13E082NAD]\n");
	printf("Razlog: predispitne obaveze\n");
	printf("Tema: Racunarska realizacija Turing-ove masine\n");
	printf("Test primer [universal]: UNIVERZALNI PROGRAM\n");
	printf("Mentor: dr Branko Malesevic, vanredni profesor\n");
	printf("Student 2: Nemanja Karapetrovic [broj indeksa: ****/****]\n");
	printf("Napomena: Potrebno je da se ulazna datoteka zove ulaz.txt i da se nalazi gde i izvorni fajl Universal_Turing_Machine.c .\n");
	printf("Vreme: %s", ctime(&vreme));
	puts("-----------------------------------------------------------------------------------------------------------------------------------------------------");
	puts("-----------------------------------------------------------------------------------------------------------------------------------------------------");
	puts("");
}

Turing* ucitavanje_trake(Turing* lst) {
	FILE* p;
	Turing* novi, * posl = NULL;
	char pod1;
	p = fopen("ulaz.txt", "r");
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

int da_li_je_broj_iza_kog_sledi_zarez(FILE* p) { //Uraditi realokaciju.
	char cifra;
	int broj[1000];
	int i = 0;
	int kraj;
	int q1;
	int stepen;
	int koeficijent;
	fscanf(p, "%c", &cifra);
	broj[i++] = (int)cifra - 48; // Da bi se od ASCII koda dobio konkretan broj.
	if (isdigit(cifra)) {
		while (isdigit(cifra)) {
			fscanf(p, "%c", &cifra);
			if (!isdigit(cifra)) break;
			broj[i++] = (int)cifra - 48;


		}//Kad iscrpi cifre proverava da li je zatvorena zagrada sledeca.
		kraj = i;
		if (cifra == ',') {//Ako jeste broj iza koga sledi zarez onda ga izracunja.
			for (i = kraj - 1, q1 = 0, stepen = 0; i >= 0; i--) {
				koeficijent = pow(10, stepen);
				q1 += broj[i] * koeficijent;
				stepen++;
			}
			return q1;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

int da_li_je_broj_ili_plus_ili_minus(FILE* p) {
	char cifra;
	fscanf(p, "%c", &cifra);
	if (isdigit(cifra) || cifra == '+' || cifra == '-') {
		if (cifra == '+') return 2;
		if (cifra == '-') return 3;
		return cifra;
	}
	else {
		return 0;
	}
}


Program* ucitavanje_programa(Program* lstP) {
	FILE* p;
	Program* novi, * posl = NULL, * tek, * pom;
	int q1; // 1, 2, 3, ... ,n
	char uslov1; // {1, b} V {0, 1, b}
	char sl_stanje_q_plus_ili_minus1; // +, -, 1, 2, 3, ... ,n
	int sl_stanje_broj1;
	char zamena1;  // {1, b} V {0, 1, b}
	int pomeraj_glave1; // +1 V -1

	char procitano;
	int procitani_broj;
	int sl_stanje_broj1_procitano;
	int sortiran = 0;

	p = fopen("program.txt", "r");
	if (p == NULL) {
		printf("Neuspesno otvaranje datoteke!!!\n");
		exit(1);
	}

	while (fscanf(p, "%c", &procitano) != EOF) {
		//U ovom trenutku procitano bi trebalo da bude f.
		if (procitano == 'f') {
			fscanf(p, "%c", &procitano);
			// Sad bi procitano trebalo da bude (.
			if (procitano == '(') {
				fscanf(p, "%c", &procitano);
				//Sad bi procitano trebalo da bude q.
				if (procitano == 'q') {
					//Sad bi procitano trebao da bude broj.
					q1 = da_li_je_broj_iza_kog_sledi_zarez(p);// Ako jeste ujedno ga cita i smesta u q1, ako nije ispisuje poruku o gresci i prekida program.
					if (q1 >= 0) {
						fscanf(p, "%c", &procitano);
						//Sad bi procitano trebalo da bude iz {1, b} V {0, 1, b}.
						if (procitano == '0' || procitano == '1' || procitano == 'b') {
							uslov1 = procitano;
							// Sad bi procitano trebalo da bude ).
							fscanf(p, "%c", &procitano);
							if (procitano == ')') {
								fscanf(p, "%c", &procitano);
								//Sad bi procitano trebalo da bude =.
								if (procitano == '=') {
									fscanf(p, "%c", &procitano);
									//Sad bi procitano trebalo da bude (.
									if (procitano == '(') {
										fscanf(p, "%c", &procitano);
										if (procitano == 'q') {
											//Sad bi procitano trebao da bude broj ili plus ili minus.
											if (sl_stanje_broj1_procitano = da_li_je_broj_ili_plus_ili_minus(p)) { //Svakako se ulazi jer, if gleda razliku od 0.

												if (sl_stanje_broj1_procitano == 2) { //Plus. Stanje q+.
													sl_stanje_q_plus_ili_minus1 = '+';
													sl_stanje_broj1 = -2; //Ovo je inikator da ne gledamo to polje.

												}
												if (sl_stanje_broj1_procitano == 3) {//Minus. Stanje q-.
													sl_stanje_q_plus_ili_minus1 = '-';
													sl_stanje_broj1 = -2;//Ovo je inikator da ne gledamo to polje.
												}
												if (isdigit(sl_stanje_broj1_procitano)) { //Broj. Stanje qn. Ovde smo sigurni da je cifra u pitanju.
													sl_stanje_broj1 = sl_stanje_broj1_procitano;
													sl_stanje_q_plus_ili_minus1 = '*'; // Zvezdica nam je indikator da ne gledam to polje.

												}// Ovde se zavrsilo citanje i smestanje u lokalne promenljive svih parametara do parametra zamene.
												fscanf(p, "%c", &procitano);

												//Sada bi procitano trebalo da bude zarez.
												if (procitano == ',') {
													fscanf(p, "%c", &procitano);
													//Sada bi procitano trebalo da bude iz {1, b} V {0, 1, b}.
													if (procitano == '0' || procitano == '1' || procitano == 'b') {
														zamena1 = procitano;
														fscanf(p, "%c", &procitano);
														//Sada bi procitano trebalo da bude zarez.
														if (procitano == ',') {
															fscanf(p, "%c", &procitano);
															//Sada bi procitano trebalo da bude znak pomeraja tj. + ili -.
															if (procitano == '+' || procitano == '-') {
																if (procitano == '+') {
																	pomeraj_glave1 = 1;
																}
																else {
																	pomeraj_glave1 = -1;
																}
																fscanf(p, "%c", &procitano);
																//Sada bi procitano trebalo da bude iskljucivo 1.
																if (procitano == '1') {
																	fscanf(p, "%c", &procitano);
																	//Sada bi procitano trebalo da bude ).
																	if (procitano == ')') {
																		fscanf(p, "%c", &procitano);
																		//Sada bi procitano trebalo da bude \n (znak za novi red).

																		/*FORMIRANJE DVOSTRUKO ULANCANE LISTE*/

																		if (procitano == '\n') {// Ako je i ovaj uslov ispunjen znaci da smo uspesno procitali jedan red datoteke. Sada formiramo dvostruko ulancanu listu.

																			novi = malloc(sizeof(Program));
																			if (novi == NULL) {
																				printf("Alokacija memorije nije uspela!!!\n");
																				system("pause");
																				exit(1);
																			}
																			novi->q = q1;
																			novi->uslov = uslov1;
																			novi->sl_stanje_broj = sl_stanje_broj1;
																			novi->sl_stanje_q_plus_ili_minus = sl_stanje_q_plus_ili_minus1;
																			novi->zamena = zamena1;
																			novi->pomeraj_glave = pomeraj_glave1;
																			novi->pret = NULL;
																			novi->sled = NULL;


																			if (lstP == NULL) {
																				lstP = novi;
																			}

																			else { //Sortiranje

																				tek = lstP;
																				pom = lstP->sled;
																				sortiran = 0;
																				while (tek != NULL && sortiran == 0) {
																					if (tek == lstP && pom == NULL && !(novi->q > tek->q)) {
																						if (novi->q <= tek->q) { //Dodavanje na pocetak.
																							tek->pret = novi;
																							novi->sled = tek;
																							lstP = novi;
																							sortiran = 1;
																						}
																					}

																					while (tek != NULL && tek->q <= novi->q) {//Dodavanje bilo gde.
																						tek = tek->sled;
																					}
																					if (tek != NULL && sortiran == 0) {
																						pom = tek;
																						tek = tek->pret;
																						tek->sled = novi;
																						novi->pret = tek;
																						novi->sled = pom;
																						pom->pret = novi;
																						sortiran = 1;
																					}
																					if (tek != NULL && sortiran == 0)tek = tek->sled;
																				}
																				if (sortiran == 0) {
																					posl->sled = novi;
																					novi->pret = posl;
																				}
																			}
																			for (tek = lstP; tek != NULL; tek = tek->sled) {
																				//posl = novi;
																				posl = tek;
																			}



																		}
																		else {
																			printf("Neispravna datoteka!!!\n");
																			system("pause");
																			exit(1);
																		}
																	}
																	else {
																		printf("Neispravna datoteka!!!\n");
																		system("pause");
																		exit(1);
																	}
																}
																else {
																	printf("Neispravna datoteka!!!\n");
																	system("pause");
																	exit(1);
																}
															}
															else {
																printf("Neispravna datoteka!!!\n");
																system("pause");
																exit(1);
															}

														}
														else {
															printf("Neispravna datoteka!!!\n");
															system("pause");
															exit(1);
														}

													}
													else {
														printf("Neispravna datoteka!!!\n");
														system("pause");
														exit(1);
													}

												}
												else {
													printf("Neispravna datoteka!!!\n");
													system("pause");
													exit(1);
												}
											}

											else {
												printf("Neispravna datoteka!!!\n");
												system("pause");
												exit(1);
											}

										}
										else {
											printf("Neispravna datoteka!!!\n");
											system("pause");
											exit(1);
										}

									}

									else {
										printf("Neispravna datoteka!!!\n");
										system("pause");
										exit(1);
									}


								}

								else {
									printf("Neispravna datoteka!!!\n");
									system("pause");
									exit(1);
								}

							}
							else {
								printf("Neispravna datoteka!!!\n");
								system("pause");
								exit(1);
							}


						}
						else {
							printf("Neispravna datoteka!!!\n");
							system("pause");
							exit(1);
						}

					}
					else {
						printf("Neispravna datoteka!!!\n");
						system("pause");
						exit(1);
					}
				}
				else {
					printf("Neispravna datoteka!!!\n");
					system("pause");
					exit(1);
				}
			}
			else {
				printf("Neispravna datoteka!!!\n");
				system("pause");
				exit(1);
			}
		}
	}
	fclose(p);
	return lstP;

}

Turing* obrada(Turing* lst, Program* lstP) {
	Turing* glava;
	Program* p;
	int trenutno_stanje_q = 0;
	glava = lst;
	p = lstP;
	//Petlja pozicionira glavu na krajnji levi element.

	while (glava->pod == ' ') {
		glava = glava->sled;
	}

	while (p != NULL) {
		if (p->q == trenutno_stanje_q) {
			if (p->uslov == glava->pod) {
				//Sada treba da menjamo.
				glava->pod = p->zamena;
				//Sada treba odraditi pomeraj glave.
				if (p->pomeraj_glave == 1) {  //Programski namesteno 1 i -1, nezavisno od upisa. 1 jeste +1.
					glava = glava->sled;
				}
				else { // Ako nije 1 onda je sigurno -1.
					glava = glava->pret;

				}
				//Sada bi trebalo videti u koje stanje se ide nakon nastalih zamena.
				if (p->sl_stanje_q_plus_ili_minus != '*') { // Zvezdica je indikator da je stanje broj.

					if (p->sl_stanje_q_plus_ili_minus == '+') {
						printf("Program je uspesno zavrsen!\n");
						return lst;
					}

					if (p->sl_stanje_q_plus_ili_minus == '-') {
						printf("Doslo je do greske u radu programa!\n");
						exit(1);
					}


				}
				else { // Ako nije * onda je sledece stanje broj.
					trenutno_stanje_q = p->sl_stanje_broj;

				}



			}

			else {
				p = p->sled;
			}
		}
		else {
			p = p->sled;
		}
	}
	return lst;
}


Turing* obrisi1(Turing* lst) {
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

Program* obrisi2(Program* lstP) {
	Program* stari, * tek;
	tek = lstP;
	while (tek != NULL) {
		stari = tek;
		tek = tek->sled;
		free(stari);
	}
	lstP = NULL;
	return lstP;
}

void ispis_trake(Turing* lst) {
	FILE* p;
	Turing* tek;
	char izbor = 'a', izbor1;



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

	printf("Rezultat (ispisuje se cela traka): ");
	puts("");
	puts("");

	if (izbor1 == '1') {
		p = fopen("izlaz.txt", "w");
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

}


void ispisi_program(Program* lstP) {
	Program* tek;
	puts(" ");
	printf("Program:\n");
	puts(" ");
	for (tek = lstP; tek != NULL; tek = tek->sled) {
		if (tek->sl_stanje_q_plus_ili_minus != '*') {
			if (tek->pomeraj_glave == 1) {


				printf("f(q%d,%c)=(q%c,%c,+%d)\n", tek->q, tek->uslov, tek->sl_stanje_q_plus_ili_minus, tek->zamena, tek->pomeraj_glave);
			}
			else {//Ako nije +1 onda je -1.

				printf("f(q%d,%c)=(q%c,%c,%c)\n", tek->q, tek->uslov, tek->sl_stanje_q_plus_ili_minus, tek->zamena, (char)tek->pomeraj_glave);
			}
		}
		else {// Ako je sledece stanje qn a, ne q+ ili q-.
			if (tek->pomeraj_glave == 1) {
				if (tek->sl_stanje_broj == 98 || tek->sl_stanje_broj == 49) tek->sl_stanje_broj -= 48;
				printf("f(q%d,%c)=(q%d,%c,+%d)\n", tek->q, tek->uslov, tek->sl_stanje_broj, tek->zamena, tek->pomeraj_glave);
			}
			else {
				if (tek->sl_stanje_broj == 98 || tek->sl_stanje_broj == 49) tek->sl_stanje_broj -= 48;
				printf("f(q%d,%c)=(q%d,%c,+%c)\n", tek->q, tek->uslov, tek->sl_stanje_broj, tek->zamena, (char)tek->pomeraj_glave);
			}
		}
	}
}


int main() {
	Turing* lst;
	Program* lstP;
	lst = NULL;
	lstP = NULL;
	time_t pocetak, kraj;
	time(&pocetak);
	podaci();
	lst = ucitavanje_trake(lst);
	lstP = ucitavanje_programa(lstP);
	ispisi_program(lstP);
	lst = obrada(lst, lstP);
	ispis_trake(lst);
	lst = obrisi1(lst);
	lstP = obrisi2(lstP);
	time(&kraj);
	puts("");
	puts("");
	printf("Vreme rada programskog dela obrade do ovog trenutka je %.2lf sekund(i,a,e).\n", difftime(kraj, pocetak));
	printf("Hvala sto ste koristili ovaj program!\n");
	puts("-----------------------------------------------------------------------------------------------------------------------------------------------------");
	puts("-----------------------------------------------------------------------------------------------------------------------------------------------------");
	system("pause");
	return 0;
}
