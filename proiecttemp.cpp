#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <fstream>



using namespace std;
void start();
void color();
void TicTacToe();
void hangmanOLD();
void hangman();
void wordRandomize(char randomWord[], char randomSave[], char randomHint[]);
int strpoz(char* str, char lit);
void snake();
void snakeSetup();
void snakeDraw();
void snakeInput();
void snakeLogic();
void pongStartup();
int stop();
void startConsole();
void startHangman();
void exitProgram();


int main()
{
    start();
    return 0;
}



void start(){
    system("CLS");
    menu:
    cout<<"> List of commands:" << endl;
    cout<<"> 1. 'color' "<< endl;
    cout<<"> 2. 'tictactoe' "<< endl;
    cout<<"> 3. 'hangman' "<< endl;
    cout<<"> 4. 'snake' " << endl;
    cout<<"> 5. 'pong' " << endl;
    cout<<"> 6. 'exit' " << endl << endl;
    cout<<"Write the name of a command:"<<endl;
    char text[256];
    int n=1000;
    for(int i=0; i<n; i++){
        cout<<"</menu/> ";
        cin>>text;
        if(strcmp(text, "color")==0)
            color();
        else if(strcmp(text, "tictactoe")==0)
            TicTacToe();
        else if(strcmp(text, "hangman")==0)
            hangman();
        else if(strcmp(text, "snake")==0)
            snake();
        else if(strcmp(text, "pong")==0)
            pongStartup();
        else if(strcmp(text, "exit")==0)
            exitProgram();
    }
    goto menu;
}
void color(){
    system("CLS");
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "> Select your text color" << endl;
    
    for(int k = 1; k < 16; k++)
    {
        SetConsoleTextAttribute(Console, k);
        cout << k <<" TEXT" << endl;
    }

    cout<<"</menu/color/>";
    int selected;
    cin>>selected;
    SetConsoleTextAttribute(Console, selected);
    cout<< "> Text color " << selected << " has been selected" << endl << endl;
    cout<< "> Select your background color" << endl << endl;

    int nr=1;
    for(int k = selected; k < 256; k+=16)
    {
        SetConsoleTextAttribute(Console, k);

        cout << nr <<" BACKGROUND" << endl;
        nr++;
    }

    cout<<"</menu/color/>";
    cin>>selected;
    int backgroundColor;
    backgroundColor=(selected-1)*16+selected;
    SetConsoleTextAttribute(Console, backgroundColor);
    cout<< "> Background color " << selected << " has been selected" << endl << endl;
    start();

}
void exitProgram(){
    system("CLS");
    char text[256];
    int n=1000;
    for(int i=0; i<n; i++){
        cout<<"Write STOP to terminate the program. If you'd like to go back to the menu write MENU."<<endl;
        cout<<"</menu/exit/> ";
        cin>>text;
        if(strcmp(text, "MENU")==0){
            startConsole();
            start();
        }
        if(strcmp(text, "STOP")==0)
            exit(1);
    } 
}
bool snakeEnd;
const int width=36;
const int height=16;
int x;
int y;
int foodX;
int foodY;
int score;
int length;
int tailX[100];
int tailY[100];
int tail;

enum direction {STOP=0, LEFT, RIGHT, UP, DOWN};
direction dir;

void snakeSetup()
{

    snakeEnd=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    foodX=rand() % width;
    foodY=rand() % height;
    score=0;
    length=1;

}
void snakeDraw()
{

    system("cls");
    for(int i=0; i<width+2; i++)
        cout<<"X";
    cout<<endl;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(j==0)
                cout<<"X";
            if(i==y && j==x)
                cout<<"O";
            else if(i==foodY && j==foodX)
                cout<<"+";
            else
            {
                bool print=false;
                for(int k=0; k<tail; k++)
                {
                    
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                    cout<<" ";

            }
            if(j==width-1)
                cout<<"X";
        }
        cout<<endl;
    }

    for(int i=0; i<width+2; i++)
        cout<<"X";
    cout<<endl;
    cout<<endl<<"Score: "<<score<<endl;
    cout<<endl<<"Snake length: "<<length<<endl;
    cout<<endl<<"Press 1 to go to MENU"<<endl;
}

