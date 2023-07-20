//
//  funkcje.cpp
//  Darwin
//
//  Created by Radek Grzywacz on 16/01/2023.
//

//WERSJA OSTATECZNA

#include "funkcje.hpp"
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

void wczytaj(ifstream& wejscie, list<list<int>>& populacja) {
    string linia;
    string chromosom;
    list<int> osobnik;
    
    
    while(getline(wejscie, linia)) {
        osobnik.clear();
        stringstream ss(linia); // tworzy stringstream z lini
        while (ss >> chromosom) { // bierze pojedyncze inty
            int liczba = atoi(chromosom.c_str());
            osobnik.push_back(liczba);
        }
        populacja.push_front(osobnik);
    }
    wejscie.close();
   
}

 
// RNG
int rand_int(int low, int high){
    static std::default_random_engine re {std::random_device{}()};
    using Dist = std::uniform_int_distribution<int>;
    static Dist uid {};
    return uid(re, Dist::param_type{low,high});
}

void losowanie(list<list<int>>& populacja, list<int>& mama, list<int>& tata){
    int indexMamy = rand_int(0,populacja.size() - 1);    //losowanie indeksu osobnika pierwszego do krzyzowania
    int indexTaty;

    do{
    indexTaty = rand_int(0, populacja.size() - 1);  //losowanie indeksu osobnika drugiego do krzyzowania z upewnieniem sie czy nie bedzie dublonu
      } while (indexMamy == indexTaty);

    auto it1 = next(populacja.begin(), indexMamy);    //przemieszczenie iteratora na wylosowana pozycje i wpisanie danych list jako rodzicow
    auto it2 = next(populacja.begin(), indexTaty);
    mama = *it1;
    tata = *it2;
}


void krzyzowanie(list<int> mama, list<int> tata, list<list<int>>& populacja){
    

    int pekniecie = rand_int(0, mama.size() + 1); //miejsce pekniecia chromosomu

    auto it = next(mama.begin(), pekniecie - 1);// iteracja do tego miejsca
    auto it2 = next(tata.begin(), pekniecie);
    
    mama.erase(it, mama.end());
    tata.erase(tata.begin(), it2); //pozbywa sie przedniej czesci chromosomu taty
    mama.splice(mama.end(), tata); // polaczenie obu

    list<int> dziecko = mama;

    populacja.push_back(dziecko);

}

void przystosowanie_max(list<list<int>>& populacja, float& max_suma){
    //petla ktora przechodzi po kazdym osoobniku i aktualizuje najwieksza sume
    for (auto& chromosomy : populacja) {
        float sum = accumulate(chromosomy.begin(), chromosomy.end(), 0);
        max_suma = max(max_suma, sum);
    }
}

void przystosowanie(list<list<int>>& populacja, float& max_suma, vector<double>& fitness){
   // vector<double> fitness; //wektor przechowujacy kolejne przystosowania
    //oblicza przystosowanie każdego osobnika
    for (auto& chromosomy : populacja) {
        int sum = accumulate(chromosomy.begin(), chromosomy.end(), 0);
        double F = sum / max_suma;
        fitness.push_back(F);
    }
}


void rozmnazanie(list<list<int>>& populacja, float& max_suma, float wspRozmnazania, list<int> mama, list<int> tata, int iloscPar, vector<double>& fitness){
    //rozmnazanie powyzej wspolczynnika rozmnazania
    auto it1 = populacja.begin();
    auto it2 = fitness.begin();
    int maxn = fitness.size();
    int n = 0;
    while (it1 != populacja.end() && n <= maxn){
        if (*it2 >= wspRozmnazania) {
            //rozmnażanie
            for(int i = 0; i < iloscPar; i++){
                losowanie(populacja, mama, tata);
                krzyzowanie(mama, tata, populacja);
                it1 = populacja.begin();
                it2 = fitness.begin();
            }
        }
        else {
            ++it1;
            ++it2;
        }
        n++;
    }
}

void usuwanie(list<list<int>>& populacja, float& max_suma, float wspWymierania, vector<double>& fitness){
    //usuwa osobniki pod progiem wymierania
    auto it = populacja.begin();
    auto fit = fitness.begin();
    int n = 0;
    int maxn = fitness.size();
    while (n < maxn){ //porownanie kolejnych osobnikow z kolejnymi przystosowaniami
        if (*fit < wspWymierania) {
            it = populacja.erase(it);
            fit = fitness.erase(fit);
        }
        else {
            ++it;
            ++fit;
        }
        n++;
    }
}

void wpisz(list<list<int>>& populacja, ofstream& wyjscie){

    for (auto osobnik : populacja){
        for (auto chromosom : osobnik){
            wyjscie << chromosom << " ";
        }
        wyjscie << endl;
    }
    
    wyjscie.close();

}
    
