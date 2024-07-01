#include "stdafx.h"
#include "conio.h"
#include "stdio.h"
#include "clocale"
#include "string.h"
#include "malloc.h"
#include <math.h>
#include "stdlib.h"
#include <windows.h>

using namespace std;
using namespace System;
using namespace System::IO;

struct z {
char nazvanie[20];
char city[20];
long kolvo;
char klass[20];
long money;
char data[11];
};

struct sp {
char fio[20];
long kolvo;
struct sp* sled;
struct sp* pred;
};

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79
#define LENGTHMENU 99 

struct z *z = NULL;  


int menu(int, char [][LENGTHMENU]);
void maxim(struct z*, int);
void text_data(char *,char *);
void kolvo(struct z *,int);
void alfalist(struct z*,struct sp** spisok,int);
void vstavka(struct z*,char*,struct sp** spisok, int);
void listing(struct z*,int);
void poisk(struct z*, int);
void diagram(struct z*,struct sp** spisok,int);
void stdat(struct  z*,int);
void gorod(struct z*, int);
void naim(struct z*, int);

void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={
"января","февраля","марта","апреля","мая","июня",
"июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}
void first(struct z* home, int NC)
{
int i;
char s[17];
struct z* best=home;
for(i=1;i<NC;i++)
if (strcmp(home[i].data,best->data)<0)
best=&home[i];
text_data(s,best->data);
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::DarkBlue;
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Самый ранний ЖК класса %s с %ld корпусами ",
best->klass,best->kolvo);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("В городе %s имеет название \"%s\" ",
best->city, best->nazvanie);
Console::CursorLeft=10;
Console::CursorTop=18;
printf("Построен %s ",s);
getch();
}

int main(array<System::String ^> ^args)
{
int i,n, NC;
FILE *in;
struct z *homes;
char dan[][LENGTHMENU]={
"Какой ЖК имеет максимальное количесвто корпусов?       ",
"Сколько ЖК находится в Москве.                         ",
"Список ЖК из конкретного города.                       ",
"Квартира в каком ЖК дешевле?                           ",
"Какой ЖК был построен раньше всех?                     ",
"Список ЖК класса \"Комфорт\", больше чем с 10 корпусами  ",
"Двусторонний список Жилых комплексов.                  ",
"Поиск совпадения.                                      ",
"Диаграмма.                                             ",
"Выход.                                                 "
};

setlocale(LC_CTYPE,"Russian");
Console::CursorVisible::set(false);
Console::BufferHeight=720;
Console::BufferWidth=1260;
if((in=fopen("Spisok.dat","r"))==NULL)
{

printf("\nФайл Spisok.dat не открыт !");
getch(); exit(1);
}
printf(" \n");
Console::CursorLeft=27;
printf("Список жилых комплексов\n");
printf(" \n");
printf(" \n");  
printf("  ЖК          Город            Корпуса     Класс   Цена за кв.(млн.р.)  Дата посторойки \n");
printf("_________________________________________________________________________________________\n");
fscanf(in,"%d",&NC);
homes=(struct z*)malloc(NC*sizeof(struct z));
for(i=0;i<NC;i++)
fscanf(in,"%s%s%ld%s%ld%s",
homes[i].nazvanie, homes[i].city, &homes[i].kolvo,
homes[i].klass, &homes[i].money, homes[i].data);
for(i=0;i<NC;i++)
printf("\n%-13s %-19s %7ld %-15s %5ld %20s",
homes[i].nazvanie,
homes[i].city, homes[i].kolvo,
homes[i].klass, homes[i].money, homes[i].data);
struct sp *spisok = nullptr;
getch();
while(1)
{
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::White;
;
;
Console::Clear();
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::DarkBlue;
Console::CursorLeft=10;
Console::CursorTop=4;
printf("                                                           ");
for(i=0;i<10;i++)
{
Console::CursorLeft=10;
Console::CursorTop=i+5;
printf(" %s ",dan[i]);
}
Console::CursorLeft=10;
Console::CursorTop=14;
printf("                                                           ");
n=menu(10, dan);
switch(n) {
case 1: maxim(homes, NC);break;
case 2: gorod(homes, NC);break;
case 3: poisk(homes, NC);break;
case 4: naim(homes, NC);break;
case 5: first(homes, NC);break;
case 6: listing(homes, NC);break;
case 7: alfalist(homes,&spisok, NC);break;
case 8: stdat(homes, NC);break;
case 9: diagram(homes,&spisok, NC);break;
case 10: exit(0);
}
}
return 0;
}