void snakeInput()
{
    if(_kbhit())
    {
        switch (_getch())
        {
            case 'w':
                dir=UP;
                break;
            case 'a':
                dir=LEFT;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'd':
                dir=RIGHT;
                break;
            case '1':
                start();
        }
    }
}

void snakeLogic()
{
    int prevX =tailX[0];
    int prevY =tailY[0];
    int prev2X;
    int prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1; i<tail; i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;

    }
    switch(dir)
    {
        case UP:
            y--;
            break;
        case LEFT:
            x--;
            break;
        case DOWN:
            y++;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }

    if(x>=width)
        x=0;
    else if(x<0)
        x=width-1;

    if(y>=height)
        y=0;
    else if(y<0)
        y=height-1;

    for(int i=0; i<tail; i++)
        if(tailX[i]==x && tailY[i]==y)
            snakeEnd=true;
    if(x==foodX && y==foodY)
    {
        tail++;
        score+=10;
        length++;
        foodX=rand() % width;
        foodY=rand() % height;
    }
}

void snake()
{
    snakeSetup();
    while(!snakeEnd)
    {
        snakeDraw();
        snakeInput();
        snakeLogic();
        Sleep(20);

    }
}


void TicTacToe()
{
    system("CLS");
    cout<<endl;
    cout<<"Player 1: 1    &    Player 2: 2"<<endl<<endl;
    cout<<"Positions: "<<endl<<endl;
    int pos=1;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cout<<pos<<' '; 
            pos++;
        }
        cout<<endl;
    }

    const int n = 3;
    int matrice[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrice[i][j] = 0;
        }
    }

    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int win=-1;
    for (int k = 0; k < 50 && win == -1; k++)
    {
        int simbol;

        if (k % 2 == 0)
        {
            simbol = 1;  
            cout << endl;
            cout<<"Player 1's turn"<<endl;
        }
        else
        {
            simbol = 2; 
            cout << endl;
            cout<<"Player 2's turn"<<endl;
        }
        cout << endl;
        cout<<"</menu/tictactoe/>";
        int location;
        cin >> location;
        
        switch (location)
        {
        case 1:
            if(matrice[0][0]==0)
                matrice[0][0] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        case 2:
            if(matrice[0][1]==0)
                matrice[0][1] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        case 3:
            if(matrice[0][2]==0)
                matrice[0][2] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        case 4:
            if(matrice[1][0]==0)
                matrice[1][0] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        case 5:
            if(matrice[1][1]==0)
                matrice[1][1] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        case 6:
            if(matrice[1][2]==0)
                matrice[1][2] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        case 7:
            if(matrice[2][0]==0)
                matrice[2][0] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        case 8:
            if(matrice[2][1]==0)
                matrice[2][1] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        case 9:
            if(matrice[2][2]==0)
                matrice[2][2] = simbol;
            else{
                cout<<endl<<"Unavailable location. Pick another one"<<endl;
                k--;
            }
            break;

        }

        cout << endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << matrice[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        string winLine="";

        if(matrice[0][0] != 0 && matrice[0][0]==matrice[0][1] && matrice[0][1]==matrice[0][2]) 
        {
            win=matrice[0][0];
            winLine+="first horizontal row";
        }
        else if(matrice[1][0] != 0 && matrice[1][0]==matrice[1][1] && matrice[1][1]==matrice[1][2]) 
        {
            win=matrice[1][0];
            winLine+="middle horizontal row";
        }
        else if(matrice[2][0] != 0 && matrice[2][0]==matrice[2][1] && matrice[2][1]==matrice[2][2])  
        {
            win=matrice[2][0];
            winLine+="last horizontal row";
        }
        else if(matrice[0][0] != 0 && matrice[0][0]==matrice[1][0] && matrice[1][0]==matrice[2][0]) 
        {
            win=matrice[0][0];
            winLine+="first vertical row";
        }
        else if(matrice[0][1] != 0 && matrice[0][1]==matrice[1][1] && matrice[1][1]==matrice[2][1])
        {
            win=matrice[0][1];
            winLine+="middle vertical row";
        }
        else if(matrice[0][2] != 0 && matrice[0][2]==matrice[1][2] && matrice[1][2]==matrice[2][2]) 
        {
            win=matrice[0][2];
            winLine+="last vertical row";
        }
        else if(matrice[0][0] != 0 && matrice[0][0]==matrice[1][1] && matrice[1][1]==matrice[2][2]) //diag principala
        {
            win=matrice[0][0];
            winLine+="principal diagonal";
        }
        else if(matrice[0][2] != 0 && matrice[0][2]==matrice[1][1] && matrice[1][1]==matrice[2][0]) //diag secundara
        {
            win=matrice[0][2];
            winLine+="secondary diagonal";
        }
        
        if(win!=-1){
            cout<<"Player "<<win<<" has won the game completing the "<<winLine<<" !"<<endl;
            cout<<"Write AGAIN to play again or MENU to go back to the menu." << endl << endl;
            cout<<endl;
            char text[256];
            int n=1000;
            for(int i=0; i<n; i++){
                cout<<"</menu/tictactoe/> ";
                cin>>text;
                if(strcmp(text, "AGAIN")==0)
                    hangman();
                if(strcmp(text, "MENU")==0){
                    startConsole();
                    start();
                }
            }
        }
    }
    if(win == -1){
        cout<<"Draw - None of the players has won."<<endl;
        cout<<endl;
        cout<<"Write AGAIN to play again or MENU to go back to the menu." << endl << endl;
        cout<<endl;
        char text[256];
        int n=1000;
        for(int i=0; i<n; i++){
            cout<<"</menu/tictactoe/> ";
            cin>>text;
            if(strcmp(text, "AGAIN")==0)
                hangman();
            if(strcmp(text, "MENU")==0){
                startConsole();
                start();
            }
        }
    }

}

