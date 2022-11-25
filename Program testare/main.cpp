#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#define infinit INT_MAX
#define epsi 0.0001
#define  MAX 100
#define MAX1 20
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <math.h>
#include<bits/stdc++.h>
#include <graphics.h>
#include <cmath>
#define WIDTH 800
#define HEIGHT 600
using namespace std;
char s5[100];
char s3[100];
char s6[100];
char functii[10][10];
char alfabet[100]= {0};
int top1,top2;
const int max_stiva=100;
bool stop=0;

double v1[max_stiva];
char v2[max_stiva];

char OperatiiBinare[200]="+-*/^<>";
char OperatiiUnare[200]="scrl";
char Operatii[200]="+-*/^<>=#scrl";
struct interval
{
    double a, b;
};

struct tzona
{
    int x1;
    int x2;
    int y1;
    int y2;

};

//Leagan Dan-Adrian
int Prioritate(char c);
bool DifInf(float x);
float Logaritm(float x);
float Inmultit(float x);
float Putere(float x, float y);
float Plus(float x, float y);
float Minus(float x, float y);
float Impartit(float x, float y);
float Sinus(float x);
float Cosinus(float x);
float Radical(float x);
bool EsteNumar(char sir[MAX1]);
int capatul_functiei(int i,char s[]);
int verif_functii(int i, char s[]);
int paranteze(char s[]);
int functia_e_corecta(char s[]);
struct functie;
double ValoareFunctie(functie E, double x);
double evaluare(char s[],double valoare);
void functie_compusa(double &a, double &b, int &nr);

//Petrea Daniela
void limba(int &nr);
void meniu(int &nr);
void despre(int &nr);
void verifica(double &a,double &b,int &nr);
void citesteSir(char s[MAX],int x, int y);
void culori(double &a,double &b,int &nr, int &culoare);
void fundal(double &a,double &b,int &nr,int &culoare);
void reprezentare_grafic(double &a, double &b, tzona zona,int &y0,int &culoare,int &nr);
void traseazaAxe(tzona zona, double &a,double &b,int&y0,int &nr,int &culoare);
void deseneazainapoi();
void deseneazaminus();
void deseneazaplus();
double metoda_trapez( double (*p)(double), double a, double b, int k);

int Prioritate(char c)
{
    if(c=='(' || c==')')
        return 0;
    if(c=='+' || c=='-')
        return 1;
    if(c=='*' || c=='/')
        return 2;
    if(c=='^')
        return 3;
    if(c=='<' || c=='>')
        return 4;
    if(c=='c' || c=='s' || c=='l' || c=='e' || c=='t' || c=='a' || c=='r')
        return 5;
}

bool DifInf(float x)
{
    return fabs(infinit-fabs(x)) > infinit / 2.0;
}
float MaiMic(float x, float y)
{
    return x < y;
}

bool MaiMare(float x, float y)
{
    return x > y;
}
float Logaritm(float x)
{
    if (x<=0)
        stop=1;
    if (x>epsi && DifInf(x))
        return log(x);
    else
        return infinit;
}

float Inmultit(float x, float y)
{
    if (DifInf(x) && DifInf(y))
        return x*y;
    else
        return infinit;
}

float Putere(float x, float y)
{
    if (x==0)
        return 0;
    else if (y==0)
        return 1;
    else if (x==infinit || y==infinit)
        return infinit;
    else
        return pow(x,y);
}

float Plus(float x, float y)
{
    if (DifInf(x) && DifInf(y))
        return x+y;
    else
        return infinit;
}

float Minus(float x, float y)
{
    if (DifInf(x) && DifInf(y))
        return x-y;
    else
        return infinit;
}

float Impartit(float x, float y)
{
    if (fabs(y)>epsi)
        return x/y;
    else
        return infinit;
}

float Sinus(float x)
{
    if (DifInf(x))
        return sin(x);
    else
        return infinit;
}

float Cosinus(float x)
{
    if (DifInf(x))
        return cos(x);
    else
        return infinit;
}


float Radical(float x)
{
    if(x<0)
        stop=1;
    if(x==0)
        return 0;
    if (DifInf(x) && (x>epsi))
        return sqrt(x);
    else
        return infinit;
}

bool EsteNumar(char sir[MAX1])
{
    if(isdigit(sir[0]))
        return 1;
    else
        return 0;
}

struct functie
{
    char expresie[300];
    char vect[MAX+1][MAX1];
    int lung;
    float a,b;
    int n;
};

