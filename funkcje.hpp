//
//  funkcje.hpp
//  Darwin
//
//  Created by Radek Grzywacz on 16/01/2023.
//

//WERSJA OSTATECZNA

#ifndef funkcje_hpp
#define funkcje_hpp

#include <stdio.h>
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 *@file
 */

/*! \mainpage Darwin
 *
 * \section intro_sec Wstep
 *  Program majacy na celu symulacje ewolucji gatunku.
 *
 *\section test_sec Plik wejsciowy
 *W zalaczonych plikach znajduje sie plik tekstowy bedacy przykladowym plikiem wejsciowym zawierajacym pierwsze pokolenie osobnikow
 *
 *\section instr_sec Instrukcja
 * Aby prawidlowo uzyc programu, nalezy uzyc takich przelacznikow:
 * 1. -i <tu wpisz nazwe pliku zrodlowego>
 * 2. -o <tu wpisz nazwe pliku wyjsciowego>
 * 3. -w <tu wpisz wspolczynnik wymierania osobnikow w przedziale od 0 do 1>
 * 4. -r <tu wpisz wspolczynnik rozmnazania w przedziale od 0 do 1>
 * 5. -p <tu wpisz ilosc pokolen>
 * 6. -k <tu wpisz ilosc par do krzyzowania>
 *
 *
 *
 *\author Radoslaw Grzywacz
 *
 */

/**
 *@brief Wczytaj - funkcja wczytujaca pierwsze pokolenie z danego pliku wejsciowego
 *@param wejscie - plik wejsciowy z pierwszym pokoleniem
 *@param populacja - lista przechowujaca wszystkie osobniki
 */
void wczytaj(ifstream& wejscie, list<list<int>>& populacja);

/**
 *@brief rand_int - funkcja bedaca generatorem losowych liczb
 *@param low - minimalna losowana liczba
 *@param high - maksymalna losowana liczba
*/
int rand_int(int low, int high);

/**
 *@brief losowanie - losowanie dwoch osobnikow do krzyzowania
 *@param populacja - lista przechowujaca calkowita populacje (wszystkie listy osobnikow)
 *@param mama - lista do ktorej trafia pierwszy wylosowany do krzyzowania osobnik
 *@param tata - lista do ktorej trafia drugi wylosowany do losowania osobnik
 */
void losowanie(list<list<int>>& populacja, list<int>& mama, list<int>& tata);

/**
 *@brief krzyzowanie - krzyzowanie wczesniej wylosowanych osobnikow
 *@param mama - lista do ktorej trafia pierwszy wylosowany do krzyzowania osobnik
 *@param tata - lista do ktorej trafia drugi wylosowany do losowania osobnik
 *@param populacja - lista przechowujaca calkowita populacje (wszystkie listy osobnikow)
*/
void krzyzowanie(list<int> mama, list<int> tata, list<list<int>>& populacja);

/**
 *@brief przystosowanie_max - wyliczenie maksymalnego przystosowania dla danego pokolenia
 *@param populacja - lista przechowujaca calkowita populacje (wszystkie listy osobnikow)
 *@param max_suma - zmienna przechowujaca przystosowanie najlepszego osobnika
*/
void przystosowanie_max(list<list<int>>& populacja, float& max_suma);

/**
 *@brief przystosowanie - wyliczenie przystosowania dla kazdego osobnika z osobna
 *@param populacja - lista przechowujaca calkowita populacje (wszystkie listy osobnikow)
 *@param max_suma - zmienna przechowujaca przystosowanie najlepszego osobnika
 *@param fitness - wektor przechowujacy przystosowanie kolejnych osobnikow
*/
void przystosowanie(list<list<int>>& populacja, float& max_suma, vector<double>& fitness);

/**
 *@brief rozmnazanie - rozmnazanie osobnikow, bedacych powyzej wspolczynnika rozmnazania
 *@param populacja - lista przechowujaca calkowita populacje (wszystkie listy osobnikow)
 *@param max_suma - zmienna przechowujaca przystosowanie najlepszego osobnika
 *@param wspRozmnazania - zmienna przechowujaca podana przez uzytkownika minimalnej wartosci potrzebnej do rozmnazania sie osobnikow
 *@param mama - lista do ktorej trafia pierwszy wylosowany do krzyzowania osobnik
 *@param tata - lista do ktorej trafia drugi wylosowany do losowania osobnik
 *@param iloscPar - zmienna przechowujaca podana przez uzytkownika ilosc par losowanych do rozmnazania sie przy kazdym pokoleniu
 *@param fitness - wektor przechowujacy przystosowanie kolejnych osobnikow

*/
void rozmnazanie(list<list<int>>& populacja, float& max_suma, float wspRozmnazania, list<int> mama, list<int> tata, int iloscPar, vector<double>& fitness);

/**
 *@brief usuwanie - usuwanie osobnikow bedacyh ponizej progu wymierania
 *@param populacja - lista przechowujaca calkowita populacje (wszystkie listy osobnikow)
 *@param max_suma - zmienna przechowujaca przystosowanie najlepszego osobnika
 *@param wspWymierania - zmienna przechowujaca podana przez uzytkownika minimalna wartosc potrzebna do przezycia osobnikow
 *@param fitness - wektor przechowujacy przystosowanie kolejnych osobnikow
*/
void usuwanie(list<list<int>>& populacja, float& max_suma, float wspWymierania, vector<double>& fitness);

/**
 *@brief wpisz - funkcja wypisujaca ostateczny stan populacji do pliku
 *@param populacja - lista przechowujaca calkowita populacje (wszystkie listy osobnikow)
 *@param wyjscie - tworzenie pliku wyjsciowego
*/
void wpisz(list<list<int>>& populacja, ofstream& wyjscie);

#endif /* funkcje_hpp */
