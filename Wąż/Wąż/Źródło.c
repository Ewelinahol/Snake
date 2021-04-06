#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include"vld.h"
#include"funkcje.h"





int main(int argc,char *argv[50])
{
	char nazwa_pliku[50] = { '\0' };
	for(int i=0;i<50;i++)
	nazwa_pliku[i] = argv[1][i];
	srand(time(NULL));
	char *odpowiedz=NULL;
	int dowiemy_sie;
	int licznik_pkt = 0;
	int wiersz=20, kolumna=70;
	punkt zjedzone = jedzonko(wiersz, kolumna);
	char **plansza;
	plansza = stworz_plansze(wiersz, kolumna, zjedzone);
		system("cls");
		wyswietl_plansze(plansza, wiersz, kolumna);
		ruch(plansza, zjedzone, wiersz, kolumna, nazwa_pliku);
		usun_plansze(plansza, wiersz);
		gotoxy(0, wiersz);
		printf("Koniec gry!\n");
		
	
	return 0;

}