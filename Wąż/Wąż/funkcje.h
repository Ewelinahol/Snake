#ifndef funkcje_h
#define funkcje_h
/*Struktura odpowiedzialna za liste- weza*/
typedef struct
{
	int poziom, pion;
	char znak;
	struct waz *pNext, *pPrev;

}waz;
/*struktura odpowiedzialna za wspolrzedne punktu, ktory ma zostac "zjedzony"*/
typedef struct
{
	int x, y;
	char z;

}punkt;
/*Struktura tworzaca liste wynikow*/
typedef struct
{
	int wartosc;
	struct wynik *pNext;

}wynik;

/*Funkcja ustawia kursor na ustalonej pozycji*/
void gotoxy(int x, int y);
/*Funkcja tworzy lub powiêksza liste- weza*/
waz* stworz_weza(waz *pHead, int wiersz, int kolumna);
/*Funkcja wyswietla weza i zostaj¹ zmienione wspó³rzêdne ostatniego elementu, który staje sie pierwszym, x- aktualna pozioma wspolrzedna, y- aktualna pionowa wspolrzedna*/
waz *wyswietl_weza(waz *pHead, int x, int y);
/*Funkcja odpowiedzialna za tworzenie listy z najlepszymi wynikami*/
wynik *rekordy(wynik *pHead, int wartosc_wyniku);
/*Funkcja usuwa listê wyników */
void usun_rekordy(wynik *pHead);
/*Funkcja losuje punkt w obrêbie planszy*/
punkt jedzonko(int l_wierszy, int l_kolumn);
/*Funkcja usuwa listê-we¿a*/
void usun_weza(waz *pHead);
/*Funkcja usuwa plansze w której porusza siê w¹¿*/
void usun_plansze(int **tablica, int l_wierszy);
/*Funkcja sprawdza wspolrzedne kazdego elementu listy czy pokrywa sie z glowa listy. W ten sposob determinowane jest czy waz "wpelznal" na siebie samego */
int skucie(waz *pHead);
/*Funkcja aalokuje dynamicznie plansze po ktorej porusza sie waz*/
char ** stworz_plansze(int wiersz, int kolumna, punkt temp);
/*Funkcja wyswietla na konsoli gotowa plansze*/
void wyswietl_plansze(char** tab, int wiersz, int kolumna);
/*funkcja wyswietla wyniki*/
void zapisz_wynik(wynik *pHead, int wiersz, char *plik);
/*Funkcja odczytujaca z klawiatury znak i w ten sposob zmieniajace pozycje kursora. Wywoluje funkcje zwiazane z tworzeniem weza, wyswietlaniem go na konsoli.
Sprawdza takze czy obecna pozycja glowy weza pokrywa sie z punktem ktory zostaje "zjedzony", albo czy obecna pozycja pokrywa sie z innym elementem nalezacym do weza.
Wywo³uje równie¿ funkcje odpoweidzialne za usuwanie wycieków pamiêci. */
void ruch(char **plansza, punkt zjedzone, int wiersz, int kolumna,char *plik);














#endif
