#include <iostream>
#include <conio.h>
#include <cstring>
#include <windows.h>
using namespace std;

int main()
{
    setup();
    while(!snakeEnd)
    {
        draw();
        input();
        logic();
        Sleep(20);

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

void setup()
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
void draw()
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
    cout<<"Score: "<<score<<endl;
    cout<<"Snake length: "<<length<<endl;
}

void input()
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
        }
    }
}

void logic()
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
