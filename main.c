/*******************************
* SUDOKU IN C BY HARY PATRASCU *
* 28/12/23                     *
*******************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h> // pentru functia Sleep()

#define FALSE 0
#define TRUE 1
#define DIM_VALORI 9

int verifica_liber(int sudoku[9][9], int dim, int *lin, int *col)
{
	/*
	* functia verifica daca exista o celula libera in sudoku, daca
	* exista o sa returneze true si o sa modifice coordonatele astfel
	* incat sa fie egale cu celula libera.
	*/
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			if (sudoku[i][j] == 0)
			{
				*lin = i;
				*col = j;
				return TRUE;
			}
	
				return FALSE;
}

int verifica_coloana(int sudoku[9][9], int dim, int col, int num)
{
	// functie care verifica daca mai exista acelasi numar pe coloana
	int i;
	for (i = 0; i < 9; i++)
		if (sudoku[i][col] == num)
			return FALSE;

			return TRUE;
}

int verifica_linia(int sudoku[9][9], int dim, int lin, int num)
{
	// functie care verifica daca mai exista acelasi numar pe linie
	int i;
	for (i = 0; i < 9; i++)
		if (sudoku[lin][i] == num)
			return FALSE;

			return TRUE;
}

int verifica_patrat(int sudoku[9][9], int dim, int lin, int col, int num)
{
	// functie care verifica daca mai exista acelasi numar intr-o submatrice din sudoku
	int lin_start, col_start, i, j;
	lin_start = (lin / 3) * 3;
	col_start = (col / 3) * 3;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			if (sudoku[lin_start + i][col_start + j] == num)
				return FALSE;

				return TRUE;
}

int verifica_valid(int sudoku[9][9], int dim, int lin, int col, int num)
{
	// functie care verifica daca toate conditiile sunt indeplinite astfel incat sa amplasam un numar intr-o celula
	if (verifica_linia(sudoku, dim, lin, num)		== TRUE &&
		verifica_coloana(sudoku, dim, col, num)		== TRUE &&
		verifica_patrat(sudoku, dim, lin, col, num) == TRUE)
			return TRUE;
			

			return FALSE;
}

void amesteca(int* valori, int dim)
{
	// functie care randomizeaza un vector astfel incat sa generam un sudoku aleatoriu
	int i, r1, r2, aux;
	for (i = 0; i < dim; i++)
	{
		r1 = rand() % dim;
		r2 = rand() % dim;
		aux = valori[r1];
		valori[r1] = valori[r2];
		valori[r2] = aux;
	}
}

void init_sudoku(int sudoku[9][9], int dim)
{
	// functie care initializeaza toate valorile din sudoku cu 0
	int i, j;
	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			sudoku[i][j] = 0;
}

int creeaza_sudoku(int sudoku[9][9], int valori[DIM_VALORI], int dim)
{
	// functie care creeaza un sudoku aleatoriu
	int i, lin, col;
	// daca nu mai exista patrate libere inseamna ca sudoku este complet
	if (!verifica_liber(sudoku, dim, &lin, &col))
		return TRUE;
	// amestecam valorile din vectorul valori = { 1, 2, ..., 9}
	amesteca(valori, DIM_VALORI);
	for (i = 0; i < DIM_VALORI; i++)
	{
		// selectam pe rand si verificam daca valorile sunt valide in puzzle
		if (verifica_valid(sudoku, dim, lin, col, valori[i]))
		{
			sudoku[lin][col] = valori[i];
			// verificam folosind recursivitate 
			if (creeaza_sudoku(sudoku, valori, dim))
				return TRUE;
			// daca nu returneaza TRUE, inseamna ca valoarea selectata nu creeaza un puzzle corect
			sudoku[lin][col] = 0;
		}
	}
				return FALSE;
}

void elimina_cifre(int sudoku[9][9], int dim, int cifre)
{
	// functie care elimina cifre din sudoku-ul creat in functie de dificultatea selectata de catre utiliazator
	int nr = cifre, i, j, celula;
	while (nr != 0)
	{
		celula = rand() % (dim * dim);
		i = celula / dim;
		j = celula % dim;
		if (sudoku[i][j] != 0)
		{
			sudoku[i][j] = 0;
			nr--;
		}
	}
}

int rezolva_sudoku(int sudoku[9][9])
{
	// functie care rezolva un sudoku
	int i, lin, col;
	// daca nu mai exista patrate libere inseamna ca sudoku este complet, altfel modificam pozitiile lin, col
	if (!verifica_liber(sudoku, 9, &lin, &col))
			return TRUE;

	// luam pe rand fiecare valoarea de la 1-9 si verificam daca se potrivesc in sudoku
	for (i = 1; i < 10; i++)
	{
		if (verifica_valid(sudoku, 9, lin, col, i))
		{
			sudoku[lin][col] = i;

			if (rezolva_sudoku(sudoku))
				return TRUE;

			sudoku[lin][col] = 0;
		}
	}

			return FALSE;
}

void copiaza(int copie[9][9], int sudoku[9][9], int dim)
{
	int i, j;
	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			copie[i][j] = sudoku[i][j];
	
}