int menu(int n, char dan[][LENGTHMENU])
{
int y1=0,y2=n-1;
char c=1;
while (c!=ESC)
{
switch(c) {
case DOWN: y2=y1; y1++; break;
case UP: y2=y1; y1--; break;
case ENTER: return y1+1;
case HOME: y2=y1;y1=0;break;
case END: y2=y1;y1=n-1;break;
}
if(y1>n-1){y2=n-1;y1=0;}
if(y1<0) {y2=0;y1=n-1;}
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::CursorLeft=11;
Console::CursorTop=y1+5;
printf("%s",dan[y1]);
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::DarkBlue;
Console::CursorLeft=11;
Console::CursorTop=y2+5;
printf("%s",dan[y2]);
c=getch();
}
exit (0);
}
void maxim(struct z* home, int NC)
{
int i=0; struct z max;
strcpy(max.nazvanie,home[0].nazvanie);
max.kolvo=home[0].kolvo;
for(i=1;i<NC;i++)
if (home[i].kolvo>max.kolvo)
{
strcpy(max.nazvanie,home[i].nazvanie);
max.kolvo=home[i].kolvo;
}
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::DarkBlue;
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Максимальное количество корпусов: %ld ",max.kolvo);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("находится в ЖК: %s ",max.nazvanie);
getch();
}

void naim(struct z* home, int NC)
{
int i=0; struct z min;
strcpy(min.nazvanie,home[0].nazvanie);
min.money=home[0].money;
for(i=1;i<NC;i++)
if (home[i].money<min.money)
{
strcpy(min.nazvanie,home[i].nazvanie);
min.money=home[i].money;
}
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::DarkBlue;
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Самая дешевая квартира, стоимость которой %ld млн.р. ",min.money);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("находится в ЖК \"%s\" ",min.nazvanie);
getch();
}

void gorod(struct z *home, int NC)
{
int i,k=0;
for(i=0;i<NC;i++)
if (strcmp(home[i].city,"Москва")==0)
k++;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::DarkBlue;
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Количесво ЖК в городе Москва: %d ",k);
getch();
}
void alfalist(struct z* home, struct sp** spisok, int NC)
{
int i;
struct sp *nt, *z;
Console::ForegroundColor=ConsoleColor::DarkBlue;
Console::BackgroundColor=ConsoleColor::White;
Console::Clear();
printf("\nАлфавитный список Жилых комплексов");
printf("\t\tОбратный список Жилых комплексов");
printf("\n");
printf("\t");
printf("\n");
printf("\t");
printf("ЖК          Корпуса ");
printf("\t\t\t      ЖК            Корпуса ");
printf("\n __________________________________");
printf("\t    __________________________________\n");

if(!*spisok)
for(i=0;i<NC;i++)
vstavka(home, home[i].nazvanie, spisok, NC);
for(nt=*spisok; nt!=0; nt=nt->sled)
printf("\n %-20s %ld",nt->fio,nt->kolvo);
for(nt=*spisok, z=0; nt!=0; z=nt, nt=nt->sled);
Console::CursorTop=7;
for(nt=z, i=0; nt!=0; i++, nt=nt->pred){
Console::CursorLeft=49;
printf("%-20s % ld", nt->fio,nt->kolvo);
Console::CursorTop+=1;
}
_getch();
}
void vstavka(struct z* home,char* fio, struct sp** spisok, int NC)
{
int i;
struct sp *nov,*nt,*z=0;
for(nt=*spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled);
if(nt && strcmp(nt->fio,fio)==0) return;
nov=(struct sp *) malloc(sizeof(struct sp));
strcpy(nov->fio,fio);
nov->sled=nt;
nov->kolvo=0;
nov->pred=z;
for(i=0;i<NC;i++)
if(strcmp(home[i].nazvanie,fio)==0)
nov->kolvo+=home[i].kolvo;
if(!z) *spisok=nov;
else z->sled=nov;
if (nt) nt->pred=nov;
return;
}
void listing(struct z* home, int NC)
{
int i;
struct z* nt;
Console::ForegroundColor=ConsoleColor::DarkBlue;
Console::BackgroundColor=ConsoleColor::White;
Console::Clear();
printf("\n\r Список ЖК класса \"Комфорт\", больше чем с 10 корпусами");
printf(" \n");
printf("\n\r     ЖК             Корпуса \n\r");
printf("______________________________________________________\n");
for(i=0,nt=home;i<NC;nt++,i++)
if (nt->kolvo>10 && strcmp(nt->klass,"Комфорт")==0)
printf("\n\r %-20s %ld ",nt->nazvanie,nt->kolvo);
getch();
}