void wordRandomizeOLD(string &randomWord, string &randomSave, string &randomHint)
{
    int generator;
    srand((unsigned) time(0));
    generator = rand() % 20 + 1;
  
    switch(generator){
        case 1:
        {
            randomWord = "M A R I O";
            randomSave = "M _ _ _ O";
            randomHint = "Character in 2D game";
            break;
        }
        case 2:
        {
            randomWord = "A B S U R D";
            randomSave = "A _ _ _ _ D";
            randomHint = "Synonym of 'illogical' ";
            break;
        }
        case 3:
        {
            randomWord = "M O U S E P A D";
            randomSave = "M _ _ _ _ _ _ D";
            randomHint = "PC peripheral";
            break;
        }
        case 4:
        {
            randomWord = "S U B W A Y";
            randomSave = "S _ _ _ _ Y";
            randomHint = "An underground tunnel... or a famous fast food chain";
            break;
        }
        case 5:
        {
            randomWord = "B A N J O";
            randomSave = "B _ _ _ O";
            randomHint = "A stringed musical instrument";
            break;
        }
        case 6:
        {
            randomWord = "B E A C H";
            randomSave = "B _ _ _ H";
            randomHint = "Coast of a sea/ocean";
            break;
        }
        case 7:
        {   
            randomWord = "G R A P H";
            randomSave = "G _ _ _ H";
            randomHint = "Diagram that shows multiple variables";
            break;
        }
        case 8:
        {
            randomWord = "C R Y S T A L";
            randomSave = "C _ _ _ _ _ L";
            randomHint = "Clear, transparent and beautiful rock";
            break;
        }
        case 9:
        {
            randomWord = "L U C K Y";
            randomSave = "L _ _ _ Y";
            randomHint = "Fortune";
            break;
        }
        case 10:
        {
            randomWord = "K E T C H U P";
            randomSave = "K _ _ _ _ _ P";
            randomHint = "Sauce made from tomatoes";
            break;
        }
        case 11:
        {
            randomWord = "Z O M B I E";
            randomSave = "Z _ _ _ _ E";
            randomHint = "Dead character whose corpse was revived (movies / video games)";
            break;
        }
        case 12:
        {
            randomWord = "Z E B R A";
            randomSave = "Z _ _ _ A";
            randomHint = "African animal with black and white stripes";
            break;
        }
        case 13:
        {
            randomWord = "T I G E R";
            randomSave = "T _ _ _ R";
            randomHint = "Large wild animal with orange fur and black stripes";
            break;
        }
        case 14:
        {
            randomWord = "K E Y B O A R D";
            randomSave = "K _ _ _ _ _ _ D";
            randomHint = "PC Peripheral";
            break;
        }
        case 15:
        {
            randomWord = "D R A W E R";
            randomSave = "D _ _ _ _ R";
            randomHint = "Furniture meant to storage clothes";
            break;
        }
        case 16:
        {
            randomWord = "R A M E N";
            randomSave = "R _ _ _ N";
            randomHint = "Japanese soup with noodles";
            break;
        }
        case 17:
        {
            randomWord = "F R A N C E";
            randomSave = "F _ _ _ _ E";
            randomHint = "Country in West Europe";
            break;
        }
        case 18:
        {
            randomWord = "J O Y S T I C K";
            randomSave = "J _ _ _ _ _ _ K";
            randomHint = "Device meant to control devices such as a computer";
            break;
        }
        case 19:
        {
            randomWord = "M A C H I N E";
            randomSave = "M _ _ _ _ _ E";
            randomHint = "System that uses power and has several parts and structures";
            break;
        }
        case 20:
        {
            randomWord = "W A T E R";
            randomSave = "W _ _ _ R";
            randomHint = "Essential substance for life";
            break;
        }

    }
}

