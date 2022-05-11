#include <iostream>
#include <vector>
#include "../../src/EColors.h"

using namespace std;

void GetColor (EColors color){
    switch (color) {
        case BLACK:             cout << "\u001b[30m";   break;
        case RED :              cout << "\u001b[31m";   break;
        case GREEN :            cout << "\u001b[32m";   break;
        case YELLOW :           cout << "\u001b[33m";   break;
        case BLUE :             cout << "\u001b[34m";   break;
        case MAGENTA :          cout << "\u001b[35m";   break;
        case CYAN :             cout << "\u001b[36m";   break;
        case WHITE :            cout << "\u001b[37m";   break;
        case BRIGHT_BLACK :     cout << "\u001b[30;1m"; break;
        case BRIGHT_RED :       cout << "\u001b[31;1m"; break;
        case BRIGHT_GREEN :     cout << "\u001b[32;1m"; break;
        case BRIGHT_YELLOW :    cout << "\u001b[33;1m"; break;
        case BRIGHT_BLUE :      cout << "\u001b[34;1m"; break;
        case BRIGHT_MAGENTA :   cout << "\u001b[35;1m"; break;
        case BRIGHT_CYAN :      cout << "\u001b[36;1m"; break;
        case BRIGHT_WHITE :     cout << "\u001b[37;1m"; break;
        case BACKGROUND_YELLOW: cout << "\u001b[43m\u001b[30m"; break;
        case BACKGROUND_RED:    cout << "\u001b[41m\u001b[30m"; break;
        case BACKGROUND_WHITE:  cout << "\u001b[47m\u001b[30m"; break;
        case RESET :            cout << "\u001b[0m";    break;
        default: break;
    }
}

void printChar (char c){
    switch (c) {
        case '#': GetColor(EColors::CYAN);                   cout << "#"; break;
        case 'X': GetColor(EColors::BACKGROUND_YELLOW);      cout << " "; GetColor (EColors::RESET); break;
        case 'x': GetColor(EColors::BACKGROUND_YELLOW);      cout << "▓"; GetColor (EColors::RESET); break;
        case '>': GetColor(EColors::GREEN);                  cout << "\033[5m>\033[25m"; break;
        case '<': GetColor(EColors::GREEN);                  cout << "\033[5m<\033[25m"; break;
        case '^': GetColor(EColors::GREEN);                  cout << "\033[5m^\033[25m"; break;
        case 'v': GetColor(EColors::GREEN);                  cout << "\033[5mv\033[25m"; break;
        case '{': GetColor(EColors::RED);                    cout << "\033[5m<\033[25m"; break;
        case '}': GetColor(EColors::RED);                    cout << "\033[5m>\033[25m"; break;
        case 'L': GetColor(EColors::BACKGROUND_RED);         cout << "▓"; GetColor (EColors::RESET); break;
        case 'A': GetColor(EColors::RESET);                  cout << " "; break;
        case 'C': GetColor(EColors::BACKGROUND_WHITE);       cout << " "; GetColor (EColors::RESET); break;
        case 'c': GetColor(EColors::BACKGROUND_WHITE);       cout << "▓"; GetColor (EColors::RESET); break;
        default : break;
    }
}

void PrintData (char c, size_t i, size_t j){
    switch (c){
        case 'A': cout << "A " << i << " " << j << " 1" << endl; break;
        case 'L': cout << "L " << i << " " << j << " 1" << endl; break;
        case 'X': cout << "X " << i << " " << j << " 200" << endl; break;
        case 'C': cout << "C " << i << " " << j << " 500" << endl; break;
        case '#': cout << "# " << i << " " << j << " 1" << endl; break;
    }
}

int main (void) {

    size_t width, height;

    vector < vector < char > > map;

    cin  >> width;
    cin >> height;

    map.resize(height);
    for (size_t i = 0; i < height; ++i)
        map[i].resize(width);

    for (size_t i = 0; i < height; ++i){
        char c;

        for (size_t j = 0; j < width; ++j){
            cin >> c;
            if ( (i == 0 || i == height - 1 || j == 0 || j == width -1) && c != '#' ){
                cout << "Borders fail" << endl;
                return 1;
            }
            if ( c != '#' && c != 'A' && c != 'X' && c != 'C' && c != 'L'){
                cout << "Unknown field" << endl;
                return 2;
            }
            map[i][j] = c;
        }
    }

   /*
    for (size_t i = 0; i < height; ++i){
        for (size_t j = 0; j < width ; ++j){
            printChar(map[i][j]);
        }
        cout << endl;
    }
    */

    cout << "MAP_INFO" << endl;
    cout << width << " " << height << endl << endl;

    for (size_t i = 0; i < height; ++i){
        for (size_t j = 0; j < width; ++j){
            PrintData (map[i][j], i, j);
        }
        cout << endl;
    }

    cout << "END_OF_MAP_INFO" << endl;

    return 0;
}