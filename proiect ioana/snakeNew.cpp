#include <iostream>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <conio.h>

void snake();
void startSnake();
void input();
using namespace std;

struct Dir{
    int x;
    int y;
};
Dir directie={0,0};
Dir UP={-1,0};
Dir DOWN={1,0};
Dir LEFT={0,-1};
Dir RIGHT={0,1};

int main(){
    snake();
    int c;
    cin>>c;
    return 0;
}

void startSnake(){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   
    cfi.dwFontSize.Y = 50;                  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); 
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd,SW_SHOWMAXIMIZED);
}

void snake(){
    startSnake();

    int n=16;
    int m=26;
    char arena[n][m];
    for(int i=0; i<n; i++){ 
        for(int j=0; j<m; j++){
            if(i==0 || i==n-1 || j==0 || j==m-1)
                arena[i][j]='#';
            else
                arena[i][j]=' ';
        }
    }
    
    arena[n/2][m/2]='O'; //start
    srand((unsigned) time(0)); //generare food
    int xFood=rand()%14+1;
    int yFood=rand()%24+1;
    arena[xFood][yFood]='+'; 
    int i;
    int j;
    i=n/2;
    j=m/2;
    bool end=false;
    while (1)
    {
        input();
        if(i==0 || i==n-1 || j==0 || j==m-1)
            break;
        else{
            if(i==0 || i==n-1 || j==0 || j==m-1){
                i+=directie.x;
                j+=directie.y;
                for(int a=0; a<n; a++){
                    for(int b=0; b<m; b++)
                        cout<<arena[a][b]<<" ";
                    cout<<endl;
                }
            }
            else{
                swap(arena[i][j],arena[i+directie.x][j+directie.y]);
                i+=directie.x;
                j+=directie.y;
                for(int a=0; a<n; a++){
                    for(int b=0; b<m; b++)
                        cout<<arena[a][b]<<" ";
                    cout<<endl;
                }
            }
        }
        system("cls");
    }
    
}

void input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
            case 'w':
                directie=UP;
                break;
            case 'a':
                directie=LEFT;
                break;
            case 's':
                directie=DOWN;
                break;
            case 'd':
                directie=RIGHT;
                break;
        }
    }
}