double ValoareFunctie(functie E, double x)
{
    int i;
    double valo,x_1,x_2;
    for (i=1; i<=max_stiva; i++)
    {
        v1[i]=0;
        v2[i]='@';
    }
    top1=0;
    top2=1;
    v2[top2]='(';
    i=0;
    while (i<=E.lung && top2>0)
    {
        i++;

        if (EsteNumar(E.vect[i]))
        {
            top1++;
            valo=atof(E.vect[i]);
            v1[top1]=valo;

        }
        else
            switch (E.vect[i][0])
            {

            case 'x':
                top1++;
                v1[top1]=x;
                break;
            case '(':
                top2++;
                v2[top2]='(';
                break;
            default:
                while ((top2>0) && !(strchr("()",v2[top2])) &&
                        Prioritate(v2[top2])>=Prioritate(E.vect[i][0]))
                {
                    if (top1>1)
                        x_1=v1[top1-1];
                    x_2=v1[top1];

                    switch (v2[top2])
                    {
                    case '<':
                        valo=MaiMic(x_1,x_2);
                        break;
                    case '>':
                        valo=MaiMare(x_1,x_2);
                        break;
                    case '+':
                        valo=Plus(x_1,x_2);
                        break;
                    case '-':
                        valo=Minus(x_1,x_2);
                        break;
                    case '*':
                        valo=Inmultit(x_1,x_2);
                        break;
                    case '/':
                        valo=Impartit(x_1,x_2);
                        break;
                    case '^':
                        valo=Putere(x_1,x_2);
                        break;
                    case 's':
                        valo=Sinus(x_2);
                        break;
                    case 'c':
                        valo=Cosinus(x_2);
                        break;
                    case 'l':
                        valo=Logaritm(x_2);
                        break;
                    case 'r':
                        valo=Radical(x_2);
                        break;
                    }
                    if (strchr(OperatiiBinare,v2[top2]))
                        top1--;
                    if (strchr(Operatii,v2[top2]))
                        v1[top1]=valo;
                    top2--;
                }
                if (top2>0)
                    if ((v2[top2]!='(') || (strcmp(E.vect[i],")")))
                    {
                        top2++;
                        v2[top2] = E.vect[i][0];
                    }
                    else
                        top2--;
            }
    }
    return v1[1];

}
int capatul_functiei(int i,char s[])
{
    int pas=0;
    int k=0;
    for(int j=1; j<=5; j++)
    {
        int ok=1;
        k=0;
        int y=i;
        while(pas<strlen(functii[j]))
        {
            if(s[y]!=functii[j][k])
            {
                ok=0;
                break;
            }
            y++;
            k++;
            pas++;
        }
        if(ok==1)
            return k-1;
    }
    return 0;
}
int verif_functii(int i, char s[])
{
    int pas=0;
    int k=0;
    for(int j=1; j<=5; j++)
    {
        int ok=1;
        k=0;
        int y=i;
        while(pas<strlen(functii[j]))
        {
            if(s[y]!=functii[j][k])
            {
                ok=0;
                break;
            }
            y++;
            k++;
            pas++;
        }
        if(ok==1&&(strlen(s)-i>=5))
            return 1;
    }
    return 0;
}
int paranteze(char s[])
{
    int pdeschise=0;
    int pinchise=0;
    for(int i=0; i<strlen(s); i++)
    {
        if(s[i]=='(')
            pdeschise++;
        if(s[i]==')')
            pinchise++;
        if(pinchise>pdeschise)
            return 0;
    }
    if(pdeschise==pinchise)
        return 1;
    else
        return 0;
}
int functia_e_corecta(char s[])
{
    char operatori[]="+-*/^";
    int nr_variabile=0;
    strcpy(functii[1],"sin");
    strcpy(functii[2],"cos");
    strcpy(functii[3],"r");
    strcpy(functii[4],"ctg");
    strcpy(functii[5],"ln");
    int ok=1;
    if(isdigit(s[0])==1||isalpha(s[0])||s[0]=='(')
        ok=ok;
    else
        return 0;
    for(int i=0; i<strlen(s)-3; i++)
    {
        ok=1;
        if(strchr(operatori,s[i])&&i+1<strlen(s))
        {
            if(s[i+1]=='(')
            {
                ok=1;
            }
            else if(isalpha(s[i+1]))
                ok=1;
            else if(isdigit(s[i+1]))
                ok=1;
            else if(verif_functii(i+1,s))
                ok=1;
            else
            {
                ok=0;
                break;
            }
        }
        if(verif_functii(i,s)==1&&i+1<=strlen(s))
        {
            if(s[i+capatul_functiei(i,s)+1]=='(')
            {
                ok=1;
                i=i+capatul_functiei(i,s)+1;
            }
            else
            {
                ok=0;
                break;
            }
        }
        if(isalpha(s[i])&&i+1<strlen(s))
        {
            if(s[i+1]==')')
                ok=1;
            else if(strchr(operatori,s[i+1]))
                ok=1;
            else if((i==(strlen(s)-3)))
                ok=1;
            else
            {
                ok=0;
                break;
            }
            if(alfabet[s[i]-'a']==0)
            {
                nr_variabile++;
                alfabet[s[i]-'a']=1;
            }
        }
        if(isdigit(s[i])&&i<strlen(s))
        {
            if(s[i+1]==')')
                ok=1;
            else if(strchr(operatori,s[i+1]))
                ok=1;
            else if(isdigit(s[i+1]))
                ok=1;
            else if((i==(strlen(s)-3)))
                ok=1;
            else
            {
                ok=0;
                break;
            }
        }
        if(s[i]=='('&&i+1<=strlen(s))
        {
            if(s[i+1]=='(')
                ok=1;
            else if(isdigit(s[i+1]))
                ok=1;
            else if(isalpha(s[i+1]))
                ok=1;
            else if(s[i+1]=='+'||s[i+1]=='-')
                ok=1;
            else
            {
                ok=0;
                break;
            }
        }

    }
    for(int i=0; i<strlen(s)-2; i++)
        if(isalpha(s[i])&&s[i]!='x')
        {
            if(s[i]=='s'&&s[i+1]=='i'&&s[i+2]=='n')
                i=i+2;
            else if(s[i]=='c'&&s[i+1]=='o'&&s[i+2]=='s')
                i=i+2;
            else if(s[i]=='l'&&s[i+1]=='n')
                i=i+1;
            else if(s[i]=='r')
                i=i;
            else
                ok=2;
        }

    if(nr_variabile>=2)
        ok=2;
    if(paranteze(s)==0)
        ok=0;

    if(ok==1)
        return 1;
    else if(ok==0)
        return 0;
    else if(ok==2)
        return 2;

}
double evaluare(char s[],double valoare)
{
    int pas=1;
    char aux[256];
    functie F;
    int ok=functia_e_corecta(s);
    ok=1;
    if(ok==1)
    {
        strcpy(F.expresie,s);
        strcat(F.expresie,")");
        strcpy(F.vect[0],"(");
        for(int i=0; i<strlen(s); i++)
        {
            int k=0;
            aux[k]=s[i];
            while((isdigit(s[i])&&isdigit(s[i+1])))
            {
                k++;
                i++;
                aux[k]=s[i];
            }
            while((isalpha(s[i])&&isalpha(s[i+1])))
            {
                k++;
                i++;
                aux[k]=s[i];
            }
            aux[k+1]=NULL;
            strcpy(F.vect[pas],aux);
            pas++;
        }
        strcpy(F.vect[strlen(s)+1],")");
        F.lung=strlen(F.expresie);
        float a=ValoareFunctie(F,valoare);
        return a;
    }
    else if(ok==0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
    return 0;
}
void functie_compusa(double &a, double &b, int &nr)
{
    bool gata=false;
    int x,y,culoare;
    settextstyle(8,0,5);
    switch(nr)
    {
    case 1:
        readimagefile("fundal1.jpg",0,0,800,600);
        settextstyle(10,0,4);
        outtextxy(30,100,"f1(x)=");
        setfillstyle( SOLID_FILL, BLACK);
        outtextxy(30,200,"f2(x)=");
        bar(150,80,500,150);
        bar(150,180,500,250);
        rectangle(150,80,500,150);
        rectangle(150,180,500,250);
        settextstyle(10,0,5);
        rectangle(250,280,550,350);
        settextstyle(8,0,5);
        break;
    case 2:
        readimagefile("fundaleng1.jpg",0,0,800,600);
        settextstyle(10,0,4);
        outtextxy(30,100,"f1(x)=");
        setfillstyle( SOLID_FILL, BLACK);
        outtextxy(30,200,"f2(x)=");
        bar(150,80,500,150);
        bar(150,180,500,250);
        rectangle(150,80,500,150);
        rectangle(150,180,500,250);
        settextstyle(10,0,5);
        rectangle(250,280,550,350);
        settextstyle(8,0,5);
        break;
    default:
        readimagefile("fundalfr1.jpg",0,0,800,600);
        settextstyle(10,0,4);
        outtextxy(30,100,"f1(x)=");
        setfillstyle( SOLID_FILL, BLACK);
        outtextxy(30,200,"f2(x)=");
        bar(150,80,500,150);
        bar(150,180,500,250);
        rectangle(150,80,500,150);
        rectangle(150,180,500,250);
        settextstyle(10,0,5);
        rectangle(250,280,550,350);
        settextstyle(8,0,5);
        break;
    }
    char s[MAX],asir[MAX],bsir[MAX];
    deseneazainapoi();
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>=5 && x<=65 && y>=5&&y<=35)
            {
                cleardevice();
                meniu(nr);
            }
            gata=true;
        }
    }
    while (!gata);
    int ok=1;
    s3[0]='(';
    int pas=1;
    citesteSir(s5,180,100);
    cout<<s5<<endl;
    for(int i=0; i<strlen(s5)-2; i++)
    {
        s3[pas]=s5[i];
        pas++;
    }
    s3[pas]=')';
    pas++;
    s3[pas]='*';
    pas++;
    s3[pas]='(';
    pas++;
    citesteSir(s5,580,100);
    for(int i=1; i<strlen(s5)-2; i++)
    {
        s3[pas]=s5[i];
        pas++;
    }
    s3[pas]=')';
    pas++;
    s3[pas]='+';
    pas++;
    s3[pas]='(';
    pas++;
    citesteSir(s5,180,200);
    cout<<s5<<endl;
    for(int i=1; i<strlen(s5)-2; i++)
    {
        s3[pas]=s5[i];
        pas++;
    }
    s3[pas]=')';
    pas++;
    s3[pas]='*';
    pas++;
    s3[pas]='(';
    pas++;
    citesteSir(s5,580,200);
    for(int i=1; i<strlen(s5)-2; i++)
    {
        s3[pas]=s5[i];
        pas++;
    }
    s3[pas]=')';
    pas++;
    s3[pas]=NULL;
    strcpy(s5,s3);
    for(int i=0; i<strlen(s5); i++)
        if(s5[i]=='/'&&s5[i+1]=='0')
        {
            switch(nr)
            {
            case 1:
                outtextxy(120,400,"Functia nu este corecta");
                break;
            case 2:
                outtextxy(120,400,"The function is incorrect");
                break;
            default:
                outtextxy(120,400,"La fonction est incorrecte");
                break;
            }
            delay(1000);
            cleardevice();
            verifica(a,b,nr);
        }
    if(ok==0)
    {
        switch(nr)
        {
        case 1:
            outtextxy(120,400,"Functia nu este corecta");
            break;
        case 2:
            outtextxy(120,400,"The function is incorrect");
            break;
        default:
            outtextxy(10,380,"La fonction est incorrecte");
            break;
        }
        delay(1000);
        cleardevice();
        verifica(a,b,nr);
    }
    else if(ok==2)
    {
        switch(nr)
        {
        case 1:
            outtextxy(70,400,"Folositi doar variabila x");
            break;
        case 2:
            outtextxy(80,400,"Use only the variable x");
            break;
        default:
            outtextxy(10,400,"Utilisez seulement la variable x");
            break;
        }
        delay(1000);
        cleardevice();
        verifica(a,b,nr);
    }
    outtextxy(220,500,"a=");
    citesteSir(asir,280,500);
    if((isdigit(asir[0])!=0)||asir[0]=='-')
    {
        a=atof(asir);
    }
    else
    {
        switch(nr)
        {
        case 1:
            outtextxy(120,400,"Functia nu este corecta");
            break;
        case 2:
            outtextxy(120,400,"The function is incorrect");
            break;
        default:
            outtextxy(10,380,"La fonction est incorrecte");
            break;
        }
        delay(1000);
        cleardevice();
        verifica(a,b,nr);
    }
    outtextxy(490,500,"b=");
    citesteSir(bsir,550,500);
    if((isdigit(bsir[0])!=0)||bsir[0]=='-')
    {
        b=atof(bsir);
    }
    else
    {
        switch(nr)
        {
        case 1:
            outtextxy(120,400,"Functia nu este corecta");
            break;
        case 2:
            outtextxy(120,400,"The function is incorrect");
            break;
        default:
            outtextxy(10,380,"La fonction est incorrecte");
            break;
        }
        delay(1000);
        cleardevice();
        verifica(a,b,nr);
    }
    if(a>b)
        swap(a,b);
    cout<<a<<" "<<b<<endl;
    gata=false;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>=5 && x<=65 && y>=5&&y<=35)
            {
                cleardevice();
                meniu(nr);
            }
            if (x>=250 && x<=550 && y>=280 && y<=350)
            {
                cleardevice();
                culori(a,b,nr,culoare);
            }
            gata=true;
        }
    }
    while (!gata);
    cleardevice();
}
double f(double x)
{

    //cout<<x<<" ";
    double rez=evaluare(s5,x);
    if(rez>=infinit)
        rez=0;
    //cout<<"rez este: "<<rez<<endl;
    return rez;

}

