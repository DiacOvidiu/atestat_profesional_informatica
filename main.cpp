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

struct tunsoare
{
    int cod;//codul tunsorii
    int marime;//numarul tunsorii
    char culoare[15];//culoarea tunsorii
    int s;//pentru ce sex e facut tunsorea
    char categorie[31];//tipul tunsorii
};

struct clienti
{
    int numar;//numarul clientului
    int cod;//codul clientului
    char nume[15];//numele clientului
    int varsta;//varsta clientului
    int mascfen;//sexul(feminin/masculin)
};

clienti r[100];
tunsoare g[100];
int ncp;
/*
void stergeret(tunsoare v[],int &n,int x) //stergere tunsoare
{
    int i,j;
    for(i=0;i<n;i++)
        if(v[i].cod==x)
            break;
    if(i==n+1)
        cout<<"Nu am ce sa sterg !";
    else
        for(j=i;j<n-1;j++)
            v[j]=v[j+1];
    n--;
    cout<<"Tunsoarea a fost stearsa cu SUCCES !";
}
*/
NOD o[100];
NOD N[100];

void desen_nod(NOD N,int c1,int c2)
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

void citirenr(int &nrt,int nr,int x,int y,int ct,int cbt)
{
    char lit,t[1000];
    setcolor(ct);
    setbkcolor(cbt);
    int l=1;
    t[0]='-';
    t[l]='\0';
    do
    {
        settextstyle(6,0,3);outtextxy(x,y,t);
        lit=getch();
        if(isdigit(lit) && lit!=8 && lit!=13 && l<nr)
        {
            t[l-1]=lit;
            t[l]='-';
            t[l+1]='\0';
            l++;
        }
        else
            if(lit==8 && l>1)
            {
                setcolor(cbt);outtextxy(x,y,t);
                t[l-2]=t[l-1];
                t[l-1]='\0';
                l--;
                setcolor(ct);outtextxy(x,y,t);
            }
    }
    while(lit!=13);
    nrt=atoi(t);
    setcolor(cbt);outtextxy(x,y,t);
    t[l-1]='\0';
    setcolor(ct);outtextxy(x,y,t);
}

void desenare_noduri_toate(NOD N[] , int n)
{
    for(int i=1; i<=n ;i++)
    {
        desen_nod(N[i],BLACK,WHITE);
        delay(100);

    }
}

void desen_muchie2(int ni , int nf,int cl)
{
    char s[10];
//    char t[10];
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
//    char s[10];
 //   char t[10];
    setcolor(cl);
    setlinestyle(1,1,5);
    line(o[ni].x , o[ni].y , o[nf].x , o[nf].y);
    desen_nod(o[ni],cl,WHITE);
    desen_nod(o[nf],cl,WHITE);
}

void desen_graf()
{
    desenare_noduri_toate(o,n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n ;j++)
            if(ma[i][j]!=0)
            {
                desen_muchie2(i,j,BLACK);
                delay(100);
            }
}

void cit(char nf[],tunsoare v[],int &n)
{
    ifstream f(nf);
    int i;
    f>>n;
    for(i=0;i<n;i++)
    {
        f>>v[i].cod;
        f>>v[i].marime;
        f.get();
        f>>v[i].culoare;
        f.get();
        f>>v[i].s;
        f.get();
        f>>v[i].categorie;
    }
    f.close();
}

void salvarea()
{
    ofstream ou("date.in");
    ou<<n<<" "<<m<<endl;
    ou<<endl;
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            if(ma[i][j]!=0)
                ou<<i<<" "<<j<<" "<<ma[i][j]<<endl;
    ou.close();
}

void salvare1(int &en)
{
    int i;
    for(i=1;i<=n;i++,cout<<'\n')
    {
        cout<<o[i].x<<' '<<o[i].y<<'\n'<<o[i].num;
    }
}

void citire_o(int k)
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

void citire_or(int k)
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
/*
void afisare()
{
    initwindow(getmaxwidth(),getmaxheight(),"Tunsori");
    for(int i=1;i<=n;i++)
    {
        //outtextxy()<<o[i].r<<'.';
        cout<<o[i].r<<'.';
        cout<<o[i].num<<endl;
        cout<<endl;
    }
}
*/
void citire()
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