void diagram(struct z *home, struct sp** spisok, int NC)
{
struct sp *nt;
int len,i,NColor;
long sum = 0 ;
char str1[20];
char str2[20];
System::ConsoleColor Color;
Console::ForegroundColor=ConsoleColor::DarkBlue;
Console::BackgroundColor=ConsoleColor::White;
Console::Clear();
for(i=0;i<NC;i++) sum = sum+home[i].kolvo ;
if(!*spisok)
for(i=0;i<NC;i++)
vstavka(home,home[i].nazvanie, spisok, NC);
Color=ConsoleColor::Black; NColor=0;
for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)
{
sprintf(str1,"%s",nt->fio);
sprintf(str2,"%3.1f%%",(nt->kolvo*100./sum));
Console::ForegroundColor=ConsoleColor::DarkBlue;
Console::BackgroundColor= ConsoleColor::White;
Console::CursorLeft=5; Console::CursorTop=i+1;
printf(str1);
Console::CursorLeft=20;
printf("%s",str2);
Console::BackgroundColor=++Color; NColor++;
Console::CursorLeft=30;
for(len=0; len<nt->kolvo*100/sum; len++) printf(" ");
if(NColor==14)
{ Color=ConsoleColor::Black; NColor=0; }
}
getch();
return ;
}

void stdat(struct z*home, int NC)
{
int i, k, flag=0;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::DarkBlue;
Console::CursorLeft=9;
Console::CursorTop=13;
for (k=0; k<NC; k++)
{
for (i=k+1; i<NC; i++)
{
if(strcmp(home[i].city, home[k].city)==0 && (home[i].kolvo ==
home[k].kolvo))
{
flag++;
Console::CursorLeft=10;
Console::CursorTop=16;
printf(" ЖК %s и %s из города '%s' \n",home[i].nazvanie, home[k].nazvanie, home[i].city);
Console::CursorLeft=10;
printf(" имеют %d корпусов", home[i].kolvo);
break;
}
if (flag==1) break;
}
}
if (flag==0)
{
Console::CursorLeft=10;
Console::CursorTop=18;
printf(" Совпадений не найдено!");
}
getch();
}


void poisk(struct z* home, int NC)
{
Console::ForegroundColor=ConsoleColor::DarkBlue;
Console::BackgroundColor=ConsoleColor::White;
Console::Clear();
int i, kolvo=0;
char search[15];
printf (" Список ЖК из конкретного города \n");
printf (" Введите название города :");
Console::CursorLeft++;
Console::CursorVisible::set(true);
SetConsoleCP(1251);
scanf("%s",search);
SetConsoleCP(866);
Console::CursorVisible::set(false);
printf("\n ЖК              Корпуса  Класс        Дата посторойки");
printf("\n___________________________________________________________ \n");
for (i=0;i<NC;i++)
{
if(strcmp(home[i].city,search)==0)
{
printf("\n %-20s %2ld %-14s %s",home[i].nazvanie, home[i].kolvo, home[i].klass, home[i].data);
kolvo++;
}
}
if (kolvo==0) 
printf("\n_________________________________________________ \n ЖК из данного города не найдены");
if (kolvo) printf("\n\nКол-во ЖК из интересующего города: %-7d",kolvo);
getch();
return ;
}