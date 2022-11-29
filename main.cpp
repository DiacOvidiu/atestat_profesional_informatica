//-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
#include <iostream>
#include <fstream>
#include <windows.h>
#include <graphics.h>
#include <cstring>
#include <iomanip>
#include <string.h>
#include <ctime>
#define INF 100000000;

using namespace std;
int ma[100][100] ,m , n,  d[100], v[100], t[100],x,y,z;
int clbk=RED;
int lp , ls;//locul de plecare , locul de sosire
int k;
struct NOD
{
    int x, y,r;//coordonate , rang
    char num[100];//nume
    int cb, cnr;//culoare bk , culoare numar

};

int ncp;
NOD o[100];
NOD N[100];

void desen_nod(NOD N,int c1,int c2) //functia de desenare a unui nod
{
    setfillstyle(1 ,c1);
    setcolor(c1);
    pieslice(N.x , N.y , 0 , 360 , 14 );
    char t[100];
    itoa(N.r , t , 10);
    setcolor(c2);
    setbkcolor(c1) ;
    outtextxy(N.x-textwidth(t)/2 ,N.y-textheight(t)/2 , t);setbkcolor(clbk) ;
    outtextxy(N.x-textwidth(t)/2-30 ,N.y-textheight(t)/2+25 , N.num);

}

void desenare_noduri_toate(NOD N[] , int n) //functia de desenare a tuturor nodurilor
{
    for(int i=1; i<=n ;i++) //parcurgere
    {
        desen_nod(N[i],BLACK,WHITE); //apelare functie desen nod
        delay(100); //pauza

    }
}

void desen_muchie2(int ni , int nf,int cl)
{
    char s[10];
    int k,l;
    setcolor(cl);
    setlinestyle(1,1,5);
    line(o[ni].x , o[ni].y , o[nf].x , o[nf].y);
    desen_nod(o[ni],BLACK,WHITE);
    desen_nod(o[nf],BLACK,WHITE);
    k=ma[ni][nf];
    itoa(k,s,10);
    k=o[ni].x+o[nf].x;
    l=o[ni].y+o[nf].y;
    delay(10);
    outtextxy(k/2+5,l/2+5,s);
}

void desen_muchie3(int ni , int nf,int cl)
{
    setcolor(cl);
    setlinestyle(1,1,5);
    line(o[ni].x , o[ni].y , o[nf].x , o[nf].y);
    desen_nod(o[ni],cl,WHITE);
    desen_nod(o[nf],cl,WHITE);
}

void desen_graf() //desenare graf
{
    desenare_noduri_toate(o,n); //desenarea tuturor nodurilor
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n ;j++)
            if(ma[i][j]!=0)
            {
                desen_muchie2(i,j,BLACK); //desenarea unei muchii
                delay(100);
            }
}

void citire_europa(int k) //citirea localitatiilor din Europa
{
    ifstream inn("dati.in");
    for(int i=1;i<=k;i++)
    {
        o[i].r=i;
        inn>>o[i].x>>o[i].y;
        inn>>o[i].num;
    }
    inn.close();
}

void citire_romania(int k) //citirea localitatiilor din Romania
{
    ifstream inn("ro.in");
    for(int i=1;i<=k;i++)
    {
        o[i].r=i;
        inn>>o[i].x>>o[i].y;
        inn>>o[i].num;
    }
    inn.close();
}

void citireeu()
{
    ifstream in ("date2.in");
    in>>n>>m;
    for(int i=1;i<=m;i++)
    {
        in>>x>>y>>z;//x de unde y unde z cat
        ma[x][y]=ma[y][x]=z;//de la  nodul x la nodul y exista costul z
    }
    in.close();
}

void citirer()
{
    ifstream in ("date.in");
    in>>n>>m;
    for(int i=1;i<=m;i++)
    {
        in>>x>>y>>z;//x de unde y unde z cat
        ma[x][y]=ma[y][x]=z;//de la  nodul x la nodul y exista costul z
    }
    in.close();
}

void relax(int x)
{
    for(int i=1;i<=n;i++)
        if(ma[x][i]!=0 && d[i]>d[x]+ma[x][i])
        {
            d[i]=d[x]+ma[x][i];
            t[i]=x;
        }
}

int minim() //functia de drumul cu costul cel mai mic
{
    int x=0;//presupunem ca nodul x este nodul care este cel mai aproape
    int dmin=INF;
    for(int i=1;i<=n;i++)//se parcurg toate nodurile grafului
        if(v[i]==0&&d[i]<dmin)//daca gasim un nod nevizitat si distanta pana la el e mai mica decat distanta minima propusa
        {
            dmin=d[i];
            x=i;//retinem nodul cel mai apropiat
        }
    return x;
}

void djikstra(int np)//np nod de pornire
{
    int x;
    for(int i=1;i<=n;i++)
    {
        d[i]=INF;//distanta minima initiall este infinit
        v[i]=0;
        t[i]=0;
    }
    d[np]=0;//distanta de pornire este 0
    do
    {
        x=minim();//pasul 1. depistam care este nodul cu distanta cea mai mica daca exista
        if(x!=0)//sa gasit acel nod
        {
            v[x]=1;//il vizitam
            relax(x);//pasul2. relaxam nodurile care se leaga de x
        }
    }while(x!=0);//repetam pana cand x diferit de 0
}

