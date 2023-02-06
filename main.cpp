#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <windows.h>
#include <conio.h>
using namespace std;
// X & O code starts

char mat[3][3]={'-','-','-','-','-','-','-','-','-'};
char defaultmat[3][3]={'1','2','3','4','5','6','7','8','9'};
char player1[30],player2[30];
int i,j;
char gameOverXandO=false;
int currentPlayer=1;
int positionChosen;
char winner='-';
int positionsAvailable[10];

void DrawXandO(){
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Input(){
    char simbol;
    if(currentPlayer==1)
        simbol='X';
    else
        simbol='O';
    if(positionChosen==1)
        mat[0][0]=simbol;
    if(positionChosen==2)
        mat[0][1]=simbol;
    if(positionChosen==3)
        mat[0][2]=simbol;
    if(positionChosen==4)
        mat[1][0]=simbol;
    if(positionChosen==5)
        mat[1][1]=simbol;
    if(positionChosen==6)
        mat[1][2]=simbol;
    if(positionChosen==7)
        mat[2][0]=simbol;
    if(positionChosen==8)
        mat[2][1]=simbol;
    if(positionChosen==9)
        mat[2][2]=simbol;
    positionsAvailable[positionChosen]=1;
}

void TogglePlayer(){
    if(currentPlayer==1)
        currentPlayer=2;
    else
        currentPlayer=1;
}

void Check(){
    if(mat[0][0]==mat[1][1] && mat[1][1]==mat[2][2] && mat[2][2]!='-')
        winner=mat[1][1];
    int ok=0;
    for(i=0;i<3 && ok==0;i++){
        if(mat[i][0]==mat[i][1] && mat[i][0]==mat[i][2] && mat[i][2]!='-'){
            winner=mat[i][0];
            ok=1;
        }
    }
    ok=0;
    for(i=0;i<3 && ok==0;i++){
        if(mat[0][i]==mat[1][i] && mat[0][i]==mat[2][i] && mat[2][i]!='-'){
            winner=mat[0][i];
            ok=1;
        }
    }
    if(mat[2][0]==mat[1][1] && mat[1][1]==mat[0][2] && mat[0][2]!='-')
        winner=mat[1][1];
    if(winner!='-'){
        gameOverXandO=true;
    }
    else{
        int available=0;
        for(i=1;i<10;i++){
            if(positionsAvailable[i]==0)
                available++;
        }
        if(available==0){
            gameOverXandO=true;
            winner='-';
        }
    }
}

// X & O code ends

//snake code starts

bool gameOverSnake;

const int width=40;
const int height=20;

int x,y,fruitX,fruitY,score;
int tailX[101],tailY[101];
int nTail;
enum eDirecton{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirecton dir;

void Setup(){
    gameOverSnake=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand()%width;
    fruitY=rand()%height;
    score=0;
}

void DrawSnake(){
    system("cls");
    for(int i=0;i<width+2;i++){
        cout<<"-";
    }
    cout<<endl;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0){
                cout<<"|";
            }
            if(y==i && x==j){
                cout<<"O";
            }
            else if(i==fruitY && j==fruitX){
                cout<<"$";
            }
            else{
                bool print=false;
                for(int k=0;k<nTail;k++){
                    if(tailX[k]==j && tailY[k]==i){
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                    cout<<" ";
            }
            if(j==width-1)
                cout<<"|";
        }
        cout<<endl;
    }
    for(int i=0;i<width+2;i++){
        cout<<"-";
    }
    cout<<endl;
    cout<<"Scor:"<<score;
}

void InputSnake(){
    if(_kbhit()){
        switch(_getch()){
            case 'a':
               dir=LEFT;
               break;
            case 'd':
                dir=RIGHT;
                break;
            case 'w':
                dir=UP;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'x':
                gameOverSnake=true;
                break;
        }
    }
}

void Logic(){
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<nTail;i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x>width || x<0 || y<0 || y>height)
        gameOverSnake=true;
    for(int i=0;i<nTail;i++){
        if(tailX[i]==x && tailY[i]==y)
            gameOverSnake=true;
    }
    if(x==fruitX && y==fruitY){
        score+=1;
        fruitX=rand()%width;
        fruitY=rand()%height;
        nTail++;
    }
}

//snake code ends

//Hangman code starts

//Hangman code ends

int main(){
    cout<<"Welcome to the UNKNOWN Mini-games launcher"<<"\n";
    cout<<"This are the games that you can choose from:"<<"\n";
    cout<<"1. X & O - The easiest game"<<"\n";
    cout<<"2. Snake - The classic game"<<"\n";
    cout<<"3. Hangman - The impossible game"<<"\n";
    char name[30];
    cout<<"Enter a username:";
    cin>>name;
    cout<<"Hello there:"<<name;
    cout<<endl;
    cout<<"Choose a game to play:";
    int gamemode;
    cin>>gamemode;
    if(gamemode==1){
        cout<<"Welcome to X and O";
        cout<<endl;
        cout<<"Rules:";
        cout<<endl;
        cout<<"1.Choose a position from the example";
        cout<<endl;
        cout<<"2.You need two players to play";
        cout<<endl;
        cout<<"3.Enjoy playing";
        cout<<endl;
        cout<<"Example:";
        cout<<endl;
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                cout<<defaultmat[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"Enter a name for the first player:";
        cin>>player1;
        cout<<"Welcome "<<player1;
        cout<<endl;
        cout<<"Enter name for the second player:";
        cin>>player2;
        cout<<"Welcome "<<player2;
        cout<<endl;
        cout<<"May the best win!!!";
        cout<<endl;
        while(!gameOverXandO){
            if(currentPlayer==1)
                cout<<player1<<" ";
            else
                cout<<player2<<" ";
            cout<<"choose a position:";
            cin>>positionChosen;
            cout<<endl;
            Input();
            DrawXandO();
            TogglePlayer();
            Check();
        }
        if(winner=='X')
            cout<<"Congrats to "<<player1<<"!!!!";
        else if(winner=='O')
            cout<<"Congrats to "<<player2<<"!!!!";
        else
            cout<<"Unfortunatly it was a draw.";
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"                                                    GAME OVER";
        cout<<endl;
        cout<<"                                    Thanks for playing.For more rerun the project.";
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
    }
    if(gamemode==2){
        Setup();
        while(!gameOverSnake){
            DrawSnake();
            InputSnake();
            Logic();
            Sleep(30);
        }
        system("cls");
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"                                                    GAME OVER";
        cout<<endl;
        cout<<"                                    Thanks for playing.For more rerun the project.";
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
    }
    if(gamemode==3){
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"                                    Coming soon!";
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"                                    Thanks for playing.For more rerun the project.";
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
    }
    return 0;
}