double metoda_trapez( double (*p)(double), double a, double b, int k)
{
    double h,integrala;
    int i;
    h=(b-a)/(k-1);
    integrala=((*p)(a)+(*p)(b))/2.0;
    for(i=2; i<=k-1; i++)
        integrala=integrala+(*p)(a+(i-1)*h);
    integrala=h*integrala; // arie_trapez=(B+b)*h/2
    return integrala;
}

void deseneazainapoi()
{
    rectangle(5,5,65,35);
    line(30,10,10,20);
    line(10,20,30,30);
    line(30,30,30,10);
    rectangle(30,15,50,25);
}
void deseneazaplus ()
{
    rectangle(725,75,765,105);
    line (735,90,755,90);
    line (745,80,745,100);
}
void deseneazaminus ()
{
    rectangle(725,25,765,55);
    line (735,40,755,40);
}
void limba(int &nr)  // fiecarei limbi ii corespunde un numar
{
    int buton;
    settextstyle(10,0,5);
    outtextxy(250, 50, "Alege limba");//Se alege limba
    readimagefile("limba1.jpg",350,120,450,220);
    readimagefile("limba2.jpg",350,250,450,350);
    readimagefile("limba3.jpg",350,380,450,480);
    bool gata=false;
    int x,y;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>=350 && x<=450)
            {
                if( y>=120&&y<=220)
                    nr=1;
                else if(y>=250&&y<=350)
                    nr=2;
                else if(y>=380&&y<=480)
                    nr=3;
            }
            gata=true;
        }
    }
    while (!gata);
    cleardevice();
    meniu(nr);
}
void meniu(int &nr) // fiecarei limbi ii corespunde un numar
{
    double a,b;
    settextstyle(10,0,5);
    int x,y,gata;
    switch(nr)
    {
    case 1:
        readimagefile("fundal.jpg",0,0,800,600);
        deseneazainapoi();
        settextstyle(10,0,4);
        break;
    case 2:
        readimagefile("fundaleng.jpg",0,0,800,600);
        deseneazainapoi();
        settextstyle(10,0,5);
        break;
    default:
        readimagefile("fundalfr.jpg",0,0,800,600);
        deseneazainapoi();
        settextstyle(10,0,4);
        break;
    }
    rectangle(250,220,550,280);
    rectangle(250,320,550,380);
    rectangle(250,420,550,480);
    settextstyle(8,0,5);
    gata=false;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>=250 && x<=550)
            {
                if (y>=220&&y<=280)
                {
                    cleardevice();
                    verifica(a,b,nr);
                }
                else if(y>=320&&y<=380)
                {
                    cleardevice();
                    despre(nr);
                }
                else if(y>=420&&y<=480)
                {
                    return;
                    closegraph();
                }
            }
            if (x>=5 && x<=65 && y>=5&&y<=35)
            {
                cleardevice();
                limba(nr);
            }
            gata=true;
        }
    }
    while (!gata);
    cleardevice();
}
void verifica(double &a,double &b,int &nr)
{
    bool gata=false;
    int x,y,culoare;
    settextstyle(8,0,5);
    switch(nr)
    {
    case 1:
        readimagefile("fundal1.jpg",0,0,800,600);
        settextstyle(10,0,4);
        outtextxy(40,100,"f(x)=");
        setfillstyle( SOLID_FILL, BLACK);
        bar(150,80,750,150);
        rectangle(150,80,750,150);
        settextstyle(10,0,5);
        rectangle(250,280,550,350);
        settextstyle(8,0,5);
        break;
    case 2:
        readimagefile("fundaleng1.jpg",0,0,800,600);
        settextstyle(10,0,4);
        outtextxy(40,100,"f(x)=");
        setfillstyle( SOLID_FILL, BLACK);
        bar(150,80,750,150);
        rectangle(150,80,750,150);
        settextstyle(10,0,5);
        rectangle(250,280,550,350);
        settextstyle(8,0,5);
        break;
    default:
        readimagefile("fundalfr1.jpg",0,0,800,600);
        settextstyle(10,0,4);
        outtextxy(40,100,"f(x)=");
        setfillstyle( SOLID_FILL, BLACK);
        bar(150,80,750,150);
        rectangle(150,80,750,150);
        settextstyle(10,0,5);
        rectangle(250,280,550,350);
        settextstyle(8,0,5);
        break;
    }
    char s[MAX],asir[MAX],bsir[MAX];
    bar(605,5,765,35);
    if(nr==1)
    {
        settextstyle(10,0,4);
        outtextxy(620,3,"compusa");
        rectangle(605,5,765,35);
        settextstyle(8,0,5);
    }
    else if(nr==2)
    {
        settextstyle(10,0,4);
        outtextxy(610,3,"composed");
        rectangle(605,5,765,35);
        settextstyle(8,0,5);
    }
    else if(nr==3)
    {
        settextstyle(10,0,4);
        outtextxy(610,3,"composée");
        rectangle(605,5,765,35);
        settextstyle(8,0,5);
    }
    deseneazainapoi();
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>=5 && x<=65 && y>=5&&y<=35)
            {
                cleardevice();
                meniu(nr);
            }
            if (x>=605 && x<=765 && y>=5&&y<=35)
            {
                cleardevice();
                functie_compusa(a,b,nr);
            }
            gata=true;
        }
    }
    while (!gata);
    citesteSir(s5,180,100);
    int ok=functia_e_corecta(s5);
    for(int i=0; i<strlen(s5); i++)
        if(s5[i]=='/'&&s5[i+1]=='0')
        {
            switch(nr)
            {
            case 1:
                outtextxy(120,400,"Functia nu este corecta");
                break;
            case 2:
                outtextxy(120,400,"The function is incorrect");
                break;
            default:
                outtextxy(120,400,"La fonction est incorrecte");
                break;
            }
            delay(1000);
            cleardevice();
            verifica(a,b,nr);
        }
    if(ok==0)
    {
        switch(nr)
        {
        case 1:
            outtextxy(120,400,"Functia nu este corecta");
            break;
        case 2:
            outtextxy(120,400,"The function is incorrect");
            break;
        default:
            outtextxy(10,380,"La fonction est incorrecte");
            break;
        }
        delay(1000);
        cleardevice();
        verifica(a,b,nr);
    }
    else if(ok==2)
    {
        switch(nr)
        {
        case 1:
            outtextxy(70,400,"Folositi doar variabila x");
            break;
        case 2:
            outtextxy(80,400,"Use only the variable x");
            break;
        default:
            outtextxy(10,400,"Utilisez seulement la variable x");
            break;
        }
        delay(1000);
        cleardevice();
        verifica(a,b,nr);
    }
    cout<<s5<<endl;
    outtextxy(220,200,"a=");
    citesteSir(asir,280,200);
    if((isdigit(asir[0])!=0)||asir[0]=='-')
    {
        a=atof(asir);
    }
    else
    {
        switch(nr)
        {
        case 1:
            outtextxy(120,400,"Functia nu este corecta");
            break;
        case 2:
            outtextxy(120,400,"The function is incorrect");
            break;
        default:
            outtextxy(10,380,"La fonction est incorrecte");
            break;
        }
        delay(1000);
        cleardevice();
        verifica(a,b,nr);
    }
    outtextxy(490,200,"b=");
    citesteSir(bsir,550,200);
    if((isdigit(bsir[0])!=0)||bsir[0]=='-')
    {
        b=atof(bsir);
    }
    else
    {
        switch(nr)
        {
        case 1:
            outtextxy(120,400,"Functia nu este corecta");
            break;
        case 2:
            outtextxy(120,400,"The function is incorrect");
            break;
        default:
            outtextxy(10,380,"La fonction est incorrecte");
            break;
        }
        delay(1000);
        cleardevice();
        verifica(a,b,nr);
    }
    if(a>b)
        swap(a,b);
    cout<<a<<" "<<b<<endl;
    gata=false;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>=5 && x<=65 && y>=5&&y<=35)
            {
                cleardevice();
                meniu(nr);
            }
            if (x>=250 && x<=550 && y>=280 && y<=350)
            {
                cleardevice();
                culori(a,b,nr,culoare);
            }
            gata=true;
        }
    }
    while (!gata);
    cleardevice();
}
void citesteSir(char s[MAX],int x, int y)
{
    strcpy(s,"");
    char s1[MAX];
    char t[2];
    char tasta;
    t[0]=tasta;
    t[1]='\0';
    strcat(s,t);
    strcpy(s1,s);
    strcat(s1,"_");
    setcolor(WHITE);
    outtextxy(x,y,s1);
    do
    {
        tasta=getch();
        if (tasta==8) // backspace
            if (strlen(s)>0)
            {
                setcolor(BLACK);
                strcpy(s1,s);
                strcat(s1,"_");
                outtextxy(x,y,s1);
                s[strlen(s)-1]='\0';
                strcpy(s1,s);
                strcat(s1,"_");
                outtextxy(x,y,s1);
                setcolor(WHITE);
                outtextxy(x,y,s1);
            }
            else
                Beep(1000,100);
        else
        {
            t[0]=tasta;
            t[1]='\0';
            strcat(s,t);
            strcpy(s1,s);
            setcolor(WHITE);
            outtextxy(x,y,s1);
        }
    }
    while (tasta!=13);
    t[0]=tasta;
    t[1]='\0';
    strcat(s,t);
    strcpy(s1,s);
    outtextxy(x,y,s1);
}
void culori(double &a,double &b,int &nr,int &culoare) //se alege culoare dorita la trasarea graficului
{
    int x,y;
    settextstyle(8,0,5);
    bool gata=false;
    switch(nr)
    {
    case 1:
        outtextxy(180,80,"Alege o culoare");
        break;
    case 2:
        outtextxy(180,80,"Choose a colour");
        break;
    default:
        outtextxy(180,80,"Choisi une couleur");
        break;
    }
    settextstyle(10,0,5);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(100,280,200,380);
    floodfill(101,290,WHITE);
    setfillstyle(SOLID_FILL,RED);
    rectangle(250,280,350,380);
    floodfill(251,290,WHITE);
    setfillstyle(SOLID_FILL,YELLOW);
    rectangle(400,280,500,380);
    floodfill(401,290,WHITE);
    setfillstyle(SOLID_FILL,MAGENTA);
    rectangle(550,280,650,380);
    floodfill(551,290,WHITE);
    deseneazainapoi();
    gata=false;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (y>=280 && y<=380)
            {
                if (x>=100 && x<=200)
                    culoare=1;
                else if (x>=250 && x<=350)
                    culoare=4;
                else if (x>=400 && x<=500 )
                    culoare=14;
                else if (x>=550 && x<=650 )
                    culoare=5;
            }
            if (x>=5 && x<=65 && y>=5&&y<=35)
            {
                cleardevice();
                verifica(a,b,nr);
            }
            gata=true;
        }
    }
    while (!gata);
    cleardevice();
    fundal(a,b,nr,culoare);
}
void fundal(double &a,double &b,int &nr,int &culoare)
{
    int y0;
    cleardevice();
    tzona zona = {58,696,464,116};
    settextstyle(6,0,1);
    setbkcolor(GREEN);
    cleardevice();
    int x=1,y=1;
    for (int r = 0; r <=29; r++)
    {
        for (int c = 1; c <= 40; c++)
        {
            setcolor(8);
            rectangle(x,y,x+29.5,y+29.5);
            x=x+29.5;
        }
        y=y+29.5;
        x=1;
    }
    reprezentare_grafic(a,b,zona,y0,culoare,nr);
    traseazaAxe(zona,a,b,y0,nr,culoare);
}
void reprezentare_grafic(double &a, double &b, tzona zona,int &y0,int &culoare,int &nr)
{
    double ymin,ymax;
    double x,y;//coordonatele din planul real
    int yev,xev; //coordonate ecran vechi
    int xe,ye,i; //xe,ye-coordonate ecran, i=contor pt. reprezentare
    int imin,imax,x0;
    //se determina ymin si ymax, parcurgand [a,b] si comparand valorile curente stabilite, cu valorile functiei in fiecare punct considerat
    ymin=f(a);
    ymax=ymin;
    for (i=0; i<=(zona.x2-zona.x1); i++)
    {
        x=a+i*(b-a)/(zona.x2-zona.x1);
        y=f(x);
        if (y>=ymax)  //actualizare y maxim
        {
            ymax=y;
            imax=x;
        }
        if (y<ymin)  //actualizare y minim
        {
            ymin=y;
            imin=x;
        }
    }
    x0 = round((b*zona.x1-a*zona.x2)/(b-a));
    y0= round((ymax*zona.y1-ymin*zona.y2)/(ymax-ymin));
    if(y0<=0)
    {
        cleardevice();
        setcolor(WHITE);
        switch(nr)
        {
        case 1:
            settextstyle(10,0,5);
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            outtextxy(200,300,"Nu se poate afisa");
            break;
        case 2:
            settextstyle(10,0,5);
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            outtextxy(200,300,"Cannot be displayed");
            break;
        default:
            settextstyle(10,0,5);
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            outtextxy(150,300,"Ne peut pas être affiché");
            break;
        }
        delay(1000);
        cleardevice();
        return;
        y0=0;
    }
    else
    {
        x = a;
        y= f(a);
        xev= round((zona.x2-zona.x1)*x/(b-a)+(b*zona.x1-a*zona.x2)/(b-a));
        yev = round((zona.y2-zona.y1)*y/(ymax-ymin)+(ymax*zona.y1-ymin*zona.y2)/(ymax-ymin));
        for( i= 0; i<=(zona.x2-zona.x1); i++)
        {
            x=a+i*(b-a)/(zona.x2-zona.x1);
            xe=round((zona.x2-zona.x1)*x/(b-a)+(b*zona.x1-a*zona.x2)/(b-a));//xe si ye vor fi rotunjite la numere intregi
            y=f(x); //determinarea valorii reale a functiei f in punctul x
            ye=round((zona.y2-zona.y1)*y/(ymax-ymin)+(ymax*zona.y1-ymin*zona.y2)/(ymax-ymin));
            setlinestyle(0, 0, 3);
            setcolor(culoare);
            if((y!=0)||(y==0&&x==0)||(f(x)!=0))
                line(xev,yev,xe,ye);
            //cout<<"linie lg"<<xev<<" "<<yev<<" "<<xe<<" "<<ye<<" "<<endl;
            setlinestyle(0, 0, 1);
            setcolor(WHITE);
            //se actualizeaza valorile vechi
            xev= xe;
            yev= ye;
        }
    }
    double integrala;
    int k=1000;
    integrala=metoda_trapez(f,a,b,k);
    char arr[100];
    switch(nr)
    {
    case 1:
        sprintf(arr, "Valoare minima a functiei este: %g  ",ymin);
        outtextxy(100,10,arr);
        sprintf(arr, "Valoare maxima a functiei este: %g  ",ymax);
        outtextxy(100,40,arr);
        sprintf(arr, "Valoarea integralei pe intervalul [a,b] este: %g  ", integrala);
        outtextxy(100,70,arr);
        break;
    case 2:
        sprintf (arr, "Minimum value of the function is: %g ", ymin);
        outtextxy (100,10, arr);
        sprintf (arr, "Maximum value of the function is: %g ", ymax);
        outtextxy (100,40, arr);
        sprintf (arr, "The value of the integral on the interval [a, b] is: %g ", integrala);
        outtextxy (100,70, arr);
        break;
    default:
        sprintf (arr, "La valeur minimale de la fonction est: %g ", ymin);
        outtextxy (100,10, arr);
        sprintf (arr, "La valeur maximale de la fonction est: %g ", ymax);
        outtextxy (100,40, arr);
        sprintf (arr, "La valeur de l'intégrale sur l'intervalle [a, b] est: %g ", integrala);
        outtextxy (100,70, arr);
        break;
    }
    sprintf(arr, "a= %g  ",a);
    outtextxy(zona.x1-3,y0+10,arr);
    sprintf(arr, "b= %g  ",b);
    outtextxy(zona.x2+2,y0+10,arr);
}
void traseazaAxe(tzona zona, double &a,double &b,int&y0,int &nr,int &culoare)
{
    if(y0>0)
    {
        setcolor(WHITE);
        rectangle(zona.x1,zona.y1,zona.x2,zona.y2);
        line(0, y0, 785, y0);
        outtextxy(785,y0, "X");
        setcolor(WHITE);
        outtextxy((-a)*(zona.x2-zona.x1)/(b-a)+zona.x1, y0-2, "O");
        outtextxy((-a)*(zona.x2-zona.x1)/(b-a)+zona.x1, zona.y2-20, "Y");
        line((-a)*(zona.x2-zona.x1)/(b-a)+zona.x1, zona.y1, (-a)*(zona.x2-zona.x1)/(b-a)+zona.x1, zona.y2);
        //cout<<"oy="<<(-a)*(zona.x2-zona.x1)/(b-a)+zona.x1<<" "<<zona.y1<<" "<<(-a)*(zona.x2-zona.x1)/(b-a)+zona.x1<<" "<<zona.y2<<endl;
        deseneazainapoi();
        deseneazaminus();
        deseneazaplus();
        int buton,tasta1,x,y;
        bool gata=false;
        int ok=1;
        do
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if (x>=5 && x<=65 && y>=5&&y<=35)
                {
                    cleardevice();
                    setbkcolor(BLACK);
                    cleardevice();
                    culori(a,b,nr,culoare);
                    gata=true;
                }
                if (x>=725 && x<=765)
                {
                    if (y>=25&&y<=55)
                        tasta1=1;
                    else if(y>=75&&y<=105)
                        tasta1=2;
                }
                do
                {
                    switch (tasta1)
                    {
                    case 1:
                        a=a-0.5;
                        b=b+0.5;
                        cleardevice();
                        if(y0==0)
                            ok=0;
                        else
                            fundal(a,b,nr,culoare);
                        break;
                    case 2:
                        a=a+0.5;
                        b=b-0.5;
                        if(a>=b)
                        {
                            cleardevice();
                            switch(nr)
                            {
                            case 1:
                                settextstyle(10,0,5);
                                settextjustify(LEFT_TEXT, CENTER_TEXT);
                                outtextxy(200,300,"Nu se poate afisa");
                                break;
                            case 2:
                                settextstyle(10,0,5);
                                settextjustify(LEFT_TEXT, CENTER_TEXT);
                                outtextxy(200,300,"Cannot be displayed");
                                break;
                            default:
                                settextstyle(10,0,5);
                                settextjustify(LEFT_TEXT, CENTER_TEXT);
                                outtextxy(150,300,"Ne peut pas être affiché");
                                break;
                            }
                            delay(1000);
                            return;
                            ok=0;
                            break;
                        }
                        cleardevice();
                        fundal(a,b,nr,culoare);
                        break;
                        closegraph();
                    }
                }
                while(ok!=1);
                if (x>=5 && x<=65 && y>=5&&y<=35)
                {
                    cleardevice();
                    setbkcolor(BLACK);
                    cleardevice();
                    culori(a,b,nr,culoare);
                }
                gata=true;
            }
        }
        while (!gata);
    }
}
void despre(int &nr)
{
    deseneazainapoi();
    bool gata=false;
    int x,y,buton;
    switch(nr)
    {
    case 1:
        settextstyle(10,0,6);
        outtextxy(290, 35, "Despre");
        settextstyle(10,0,3);
        outtextxy(20, 105, "Operatii, functii si constante disponibile: ");
        settextstyle(10,0,2);
        outtextxy(70, 135, "+ (Adunarea)");
        outtextxy(70, 165, "- (Scaderea)");
        outtextxy(70, 195, "* (Inmultirea)");
        outtextxy(70, 225, "/ (Impartirea)");
        outtextxy(70, 255, "^ (Functia putere)");
        outtextxy(70, 285, "ln() (Logaritm natural)");
        outtextxy(70, 315, "r() (Functia radical)");
        outtextxy(70, 345, "sin() (Functia sinus)");
        outtextxy(70, 375, "cos() (Functia cosinus)");
        settextstyle(10,0,3);
        outtextxy(455, 445, "Proiect realizat de:");
        settextstyle(10,0,2);
        outtextxy(565, 475, "Leagan Dan");
        outtextxy(540, 505, "Petrea Daniela");
        outtextxy(410, 535, "Grupa A5, Anul I, 2020-2021");
        settextstyle(10,0,5);
        break;
    case 2:
        settextstyle(10,0,6);
        outtextxy(290,35, "About");
        settextstyle(10,0,3);
        outtextxy(20, 105, "Operations, functions and constants available: ");
        settextstyle(10,0,2);
        outtextxy (70, 135, "+ (Assembly)");
        outtextxy (70, 165, "- (Decrease)");
        outtextxy (70, 195, "* (Multiplication)");
        outtextxy (70, 225, "/ (Sharing)");
        outtextxy (70, 255, "^ (Power function)");
        outtextxy (70, 285, "ln () (Natural logarithm)");
        outtextxy (70, 315, "r () (Radical function)");
        outtextxy (70, 345, "sin () (Sin function)");
        outtextxy (70, 375, "cos () (Cos function)");
        settextstyle(10,0,3);
        outtextxy(455, 445, "Project realized by:");
        settextstyle(10,0,2);
        outtextxy(565, 475, "Leagan Dan");
        outtextxy(540, 505, "Petrea Daniela");
        outtextxy(410, 535, "Group A5, Year I, 2020-2021");
        settextstyle(10,0,5);
        break;
    default:
        settextstyle(10,0,6);
        outtextxy(290, 35, "Description");
        settextstyle(10,0,3);
        outtextxy(20, 105, "Opérations, fonctions et constantes disponibles:");
        settextstyle(10,0,2);
        outtextxy (70, 135, "+ (Assemblage)");
        outtextxy (70, 165, "- (Diminuer)");
        outtextxy (70, 195, "* (Multiplication)");
        outtextxy (70, 225, "/ (Partage)");
        outtextxy (70, 255, "^ (Fonction puissance)");
        outtextxy (70, 285, "ln () (Logarithme naturel)");
        outtextxy (70, 315, "r () (Fonction radicale)");
        outtextxy (70, 345, "sin () (Fonction sin)");
        outtextxy (70, 375, "cos () (Fonction cosin)");
        settextstyle(10,0,3);
        outtextxy(455, 445, "Projet par:");
        settextstyle(10,0,2);
        outtextxy(565, 475, "Leagan Dan");
        outtextxy(540, 505, "Petrea Daniela");
        outtextxy(410, 535, "Groupe A5, L'année I, 2020-2021");
        settextstyle(10,0,5);
        break;
    }
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            PlaySound(TEXT("BUTTON.wav"),NULL,SND_ASYNC);
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>=5 && x<=65 && y>=5&&y<=35)
            {
                cleardevice();
                meniu(nr);
            }
            gata=true;
        }
    }
    while (!gata);
    cleardevice();
}
int main()
{
    int nr;
    initwindow(WIDTH,HEIGHT, "Graficul unei functii");
    limba(nr);
    return (0);
}
