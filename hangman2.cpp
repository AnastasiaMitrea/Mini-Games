#include <iostream>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <windows.h>

void hangman2();
void wordRandomize(char randomWord[], char randomSave[], char randomHint[]);
char strindex(char* str, int index);
int strpoz(char* str, char lit);
void startHangman();
void draw(int mistakes, char* sent1, char* alph, char* sent2, char* save, int indexLitera, char citit, char* negative, char* affirmative, char*word, bool guessed);
void input(int mistakes, char* hint, char& citit);
void logic(char* word, char citit, char* save, char* alph, int& indexLitera, int& mistakes);

using namespace std;

const int HEIGHT=43;
const int WIDTH=95;
const int NR_DESENE=7;
const int HEIGHT_DESEN=36;
const int WIDTH_DESEN=51;
const int CHAR_NR=256;
const int POSL_DRAWING=3;
const int POSC_DRAWING=37;
const int POSL_SENT1=8;        //POSL = positon line 
const int POSC_SENT1=7;        //POSC = position column
const int POSL_ALPH=12;
const int POSC_ALPH=3;
const int POSL_SENT2=16;
const int POSC_SENT2=9;
const int POSL_SAVE=19;
const int POSC_SAVE=12;
const int POSL_GUESSED=22;

char matrice[HEIGHT][WIDTH];
char drawing[NR_DESENE][HEIGHT_DESEN][WIDTH_DESEN];

int main(){
    hangman2();
    int c;
    cin>>c;
    return 0;
}

/*

FONT: 28

window size

WIDTH:  192
HEIGHT:  45

*/

void startHangman(){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   
    cfi.dwFontSize.Y = 28;                  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); 
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd,SW_SHOWMAXIMIZED);
}

void wordRandomize(char randomWord[], char randomSave[], char randomHint[]){
    int generator;
    srand((unsigned) time(0));
    generator = rand() % 20 + 1;
    const char* words[20]={"MARIO", "ABSURD", "MOUSEPAD", "SUBWAY", "BANJO", "BEACH", "GRAPH", "CRYSTAL", "LUCKY", "KETCHUP", "ZOMBIE", "ZEBRA", "TIGER", "KEYBOARD", "DRAWER", "RAMEN", "FRANCE", "JOYSTICK", "MACHINE", "WATER"};
    const char* saves[20]={"M___O", "A____D", "M______D", "S____Y", "B___O", "B___H", "G___H", "C_____L", "L___Y", "K_____P", "Z____E", "Z___A", "T___R", "K______D", "D____R", "R___N", "F____E", "J______K", "M_____E", "W___R"};
    const char* hints[20]={"Character in 2D game", "Synonym of 'illogical' ", "PC peripheral", "An underground tunnel... or a famous fast food chain", "A stringed musical instrument", "Coast of a sea/ocean", "Diagram that shows multiple variables", "Clear, transparent and beautiful rock", "Fortunate", "Tomato sauce", "Dead character whose corpse was revived (movies / video games)", "African animal with black and white stripes", "Large wild animal with orange fur and black stripes", "PC Peripheral", "Furniture meant to storage clothes", "Japanese soup with noodles", "Country in West Europe", "Device meant to control devices such as a computer", "System that uses power and has several parts and structures", "Essential substance for life"};
    strcpy(randomWord, words[generator-1]);
    strcpy(randomSave, saves[generator-1]);
    strcpy(randomHint, hints[generator-1]);
}


void hangman2(){
    startHangman();
    char word[CHAR_NR];
    char save[CHAR_NR];
    char hint[CHAR_NR];
    wordRandomize(word, save, hint);
    ifstream reader("mistakes.txt");
    
    for(int k=0; k<NR_DESENE; k++)
        for(int i=0; i<HEIGHT_DESEN; i++)
            for(int j=0; j<WIDTH_DESEN; j++){
                char nr;
                reader>>nr;
                if(nr=='.'){
                    nr=' ';
                    drawing[k][i][j]=nr;
                }
                else
                    drawing[k][i][j]=nr;   
            }
   
    char sent1[]="Available letters";
    char sent2[]="Your word is";
    char alph[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphLength=strlen(alph);
    int k=0;
    bool guessed=false;
    int mistakes=0;
    char affirmative[]=" was one of the letters!";
    char negative[]=" was not one of the letters";

    char citit=' ';
    int indexLitera=-1;
    while(!guessed && mistakes<6){
        draw(mistakes, sent1, alph, sent2, save, indexLitera, citit, negative, affirmative, word, guessed);
        input(mistakes, hint, citit);
        logic(word, citit, save, alph, indexLitera, mistakes);
        //TODO: put this code in draw
        
    }
    if(mistakes==6){
        cout<<endl<<"You have lost the game.";
    }
}

int strpoz(char* str, char lit){
    for(int i=0; i<strlen(str); i++)
        if(str[i]==lit){
            return i;
            break;
        }
    return -1;
}

void draw(int mistakes, char* sent1, char* alph, char* sent2, char* save, int indexLitera, char citit, char* negative, char* affirmative, char*word, bool guessed){
    for(int i=0; i<HEIGHT; i++)
        for(int j=0; j<WIDTH; j++)
            matrice[i][j]=' ';
    for(int i=0; i<HEIGHT; i++)
        for(int j=0; j<WIDTH; j++)
            if(i!=0 && i!=HEIGHT-1)
                matrice[i][WIDTH/3]='|';

    for(int i=0; i<HEIGHT_DESEN; i++)
        for(int j=0; j<WIDTH_DESEN; j++)
            matrice[i+POSL_DRAWING][j+POSC_DRAWING]=drawing[mistakes][i][j];
        
    strcpy(&matrice[POSL_SENT1][POSC_SENT1], sent1);
    strcpy(&matrice[POSL_ALPH][POSC_ALPH], alph);
    strcpy(&matrice[POSL_SENT2][POSC_SENT2], sent2);
    strcpy(&matrice[POSL_SAVE][POSC_SAVE], save);
    if(indexLitera!=-1){
        matrice[POSL_GUESSED][indexLitera]=citit; 
        strcpy(&matrice[POSL_GUESSED][indexLitera+1], indexLitera==2?negative:affirmative);
    }
    if(strchr(save, '_')==NULL){
        cout<<endl<<"You have guessed the word "<<word<<" !";
        guessed=true;
    }
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++)
            cout<<matrice[i][j]<<" ";
        cout<<endl;
    } 
}
void input(int mistakes, char* hint, char& citit){
    int dif='a'-'A';
    back:
        cout<<endl<<"Please introduce a valid letter: "<<endl;
        if(mistakes==5)
            cout<<"HINT:"<<hint<<endl;
        cout<<"</menu/hangman/>";
        
        cin>>citit;
        if(citit>='a' && citit<='z')
            citit-=dif;
        else if(citit>='A' && citit<='Z')
            citit=citit;
        else
            goto back;
}

void logic(char* word, char citit, char* save, char* alph, int& indexLitera, int& mistakes){
    int pozitie=strpoz(word, citit); 
    if(pozitie!=-1){ 
        save[pozitie]=word[pozitie];
        
        indexLitera=4;
    } else {
        indexLitera=2;
        mistakes++;    
    }
    alph[strpoz(alph,citit)]='-';
}



