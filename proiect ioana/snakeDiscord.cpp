#include<iostream>
#include <ctime>
#include <list>
#include <chrono>
#include <thread>

#include <stdbool.h>
#include <conio.h>
#include<cstring>

using namespace std;

struct Pozitii{
    int x;
    int y;
};

const int HEIGHT=30;
const int WIDTH=30;
const int DIM=HEIGHT*(WIDTH+1)+1;
const int DIM_COMANDA = 256;

void execute(char* comanda);
void snake();

int main(){
    char comanda[DIM_COMANDA];
    while(true){
        cout<<">";
        cin.get(comanda,DIM_COMANDA);
        cin.get();
        execute(comanda);
    }
}

void execute(char* comanda){
    if(strcmp(comanda,"exit")==0)
        exit(0);
    else if(strcmp(comanda,"clear")==0)
        system("cls");
    else if(strcmp(comanda,"snake")==0)
        snake();
    

}
void snake()
{
    srand((unsigned)time(0)); 

    char map[HEIGHT][WIDTH];
    char str[DIM];
    Pozitii sarpe={5,7};
    Pozitii food={rand() % (HEIGHT-2)+1, rand() % (WIDTH-2)+1};
    int contor=0;
    int tail=0;
    char dir;
    int k;
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            if(i==0 || i==HEIGHT-1)
                map[i][j]='-';
            else if(j==0 || j==WIDTH-1)
                map[i][j]='|';
            else
                map[i][j]=' ';
        }
    }
    char printMap[HEIGHT*(WIDTH*2+1)+1];
    printMap[HEIGHT*(WIDTH*2+1)]='\0';
    list<Pozitii*> lista;
    bool gasitSarpe;    
    int time=100;
    int score=0;
    while(true)
    {    
        this_thread::sleep_for(chrono::milliseconds(time));
        system("cls");
        k=0;
        for(int i=0;i<HEIGHT;i++){
            for(int j=0;j<WIDTH;j++){
                gasitSarpe=false;
                for(Pozitii* p:lista){
                    if(p->x==i and p->y==j){
                        gasitSarpe=true;
                        printMap[k++]='#';
                        break;
                    }
                }
                if(!gasitSarpe)
                    if(i==sarpe.x and j==sarpe.y)
                        printMap[k++]='#';
                    else if(i==food.x and j==food.y)        
                        printMap[k++]='$';
                    else
                        printMap[k++]=map[i][j];                
                printMap[k++]=' ';
            }
            printMap[k++]='\n';
        }
        cout<<printMap<<endl;
        cout<<score;
        fflush(stdout);
        if(_kbhit()){    
            dir=getch();
        }
        Pozitii old=sarpe;
        if(dir=='a')
            sarpe.y--;
        else if(dir=='d')
            sarpe.y++;
        else if(dir=='w')
            sarpe.x--;
        else if(dir=='s')
            sarpe.x++;
        if(sarpe.x==0 || sarpe.y==0 || sarpe.x==HEIGHT-1 || sarpe.y==WIDTH-1){
            cout<<"you died"<<endl;
            return;
        }
        else if(sarpe.x==food.x && sarpe.y==food.y){
            score++;
            time=max(time-1,0);
            Pozitii* p=new Pozitii;
            p->x=old.x;
            p->y=old.y;
            lista.push_back(p);
            food.x=rand() % (HEIGHT-2)+1;
            food.y=rand() % (WIDTH-2)+1;
        }
        for(Pozitii* p:lista){
            swap(p->x,old.x);
            swap(p->y,old.y);
        }
        }
    for(Pozitii* p:lista)
        delete p;
}