void afiseaza_sudoku(int sudoku[9][9], int dim)
{
	// functie care afiseaza un sudoku / hardcodata
	int i, j;
	printf(" ");
	for (i = 1; i <= dim; i++)
		if ((i - 1) % 3 != 0)
			printf("%d ", i);
		else
			printf("  %d ", i);
	printf("\n  ");
	for (j = 0; j < 23; j++)
		printf("-");
	printf("\n");
	for (i = 0; i < dim; i++)
	{
		printf("%d", i + 1);
		for (j = 0; j < dim; j++)
			if ((j + 1) % 3 == 0)
				printf("%d | ", sudoku[i][j]);
			else if(j == 0 && i != dim)
				printf("| %d ", sudoku[i][j]);
			else
				printf("%d ", sudoku[i][j]);
		if ((i + 1) % 3 == 0)
		{
			if (i != dim - 1)
				printf("\n |");
			else
				printf("\n  ");
			for (j = 0; j < 23; j++)
				printf("-");
			if(i != dim - 1)
				printf("|");
		}
		printf("\n");
	}
}

void afisare_text(char* sir)
{
	int i;
	for (i = 0; i < strlen(sir); i++)
	{
		printf("%c", sir[i]);
		Sleep(25);
	}
}

void init_joc(int sudoku[9][9], int sudoku_jucator[9][9], int valori[DIM_VALORI], int dim, int cifre)
{
	int lin, col, nr, opt, vieti = 3;
	creeaza_sudoku(sudoku, valori, dim);
	copiaza(sudoku_jucator, sudoku, dim);
	elimina_cifre(sudoku_jucator, dim, cifre);
	do
	{
		opt = 0;
		afiseaza_sudoku(sudoku_jucator, dim);
		printf("		   %d VIETI\n", vieti);
		printf("ALEGE COORDONATELE:\n");
		do
		{
			if (opt == 0)
			{
				printf("LINIA(1-9): ");
				scanf("%d", &lin);
			}
			else
			{
				printf("LINIA ALEASA NU ESTE VALIDA, ALEGE ALTA LINIE: ");
				scanf("%d", &lin);
			}
			opt = 1;
		} while (lin < 1 || lin > 9);
		lin--;
		opt = 0;
		do
		{
			if (opt == 0)
			{
				printf("COLOANA(1-9): ");
				scanf("%d", &col);
			}
			else
			{
				printf("COLOANA ALEASA NU ESTE VALIDA, ALEGE ALTA COLOANA: ");
				scanf("%d", &col);
			}
		} while (col < 1 || col > 9);
		col--;
		if (sudoku_jucator[lin][col] == 0)
		{
			opt = 0;
			do
			{
				if (opt > 0)
				{
					vieti--;
					if (vieti == 0)
						break;
					system("cls");
					afiseaza_sudoku(sudoku_jucator, dim);
					printf("		   %d VIETI\n", vieti);
					printf("NUMARUL NU ESTE CORECT, ALEGE ALT NUMAR: ");
					scanf("%d", &nr);
				}
				else
				{
					printf("NUMAR(1-9): ");
					scanf("%d", &nr);
				}
				opt = 1;
			} while ((nr < 1 || nr > 9) || sudoku[lin][col] != nr);
			if(vieti > 0)
				sudoku_jucator[lin][col] = nr;
		}
		else
		{
			afisare_text("COORDONATELE ALESE SUNT OCUPATE DEJA, ALEGE ALTE COORDONATE!");
			Sleep(500);
		}
		system("cls");
		if (vieti == 0)
			break;
	} while (verifica_liber(sudoku_jucator, 9, &lin, &col) == TRUE);
	if (vieti > 0)
		afisare_text("AI CASTIGAT!\n");
	else
	{
		afiseaza_sudoku(sudoku_jucator, dim);
		printf("		   %d VIETI\n", vieti);
		afisare_text("AI PIERDUT!\n");
	}
}

int main()
{
	// setup
	int sudoku[9][9], sudoku_jucator[9][9];
	int valori[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	enum dificultate{IESIRE, FOARTE_USOR, USOR, MEDIU, GREU, EXPERT};
	int optiune, cifre = 15;
	srand(time(NULL));

	do
	{
		afisare_text("0 - IESIRE\n");
		afisare_text("1 - FOARTE_USOR\n");
		afisare_text("2 - USOR\n");
		afisare_text("3 - MEDIU\n");
		afisare_text("4 - GREU\n");
		afisare_text("5 - EXPERT\n");
		afisare_text("ALEGE O OPTIUNE: ");
		scanf("%d", &optiune);
		system("cls");

		init_sudoku(sudoku, 9);
		init_sudoku(sudoku_jucator, 9);

		switch (optiune)
		{
			case IESIRE:
				exit(0);
				break;
			case FOARTE_USOR:
				cifre = 15;
				break;
			case USOR: 
				cifre = 30;
				break;
			case MEDIU:
				cifre = 40;
				break;
			case GREU:
				cifre = 50;
				break;
			case EXPERT:
				cifre = 60;
				break;
			default:
				printf("OPTIUNE INVALIDA!\n");
		}
		init_joc(sudoku, sudoku_jucator, valori, 9, cifre);
	} while (1);

	return 0;
}