void desenare_drum(int nf)
{
    int ve[100], ct=0;//contor
    while(nf!=0)
    {
        ct++;
        ve[ct]=nf;
        nf=t[nf];
    }
    if(ct==1)
    {
        cout<<"Nu se poate ajunge la destinatie. ";
        exit(1);
    }
    else
        for(int i=ct ;i>=2 ;i--)
        {
            if(i!=1)
            {
                desen_muchie3(o[ve[i-1]].r,o[ve[i]].r,LIGHTBLUE) ;
                delay(500);
            }
        }
}

int unde(int x ,int y)
{
    for(int i=1;i<=n;i++)
        if(x>o[i].x-14 && x<o[i].x+14 && y>o[i].y-14 && y<o[i].y+14 )
            return i;
}

void drumul_in_km()
{
    char g[100];
    outtextxy(15,44,"Apasa pe nodul de pornire:");
    while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN,x,y);
    clearmouseclick(WM_LBUTTONDOWN);
    lp=unde(x,y);
    itoa(lp,g,10);
    outtextxy(15,59,g);
    outtextxy(15,44,"Apasa pe nodul de oprire:  ");
    while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN,x,y);
    clearmouseclick(WM_LBUTTONDOWN);
    ls=unde(x,y);
    itoa(ls,g,10);
    outtextxy(15,80,g);
    djikstra(lp);//apelarea functiei dijkstra
    desenare_drum(ls);
    system("CLS");

}

int saloane_europa()
{
    closegraph();
    initwindow(800,600,"Afisarea saloanelor DVO din Europa");
    readimagefile("hartaeu.jpg",0,0,800,600);
    setbkcolor(clbk);
    citireeu();
    citire_europa(n);
    //cleardevice();
    desen_graf();
    drumul_in_km();
    ls=0;
    lp=0;
    while(!ismouseclick(WM_LBUTTONDOWN));
    clearmouseclick(WM_LBUTTONDOWN);
}

int saloane_romania()
{
    closegraph();
    initwindow(800,600,"Afisarea saloanelor DVO din Romania");
    readimagefile("harta.jpg",0,0,800,600);
    setbkcolor(clbk);
    citirer();
    citire_romania(n);
    //cleardevice();
    desen_graf();
    drumul_in_km();
    ls=0;
    lp=0;
    while(!ismouseclick(WM_LBUTTONDOWN));
    clearmouseclick(WM_LBUTTONDOWN);
}

void pachetpaste() //pachetul de paste
{
    closegraph();
    initwindow(800,600,"Pachet de PASTE - DVO Hairstyle",0,0);
    int op;
    do
    {
    cleardevice();
    readimagefile("pachetpaste.jpg",0,0,800,600);
    op=getch();
    switch(op)
        {
            case '0':exit(1);break;
        }

    }while(op!=0);
}

void pachetcraciun() //pachetul de CRACIUN
{
    closegraph();
    initwindow(800,600,"Pachet de CRACIUN - DVO Hairstyle",0,0);
    int op;
    do
    {
    cleardevice();
    readimagefile("pachetcraciun.jpg",0,0,800,600);
    op=getch();
    switch(op)
        {
            case '0':exit(1);break;
        }

    }while(op!=0);

}

void pachetnunta() //pachetul de NUNTA
{
    closegraph();
    initwindow(800,600,"Pachet de NUNTA - DVO Hairstyle",0,0);
    int op;
    do
    {
    cleardevice();
    readimagefile("pachetnunta.jpg",0,0,800,600);
    op=getch();
    switch(op)
        {
            case '0':exit(1);break;
        }

    }while(op!=0);

}

 void meniu2() //meniu tunsori
{
    closegraph();
    initwindow(800,600,"Meniul cu tunsori - DVO Hairstyle",0,0);
    int loc,loc2,x,y,op;
    do
    {
    cleardevice();
    settextstyle(6,0,45);
    readimagefile("pachete.jpg",0,0,800,600);
    op=getch();
    switch(op)
    {
        case '1':pachetpaste();break;
        case '2':pachetcraciun();break;
        case '3':pachetnunta();break;
        case '0':exit(1);break;
    }
    }while(op!=4);

}
 void meniu_principal()
{
    closegraph();
    initwindow(800,600,"DVO Hairstyle",0,0);
    int loc,loc2,x,y,op;
    do
    {
    setbkcolor(clbk);
    cleardevice();
    settextstyle(6,0,45);
    readimagefile("salon1.jpg",0,0,800,600);
    op=getch();
    switch(op)
    {
        case '1':saloane_europa();break; // Apelare functie afisarea locatiilor din Europa
        case '2':saloane_romania();break; // Apelare functie afisarea locatiilor din Romania
        case '3':meniu2();break; // Apelare functie meniu principal
        case '0':exit(1);break; //iesire
    }
    }while(op!=4);
}

/// Functia de INTRO a proiectului ///

int intro()
{
    int kappa;
    kappa=initwindow(960,384,"");
    cleardevice();
    readimagefile("start2.jpg",0,0,960,384);
    delay(5000);
    closegraph(kappa);

}


int main()
{
    intro(); //functia de incepere a programului
    initwindow(800, 600 , "D.V.O Hairstyle" , 0 , 0 );
    meniu_principal();
    while(!ismouseclick(WM_LBUTTONDOWN));
    closegraph();
    return 0;
}
