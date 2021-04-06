#define _CRT_SECURE_NO_WARNINGS
#include"funkcje.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

waz* stworz_weza(waz *pHead, int wiersz, int kolumna)
{
	if (!pHead)
	{
		pHead = (waz*)malloc(sizeof(waz));
		pHead->pion = kolumna;
		pHead->poziom = wiersz;
		pHead->znak = '#';
		pHead->pNext = NULL;
		pHead->pPrev = NULL;
		return pHead;
	}
	waz* nowy = (waz*)malloc(sizeof(waz));
	nowy->pNext = NULL;
	nowy->znak = '#';
	nowy->pion = kolumna;
	nowy->poziom = wiersz;
	waz *p = pHead;
	while (p->pNext)
		p = p->pNext;
	nowy->pPrev = p;
	p->pNext = nowy;
	return pHead;
}
int sprawdz_wylosowany_punkt(waz *pHead, punkt zjedzone)
{
	waz *p = pHead;
	while (p->pNext)
	{
		if (p->poziom == zjedzone.x && p->pion == zjedzone.y)
			return 0;
		p = p->pNext;
	}
	return 1;
}
waz *wyswietl_weza(waz *pHead, int x, int y)
{

	waz *p = pHead;
	waz *temp = p;
	waz *temp2 = p;


	while (p->pNext != NULL)
	{


		gotoxy(p->poziom, p->pion);
		printf("%c", p->znak);

		p = p->pNext;
	}

	if (p != pHead)
	{
		temp = p->pPrev;
		temp2 = p;
		temp->pNext = NULL;
		temp2->pPrev = NULL;
		p->pNext = pHead;
		pHead->pPrev = p;

		pHead = p;
	}

	gotoxy(p->poziom, p->pion);
	printf(" ");
	gotoxy(x, y);
	printf("%c", p->znak);
	gotoxy(x, y);

	p->pion = y;
	p->poziom = x;

	return pHead;
}
wynik *rekordy(wynik *pHead, int wartosc_wyniku)
{
	if (!pHead)
	{
		pHead = (wynik*)malloc(sizeof(wynik));
		pHead->wartosc = wartosc_wyniku;
		pHead->pNext = NULL;
		return pHead;
	}
	wynik *nowy = (wynik*)malloc(sizeof(wynik));
	nowy->wartosc = wartosc_wyniku;
	nowy->pNext = NULL;
	wynik *s = pHead;
	while (s->pNext)
		s = s->pNext;
	s->pNext = nowy;

	return pHead;
}
void usun_rekordy(wynik *pHead)
{
	while (pHead)
	{
		waz *nastepnik = pHead->pNext;
		free(pHead);
		pHead = nastepnik;
	}
	return;
}
punkt jedzonko(int l_wierszy, int l_kolumn)
{
	punkt mysz;
	mysz.x = 1 + (rand() / (RAND_MAX + 1.0) * (l_kolumn - 3));
	mysz.y = 3 + (rand() / (RAND_MAX + 1.0)* (l_wierszy - 4));
	mysz.z = '@';
	return mysz;
}
void usun_weza(waz *pHead)
{
	while (pHead)
	{
		waz *nastepnik = pHead->pNext;
		free(pHead);
		pHead = nastepnik;
	}
	return;
}
void usun_plansze(int **tablica, int l_wierszy)
{
	for (int i = 0; i < l_wierszy; i++)
	{
		free(tablica[i]);
	}
	free(tablica);
	return;
}
int skucie(waz *pHead)
{

	waz *p = pHead;
	while (p->pNext)
	{
		p = p->pNext;
		if (p->poziom == pHead->poziom && p->pion == pHead->pion)
			return 1;

	}
	return 0;
}
char ** stworz_plansze(int wiersz, int kolumna, punkt temp)
{
	char **tablica;


	tablica = malloc(wiersz * sizeof(char*));
	for (int k = 0; k < wiersz; k++)
	{
		tablica[k] = malloc(kolumna * sizeof(char));
	}
	for (int i = 0; i < wiersz; i++)
	{
		for (int j = 0; j < kolumna; j++)
		{
			if (i == 0 || i == wiersz - 1)
			{
				tablica[i][j] = '-';

			}
			else if (j == 0 || j == kolumna - 1)
			{
				tablica[i][j] = '|';

			}
			else
				tablica[i][j] = ' ';
		}

	}

	tablica[temp.y][temp.x] = temp.z;


	return tablica;
}
void wyswietl_plansze(char** tab, int wiersz, int kolumna)
{
	for (int i = 0; i < wiersz; i++)
	{
		for (int j = 0; j < kolumna; j++)
		{
			printf("%c", tab[i][j]);
		}
		printf("\n");
	}
}