void hangmanOLD()
{
    string alph = "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
    string word;
    string save;
    string hint;
    // wordRandomize(word,save,hint);


    cout << endl;
    cout << "Available letters: " << endl << endl;
    cout << alph << endl << endl;

    int length = word.size();

    cout << "Your word is: " << endl << endl;
    cout << save << endl << endl;

    char a;
    int mistakes = 0;

    bool wordWasGuessed = false;

    char text[256];
    int n=1000;
    char comandaMENU[5] = {'M' , 'E' , 'N' , 'U' , '\0'};
    char comandaAGAIN[6] = {'A', 'G', 'A', 'I', 'N', '\0'};

    for (int i = 0; mistakes != 5 && wordWasGuessed == false; i++)
    {
        cin >> a;

        size_t found = word.find(a);
        if (found != string::npos) // GUESSED
        {
            cout << endl << a << " was one of the letters!" << endl << endl;
            for (int i = 0; i <= length; i++)
            {
                if (i > 0 && i < length - 1 && word.at(i) != word.at(1))
                {
                    if (word.at(i) == word.at(found)) 
                    {
                        string aux = "";
                        aux+=a;
                        save.replace(found, 1, aux);
                        cout << endl << save << endl;
                    } 
                }
                if(word==save)
                {
                    wordWasGuessed = true;
                    break;
                }
            }
        }
        else // NOT GUESSED
        {
            cout << "The word does not contain " << a << endl << endl;
            
            cout << save << endl;

            mistakes++;
            if (mistakes == 4){

                cout<< endl << endl << "You have 1 try left." << endl << endl << endl;
                cout << "Your hint is: " << endl << hint << endl;
            }
            else{
                cout << endl << endl << "You have " << 5 - mistakes << " tries left." << endl << endl;
            }
        }
        replace(alph.begin(), alph.end(), a, ' ');
        cout << endl;
        cout << "Available letters: " << endl;
        cout << alph << endl << endl;
    }
    if(wordWasGuessed){
        cout<<endl<<"You have guessed the word "<<word<<" ! Game over." << endl << endl;
        cout<<"Write AGAIN to play again or MENU to go back to the menu." << endl << endl;
        for(int i=0; i<n; i++)
        {
            cout<<"> ";
            cin>>text;
            if(strcmp(text, comandaAGAIN)==0)
                hangman();
            if(strcmp(text, comandaMENU)==0)
                start();
        }
    }
    else
    { 
        cout<<endl<<"You did not guess the word. Write AGAIN to try again for another word or MENU to go back to the menu." << endl;


        for(int i=0; i<n; i++)
        {
            cout<<"> ";
            cin>>text;
            if(strcmp(text, comandaAGAIN)==0)
                hangman();
            if(strcmp(text, comandaMENU)==0)
                start();
        } 
    }   
}

