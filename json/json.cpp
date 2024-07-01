#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void jest_json(bool json, ifstream& plik) {         //funkcja wyswietla informacje o poprawnosci pliku i wychodzi z programu
    cout << "PLIK JEST PRAWIDLOWYM FORMATEM JSON!" << endl;
    json = true;
    plik.close();
    exit(0);
}

void nie_jest_json(int liczw, bool json, ifstream& plik) {        //funkcja wyswietla informacje o niepoprawnosci pliku i wychodzi z programu
    cout << "PLIK NIE JEST PRAWIDLOWYM FORMATEM JSON! BLAD WYSTEPUJE W " << liczw + 1 << " ZNAKU" << endl;
    json = true;
    plik.close();
    exit(0);
}
void sprawdzenie_dla_ws(int liczw, bool json, ifstream& plik, char t[], int wyraz) {        //jezeli przed indexem miejsca (liczws) jest WS
    liczw++;
    if (t[liczw + 1] != ' ' && t[liczw + 1] != '\n' && t[liczw + 1] != '\t' && t[liczw + 1] != '\r') {
        nie_jest_json(liczw, json, plik);
    }

    while (t[liczw + 1] == ' ' || t[liczw + 1] == '\n' || t[liczw + 1] == '\t' || t[liczw + 1] == '\r') {
        liczw++;
        
        if (liczw == wyraz - 1) {
            jest_json(json, plik);
        }

        if (t[liczw + 1] != ' ' && t[liczw + 1] != '\n' && t[liczw + 1] != '\t' && t[liczw + 1] != '\r') {
            nie_jest_json(liczw, json, plik);
        }
    }
}

void sprawdzenie_po_kropce(int liczw, bool json, ifstream& plik, char t[], int wyraz) {        //jezeli przed indexem miejsca (liczws) jest kropka
    liczw++;
    if (t[liczw + 1] != '0' && t[liczw + 1] != '1' && t[liczw + 1] != '2' && t[liczw + 1] != '3' && t[liczw + 1] != '4' && t[liczw + 1] != '5' && t[liczw + 1] != '6' && t[liczw + 1] != '7' && t[liczw + 1] != '8' && t[liczw + 1] != '9') {
        nie_jest_json(liczw, json, plik);
    }
    else {
        while (t[liczw + 1] == '0' || t[liczw + 1] == '1' || t[liczw + 1] == '2' || t[liczw + 1] == '3' || t[liczw + 1] == '4' || t[liczw + 1] == '5' || t[liczw + 1] == '6' || t[liczw + 1] == '7' || t[liczw + 1] == '8' || t[liczw + 1] == '9') {

            liczw++;

            if (liczw == wyraz - 1) {
                jest_json(json, plik);
            }

            if (t[liczw + 1] == ' ' || t[liczw + 1] == '\n' || t[liczw + 1] == '\t' || t[liczw + 1] == '\r') {
                sprawdzenie_dla_ws(liczw,json, plik, t, wyraz);

            }
            if (t[liczw + 1] != '0' && t[liczw + 1] != '1' && t[liczw + 1] != '2' && t[liczw + 1] != '3' && t[liczw + 1] != '4' && t[liczw + 1] != '5' && t[liczw + 1] != '6' && t[liczw + 1] != '7' && t[liczw + 1] != '8' && t[liczw + 1] != '9' && t[liczw + 1] != ' ' && t[liczw + 1] != '\n' && t[liczw + 1] != '\t' && t[liczw + 1] != '\r') {
                nie_jest_json(liczw,json, plik);
            }
        }
        
    }
}