void zapisz_wynik(wynik *pHead, int wiersz, char *nazwa_pliku)
{
	FILE *nowy = fopen(nazwa_pliku, "ab+");
	wynik *p = pHead;

	while (p)
	{
		fprintf(nowy,"%d \n", p->wartosc);
		p = p->pNext;

	}
	
	fclose(nowy);

}
void ruch(char **plansza, punkt zjedzone, int wiersz, int kolumna, char *plik)
{
	
	struct wynik *najlepszy_wynik = NULL;
	struct waz *franek = NULL;
	int licznik_pkt = 0;
	gotoxy(kolumna + 5, wiersz - 12);
	printf("Score: %d", licznik_pkt);
	int x = 5, y = 5, pre_x = x, pre_y = y;
	char a;
	franek = stworz_weza(franek, x, y);
	if (sprawdz_wylosowany_punkt(franek, zjedzone) == 0)
		jedzonko(wiersz, kolumna);
	gotoxy(pre_x, pre_y);
	printf(" ");
	gotoxy(x, y);
	franek = wyswietl_weza(franek, x, y);

	while (1)
	{

		if (x < pre_x&&y == pre_y)
		{

			franek = wyswietl_weza(franek, x, y);
			if (skucie(franek) == 1)
			break;
			gotoxy(x + 1, y);
		}
		else if (y > pre_y && x == pre_x)
		{
			franek = wyswietl_weza(franek, x, y);
			if (skucie(franek) == 1)
				break;
			gotoxy(x - 1, y - 1);
		}
		else if (y < pre_y && x == pre_x)
		{
			franek = wyswietl_weza(franek, x, y);
			if (skucie(franek) == 1)
				break;
			gotoxy(x - 1, y + 1);
		}
		else if (x > pre_x && y == pre_y)
		{
			franek = wyswietl_weza(franek, x, y);
			if (skucie(franek) == 1)
				break;
			gotoxy(x - 1, y);
		}
		gotoxy(x, y);
		a = _getch();
		pre_x = x;
		pre_y = y;
		if (a == 80)
			y += 1;
		if (a == 72)
			y -= 1;
		if (a == 77)
			x += 1;
		if (a == 75)
			x -= 1;
		if (x == kolumna-1 || x == 0 || y == wiersz - 1 || y == 0)
		{
			najlepszy_wynik = rekordy(najlepszy_wynik, licznik_pkt);
			break;
		}
		if (skucie(franek) == 1)
			break;


		if (x == zjedzone.x && y == zjedzone.y)
		{
			licznik_pkt += 3;
			franek = stworz_weza(franek, x, y);
			gotoxy(kolumna + 11, wiersz - 12);
			printf(" %d", licznik_pkt);
			gotoxy(x, y);
			zjedzone = jedzonko(wiersz, kolumna);
			plansza[zjedzone.y][zjedzone.x] = zjedzone.z;
			gotoxy(zjedzone.x, zjedzone.y);
			printf("%c", plansza[zjedzone.y][zjedzone.x]);
			gotoxy(x, y);
		}
		if (skucie(franek) == 1)
			break;
		if (sprawdz_wylosowany_punkt(franek, zjedzone) == 0)
			jedzonko(wiersz, kolumna);
	}
	usun_weza(franek);
	zapisz_wynik(najlepszy_wynik, wiersz,plik);
	usun_rekordy(najlepszy_wynik);
	
	return;
}