int minim()
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
   // v[np]=1;
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
    //s=0;
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
                //desen_nod(o[ve[i]],LIGHTBLUE,WHITE);
                delay(500);
            }
        }
       // desen_nod(o[ve[1]],LIGHTBLUE,WHITE);
}

int unde(int x ,int y)
{
    for(int i=1;i<=n;i++)
        if(x>o[i].x-14 && x<o[i].x+14 && y>o[i].y-14 && y<o[i].y+14 )
            return i;
}

void afisare(tunsoare v[],int n)
{
    initwindow(getmaxwidth(),getmaxheight(),"AFAFGA");
    cleardevice();
    int i;
    char j[16];
    char k[100];
    //cout<<n<<" modele de tunsori:"<<'\n';

    for(i=0;i<n;i++)
    {
        strcpy(k,"Tunsoarea cu numarul ");
        itoa(i+1,j,10);
        strcat(k,j);
        outtextxy(0,i*100,k);
        j[0]='\0';
        outtextxy(50,i*10+5,j); //Tunsoarea cu numarul x
        /*cout<<"Codul tunsorii: "<<v[i].cod<<'\n'; //codul tunsorii
        cout<<"Numarul paginii(catalog): "<<v[i].marime<<'\n'; //numarul paginii din catalog
        cout<<"Culoarea parului: "<<v[i].culoare<<'\n'; //culoarea parului
        if(v[i].s==0)
        cout<<"Sexul: "<<"Barbat"<<'\n'; //sex masculin
        else
        if(v[i].s==1)
            cout<<"Sexul: "<<"Femeie"<<'\n'; //sex feminin
        cout<<"Anotimp preferabil: "<<v[i].categorie<<'\n'<<endl; */
    }
    while(!kbhit());
}

void adaugare(tunsoare v[],int &n)
{
    cleardevice();
    outtextxy(380,15,"=> ADAUGAREA UNEI NOI TUNSORI \n <=");
    //citirenr(nrt,nr,x,y,ct,cbt);
    outtextxy(100,200,"- Codul tunsorii:\n \n ");
    outtextxy(100,300,"- Codul paginii : (din catalog) \n ");
    outtextxy(100,400,"- Culoarea parului:\n \n ");
    outtextxy(100,500,"- Sexul pentru care este tunsoarea-0=BARBAT,1=FEMEIE:\n ");
    outtextxy(100,600,"- Categoria tunsorii(de ex. iarna/vara):\n ");
    //cout<<"Codul tunsorii:\n";
    cin>>v[n].cod;
    //cout<<"Codul paginii : (din catalog)\n";
    cin>>v[n].marime;
    //cout<<"Culoarea parului:\n";
    cin.get();
    cin.get(v[n].culoare,15);
   // cout<<"Sexul pentru care este tunsoarea-0=BARBAT,1=FEMEIE:\n";
    cin>>v[n].s;
   // cout<<"Categoria tunsorii(de ex. iarna/vara):\n";
    cin.get();
    cin.get(v[n].categorie,31);
    n++;
}

void modificare(tunsoare v[],int &n,int x)
{
    int i;
    for(i=0;i<n;i++)
        if(v[i].cod==x)
            break;
    if(i==n)
        cout<<"Nu exista codul introdus ! ";
    else
    {
        cout<<"Vechiul cod este: "<<v[i].cod<<endl;
        cout<<"Introdu noul cod: ";cin>>v[i].cod;
    }
}

void salvare3(char nf[],tunsoare v[],int n)
{
    ofstream out(nf);
    int i;
    out<<n<<'\n';
    for(i=0;i<n;i++)
    {
        out<<v[i].cod<<'\n';
        out<<v[i].marime<<'\n';
        out<<v[i].culoare<<'\n';
        if(v[i].s==0)
            out<<0<<'\n';
        else

            out<<1<<'\n';
        out<<v[i].categorie<<'\n';
    }
    out.close();
}

void drumul()
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
   // outtextxy(15,240,"Iesire");
    desenare_drum(ls);
    system("CLS");

}

int ccod()
{
    initwindow(getmaxwidth(),getmaxheight(),"Afisarea saloanelor DVO din Europa");
    setbkcolor(clbk);
    citire();
    citire_o(n);
    cleardevice();
    desen_graf();
    drumul();
    ls=0;
    lp=0;
    while(!ismouseclick(WM_LBUTTONDOWN));
    clearmouseclick(WM_LBUTTONDOWN);
}

