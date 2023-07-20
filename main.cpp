//
//  main.cpp
//  Darwin
//
//  Created by Radek Grzywacz on 16/01/2023.
//

//WERSJA OSTATECZNA

#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "funkcje.hpp"
#include <algorithm>


using namespace std;

int main(int argc, char* argv[]){
    
    
    float wspWymierania;
    float wspRozmnazania;
    int iloscPokolen;
    int iloscPar;
    string wej;
    string wyj;
    list<list<int>> populacja;
    vector<list<int>> pary;
    list<int> mama;
    list<int> tata;
    
        for(int i = 1; i < argc; i++){
            string a = argv[i];
            if(a == "-i"){ //plik wejściowy z populacja
                wej = argv[i + 1];
                i++;
            }
            else if(a == "-o"){ //plik wyjściowy z populacja
                wyj = argv[i + 1];
                i++;
                
            }
            else if(a == "-w"){ //wspolczynnik wymierania
                wspWymierania = stof(argv[i + 1]);
                i++;
            }
            else if(a == "-r"){ //wspolczynnik rozmnazania
                wspRozmnazania = stof(argv[i+1]);
                i++;
            }
            else if(a == "-p"){ //liczba pokolen p
                iloscPokolen = atoi(argv[i+1]);
                i++;
            }
            else if(a == "-k"){ //liczba osobnikow losowanych do krzyzowania
                iloscPar = atoi(argv[i+1]);
                i++;
            }
        }
    
    //wyswietlanie instrukcji przy blednym wprowadzeniu argumentów i kontrola błędu wprowadzania
    if (argc < 13 || wej.empty() || wyj.empty() || wspWymierania == 0.0 || wspRozmnazania == 0.0 || iloscPokolen == 0 || iloscPar == 0) {
        cout << "INSTRUKCJA UZYCIA PROGRAMU: \nPodaj poprawne argumenty: \n-i <tu wpisz nazwe pliku źródłowego> \n-o <tu wpisz nazwe pliku wyjsciowego> \n-w <tu wpisz współczynnik wymierania osobników w przedziale od 0 do 1> \n-r <tu wpisz współczynnik rozmnazania w przedziale od 0 do 1> \n-p <tu wpisz ilość pokoleń> \n-k <tu wpisz ilość par do krzyżowania> " << endl;
        return 0;
        }
    
    
    //dodawanie pierwszych osobnikow do listy
    ifstream wejscie(wej);

    if(!wejscie.good()|| !wejscie.is_open()){
        cout << "Plik wejściowy nie został otwarty. Podaj poprawną nazwe pliku np. populacja_wejscie.txt" << endl;
        return 0;

    }
        wczytaj(wejscie, populacja);
        for(int i = 0; i < iloscPokolen; i++){  //petla dla kazdej generacji
            float max_suma = 0; //max_suma gorna granica wspolczynnika
            vector<double> fitness;
            przystosowanie_max(populacja, max_suma);
            przystosowanie(populacja, max_suma, fitness);
            rozmnazanie(populacja, max_suma, wspRozmnazania, mama, tata, iloscPar, fitness);
            usuwanie(populacja, max_suma, wspWymierania, fitness);
        }
        
        ofstream wyjscie(wyj);
        if(!wyjscie.good()|| !wyjscie.is_open()){
            cout << "Plik wyjściowy nie został otwarty" << endl;
            return 0;
        }

        wpisz(populacja, wyjscie);
        cout << "Symulacja została zakończona. Wyniki znajdują się w pliku wyjściowym." << endl;
        return 0;
    }