int main()
{
    char opcje;          //zmienna do switch case
    string nazwa_pliku;  //nazwa pliku do wpisania
    int licznik = 0;     //licznik 
    char tab[1001];     //tablica skladujaca dane wczytane z pliku
    int wyrazy = 0;     //ilosc wyrazow w pliku
    int ws = 0;         //licznik zliczajacy znaki WS przed pojawieniem sie 1 znaku nie bedacego WS
    int liczws = 0;     //licznik aktualnej pozycji w tablicy wczytanych charow
    bool sprawdzenie_json = false;    //jesli = true - program wykonal sprawdzenie formatu pliku
    ifstream plik;      // wczytywany plik

    do {
        wyrazy = 0;    //zerowanie wszystkich wartosci na poczatku petli
        licznik = 0;
        ws = 0;
        liczws = 0;
        for (int j = 0; j < 1000; j++) {
            tab[j] = ' ';
        }
        cout << "=============================================PROJEKT JSON===========================================" << endl;
        cout << "'H'-menu pomocnicze | 'O'-otworz plik | 'C'-sprawdz poprawnosc formatu JSON | 'Q' - wyjdz z programu" << endl << endl;
        cout << "Wybierz opcje:" << endl;
        cin >> opcje;
        system("cls");
        switch (opcje) {
        case 'h':     //operacja h - wyswietlenie helpa
            cout << "LISTA DOSTEPNYCH OPERACJI:" << endl;
            cout << "'O'- Operacja otwarcia pliku o nazwie podanej przez uzytkownika. Operacja informuje, czy plik zostal otwarty." << endl;
            cout << "'H'- Operacja wyswietla liste dostepnych operacji" << endl;
            cout << "'C'- Operacja sprawdza, czy otwarty plik jest poprawnym formatem JSON. Jesli nie jest, to wskazuje miejsce bledu w pliku" << endl;
            cout << "'P'- Operacja pobiera dane z pliku przy uzyciu JSONpath. Podaje wartosc danych oraz informuje o typie danych" << endl;
            cout << "PROJEKT WYKONAL BARTLOMIEJ RADZIUN 186914" << endl;
            system("pause");
            system("cls");
            break;

        case 'o':    //operacja o - otwarcie pliku
            plik.close();
            cout << "podaj nazwe pliku: " << endl;
            cin >> nazwa_pliku;
            plik.open(nazwa_pliku);
            if (plik.is_open()) {
                cout << "Plik jest otwarty" << endl;
            }
            else {
                cout << "nie udalo sie otworzyc pliku" << endl;
            }
            system("pause");
            system("cls");
            break;
        case 'c':                                    //operacja c- sprawdzenie poprawnosci pliku json
            if (plik.is_open()) {
                cout << "Plik jest otwarty" << endl;     
                while (!plik.eof()) {                //wczytanie danych z pliku tekstowego. skladowanie ich char po charze w tablicy
                    plik.get(tab[licznik]);
                    licznik++;
                    wyrazy++;
                }

                //sprawdzenie, czy ostatni znak jest WS
                if (tab[licznik-2] != ' ' && tab[licznik-2] != '\n' && tab[licznik-2] != '\t' && tab[licznik-2] != '\r') {
                    cout << "PLIK NIE JEST PRAWIDLOWYM FORMATEM JSON, KONCOWY ZNAK MUSI BYC WS" << endl;
                    sprawdzenie_json = true;
                    plik.close();
                    exit(0);
                }
                //zliczenie poczatkowego ciagu WS, sprawdzenie, czy plik zawiera jakas wartosc
                while (tab[ws] == ' '|| tab[ws] == '\n' || tab[ws] == '\t' || tab[ws] == '\r') {
                    ws++;
                    liczws++;
                    if (liczws == wyrazy - 1) {
                        cout << "PLIK NIE JEST PRAWIDLOWYM FORMATEM JSON, BRAKUJE WARTOSCI" << endl;
                        sprawdzenie_json = true;
                        plik.close();
                        exit(0);
                    }
                }
                //sprawdzenie, czy zerowy znak jest WS
                if (tab[0] != ' ' && tab[0] != '\n' && tab[0] != '\t' && tab[0] != '\r') {
                    cout << "PLIK NIE JEST PRAWIDLOWYM FORMATEM JSON, ZEROWY ZNAK W PLIKU MUSI BYC WS" << endl;
                    sprawdzenie_json = true;
                    plik.close();
                    exit(0);
                }
                
                while (sprawdzenie_json == false) {     
                    //=======WARUNEK DLA CYFR 1-9============================================================================== 
                    if (tab[liczws] == '1' || tab[liczws] == '2' || tab[liczws] == '3' || tab[liczws] == '4' || tab[liczws] == '5' || tab[liczws] == '6' || tab[liczws] == '7' || tab[liczws] == '8' || tab[liczws] == '9') {
                        if (tab[liczws + 1] == '0' || tab[liczws + 1] == '1' || tab[liczws + 1] == '2' || tab[liczws + 1] == '3' || tab[liczws + 1] == '4' || tab[liczws + 1] == '5' || tab[liczws + 1] == '6' || tab[liczws + 1] == '7' || tab[liczws + 1] == '8' || tab[liczws + 1] == '9') {
                            liczws++; 
                            while (tab[liczws + 1] == '0' || tab[liczws + 1] == '1' || tab[liczws + 1] == '2' || tab[liczws + 1] == '3' || tab[liczws + 1] == '4' || tab[liczws + 1] == '5' || tab[liczws + 1] == '6' || tab[liczws + 1] == '7' || tab[liczws + 1] == '8' || tab[liczws + 1] == '9') {
                                liczws++;
                                if (liczws == wyrazy - 1) {
                                    jest_json(sprawdzenie_json, plik);
                                }
                                    
                            }
                           
                            if (tab[liczws + 1] == '.') {
                                sprawdzenie_po_kropce(liczws, sprawdzenie_json, plik, tab, wyrazy);
                               
                            }
                            else if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                                sprawdzenie_dla_ws(liczws, sprawdzenie_json, plik,tab, wyrazy);
                                
                            }
                            
                            
                        }
                        
                        else if (tab[liczws + 1] == '.') {
                            sprawdzenie_po_kropce(liczws, sprawdzenie_json, plik, tab, wyrazy);
                            
                        }
                        else if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                        sprawdzenie_dla_ws(liczws, sprawdzenie_json, plik, tab, wyrazy);
                           
                        }
                        else {
                        nie_jest_json(liczws, sprawdzenie_json, plik);
                        }
                    }//DLA 0 =========================================================================================================================
                    else if(tab[liczws] == '0') {       //jesli po 0 wystepuje bialy znak
                        if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                            sprawdzenie_dla_ws(liczws, sprawdzenie_json, plik, tab, wyrazy);
                            
                        }
                        //Warunek, jesli po 0 wystepuje kropka
                        else if (tab[liczws + 1] == '.') {
                            sprawdzenie_po_kropce(liczws, sprawdzenie_json, plik, tab, wyrazy);
                            
                        }
                        else {
                            nie_jest_json(liczws, sprawdzenie_json, plik);
                        }

                    }//DLA '-' ==================================================================================================================
                    else if(tab[liczws] == '-') { //dla 0 po minusie
                        if (tab[liczws+1] == '0') {
                            liczws++;
                            if (tab[liczws + 1] == '.') {
                                sprawdzenie_po_kropce(liczws, sprawdzenie_json, plik, tab, wyrazy);
                                
                            }
                            else {
                                nie_jest_json(liczws, sprawdzenie_json, plik);
                            }
                        }
                        //waunek dla 1-9 po minusie
                        if (tab[liczws + 1] == '1' || tab[liczws + 1] == '2' || tab[liczws + 1] == '3' || tab[liczws + 1] == '4' || tab[liczws + 1] == '5' || tab[liczws + 1] == '6' || tab[liczws + 1] == '7' || tab[liczws + 1] == '8' || tab[liczws + 1] == '9') {
                            liczws++;
                            if (tab[liczws + 1] == '0' || tab[liczws + 1] == '1' || tab[liczws + 1] == '2' || tab[liczws + 1] == '3' || tab[liczws + 1] == '4' || tab[liczws + 1] == '5' || tab[liczws + 1] == '6' || tab[liczws + 1] == '7' || tab[liczws + 1] == '8' || tab[liczws + 1] == '9') {
                                liczws++; 
                                while (tab[liczws + 1] == '0' || tab[liczws + 1] == '1' || tab[liczws + 1] == '2' || tab[liczws + 1] == '3' || tab[liczws + 1] == '4' || tab[liczws + 1] == '5' || tab[liczws + 1] == '6' || tab[liczws + 1] == '7' || tab[liczws + 1] == '8' || tab[liczws + 1] == '9') {
                                    liczws++;
                                    if (liczws == wyrazy - 1) {
                                        jest_json(sprawdzenie_json, plik);
                                    }

                                }

                                if (tab[liczws + 1] == '.') {
                                    sprawdzenie_po_kropce(liczws, sprawdzenie_json, plik, tab, wyrazy);
                                    
                                }
                                else if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                                    sprawdzenie_dla_ws(liczws, sprawdzenie_json, plik, tab, wyrazy);
                                    
                                }

                            }
                            else if (tab[liczws + 1] == '.') {
                                sprawdzenie_po_kropce(liczws, sprawdzenie_json, plik, tab, wyrazy);
                                
                            }
                            else if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                                sprawdzenie_dla_ws(liczws, sprawdzenie_json, plik, tab, wyrazy);
                                
                            }
                            else {
                            nie_jest_json(liczws, sprawdzenie_json, plik);
                            }
                        }
                        else{
                        nie_jest_json(liczws, sprawdzenie_json, plik);
                        }
                    }//KONIEC WARUNKU DLA CYFRY================================================================================================================
                     //====WARUNEK DLA STRINGA=================================================================================================================
                    else if(tab[liczws] == '"') {
                        while (tab[liczws+1] != '"' && liczws != wyrazy-2) {
                            if (tab[liczws + 1] == '\\' && tab[liczws + 2] == '\\') {
                                liczws++;
                                liczws++;

                            }
                            else if (tab[liczws+1] == '\\' && tab[liczws + 2] == 't') {
                                liczws++;
                                liczws++;
                            }
                            else if (tab[liczws+1] == '\\' && tab[liczws + 2] == '"') {

                                liczws++;
                                liczws++;
                            }
                            else if (tab[liczws+1] == '\\' && tab[liczws + 2] != '"' && tab[liczws + 2] != 't' && tab[liczws + 2] != '\\') {
                                nie_jest_json(liczws, sprawdzenie_json, plik);
                           }
                            else {
                                liczws++;
                            }
                            
                        }
                        if (tab[liczws + 1] == '"') {
                            liczws++;
                            if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                                liczws++;
                                if (tab[liczws + 1] != ' ' && tab[liczws + 1] != '\n' && tab[liczws + 1] != '\t' && tab[liczws + 1] != '\r') {
                                    nie_jest_json(liczws, sprawdzenie_json, plik);
                                }

                                while (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                                    liczws++;
                                    if (tab[liczws + 1] == NULL) {
                                        jest_json(sprawdzenie_json, plik);
                                    }
                                    if (liczws == wyrazy - 1) {
                                        jest_json(sprawdzenie_json, plik);
                                    }

                                    if (tab[liczws + 1] != ' ' && tab[liczws + 1] != '\n' && tab[liczws + 1] != '\t' && tab[liczws + 1] != '\r') {
                                        nie_jest_json(liczws, sprawdzenie_json, plik);
                                    }
                                }
                            }
                            else {
                                nie_jest_json(liczws, sprawdzenie_json, plik);
                            }
                        }
                        if (liczws == wyrazy - 2) {
                            cout << "PLIK NIE JEST PRAWIDLOWYM FORMATEM JSON, BRAKUJE ZAMKNIECIA STRINGA" << endl;
                            sprawdzenie_json = true;
                            plik.close();
                            exit(0);
                        }
                    }
                   // ===========WARUNEK NA LITERAL TRUE==================================================================================================
                    else if(tab[liczws] == 't') {
                        if (tab[liczws + 1] == 'r') {
                            liczws++;
                            if (tab[liczws + 1] == 'u') {
                                liczws++;
                                if (tab[liczws + 1] == 'e') {
                                    liczws++;
                                    if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                                        sprawdzenie_dla_ws(liczws, sprawdzenie_json, plik, tab, wyrazy);
                                        
                                    }
                                    else {
                                        nie_jest_json(liczws, sprawdzenie_json, plik);
                                    }
                                }
                                else {
                                    nie_jest_json(liczws, sprawdzenie_json, plik);
                                }
                            }
                            else {
                                nie_jest_json(liczws, sprawdzenie_json, plik);
                            }
                        }
                        else {
                            nie_jest_json(liczws, sprawdzenie_json, plik);
                        }
                    }//warunek dla null
                    else if (tab[liczws] == 'n') {
                        if (tab[liczws + 1] == 'u') {
                            liczws++;
                            if (tab[liczws + 1] == 'l') {
                                liczws++;
                                if (tab[liczws + 1] == 'l') {
                                    liczws++;
                                    if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                                        sprawdzenie_dla_ws(liczws, sprawdzenie_json, plik, tab, wyrazy);
                                        
                                    }
                                    else {
                                        nie_jest_json(liczws, sprawdzenie_json, plik);
                                    }
                                }
                                else {
                                    nie_jest_json(liczws, sprawdzenie_json, plik);
                                }
                            }
                            else {
                                nie_jest_json(liczws, sprawdzenie_json, plik);
                            }
                        }
                        else {
                            nie_jest_json(liczws, sprawdzenie_json, plik);
                        }
                    }//warunek dla false
                    else if(tab[liczws] == 'f') {
                        if (tab[liczws + 1] == 'a') {
                            liczws++;
                            if (tab[liczws + 1] == 'l') {
                                liczws++;
                                if (tab[liczws + 1] == 's') {
                                    liczws++;
                                    if (tab[liczws + 1] == 'e') {
                                        liczws++;
                                        if (tab[liczws + 1] == ' ' || tab[liczws + 1] == '\n' || tab[liczws + 1] == '\t' || tab[liczws + 1] == '\r') {
                                            sprawdzenie_dla_ws(liczws, sprawdzenie_json, plik, tab, wyrazy);
                                            
                                        }
                                        else {
                                            nie_jest_json(liczws, sprawdzenie_json, plik);

                                        }
                                    }
                                    else {
                                        nie_jest_json(liczws, sprawdzenie_json, plik);
                                    }
                                }
                                else {
                                    nie_jest_json(liczws, sprawdzenie_json, plik);
                                }
                            }
                            else {
                                nie_jest_json(liczws, sprawdzenie_json, plik);
                            }
                        }
                        else {
                            nie_jest_json(liczws, sprawdzenie_json, plik);
                        }
                    }
                    else {          //jezeli wartosc(pomijajac WS) nie rozpoczyna sie tak jak powinna liczba, string, true, false, null - czyli != {t,f,n,",-,0,1,2,3,4,5,6,7,8,9}
                        cout << "PLIK NIE JEST PRAWIDLOWYM FORMATEM JSON! BLAD WYSTEPUJE W " << liczws  << " ZNAKU" << endl;
                        sprawdzenie_json = true;
                        plik.close();
                        exit(0);
                    }
                }
            }
            else {
                cout << "Nie ma otwartego pliku!" << endl;
            }

            plik.close();
            system("pause");
            system("cls");
            break;
        case 'q':
            break;
        default:
            cout << "niepoprawna opcja" << endl;
            break;

        }
    } while (opcje != 'q');

    plik.close();
    return 0;
}