int ccod2()
{
    initwindow(getmaxwidth(),getmaxheight(),"Afisarea saloanelor DVO din Romania");
    setbkcolor(clbk);
    citire();
    citire_or(n);
    cleardevice();
    desen_graf();
    drumul();
    ls=0;
    lp=0;
    while(!ismouseclick(WM_LBUTTONDOWN));
    clearmouseclick(WM_LBUTTONDOWN);
}

void pachetpaste() //pachetul de paste
{
    closegraph();
    initwindow(getmaxwidth(),getmaxheight(),"Pachet de PASTE - DVO Hairstyle",0,0);
    int op;
    do
    {
    cleardevice();
    readimagefile("pachetpaste.jpg",0,0,getmaxwidth(),getmaxheight());
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
    initwindow(getmaxwidth(),getmaxheight(),"Pachet de CRACIUN - DVO Hairstyle",0,0);
    int op;
    do
    {
    cleardevice();
    readimagefile("pachetcraciun.jpg",0,0,getmaxwidth(),getmaxheight());
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
    initwindow(getmaxwidth(),getmaxheight(),"Pachet de NUNTA - DVO Hairstyle",0,0);
    int op;
    do
    {
    cleardevice();
    readimagefile("pachetnunta.jpg",0,0,getmaxwidth(),getmaxheight());
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
    initwindow(getmaxwidth(),getmaxheight(),"Meniul cu tunsori - DVO Hairstyle",0,0);

    int loc,loc2,x,y,op;
    do
    {
    //setbkcolor(clbk);
    cleardevice();
    settextstyle(6,0,45);
    readimagefile("pachete.jpg",0,0,getmaxwidth(),getmaxheight());
    /*
    outtextxy(350,15,"||============MENIU TUNSORI============||");
    outtextxy(350,90,"              1.Afisarea Tunsorilor   ");
    outtextxy(350,160,"             2.Adaugarea unei tunsori      ");
    outtextxy(350,240,"             3.Modifica o tunsoare                             ");
    outtextxy(350,400,"             0.Iesire din meniu                             ");
    outtextxy(350,490,"||============Alege optiunea dorita !============||");
*/
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
 void meniu()
{
    closegraph();
    initwindow(getmaxwidth(),getmaxheight(),"DVO Hairstyle",0,0);
    int loc,loc2,x,y,op;
    do
    {
    setbkcolor(clbk);
    cleardevice();
    settextstyle(6,0,45);
    readimagefile("salon1.jpg",0,0,getmaxwidth(),getmaxheight());
    /*
    outtextxy(350,15,"||============MENIU PRINCIPAL============||");
    outtextxy(350,90,"              1.Afisarea cabinetelor din Europa   ");
    outtextxy(350,160,"             2.Afisarea cabinetelor din Romania      ");
    outtextxy(350,240,"             3.Meniul pentru Tunsori      ");
    outtextxy(350,360,"             0.Iesire/EXIT                               ");
    outtextxy(350,460,"||============Alege optiunea dorita !============||");
*/
    op=getch();
    switch(op)
    {
        case '1':ccod();break;
        case '2':ccod2();break;
        case '3':meniu2();break;
        case '0':exit(1);break;
    }
    }while(op!=4);
}
/*
        cout<<"                |============MENIU TUNSORI============|"<<endl;
        cout<<"                |1.Afisarea Tunsorilor                |\n";
        cout<<"                |2.Adaugarea unei tunsori             |\n";//
        cout<<"                |3.Stergere                           |\n";//
        cout<<"                |4.Modificare                         |\n";//
        cout<<"                |5.Cautare                            |\n";//
        cout<<"                |                                     | \n";
        //MAI MULTE COUTURI,in functie de program
        cout<<"                |0.Reveniti la meniul principal       |\n";//iesire
        cout<<"                |=====================================|"<<endl;
        cout<<"                |                                     |"<<endl;
        cout<<"               Tastati optiunea dorita: "<<' ';

*/
int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    closegraph();
    initwindow(getmaxwidth(), getmaxheight() , "D.V.O" , 0 , 0 );
    setbkcolor(clbk);
    cit("date3.in",g,n);
    salvare3("date3.in",g,n);
    /*
    citire();
    citire_o(n);
    cleardevice();
    desen_graf();
    drumul();
    */
    meniu();

    while(!ismouseclick(WM_LBUTTONDOWN));
    closegraph();
    salvarea();
    return 0;
}