void startHangman(){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   
    cfi.dwFontSize.Y = 28;                  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); 
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd,SW_SHOWMAXIMIZED);
}

void wordRandomize(char randomWord[], char randomSave[], char randomHint[]){
    int generator;
    srand((unsigned) time(0));
    generator = rand() % 20 + 1;
    char* words[20]={"MARIO", "ABSURD", "MOUSEPAD", "SUBWAY", "BANJO", "BEACH", "GRAPH", "CRYSTAL", "LUCKY", "KETCHUP", "ZOMBIE", "ZEBRA", "TIGER", "KEYBOARD", "DRAWER", "RAMEN", "FRANCE", "JOYSTICK", "MACHINE", "WATER"};
    char* saves[20]={"M___O", "A____D", "M______D", "S____Y", "B___O", "B___H", "G___H", "C_____L", "L___Y", "K_____P", "Z____E", "Z___A", "T___R", "K______D", "D____R", "R___N", "F____E", "J______K", "M_____E", "W___R"};
    char* hints[20]={"Character in 2D game", "Synonym of 'illogical' ", "PC peripheral", "An underground tunnel... or a famous fast food chain", "A stringed musical instrument", "Coast of a sea/ocean", "Diagram that shows multiple variables", "Clear, transparent and beautiful rock", "Fortunate", "Tomato sauce", "Dead character whose corpse was revived (movies / video games)", "African animal with black and white stripes", "Large wild animal with orange fur and black stripes", "PC Peripheral", "Furniture meant to storage clothes", "Japanese soup with noodles", "Country in West Europe", "Device meant to control devices such as a computer", "System that uses power and has several parts and structures", "Essential substance for life"};
    strcpy(randomWord, words[generator-1]);
    strcpy(randomSave, saves[generator-1]);
    strcpy(randomHint, hints[generator-1]);
}

void hangman(){
    // system("CLS");
    startHangman();
    int n=43;
    int m=95;
    char matrice[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i==0 || i==n-1 || j==0 || j==m-1)
                matrice[i][j]='#';
            else
                matrice[i][j]=' ';
        }
    }
    char word[256];
    char save[256];
    char hint[256];
    wordRandomize(word, save, hint);
    ifstream reader("mistakes.txt");
    int p=7;
    int q=36;
    int r=51;
    char drawing[p][q][r];
    for(int k=0; k<p; k++)
        for(int i=0; i<q; i++)
            for(int j=0; j<r; j++){
                char nr;
                reader>>nr;
                if(nr=='.'){
                    nr=' ';
                    drawing[k][i][j]=nr;
                }
                else
                    drawing[k][i][j]=nr;   
            }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            if(i!=0 && i!=n-1)
                matrice[i][m/3]='|';
    }
    char sent1[]="Available letters";
    char sent2[]="Your word is";
    char alph[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphLength=strlen(alph);
    int k=0;

    for(int j=7; j<25-1; j++){
        matrice[8][j]=sent1[k];
        k++;
    }
    k=0;
    for(int j=3; j<30-1; j++){
        matrice[12][j]=alph[k];
        k++;
    }
    k=0;
    for(int j=9; j<22-1; j++){
        matrice[16][j]=sent2[k];
        k++;
    }
    k=0;
    for(int j=12; j<13+strlen(word)-1; j++){
        matrice[19][j]=save[k];
        k++;
    }

    for(int i=0; i<q; i++)
        for(int j=0; j<r; j++){
            matrice[i+3][j+37]=drawing[0][i][j];
        }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
           cout<<matrice[i][j]<<" ";
        cout<<endl;
    }        
    

    bool guessed=false;
    int mistakes=0;
    char affirmative[]=" was one of the letters!";
    char negative[]=" was not one of the letters";

    int dif='a'-'A';
    while(!guessed && mistakes<6){
        back:
        cout<<endl<<"Please introduce a valid letter: "<<endl;
        if(mistakes==5)
            cout<<"HINT:"<<hint<<endl;
        cout<<"</menu/hangman/>";
        char citit;
        cin>>citit;
        k=0;
        if(citit>='a' && citit<='z')
            citit-=dif;
        else if(citit>='A' && citit<='Z')
            citit=citit;
        else
            goto back;
        k=0;

        int pozitie=strpoz(word, citit);
        if(strchr(word, citit)!=NULL){ 
            system("CLS");
            matrice[22][4]=citit;
            for(int j=5; j<30-1; j++){
                matrice[22][j]=affirmative[k];
                k++;
            }
            save[pozitie]=word[pozitie];
            int alphPoz=strpoz(alph,citit);
            alph[alphPoz]='/'; 

            k=0;
            for(int j=12; j<13+strlen(word)-1; j++){
                matrice[19][j]=save[k];
                k++;
            }
            k=0;
            for(int j=3; j<30-1; j++){
                matrice[12][j]=alph[k];
                k++;
            }
            // system("CLS");
            for(int i=0; i<q; i++)
                for(int j=0; j<r; j++){
                matrice[i+3][j+37]=drawing[mistakes][i][j];
            }
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++)
                    cout<<matrice[i][j]<<" ";
                cout<<endl;
            } 
        }
        if(strchr(word, citit)==NULL){
            system("CLS");
            k=0;
            matrice[22][2]=citit;
            for(int j=3; j<30; j++){
                matrice[22][j]=negative[k];
                k++;
            }
            int alphPoz=strpoz(alph,citit);
            alph[alphPoz]='/';
            k=0;
            for(int j=3; j<30-1; j++){
                matrice[12][j]=alph[k];
                k++;
            } 
            mistakes++;
            for(int i=0; i<q; i++)
                for(int j=0; j<r; j++){
                matrice[i+3][j+37]=drawing[mistakes][i][j];
            }
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++)
                    cout<<matrice[i][j]<<" ";
                cout<<endl;
            }
        }
        if(strchr(save, '_')==NULL){
            cout<<endl<<"You have guessed the word "<<word<<" ! Game over." << endl << endl;
            cout<<"Write AGAIN to play again or MENU to go back to the menu." << endl << endl;
            guessed=true;
            char text[256];
            int n=1000;
            for(int i=0; i<n; i++){
                cout<<"</menu/hangman/> ";
                cin>>text;
                if(strcmp(text, "AGAIN")==0)
                    hangman();
                if(strcmp(text, "MENU")==0){
                    startConsole();
                    start();
                }
            }
        }
        
    
        if(mistakes==6){
                cout<<endl<<"You did not guess the word "<<word<<". Game over." << endl << endl;
                cout<<"Write AGAIN to play again or MENU to go back to the menu." << endl << endl;
                char text[256];
                int n=1000;
                for(int i=0; i<n; i++)
                {
                    cout<<"</menu/hangman/> ";
                    cin>>text;
                    if(strcmp(text, "AGAIN")==0)
                        hangman();
                    if(strcmp(text, "MENU")==0){
                        startConsole();
                        start();
                    }
                }
            }
    }
}

int strpoz(char* str, char lit){
    for(int i=0; i<strlen(str); i++)
        if(str[i]==lit)
            return i;
    return -1;
}

void pongStartup(){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   
    cfi.dwFontSize.Y = 34;                  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); 
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    HWND hwnd = GetConsoleWindow();
    hwnd != NULL;
    MoveWindow(hwnd ,900,200 ,800,1000 ,TRUE);
    start();
    
}

void startConsole(){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   
    cfi.dwFontSize.Y = 32;                  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); 
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd,SW_SHOWMAXIMIZED);
}


