#include<iostream.h>
#include<stdlib.h>
#include<fstream.h>
#include<time.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<alloc.h>
//Declaration for  i/o Registers
 union REGS i,o ;
// INITIALISES MOUSE
interrupt initmouse()
 {
  i.x.ax = 0 ;
  int86(0x33, &i, &o) ;
  return ( o.x.ax == 0 ? -1:0 ) ;
 }
 //DISPLAY MOUSE POINTER
  showmouseptr()
  {
    i.x.ax = 1 ;
    int86( 0x33, &i, &o );
  }
 //RESTRICTS MOUSE POINTER
     restrictmouseptr(int x1, int y1, int x2, int y2 )
     {    //X - AXIS limits
     i.x.ax = 7 ;
     i.x.cx = x1 ;
     i.x.dx = x2 ;
     int86(0x33, &i, &o ) ;
      //Y - AXIS limits
     i.x.ax = 8 ;
     i.x.cx = y1 ;
     i.x.dx = y2 ;
     int86(0x33, &i, &o) ;
   }
  //GETS MOUSE COORDINATES AND BUTTON STATUS
  getmousepos(int *button, int *x, int *y )
  {
   i.x.ax = 3 ;
   int86(0x33, &i, &o ) ;
   *button = o.x.bx ;
   *x = o.x.cx ;
   *y = o.x.dx ;
  }
enum { Esc = 27 };
int flag=1,err=0,Exit=0,login=0;
char g;
char username[30];
char fname[30],lname[30],password[30],con[30],f,disp[30],disp2[30];
int ss=0,flags=0,enter,fame=0,lame=0,naes=0,pas=0,pas2=0;
void guitar()
{
cleardevice();
setfillstyle(10,DARKGRAY); //3
bar(0,0, 600,600);
bar(0,0,100,100);
setfillstyle(SOLID_FILL,BLACK);
bar(250,60,360,150);  //Note bar
setcolor(WHITE);
rectangle(250,55,360,150);      //Note outline
settextstyle(7,0,6);
outtextxy(50,70,"NOTE:-");
setfillstyle(6,BROWN);
bar(0,200,600,320);
setfillstyle(SOLID_FILL,WHITE);
bar(600,195,610,325);
setcolor(DARKGRAY);
setcolor(WHITE);
settextstyle(1,0,3);
outtextxy(530,20,"X");
for(int i=0,x=206;i<6;i++,x+=20)
{
setfillstyle(SOLID_FILL,LIGHTGRAY);
bar(0,x,600,x+5);  //string
}
setcolor(DARKGRAY);
for(i=0,x=5;i<19;i++,x+=30)
line(x,200,x,320);         //fret
setfillstyle(SOLID_FILL,WHITE);
int flag=1;
int button,  y ;
initmouse();
showmouseptr();
char key;
enum { Esc = 27 };
int xx[20]={5,35,65,95,125,155,185,215,245,275,305,335,365,395,425,455,485,515,545,575};
int y1,y2,f1,f2;
float sel[19]={0};/*freq of each string*/ char seel[19][4];//note of each string
float fret1[19]={349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880.00,932.33,987.77};
char let1[19][4]={"F","F#","G","G#","A","Bb","B","C","C#","D","D#","E","F","F#","G","G#","A","Bb","B"};
float fret2[19]={261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99};
char let2[19][4]={"C","C#","D","D#","E","F","F#","G","G#","A","Bb","B","C","C#","D","D#","E","F","F#"};
float fret3[19]={207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33};
char let3[19][4]={"G#","A","Bb","B","C","C#","D","D#","E","F","F#","G","G#","A","Bb","B","C","C#","D"};
float fret4[19]={155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00};
char let4[19][4]={"D#","E","F","F#","G","G#","A","Bb","B","C","C#","D","D#","E","F","F#","G","G#","A"};
float fret5[19]={116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63};
char let5[19][4]={"Bb","B","C","C#","D","D#","E","F","F#","G","G#","A","Bb","B","C","C#","D","D#","E"};
float fret6[19]={87.31,92.50,98.00,103.83,110.00,116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94};
while (key!=Esc)
{  while( flag!=0 )
     {getmousepos( &button, &x, &y);
      if( button & 1 == 1 ) //Left
       {        for(int i=0,x1=206,x2=211;i<6;i++,x1+=20,x2+=20)
	       {   //After the y coordinate has been clicked
		if(y>=x1&&y<=x2)
		{       //Used to specify the string to be played and pass on frequency
			y1=x1;y2=x2;
			if(y1>=206&&y2<=211)
			{  for(int j=0,g=18;j<19;j++,g--)
			  {
				sel[j]=fret6[j];
				strcpy(seel[j],let1[g]);}
			  }
			else
			if(y1>=226&&y2<=231)
			{	for(int j=0,g=18;j<19;j++,g--)
				{sel[j]=fret5[j];
				 strcpy(seel[g],let5[j]);}
				}
			else
			if(y1>=246&&y2<=251)
			{ for(int j=0,g=18;j<19;j++,g--)
			{strcpy(seel[j],let4[g]);
			sel[j]=fret4[j];}}
			else
			if(y1>=266&&y2<=271)
			{ for(int j=0,g=18;j<19;j++,g--)
			{sel[j]=fret3[j];
			strcpy(seel[j],let3[g]);}
			}
			else
			if(y1>=286&&y2<=291)
			{ for(int j=0,g=18;j<19;j++,g--)
			{sel[j]=fret2[j];
			strcpy(seel[j],let2[g]);}
			}
			else
			if(y1>=306&&y2<=311)
			{ for(int j=0,g=18;j<19;j++,g--)
			{sel[j]=fret1[j];
			strcpy(seel[j],let1[g]);}
			}
				    settextstyle(7,0,8);
		}
		}
		 if(x>=xx[0]&&x<=xx[1]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[0]+1,y1,xx[1]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[0]);
		     sound(sel[18]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[0]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[0]+1,y1,xx[1]-1,y2);
		     }
		  if(x>=xx[1]&&x<=xx[2]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[1]+1,y1,xx[2]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[1]);
		     sound(sel[17]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[1]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[1]+1,y1,xx[2]-1,y2);
		     }
		     if(x>=xx[2]&&x<=xx[3]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[2]+1,y1,xx[3]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[2]);
		     sound(sel[16]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[2]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[2]+1,y1,xx[3]-1,y2);
		     }
		   if(x>=xx[3]&&x<=xx[4]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[3]+1,y1,xx[4]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[3]);
		     sound(sel[15]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[3]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[3]+1,y1,xx[4]-1,y2);
		     }
		 if(x>=xx[4]&&x<=xx[5]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[4]+1,y1,xx[5]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[4]);
		     sound(sel[14]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[4]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[4]+1,y1,xx[5],y2);
		     }
		 if(x>=xx[5]&&x<=xx[6]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[5],y1,xx[6],y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[5]);
		     sound(sel[13]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[5]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[5],y1,xx[6],y2);
		     }
		 if(x>=xx[6]&&x<=xx[7]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[6]+1,y1,xx[7]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[6]);
		     sound(sel[12]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[6]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[6]+1,y1,xx[7]-1,y2);
		     }
		 if(x>=xx[7]&&x<=xx[8]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[7]+1,y1,xx[8]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[7]);
		     sound(sel[11]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[7]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[7]+1,y1,xx[8]-1,y2);
		     }
		if(x>=xx[8]&&x<=xx[9]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[8]+1,y1,xx[9]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[8]);
		     sound(sel[10]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[8]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[8]+1,y1,xx[9]-1,y2);
		     }
		if(x>=xx[9]&&x<=xx[10]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[9]+1,y1,xx[10]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[9]);
		     sound(sel[9]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[9]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[9]+1,y1,xx[10]-1,y2);
		     }
		if(x>=xx[10]&&x<=xx[11]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[10]+1,y1,xx[11]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[10]);
		     sound(sel[8]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[10]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[10]+1,y1,xx[11]-1,y2);
		     }
		if(x>=xx[11]&&x<=xx[12]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[11]+1,y1,xx[12]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[11]);
		     sound(sel[7]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[11]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[11]+1,y1,xx[12]-1,y2);
		     }
		    if(x>=xx[12]&&x<=xx[13]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[12]+1,y1,xx[13]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[12]);
		    sound(sel[6]);
		     delay(250);
		    nosound();
		    setcolor(BLACK);
		     outtextxy(265,50,seel[12]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[12]+1,y1,xx[13]-1,y2);
		     }
		     if(x>=xx[13]&&x<=xx[14]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[13]+1,y1,xx[14]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[13]);
		     sound(sel[5]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[13]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[13]+1,y1,xx[14]-1,y2);
		     }
		     if(x>=xx[14]&&x<=xx[15]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[14]+1,y1,xx[15]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[14]);
		     sound(sel[4]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[14]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[14]+1,y1,xx[15]-1,y2);
		     }
		     if(x>=xx[15]&&x<=xx[16]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[15]+1,y1,xx[16]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[15]);
		     sound(sel[3]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[15]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[15]+1,y1,xx[16]-1,y2);
		     }
		     if(x>=xx[16]&&x<=xx[17]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[16]+1,y1,xx[17]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[16]);
		     sound(sel[2]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[16]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[16]+1,y1,xx[17]-1,y2);
		     }
		   if(x>=xx[17]&&x<=xx[18]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[17]+1,y1,xx[18]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[17]);
		     sound(sel[1]);
		     delay(250);
		   nosound();
		   setcolor(BLACK);
		     outtextxy(265,50,seel[17]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[17]+1,y1,xx[18]-1,y2);
		     }
		     if(x>=xx[18]&&x<=xx[19]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[18]+1,y1,xx[19]+30,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[18]);
		     sound(sel[0]);
		     delay(250);
		     nosound();
		     setcolor(BLACK);
		     outtextxy(265,50,seel[18]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[18]+1,y1,xx[19]+30,y2);
		     }
		if(x>=500&&x<=560&&y>=0&&y<=60)
		{       key=27;
			break;
		}
      }
      }

     }
}
void play(float n)
{     sound(n);
      delay(200);
      nosound();
      delay(100);
}
int jjj=0,ccount=0; float r[100];
int count=0,j=0;    float s[100];int dir=0;
struct rec
{   char username[30];
    char fname[30];
    char lname[30];
    char password[30];
    char instrument[30];
    float note[100];
    int num;
    char sname[30];
    char date[9];
    char time[9];
    public:
    void copypas();
    void savesong();
    void rm();
    void gcopypas();
};
rec song,song2;
char songname[30];
void rec::copypas()
{
	num=count;
	for(int i=0;i<count;i++)
	{
		note[i]=s[i];
	}
}
void rec::gcopypas()
{
    num=ccount-1;
    for(int g=0,x=1;x<ccount;g++,x++)
    {      note[g]=r[x];
    }
}
  char datebuf[9];
  char timebuf[9];
void rec::savesong()
{   int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
setcolor(MAGENTA);
circle(319, 22, 20);
setcolor(BLUE);
line(319, 2, 297, 20);
line(297,20,319,42);
line(319,42,341,20);
line(341,20,319,2);
line(308,11,308,31);
line(308,31,330,31);
line(330,31,330,11);
line(330,11,308,11);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(306, 10, "MX");
settextstyle(4, 0, 1);
  setcolor(BLUE);
outtextxy(247, 40, "MUSICATRONIX");
settextstyle(5, 0, 4);
  setcolor(RED);
outtextxy(60,60,"The World of Music at your fingertips");
setcolor(MAGENTA);
line(20,120,637,120);
line(25,125,632,125);
line(25,125,25,470);
line(20,120,20,475);
line(25,470,632,470);
line(20,475,637,475);
line(632,470,632,125);
line(637,475,637,120);
for(int x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,120,j,125);
}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(20,x,25,j);
}
for(x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,470,j,475);
}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(632,x,637,j);
}
settextstyle(5, 0, 4);
  setcolor(CYAN);
outtextxy(235,130,"Save Song");
setcolor(MAGENTA);
settextstyle(5, 0, 2);
outtextxy(32,225,"Enter name of the song:-");
char g;
songname[0]='\0';
int flag=0,songsize=0;
 while(g!=27&&flag==0)
		    {  g=getch();
		       if(g=='\r')
		       {
			flag=1;songname[songsize]='\0';
		       }
		       if(g=='\b')
		       {songsize--;
			if(songsize<0)
			{
				songsize=0;
			}
			songname[songsize]='\0';
			setcolor(MAGENTA);
			setfillstyle(SOLID_FILL,BLACK);
			bar(270,230,600,260);
			outtextxy(270,225,songname);

		       }
		       if(g>32&&g<127)
		       {
			songname[songsize]=g;
			songsize++;
			setcolor(MAGENTA);
			setfillstyle(SOLID_FILL,BLACK);
			bar(270,230,600,260);
			outtextxy(270,225,songname);
		       }
		       if(g==' ')
		       {
			songname[songsize]=g;
			songsize++;
			setcolor(MAGENTA);
			setfillstyle(SOLID_FILL,BLACK);
			bar(270,230,600,260);
			outtextxy(270,225,songname);
		       }
		     }

cleardevice();
setcolor(MAGENTA);
circle(319, 22, 20);
setcolor(BLUE);
line(319, 2, 297, 20);
line(297,20,319,42);
line(319,42,341,20);
line(341,20,319,2);
line(308,11,308,31);
line(308,31,330,31);
line(330,31,330,11);
line(330,11,308,11);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(306, 10, "MX");
settextstyle(4, 0, 1);
  setcolor(BLUE);
outtextxy(247, 40, "MUSICATRONIX");
settextstyle(5, 0, 4);
  setcolor(RED);
outtextxy(60,60,"The World of Music at your fingertips");
setcolor(MAGENTA);
line(20,120,637,120);
line(25,125,632,125);
line(25,125,25,470);
line(20,120,20,475);
line(25,470,632,470);
line(20,475,637,475);
line(632,470,632,125);
line(637,475,637,120);
for(int z=20,k=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(z,120,k,125);
}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(20,x,25,j);
}
for(x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,470,j,475);
}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(632,x,637,j);
}
settextstyle(5, 0, 4);
  setcolor(CYAN);
outtextxy(245,125,"Song Info.");
settextstyle(6, 0, 3);
setcolor(MAGENTA);
outtextxy(32,215,"Song name");
outtextxy(255,215,"Composer");
outtextxy(440,215,"Date");
outtextxy(552,215,"Time");
line(250,220,250,275);
line(550,220,550,275);
line(435,220,435,275);
setcolor(RED);
rectangle(30,220,628,248);
rectangle(30,220,628,275);
setcolor(GREEN);
settextstyle(7,0,1);
outtextxy(32,251,songname);
outtextxy(255,251,username);
  _strdate(datebuf);
  _strtime(timebuf);
outtextxy(440,251,datebuf);
outtextxy(552,251,timebuf);
outtextxy(32,300,"Press Z to play back the song");
char KeyPressed = getch() ;
int key=0;
while( KeyPressed != Esc )
{	switch( KeyPressed )
	{
		case 'z': for(int d=0;d<num;d++)
			 {
				play(note[d]);
			 }
			 break;
		case 27: key=1;
			 break;

	}
	if(key==0)
	KeyPressed=getch();
}
cleardevice();
}
void rec::rm()
{
cleardevice();
setcolor(MAGENTA);
circle(319, 22, 20);
setcolor(BLUE);
line(319, 2, 297, 20);
line(297,20,319,42);
line(319,42,341,20);
line(341,20,319,2);
line(308,11,308,31);
line(308,31,330,31);
line(330,31,330,11);
line(330,11,308,11);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(306, 10, "MX");
settextstyle(4, 0, 1);
  setcolor(BLUE);
outtextxy(247, 40, "MUSICATRONIX");
settextstyle(5, 0, 4);
  setcolor(RED);
outtextxy(60,60,"The World of Music at your fingertips");
setcolor(MAGENTA);
line(20,120,637,120);
line(25,125,632,125);
line(25,125,25,470);
line(20,120,20,475);
line(25,470,632,470);
line(20,475,637,475);
line(632,470,632,125);
line(637,475,637,120);
for(int x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,120,j,125);
}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(20,x,25,j);
}
for(x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,470,j,475);
}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(632,x,637,j);
}
settextstyle(5, 0, 4);
  setcolor(CYAN);
outtextxy(245,125,"Song Info.");
settextstyle(6, 0, 3);
setcolor(MAGENTA);
outtextxy(32,215,"Song name");
outtextxy(255,215,"Composer");
outtextxy(440,215,"Date");
outtextxy(552,215,"Time");
setcolor(GREEN);
settextstyle(7,0,1);
outtextxy(32,251,sname);
outtextxy(255,251,username);
outtextxy(440,251,date);
outtextxy(552,251,time);
line(250,220,250,275);
line(550,220,550,275);
line(435,220,435,275);
setcolor(RED);
rectangle(30,220,628,248);
rectangle(30,220,628,275);
setcolor(GREEN);
settextstyle(7,0,1);
outtextxy(32,300,"Press Z to play back the song");
outtextxy(32,375,"Previous Song");
outtextxy(470,375,"Next Song");
settextstyle(7,0,3);
outtextxy(220,420,"A              D");
setfillstyle(SOLID_FILL,CYAN);
setcolor(CYAN);
line(250,350,250,420);//left arrow
line(250,350,190,385);
line(250,420,190,385);
floodfill(210,380,CYAN);
line(388,350,388,420);//right arrow
line(388,350,448,385);
line(388,420,448,385);
floodfill(400,380,CYAN);
char KeyPressed = getch() ;
int flag=1;
while( KeyPressed != Esc&&flag==1 )
{
	switch( KeyPressed )
	{
		case 'z': for(int d=0;d<num;d++)
			 {
				play(note[d]);
			 }
			 break;
		case 'a':
		case 'A':
			 setfillstyle(SOLID_FILL,BLACK);
		   setcolor(BLACK);
		   line(250,350,250,420);//left arrow
		   line(250,350,190,385);
		   line(250,420,190,385);
		   floodfill(210,380,BLACK);
		   setfillstyle(SOLID_FILL,CYAN);
		   setcolor(CYAN);
		   line(250,360,250,410);//left arrow
		   line(250,360,200,385);
		   line(250,410,200,385);
		   floodfill(220,380,CYAN);
		   delay(150);
		   setfillstyle(SOLID_FILL,CYAN);
		   setcolor(CYAN);
		   line(250,350,250,420);//left arrow
		   line(250,350,190,385);
		   line(250,420,190,385);
		   floodfill(203,380,CYAN);
			 dir=-1;
			 flag=0;
			 break;
		case 'd':
		case 'D':
			 setfillstyle(SOLID_FILL,BLACK);
		   setcolor(BLACK);
		   line(388,350,388,420);//right arrow
		   line(388,350,448,385);
		   line(388,420,448,385);
		   floodfill(400,380,BLACK);
		   setfillstyle(SOLID_FILL,CYAN);
		   setcolor(CYAN);
		   line(388,360,388,410);//right arrow
		   line(388,360,438,385);
		   line(388,410,438,385);
		   floodfill(418,380,CYAN);
		   delay(150);
		   setfillstyle(SOLID_FILL,CYAN);
		   setcolor(CYAN);
		   line(388,350,388,420);//right arrow
		   line(388,350,448,385);
		   line(388,420,448,385);
		   floodfill(435,380,CYAN);
			 dir=1;
			 flag=0;
			 break;
	}
	if(flag==1)
{KeyPressed=getch();}
}
if(KeyPressed==27)
Exit=1;
}
void gagain()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
showmouseptr();
setfillstyle(10,DARKGRAY); //3
bar(0,0, 700,700);
bar(0,0,300,300);
setfillstyle(SOLID_FILL,BLACK);
bar(250,60,360,150);  //Note bar
setcolor(WHITE);
rectangle(250,55,360,150);      //Note outline
settextstyle(7,0,6);
outtextxy(50,70,"NOTE:-");
setfillstyle(SOLID_FILL,BLACK);
bar(100,350,500,470);      //(recorder)  //play button( bar )
rectangle(100,350,500,470);     //outline
circle(305,410,50);
setcolor(RED);	     //Outer circle
circle(305,410,35);	  //inner circle
setfillstyle(SOLID_FILL,RED);
floodfill(305,410,RED);    //filling of inner circle
setfillstyle(SOLID_FILL,WHITE);
setcolor(WHITE);
line(220,410,135,360);      //play button
line(220,410,135,460);
line(135,360,135,460);
floodfill(170,400,WHITE);             //filling of play button
setfillstyle(SOLID_FILL,WHITE);
/*bar(400,360,430,460);
bar(450,360,480,460);*/
bar(400,370,470,440);
setfillstyle(6,BROWN);
bar(0,200,600,320);
setfillstyle(SOLID_FILL,WHITE);
bar(600,195,610,325);
setcolor(DARKGRAY);
setcolor(WHITE);
settextstyle(1,0,3);
outtextxy(530,20,"X");
for(int i=0,s=206;i<6;i++,s+=20)
{
setfillstyle(SOLID_FILL,LIGHTGRAY);
bar(0,s,600,s+5);  //string
}
setcolor(DARKGRAY);
for(i=0,s=5;i<19;i++,s+=30)
line(s,200,s,320);         //fret
}
void guitarecord()
{
clrscr();
ccount=0;
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
setfillstyle(10,DARKGRAY); //3
bar(0,0, 700,700);
bar(0,0,300,300);
setfillstyle(SOLID_FILL,BLACK);
bar(250,60,360,150);  //Note bar
setcolor(WHITE);
rectangle(250,55,360,150);      //Note outline
settextstyle(7,0,6);
outtextxy(50,70,"NOTE:-");
setfillstyle(SOLID_FILL,BLACK);
bar(100,350,500,470);      //(recorder)  //play button( bar )
rectangle(100,350,500,470);     //outline
circle(305,410,50);
setcolor(RED);	     //Outer circle
circle(305,410,35);	  //inner circle
setfillstyle(SOLID_FILL,RED);
floodfill(305,410,RED);    //filling of inner circle
setfillstyle(SOLID_FILL,WHITE);
setcolor(WHITE);
line(220,410,135,360);      //play button
line(220,410,135,460);
line(135,360,135,460);
floodfill(170,400,WHITE);             //filling of play button
setfillstyle(SOLID_FILL,WHITE);
/*bar(400,360,430,460);
bar(450,360,480,460);*/
bar(400,370,470,440);
setfillstyle(6,BROWN);
bar(0,200,600,320);
setfillstyle(SOLID_FILL,WHITE);
bar(600,195,610,325);
setcolor(DARKGRAY);
setcolor(WHITE);
settextstyle(1,0,3);
outtextxy(530,20,"X");
for(int i=0,s=206;i<6;i++,s+=20)
{
setfillstyle(SOLID_FILL,LIGHTGRAY);
bar(0,s,600,s+5);  //string
}
setcolor(DARKGRAY);
for(i=0,s=5;i<19;i++,s+=30)
line(s,200,s,320);         //fret
setfillstyle(SOLID_FILL,WHITE);
int flag=1;        int flagg=0;//triangle
char key;
enum { Esc = 27 };
int xx[20]={5,35,65,95,125,155,185,215,245,275,305,335,365,395,425,455,485,515,545,575};
int y1,y2,f1,f2;
float sel[19]={0};/*freq of each string*/ char seel[19][4];//note of each string
float fret1[19]={349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880.00,932.33,987.77};
char let1[19][4]={"F","F#","G","G#","A","Bb","B","C","C#","D","D#","E","F","F#","G","G#","A","Bb","B"};
float fret2[19]={261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99};
char let2[19][4]={"C","C#","D","D#","E","F","F#","G","G#","A","Bb","B","C","C#","D","D#","E","F","F#"};
float fret3[19]={207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33};
char let3[19][4]={"G#","A","Bb","B","C","C#","D","D#","E","F","F#","G","G#","A","Bb","B","C","C#","D"};
float fret4[19]={155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00};
char let4[19][4]={"D#","E","F","F#","G","G#","A","Bb","B","C","C#","D","D#","E","F","F#","G","G#","A"};
float fret5[19]={116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63};
char let5[19][4]={"Bb","B","C","C#","D","D#","E","F","F#","G","G#","A","Bb","B","C","C#","D","D#","E"};
float fret6[19]={87.31,92.50,98.00,103.83,110.00,116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94};
jjj=0;
int button,x,  y ;                 int flaggg=0;//not recording
initmouse();
showmouseptr();
while (key!=Esc)
{
	while( flag!=0 )
		{
		getmousepos( &button, &x, &y);
			if( button & 1 == 1 ) //Left
			{     if(y>=350&&y<=450&&x>=130&x<=230)
				{
				setfillstyle(SOLID_FILL,BLACK);
				setcolor(BLACK);
				line(135,360,135,460);
				line(220,410,135,360);      //play button
				line(220,410,135,460);
				floodfill(170,400,BLACK);
				setcolor(BLACK);
				line(135,360,135,460);
				line(220,410,135,360);      //play button
				line(220,410,135,460);
				for(int f=0;f<ccount;f++)
				{     sound(r[f]);
				      delay(100);
				      nosound();
				      delay(100);
				}
				delay(100);
				setfillstyle(SOLID_FILL,BLACK);
				bar(140,360,170,460);
				bar(180,360,210,460);
				delay(100);
				setfillstyle(SOLID_FILL,WHITE);
				setcolor(WHITE);
				line(135,360,135,460);
				line(220,410,135,360);      //play button
				line(220,410,135,460);
				floodfill(170,400,WHITE);
				}
		if(y>=360&&y<=460&&x>=250&&x<=350)
		{ 	if(flaggg==0)
			{ setcolor(WHITE);
			circle(305,410,50);
			setcolor(BLACK);	     //Outer circle
			circle(305,410,35);	  //inner circle
			setfillstyle(SOLID_FILL,BLACK);
			floodfill(305,410,BLACK);    //filling of inner circle
			delay(100);
			setcolor(RED);	     //Outer circle
			circle(305,410,40);	  //inner circle
			setfillstyle(SOLID_FILL,RED);
			floodfill(305,410,RED);flaggg=1;}
		  else
			if(flaggg==1)//stop recording
			{   setcolor(BLACK);	     //Outer circle
			circle(305,410,40);	  //inner circle
			setfillstyle(SOLID_FILL,BLACK);
			floodfill(305,410,BLACK);
			delay(100);
			setcolor(WHITE);
			circle(305,410,50);
			setcolor(RED);	     //Outer circle
			circle(305,410,35);	  //inner circle
			setfillstyle(SOLID_FILL,RED);
			floodfill(305,410,RED); flaggg=0;
			}
		 }
	     else
	     if(y>=370&&y<=440&&x>=400&&x<=470)
	     {
		   if(ccount>0)
		   {setfillstyle(SOLID_FILL,BLACK);
		   bar(400,370,470,440);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(410,380,460,430);
		   delay(150);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(400,370,470,440);
		  song2.gcopypas();
		  song2.savesong();
		  strcpy(song2.instrument,"Guitar");
		  strcpy(song2.sname,songname);
		  strcpy(song2.time,timebuf);
		  strcpy(song2.date,datebuf);
		    fstream file,file2;
		  file2.open("C:\\TC\\DSGSDG\\GUITAR.DAT",ios::app|ios::binary);
		  file.open("C:\\TC\\DSGSDG\\GUITAR2.DAT",ios::app|ios::binary);
		   file2.write((char*)&song2,sizeof(song2));
		   file2.close();
		   file.write((char*)&song2,sizeof(song2));
		   file.close();
		  cleardevice();
		  showmouseptr();
		  gagain();
		   jjj=0;
		   ccount=0;
		   flag=1;
		   }
		   else
		  { setfillstyle(SOLID_FILL,BLACK);
		   bar(400,370,470,440);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(410,380,460,430);
		   delay(150);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(400,370,470,440);
		   break;}
	     }
	     else
	       for(int i=0,x1=206,x2=211;i<6;i++,x1+=20,x2+=20)
		  {   //After the y coordinate has been clicked
			if(y>=x1&&y<=x2)
			{       //Used to specify the string to be played and pass on frequency
			y1=x1;y2=x2;
			if(y1>=206&&y2<=211)
			{  for(int j=0,g=18;j<19;j++,g--)
			  {
				sel[j]=fret6[j];
				strcpy(seel[j],let1[g]);}
			}
			else
			if(y1>=226&&y2<=231)
			{for(int j=0,g=18;j<19;j++,g--)
			{sel[j]=fret5[j];
			strcpy(seel[j],let5[g]);}
			}
			else
			if(y1>=246&&y2<=251)
			{ for(int j=0,g=18;j<19;j++,g--)
			{strcpy(seel[j],let4[j]);
			sel[j]=fret4[g];}}
			else
			if(y1>=266&&y2<=271)
			{ for(int j=0,g=18;j<19;j++,g--)
			{sel[j]=fret3[j];
			strcpy(seel[j],let3[g]);}
			}
			else
			if(y1>=286&&y2<=291)
			{ for(int j=0,g=18;j<19;j++,g--)
			{sel[j]=fret2[j];
			strcpy(seel[j],let2[g]);}
			}
			else
			if(y1>=306&&y2<=311)
			{ for(int j=0,g=18;j<19;j++,g--)
			{sel[j]=fret1[j];
			strcpy(seel[j],let1[g]);}
	       }
				    settextstyle(7,0,8);
		}
		}
		 if(x>=xx[0]&&x<=xx[1]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[0]+1,y1,xx[1]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[0]);
		     sound(sel[18]);
		     delay(250);
		     nosound();
		     if(flaggg==1)
		     { ccount++;r[jjj++]=sel[18];
		     }
		     setcolor(BLACK);
		     outtextxy(265,50,seel[0]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[0]+1,y1,xx[1]-1,y2);
		     }
		  if(x>=xx[1]&&x<=xx[2]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[1]+1,y1,xx[2]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[1]);
		     sound(sel[17]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[17];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[1]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[1]+1,y1,xx[2]-1,y2);
		     }
		     if(x>=xx[2]&&x<=xx[3]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[2]+1,y1,xx[3]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[2]);
		     sound(sel[16]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[16];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[2]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[2]+1,y1,xx[3]-1,y2);
		     }

		   if(x>=xx[3]&&x<=xx[4]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[3]+1,y1,xx[4]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[3]);
		     sound(sel[15]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[15];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[3]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[3]+1,y1,xx[4]-1,y2);
		     }
		 if(x>=xx[4]&&x<=xx[5]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[4]+1,y1,xx[5]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[4]);
		     sound(sel[14]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[14];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[4]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[4]+1,y1,xx[5],y2);
		     }
		 if(x>=xx[5]&&x<=xx[6]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[5],y1,xx[6],y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[5]);
		     sound(sel[13]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[13];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[5]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[5],y1,xx[6],y2);
		     }
		 if(x>=xx[6]&&x<=xx[7]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[6]+1,y1,xx[7]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[6]);
		     sound(sel[12]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[12];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[6]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[6]+1,y1,xx[7]-1,y2);
		     }
		 if(x>=xx[7]&&x<=xx[8]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[7]+1,y1,xx[8]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[7]);
		     sound(sel[11]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[11];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[7]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[7]+1,y1,xx[8]-1,y2);
		     }
		if(x>=xx[8]&&x<=xx[9]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[8]+1,y1,xx[9]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[8]);
		     sound(sel[10]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[10];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[8]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[8]+1,y1,xx[9]-1,y2);
		     }
		if(x>=xx[9]&&x<=xx[10]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[9]+1,y1,xx[10]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[9]);
		     sound(sel[9]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[9];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[9]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[9]+1,y1,xx[10]-1,y2);
		     }
		if(x>=xx[10]&&x<=xx[11]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[10]+1,y1,xx[11]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[10]);
		     sound(sel[8]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[8];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[10]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[10]+1,y1,xx[11]-1,y2);
		     }
		if(x>=xx[11]&&x<=xx[12]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[11]+1,y1,xx[12]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[11]);
		     sound(sel[7]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[7];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[11]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[11]+1,y1,xx[12]-1,y2);
		     }
		    if(x>=xx[12]&&x<=xx[13]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[12]+1,y1,xx[13]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[12]);
		    sound(sel[6]);
		     delay(250);
		    nosound();if(flaggg==1){ccount++;r[jjj++]=sel[6];}
		    setcolor(BLACK);
		     outtextxy(265,50,seel[12]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[12]+1,y1,xx[13]-1,y2);
		     }
		     if(x>=xx[13]&&x<=xx[14]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[13]+1,y1,xx[14]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[13]);
		     sound(sel[5]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[5];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[13]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[13]+1,y1,xx[14]-1,y2);
		     }
		     if(x>=xx[14]&&x<=xx[15]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[14]+1,y1,xx[15]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[14]);
		     sound(sel[4]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[4];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[14]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[14]+1,y1,xx[15]-1,y2);
		     }
		     if(x>=xx[15]&&x<=xx[16]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[15]+1,y1,xx[16]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[15]);
		     sound(sel[3]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[3];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[15]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[15]+1,y1,xx[16]-1,y2);
		     }
		     if(x>=xx[16]&&x<=xx[17]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[16]+1,y1,xx[17]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[16]);
		     sound(sel[2]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[2];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[16]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[16]+1,y1,xx[17]-1,y2);
		     }
		   if(x>=xx[17]&&x<=xx[18]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[17]+1,y1,xx[18]-1,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[17]);
		     sound(sel[1]);
		     delay(250);
		   nosound();if(flaggg==1){ccount++;r[jjj++]=sel[1];}
		   setcolor(BLACK);
		     outtextxy(265,50,seel[17]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[17]+1,y1,xx[18]-1,y2);
		     }
		     if(x>=xx[18]&&x<=xx[19]&&y>=y1&&y<=y2)
		 {
		setfillstyle(1,WHITE);
		     bar(xx[18]+1,y1,xx[19]+30,y2);
		     setcolor(WHITE);
		     outtextxy(265,50,seel[18]);
		     sound(sel[0]);
		     delay(250);
		     nosound();if(flaggg==1){ccount++;r[jjj++]=sel[0];}
		     setcolor(BLACK);
		     outtextxy(265,50,seel[18]);
		     setfillstyle(1,LIGHTGRAY);
		     bar(xx[18]+1,y1,xx[19]+30,y2);
		     }
	if(x>=500&&x<=560&&y>=0&&y<=60)
		{       key=27;
			break;
		}
}
      }
      }
}
void keyboard()
{
cleardevice();
settextstyle(3, 0, 6);
setcolor(WHITE);
outtextxy(100, 200, "LOADING...");
delay(1000);
rectangle(35,300,55,400);
delay(100);
rectangle(70,300,90,400);
delay(100);
rectangle(140,300,160,400);
delay(100);
rectangle(175,300,195,400);
delay(100);
rectangle(210,300,230,400);
delay(100);
rectangle(280,300,300,400);
delay(100);
rectangle(315,300,335,400);
delay(100);
rectangle(385,300,405,400);
delay(100);
rectangle(420,300,440,400);
delay(100);
rectangle(455,300,475,400);
delay(100);
rectangle(525,300,545,400);
delay(100);
rectangle(560,300,580,400);
delay(100);
for(int i=10,j=45;i<=600,j<620;i+=35,j+=35)
{delay(100);
setcolor(WHITE);
rectangle(i,300,j,450);
floodfill(i+15,350,WHITE);
}
for(i=10,j=45;i<=600,j<620;i+=35,j+=35)
{delay(100);
setcolor(BLACK);
rectangle(i,300,j,450);
}
setcolor(BLACK);
settextstyle(3, 0, 6);
outtextxy(100, 200, "LOADING...");
setcolor(MAGENTA);
circle(319, 110, 100);
setcolor(BLUE);
line(318, 10, 220, 111);
line(220,111,318,208);
line(318,208,418,111);
line(418,111,318,10);
setcolor(RED);
settextstyle(4, 0, 8);
outtextxy(260, 58, "MX");
settextstyle(4, 0, 6);
setcolor(BLUE);
outtextxy(100, 200, "MUSICATRONIX");
delay(1000);
setcolor(BLACK);
circle(319, 110, 100);
setcolor(BLACK);
line(318, 10, 220, 111);
line(220,111,318,208);
line(318,208,418,111);
line(418,111,318,10);
setcolor(BLACK);
settextstyle(4, 0, 8);
outtextxy(260, 58, "MX");
settextstyle(4, 0, 6);
setcolor(BLACK);
outtextxy(100, 200, "MUSICATRONIX");
setcolor(WHITE);
rectangle(255,50,355,150);
outtextxy(50,70,"NOTE:-");
settextstyle(20,0,1);
outtextxy(10,290," A  W S E  D  F  T G Y  H U  J  K O  L P  ;");
setcolor(BLACK);
outtextxy(10,400," C    D    E  F    G    A    B  C    D    E");
setcolor(WHITE);
outtextxy(10,350,"   C#   D#       F#  G#  Bb       C#   D#  ");
settextstyle(2,0,4);
outtextxy(10,10,"Press Esc to exit");
char KeyPressed = getch() ;
while( KeyPressed != Esc )
{
	setcolor(BLACK);
	settextstyle(20,0,1);
outtextxy(10,400," C    D    E  F    G    A    B  C    D    E");
setcolor(WHITE);
outtextxy(10,350,"   C#   D#       F#  G#  Bb       C#   D#  ");
settextstyle(2,0,4);
	switch( KeyPressed )
	{
	case 'a' :  setfillstyle(SOLID_FILL,BLACK);
		  bar(10,300,35,450);
		  bar(35,400,45,450);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(10,300,35,440);
		  bar(35,400,40,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C");
		    sound(261.63) ;//c4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(10,300,35,450);
		  bar(35,400,45,450);
		  setcolor(BLACK);
		  rectangle(10,300,35,450);
		  rectangle(35,400,45,450);
		  setcolor(WHITE);
		  line(35,400,35,449);
		    break ;
	case 'w' :setfillstyle(SOLID_FILL,WHITE);
		  bar(35,300,37,390);
		  bar(52,300,55,390);
		  bar(35,390,55,400);
		  setcolor(BLACK);
		  line(45,389,45,449);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C#");
		  sound(277.18) ;//c#4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(35,300,55,400);
		    break ;
	case 's' :setfillstyle(SOLID_FILL,BLACK);
		  bar(55,300,70,400);
		  bar(45,400,80,450);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(54,300,71,400);
		  bar(48,400,77,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D");
		  sound(293.66) ;//d4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(45,400,80,450);
		  bar(55,300,70,400);
		  setcolor(BLACK);
		  rectangle(45,400,80,450);
		  rectangle(55,300,70,400);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(54,300,55,400);
		  bar(71,300,75,400);
		  setcolor(WHITE);
		 line(56,400,69,400);
		  break ;
	case 'e' :setfillstyle(SOLID_FILL,WHITE);
		  bar(70,300,72,390);
		  bar(87,300,90,390);
		  bar(70,390,90,400);
		  setcolor(BLACK);
		  line(80,389,80,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D#");
		    sound(311.13) ;//d#4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D#");
		  delay(250);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(70,300,90,400);
		    break ;
	case 'd' :setfillstyle (SOLID_FILL,BLACK);
		 bar(90,300,115,400);
		 bar(80,400,115,450);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(88,300,113,400);
		 bar(83,400,113,440);
		 setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "E");
		   sound(329.63) ;//e4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "E");
		 delay(100);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(90,300,115,400);
		 bar(80,400,115,450);
		 setcolor(BLACK);
		 rectangle(90,300,115,400);
		 rectangle(80,400,115,450);
		 setfillstyle(SOLID_FILL,BLACK);
		 bar(88,300,90,400);
		 setcolor(WHITE);
		 line(88,400,114,400);
		 line(88,400,90,400);
		 setcolor(BLACK);
		 line(88,400,90,400);
		    break ;
	case 'f' :setfillstyle(SOLID_FILL,BLACK);
		  bar(115,300,140,450);
		  bar(140,400,150,450);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(118,300,140,440);
		  bar(140,400,145,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "F");
		     sound(349.23) ;//f4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "F");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(115,300,140,450);
		  bar(140,400,150,450);
		  setcolor(BLACK);
		  rectangle(115,300,140,450);
		  rectangle(140,400,150,450);
		  setcolor(WHITE);
		  line(140,400,140,449);
		    break ;
	case 't' :setfillstyle(SOLID_FILL,WHITE);
		  bar(140,300,142,390);
		  bar(157,300,160,390);
		  bar(140,390,160,400);
		  setcolor(BLACK);
		  line(150,389,150,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "F#");
		   sound(369.99) ;//f#4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "F#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(140,300,160,400);
		    break ;
	case 'g' :  setfillstyle(SOLID_FILL,BLACK);
		  bar(160,300,175,400);
		  bar(150,400,185,450);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(159,300,176,400);
		  bar(153,400,182,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "G");
		    sound(392.00) ;//g4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "G");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(160,300,175,400);
		  bar(150,400,185,450);
		  setcolor(BLACK);
		  rectangle(160,300,175,400);
		  rectangle(150,400,185,450);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(159,300,160,400);
		  bar(176,300,175,400);
		  setcolor(WHITE);
		  line(161,400,174,400);
		    break ;
	case 'y' :  setfillstyle(SOLID_FILL,WHITE);
		  bar(175,300,177,390);
		  bar(192,300,195,390);
		  bar(175,390,195,400);
		  setcolor(BLACK);
		  line(185,389,185,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "G#");
		    sound(415.30) ;//g#4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "G#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(175,300,195,400);
		    break ;
	case 'h' :setfillstyle(SOLID_FILL,BLACK);
		  bar(195,300,210,400);
		  bar(185,400,220,450);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(194,300,211,400);
		  bar(188,400,217,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "A");
		    sound(440.00) ;//a4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "A");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(195,300,210,400);
		  bar(185,400,220,450);
		  setcolor(BLACK);
		  rectangle(195,300,210,400);
		  rectangle(185,400,220,450);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(194,300,195,400);
		  bar(211,300,210,400);
		  setcolor(WHITE);
		  line(196,400,209,400);
		    break ;
	case 'u' :setfillstyle(SOLID_FILL,WHITE);
		  bar(210,300,212,390);
		  bar(227,300,230,390);
		  bar(210,390,230,400);
		  setcolor(BLACK);
		  line(220,389,220,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "Bb");
		    sound(466.16) ;//a#4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "Bb");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(210,300,230,400);
		    break ;
	case 'j' :setfillstyle(SOLID_FILL,BLACK);
		 bar(90+140,300,115+140,400);
		 bar(80+140,400,115+140,450);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(88+140,300,113+140,400);
		 bar(83+140,400,113+140,440);
		 setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "B");
		   sound(493.88) ;//b4
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "B");
		 delay(100);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(90+140,300,115+140,400);
		 bar(80+140,400,115+140,450);
		 setcolor(BLACK);
		 rectangle(90+140,300,115+140,400);
		 rectangle(80+140,400,115+140,450);
		 setfillstyle(SOLID_FILL,BLACK);
		 bar(88+140,300,90+140,400);
		 setcolor(WHITE);
		 line(88+140,400,114+140,400);
		 line(88+140,400,90+140,400);
		 setcolor(BLACK);
		 line(88+140,400,90+140,400);
		    break ;
	case 'k' :setfillstyle(SOLID_FILL,BLACK);
		  bar(115+140,300,140+140,450);
		  bar(140+140,400,150+140,450);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(118+140,300,140+140,440);
		  bar(140+140,400,145+140,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C");
		     sound(523.25) ;//c5
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(115+140,300,140+140,450);
		  bar(140+140,400,150+140,450);
		  setcolor(BLACK);
		  rectangle(115+140,300,140+140,450);
		  rectangle(140+140,400,150+140,450);
		  setcolor(WHITE);
		  line(140+140,400,140+140,449);
		    break ;
	case 'o' :setfillstyle(SOLID_FILL,WHITE);
		  bar(280,300,282,390);
		  bar(297,300,300,390);
		  bar(280,390,300,400);
		  setcolor(BLACK);
		  line(290,389,290,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C#");
		  sound(554.37) ; //c#5
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(280,300,300,400);
		    break ;
	case 'l' :setfillstyle(SOLID_FILL,BLACK);
		  bar(160+140,300,175+140,400);
		  bar(150+140,400,185+140,450);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(159+140,300,176+140,400);
		  bar(153+140,400,182+140,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D");
		    sound(587.33) ;//d5
		    delay(150);
		    nosound() ;
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(160+140,300,175+140,400);
		  bar(150+140,400,185+140,450);
		  setcolor(BLACK);
		  rectangle(160+140,300,175+140,400);
		  rectangle(150+140,400,185+140,450);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(159+140,300,160+140,400);
		  bar(176+140,300,175+140,400);
		  setcolor(WHITE);
		  line(161+140,400,174+140,400);
		    break ;
	case 'p' :setfillstyle(SOLID_FILL,WHITE);
		  bar(315,300,317,390);
		  bar(332,300,335,390);
		  bar(315,390,335,400);
		  setcolor(BLACK);
		  line(325,389,325,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D#");
		  sound(622.25) ;//d#5
		    delay(150);
		    nosound() ;
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(315,300,335,400);
		    break ;
	case ';' :setfillstyle(SOLID_FILL,BLACK);
		 bar(90+245,300,115+245,400);
		 bar(80+245,400,115+245,450);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(88+245,300,113+245,400);
		 bar(83+245,400,113+245,440);
		 setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "E");
		   sound(659.25) ;//e5
		    delay(150);
		    nosound() ;
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "E");
		 delay(100);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(90+245,300,115+245,400);
		 bar(80+245,400,115+245,450);
		 setcolor(BLACK);
		 rectangle(90+245,300,115+245,400);
		 rectangle(80+245,400,115+245,450);
		 setfillstyle(SOLID_FILL,BLACK);
		 bar(88+245,300,90+245,400);
		 setcolor(WHITE);
		 line(88+245,400,114+245,400);
		 line(88+245,400,90+245,400);
		 setcolor(BLACK);
		 line(88+245,400,90+245,400);
		    break ;
	}
	setcolor(BLACK);
	settextstyle(20,0,1);
outtextxy(10,400," C    D    E  F    G    A    B  C    D    E");
setcolor(WHITE);
outtextxy(10,350,"   C#   D#       F#  G#  Bb       C#   D#  ");
settextstyle(2,0,4);
	KeyPressed = getch() ;
}
getch();
}
void again()
{ setcolor(WHITE);
setfillstyle(SOLID_FILL,WHITE);
rectangle(35,300,55,400);
rectangle(70,300,90,400);
rectangle(140,300,160,400);
rectangle(175,300,195,400);
rectangle(210,300,230,400);
rectangle(280,300,300,400);
rectangle(315,300,335,400);
rectangle(385,300,405,400);
rectangle(420,300,440,400);
rectangle(455,300,475,400);
rectangle(525,300,545,400);
rectangle(560,300,580,400);
for(int i=10,j=45;i<=600,j<620;i+=35,j+=35)
{
setcolor(WHITE);
rectangle(i,300,j,450);
floodfill(i+15,350,WHITE);
}
for(i=10,j=45;i<=600,j<620;i+=35,j+=35)
{
setcolor(BLACK);
rectangle(i,300,j,450);
}
setfillstyle(SOLID_FILL,BLACK);       //-200
bar(100,150,500,270);      //(recorder)  //play button( bar )
setcolor(WHITE);
rectangle(100,150,500,270);     //outline
circle(305,210,50);
setcolor(RED);	     //Outer circle
circle(305,210,35);	  //inner circle
setfillstyle(SOLID_FILL,RED);
floodfill(305,210,RED);    //filling of inner circle
setfillstyle(SOLID_FILL,WHITE);
setcolor(WHITE);
line(220,210,135,160);      //play button
line(220,210,135,260);
line(135,160,135,260);
floodfill(170,200,WHITE);             //filling of play button
setfillstyle(SOLID_FILL,WHITE);
bar(400,170,470,240);
setcolor(WHITE);
settextstyle(4, 0, 6);
rectangle(255,50,355,150);
outtextxy(50,70,"NOTE:-");
setcolor(BLACK);
	settextstyle(20,0,1);
outtextxy(10,400," C    D    E  F    G    A    B  C    D    E");
setcolor(WHITE);
outtextxy(10,350,"   C#   D#       F#  G#  Bb       C#   D#  ");
settextstyle(2,0,4);
settextstyle(20,0,1);
outtextxy(10,290," A  W S E  D  F  T G Y  H U  J  K O  L P  ;");
settextstyle(2,0,4);
outtextxy(10,10,"Press Esc to exit");
rectangle(400,0,600,80);
outtextxy(465,5,"Instructions");
setcolor(CYAN);
outtextxy(402,20,"'N' Save Song");
setcolor(GREEN);
outtextxy(402,35,"'B' Play Song");
setcolor(RED);
outtextxy(402,50,"'Z' Record Song");
setcolor(YELLOW);
outtextxy(402,65,"'V' Reset");
}
void keyrecord()
{  int flag=0;
cleardevice();
float n[100];
int i=0;
setcolor(WHITE);
settextstyle(3, 0, 6);
outtextxy(100, 200, "LOADING...");
delay(1000);
rectangle(35,300,55,400);
delay(100);
rectangle(70,300,90,400);
delay(100);
rectangle(140,300,160,400);
delay(100);
rectangle(175,300,195,400);
delay(100);
rectangle(210,300,230,400);
delay(100);
rectangle(280,300,300,400);
delay(100);
rectangle(315,300,335,400);
delay(100);
rectangle(385,300,405,400);
delay(100);
rectangle(420,300,440,400);
delay(100);
rectangle(455,300,475,400);
delay(100);
rectangle(525,300,545,400);
delay(100);
rectangle(560,300,580,400);
delay(100);
int j;
for(i=10,j=45;i<=600,j<620;i+=35,j+=35)
{delay(100);
setfillstyle(SOLID_FILL,WHITE);
setcolor(WHITE);
rectangle(i,300,j,450);
floodfill(i+15,350,WHITE);
}
for(i=10,j=45;i<=600,j<620;i+=35,j+=35)
{delay(100);
setcolor(BLACK);
rectangle(i,300,j,450);
}
setcolor(BLACK);
settextstyle(3, 0, 6);
outtextxy(100, 200, "LOADING...");
setcolor(MAGENTA);
circle(319, 110, 100);
setcolor(BLUE);
line(318, 10, 220, 111);
line(220,111,318,208);
line(318,208,418,111);
line(418,111,318,10);
setcolor(RED);
settextstyle(4, 0, 8);
outtextxy(260, 58, "MX");
settextstyle(4, 0, 6);
setcolor(BLUE);
outtextxy(100, 200, "MUSICATRONIX");
setcolor(BLACK);
circle(319, 110, 100);
setcolor(BLACK);
line(318, 10, 220, 111);
line(220,111,318,208);
line(318,208,418,111);
line(418,111,318,10);
setcolor(BLACK);
settextstyle(4, 0, 8);
outtextxy(260, 58, "MX");
settextstyle(4, 0, 6);
setcolor(BLACK);
outtextxy(100, 200, "MUSICATRONIX");
setfillstyle(SOLID_FILL,BLACK);       //-200
bar(100,150,500,270);      //(recorder)  //play button( bar )
setcolor(WHITE);
rectangle(100,150,500,270);     //outline
circle(305,210,50);
setcolor(RED);	     //Outer circle
circle(305,210,35);	  //inner circle
setfillstyle(SOLID_FILL,RED);
floodfill(305,210,RED);    //filling of inner circle
setfillstyle(SOLID_FILL,WHITE);
setcolor(WHITE);
line(220,210,135,160);      //play button
line(220,210,135,260);
line(135,160,135,260);
floodfill(170,200,WHITE);             //filling of play button
setfillstyle(SOLID_FILL,WHITE);
bar(400,170,470,240);
setcolor(WHITE);
rectangle(255,50,355,150);
outtextxy(50,70,"NOTE:-");
settextstyle(2,0,4);
rectangle(400,0,600,80);
outtextxy(465,5,"Instructions");
setcolor(CYAN);
outtextxy(402,20,"'N' Save Song");
setcolor(GREEN);
outtextxy(402,35,"'B' Play Song");
setcolor(RED);
outtextxy(402,50,"'Z' Record Song");
setcolor(YELLOW);
outtextxy(402,65,"'V' Reset");
settextstyle(20,0,1);
outtextxy(10,290," A  W S E  D  F  T G Y  H U  J  K O  L P  ;");
settextstyle(2,0,4);
outtextxy(10,10,"Press Esc to exit");
      setcolor(BLACK);
	settextstyle(20,0,1);
outtextxy(10,400," C    D    E  F    G    A    B  C    D    E");
setcolor(WHITE);
outtextxy(10,350,"   C#   D#       F#  G#  Bb       C#   D#  ");
settextstyle(2,0,4);
char KeyPressed = getch() ;
i=0;count=0;
while( KeyPressed != Esc )
{       setcolor(BLACK);
	settextstyle(20,0,1);
outtextxy(10,400," C    D    E  F    G    A    B  C    D    E");
setcolor(WHITE);
outtextxy(10,350,"   C#   D#       F#  G#  Bb       C#   D#  ");
settextstyle(2,0,4);
	switch( KeyPressed )
	{
	case 'a' :  setfillstyle(SOLID_FILL,BLACK);
		  bar(10,300,35,450);
		  bar(35,400,45,450);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(10,300,35,440);
		  bar(35,400,40,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270, 30, "C");
		    sound(261.63) ;//c4
		    delay(150);
		    nosound() ;
		    if(flag==1)
		   {
		    s[i++]=261.63;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270, 30, "C");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(10,300,35,450);
		  bar(35,400,45,450);
		  setcolor(BLACK);
		  rectangle(10,300,35,450);
		  rectangle(35,400,45,450);
		  setcolor(WHITE);
		  line(35,400,35,449);
		    break ;
	case 'w' :setfillstyle(SOLID_FILL,WHITE);
		  bar(35,300,37,390);
		  bar(52,300,55,390);
		  bar(35,390,55,400);
		  setcolor(BLACK);
		  line(45,389,45,449);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C#");
		  sound(277.18) ;//c#4
		    delay(150);
		    nosound() ;
		    if(flag==1)
		   { s[i++]=277.18;
		    count++;}
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(35,300,55,400);
		    break ;
	case 's' :setfillstyle(SOLID_FILL,BLACK);
		  bar(55,300,70,400);
		  bar(45,400,80,450);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(54,300,71,400);
		  bar(48,400,77,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D");
		  sound(293.66) ;//d4
		    delay(150);
		    nosound() ;
		    if(flag==1)
		   { s[i++]=293.66;
		    count++;}
		    setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(45,400,80,450);
		  bar(55,300,70,400);
		  setcolor(BLACK);
		  rectangle(45,400,80,450);
		  rectangle(55,300,70,400);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(54,300,55,400);
		  bar(71,300,75,400);
		  setcolor(WHITE);
		 line(56,400,69,400);
		    break ;
	case 'e' :setfillstyle(SOLID_FILL,WHITE);
		  bar(70,300,72,390);
		  bar(87,300,90,390);
		  bar(70,390,90,400);
		  setcolor(BLACK);
		  line(80,389,80,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D#");
		    sound(311.13) ;//d#4
		    delay(150);
		    nosound() ;
		    if(flag==1)
		   { s[i++]=311.13;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D#");
		  delay(250);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(70,300,90,400);
		    break ;
	case 'd' :setfillstyle (SOLID_FILL,BLACK);
		 bar(90,300,115,400);
		 bar(80,400,115,450);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(88,300,113,400);
		 bar(83,400,113,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "E");
		   sound(329.63) ;//e4
		    delay(150);
		    nosound() ;
		    if(flag==1)
		   { s[i++]=329.63;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "E");
		 delay(100);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(90,300,115,400);
		 bar(80,400,115,450);
		 setcolor(BLACK);
		 rectangle(90,300,115,400);
		 rectangle(80,400,115,450);
		 setfillstyle(SOLID_FILL,BLACK);
		 bar(88,300,90,400);
		 setcolor(WHITE);
		 line(88,400,114,400);
		 line(88,400,90,400);
		 setcolor(BLACK);
		 line(88,400,90,400);
		    break ;
	case 'f' :setfillstyle(SOLID_FILL,BLACK);
		  bar(115,300,140,450);
		  bar(140,400,150,450);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(118,300,140,440);
		  bar(140,400,145,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "F");
		     sound(349.23) ;//f4
		    delay(150);
		    nosound() ;
		    if(flag==1){
		    s[i++]=349.23;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "F");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(115,300,140,450);
		  bar(140,400,150,450);
		  setcolor(BLACK);
		  rectangle(115,300,140,450);
		  rectangle(140,400,150,450);
		  setcolor(WHITE);
		  line(140,400,140,449);
		    break ;
	case 't' :setfillstyle(SOLID_FILL,WHITE);
		  bar(140,300,142,390);
		  bar(157,300,160,390);
		  bar(140,390,160,400);
		  setcolor(BLACK);
		  line(150,389,150,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "F#");
		   sound(369.99) ;//f#4
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=369.99;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "F#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(140,300,160,400);
		    break ;
	case 'g' :  setfillstyle(SOLID_FILL,BLACK);
		  bar(160,300,175,400);
		  bar(150,400,185,450);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(159,300,176,400);
		  bar(153,400,182,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "G");
		    sound(392.00) ;//g4
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=392.00;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "G");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(160,300,175,400);
		  bar(150,400,185,450);
		  setcolor(BLACK);
		  rectangle(160,300,175,400);
		  rectangle(150,400,185,450);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(159,300,160,400);
		  bar(176,300,175,400);
		  setcolor(WHITE);
		  line(161,400,174,400);
		    break ;
	case 'y' :  setfillstyle(SOLID_FILL,WHITE);
		  bar(175,300,177,390);
		  bar(192,300,195,390);
		  bar(175,390,195,400);
		  setcolor(BLACK);
		  line(185,389,185,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "G#");
		    sound(415.30) ;//g#4
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=415.30;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "G#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(175,300,195,400);
		    break ;
	case 'h' :setfillstyle(SOLID_FILL,BLACK);
		  bar(195,300,210,400);
		  bar(185,400,220,450);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(194,300,211,400);
		  bar(188,400,217,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "A");
		    sound(440.00) ;//a4
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=440.00;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "A");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(195,300,210,400);
		  bar(185,400,220,450);
		  setcolor(BLACK);
		  rectangle(195,300,210,400);
		  rectangle(185,400,220,450);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(194,300,195,400);
		  bar(211,300,210,400);
		  setcolor(WHITE);
		  line(196,400,209,400);
		    break ;
	case 'u' :setfillstyle(SOLID_FILL,WHITE);
		  bar(210,300,212,390);
		  bar(227,300,230,390);
		  bar(210,390,230,400);
		  setcolor(BLACK);
		  line(220,389,220,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "A#");
		    sound(466.16) ;//a#4
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=466.16;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "A#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(210,300,230,400);
		    break ;
	case 'j' :setfillstyle(SOLID_FILL,BLACK);
		 bar(90+140,300,115+140,400);
		 bar(80+140,400,115+140,450);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(88+140,300,113+140,400);
		 bar(83+140,400,113+140,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "B");
		   sound(493.88) ;//b4
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=493.88;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "B");
		 delay(100);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(90+140,300,115+140,400);
		 bar(80+140,400,115+140,450);
		 setcolor(BLACK);
		 rectangle(90+140,300,115+140,400);
		 rectangle(80+140,400,115+140,450);
		 setfillstyle(SOLID_FILL,BLACK);
		 bar(88+140,300,90+140,400);
		 setcolor(WHITE);
		 line(88+140,400,114+140,400);
		 line(88+140,400,90+140,400);
		 setcolor(BLACK);
		 line(88+140,400,90+140,400);
		    break ;
	case 'k' :setfillstyle(SOLID_FILL,BLACK);
		  bar(115+140,300,140+140,450);
		  bar(140+140,400,150+140,450);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(118+140,300,140+140,440);
		  bar(140+140,400,145+140,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C");
		     sound(523.25) ;//c5
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=523.25;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(115+140,300,140+140,450);
		  bar(140+140,400,150+140,450);
		  setcolor(BLACK);
		  rectangle(115+140,300,140+140,450);
		  rectangle(140+140,400,150+140,450);
		  setcolor(WHITE);
		  line(140+140,400,140+140,449);
		    break ;
	case 'o' :setfillstyle(SOLID_FILL,WHITE);
		  bar(280,300,282,390);
		  bar(297,300,300,390);
		  bar(280,390,300,400);
		  setcolor(BLACK);
		  line(290,389,290,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C#");
		  sound(554.37) ; //c#5
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=554.37;
		    count++;}
		  delay(100);
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "C#");
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(280,300,300,400);
		    break ;
	case 'l' :setfillstyle(SOLID_FILL,BLACK);
		  bar(160+140,300,175+140,400);
		  bar(150+140,400,185+140,450);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(159+140,300,176+140,400);
		  bar(153+140,400,182+140,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D");
		    sound(587.33) ;//d5
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=587.33;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D");
		  delay(100);
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(160+140,300,175+140,400);
		  bar(150+140,400,185+140,450);
		  setcolor(BLACK);
		  rectangle(160+140,300,175+140,400);
		  rectangle(150+140,400,185+140,450);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(159+140,300,160+140,400);
		  bar(176+140,300,175+140,400);
		  setcolor(WHITE);
		  line(161+140,400,174+140,400);
		    break ;
	case 'p' :setfillstyle(SOLID_FILL,WHITE);
		  bar(315,300,317,390);
		  bar(332,300,335,390);
		  bar(315,390,335,400);
		  setcolor(BLACK);
		  line(325,389,325,450);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D#");
		  sound(622.25) ;//d#5
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=622.25;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "D#");
		  delay(100);
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(315,300,335,400);
		    break ;
	case ';' :setfillstyle(SOLID_FILL,BLACK);
		 bar(90+245,300,115+245,400);
		 bar(80+245,400,115+245,450);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(88+245,300,113+245,400);
		 bar(83+245,400,113+245,440);
		  setcolor(WHITE);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "E");
		   sound(659.25) ;//e5
		    delay(150);
		    nosound() ;
		      if(flag==1)
		   {
		    s[i++]=659.25;
		    count++;}
		  setcolor(BLACK);
		  settextstyle(6,0,8);
		  outtextxy(270,30, "E");
		 delay(100);
		 setfillstyle(SOLID_FILL,WHITE);
		 bar(90+245,300,115+245,400);
		 bar(80+245,400,115+245,450);
		 setcolor(BLACK);
		 rectangle(90+245,300,115+245,400);
		 rectangle(80+245,400,115+245,450);
		 setfillstyle(SOLID_FILL,BLACK);
		 bar(88+245,300,90+245,400);
		 setcolor(WHITE);
		 line(88+245,400,114+245,400);
		 line(88+245,400,90+245,400);
		 setcolor(BLACK);
		 line(88+245,400,90+245,400);
		    break ;
	case 'b' : setfillstyle(SOLID_FILL,BLACK);
		  setcolor(BLACK);
		  line(220,210,135,160);      //play button
		  line(220,210,135,260);
		  line(135,160,135,260);
		  floodfill(170,200,BLACK);
		  delay(100);//filling of play button
		  setfillstyle(SOLID_FILL,WHITE);
		  bar(135,160,165,260);
		  bar(185,160,215,260);
		  circle(305,210,50);
		  setcolor(BLACK);	     //Outer circle
		  circle(305,210,40);	  //inner circle
		  setfillstyle(SOLID_FILL,BLACK);
		  floodfill(305,210,BLACK);
		  setcolor(WHITE);
		  circle(305,210,50);
		  setcolor(RED);	     //Outer circle
		  circle(305,210,35);	  //inner circle
		  setfillstyle(SOLID_FILL,RED);
		  floodfill(305,210,RED);
		  for(int k=0;k<count;k++)
		    {     sound(s[k]);
			   delay(300);
			   nosound();
			   delay(100);


		  }
		  setfillstyle(SOLID_FILL,BLACK);
		  bar(135,160,165,260);
		  bar(185,160,215,260);
		  setfillstyle(SOLID_FILL,WHITE);
		  setcolor(WHITE);
		  line(220,210,135,160);      //play button
		  line(220,210,135,260);
		  line(135,160,135,260);
		  floodfill(170,200,WHITE);
			flag=0;
		    break;
	case 'v':setfillstyle(SOLID_FILL,BLACK);
		   bar(400,170,470,240);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(410,180,460,230);
		   delay(150);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(400,170,470,240);
		     i=0;
		   count=0;
		   flag=0;
		   break;
	case 'n':  if(count>0)
		   {setfillstyle(SOLID_FILL,BLACK);
		   bar(400,170,470,240);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(410,180,460,230);
		   delay(150);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(400,170,470,240);
		  song2.copypas();
		  song2.savesong();
		  strcpy(song2.instrument,"Keyboard");
		  strcpy(song2.sname,songname);
		  strcpy(song2.time,timebuf);
		  strcpy(song2.date,datebuf);
		  fstream file,file2;
		  file2.open("C:\\TC\\DSGSDG\\KEYBOARD.DAT",ios::app|ios::binary);
		  if(!file2)
		  {cout<<"ERRRORRRR";getch();exit(0);}
		  file.open("C:\\TC\\DSGSDG\\SONGS.DAT",ios::app|ios::binary);
		    if(!file)
		  {cout<<"ERRRORRRR";getch();exit(0);}
		   file2.write((char*)&song2,sizeof(song2));
		   file2.close();
		   file.write((char*)&song2,sizeof(song2));
		   file.close();
		   again();
		   i=0;
		   count=0;
		   flag=0;
		   }
		   else
		   setfillstyle(SOLID_FILL,BLACK);
		   bar(400,170,470,240);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(410,180,460,230);
		   delay(150);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar(400,170,470,240);
		   break;
	case 'z': circle(305,210,50);
		  setcolor(BLACK);	     //Outer circle
		  circle(305,210,35);	  //inner circle
		  setfillstyle(SOLID_FILL,BLACK);
		  floodfill(305,210,BLACK);    //filling of inner circle
		  setcolor(RED);	     //Outer circle
		  circle(305,210,40);	  //inner circle
		  setfillstyle(SOLID_FILL,RED);
		  floodfill(305,210,RED);    //filling of inner circle
		  flag=1;
		  break;
	}
	setcolor(BLACK);

	settextstyle(20,0,1);
outtextxy(10,400," C    D    E  F    G    A    B  C    D    E");
setcolor(WHITE);
outtextxy(10,350,"   C#   D#       F#  G#  Bb       C#   D#  ");
settextstyle(2,0,4);
	KeyPressed = getch() ;
}
getch();
}
void recordminterface()
{   int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
cleardevice();
setcolor(MAGENTA);
circle(319, 22, 20);
setcolor(BLUE);
line(319, 2, 297, 20);
line(297,20,319,42);
line(319,42,341,20);
line(341,20,319,2);
line(308,11,308,31);
line(308,31,330,31);
line(330,31,330,11);
line(330,11,308,11);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(306, 10, "MX");
settextstyle(4, 0, 1);
  setcolor(BLUE);
outtextxy(247, 40, "MUSICATRONIX");
settextstyle(5, 0, 4);
  setcolor(RED);
outtextxy(60,60,"The World of Music at your fingertips");
setcolor(MAGENTA);
line(20,120,637,120);
line(25,125,632,125);
line(25,125,25,470);
line(20,120,20,475);
line(25,470,632,470);
line(20,475,637,475);
line(632,470,632,125);
line(637,475,637,120);
for(int x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,120,j,125);

}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(20,x,25,j);
}
for(x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,470,j,475);

}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(632,x,637,j);
}
settextstyle(5, 0, 4);
  setcolor(CYAN);
outtextxy(240,125,"Recorder");
setcolor(BLACK);
for(x=140,j=160;x<300,j<300;x+=20,j+=20)
{  setfillstyle(SOLID_FILL,WHITE);
   bar(x,240,j,300);
}
for(x=140,j=160;x<300,j<300;x+=20,j+=20)
{  setcolor(BLACK);
   rectangle(x,240,j,300);
}
setfillstyle(SOLID_FILL,BLACK);
bar(105+50,240,115+50,280);
bar(125+50,240,135+50,280);
bar(165+50,240,175+50,280);
bar(185+50,240,195+50,280);
bar(205+50,240,215+50,280);
//guitar
setfillstyle(SOLID_FILL,WHITE);
bar(450+30,240,453+30,300);
setfillstyle(6,BROWN);
bar(320+30,240,450+30,300);
int i;
for(i=0,x=245;i<5;i++,x+=12)
{  setcolor(LIGHTGRAY);
   line(320+30,x,450+30,x);
}
setfillstyle(SOLID_FILL,CYAN);
setcolor(CYAN);
rectangle(260,355,310,425);
floodfill(280,375,CYAN);
setfillstyle(SOLID_FILL,RED);
setcolor(RED);
line(300,395,350,395);
line(350,395,350,385);
line(350,385,370,395);
line(350,395,350,405);
line(350,405,370,395);
floodfill(355,395,RED);
setcolor(BLUE);
settextstyle(5,0,3);
outtextxy(120,310,"  Keyboard");
outtextxy(338,310,"  Guitar");
outtextxy(240,430, " Main Menu");
}
void recordm()
{       int flag=1,button,x,  y ;
     initmouse();
	recordminterface();
	   showmouseptr();
while(flag!=0)
{while( 1 )
     {
	getmousepos( &button, &x, &y);
      if( button & 1 == 1 )
       {        if(x>=115&&x<=315&&y>=230&&y<=310)
		{    	keyrecord();
			cleardevice();
			recordminterface();
			showmouseptr();
		}
		else
		if(x>=350&&x<=480&&y>=240&&y<=300)
		{       guitarecord();
			cleardevice();
			recordminterface();
			showmouseptr();
		}
		if(x>=215&&x<=415&&y>=325&&y<=405)      //bar(215,325,415,405);
		{       flag=0;
			break;
		}
      }
      }
     }
     }
void recordsoninterface()
{   int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
cleardevice();
setcolor(MAGENTA);
circle(319, 22, 20);
setcolor(BLUE);
line(319, 2, 297, 20);
line(297,20,319,42);
line(319,42,341,20);
line(341,20,319,2);
line(308,11,308,31);
line(308,31,330,31);
line(330,31,330,11);
line(330,11,308,11);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(306, 10, "MX");
settextstyle(4, 0, 1);
  setcolor(BLUE);
outtextxy(247, 40, "MUSICATRONIX");
settextstyle(5, 0, 4);
  setcolor(RED);
outtextxy(60,60,"The World of Music at your fingertips");
setcolor(MAGENTA);
line(20,120,637,120);
line(25,125,632,125);
line(25,125,25,470);
line(20,120,20,475);
line(25,470,632,470);
line(20,475,637,475);
line(632,470,632,125);
line(637,475,637,120);
for(int x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,120,j,125);

}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(20,x,25,j);
}
for(x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,470,j,475);

}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(632,x,637,j);
}
settextstyle(5, 0, 4);
  setcolor(CYAN);
outtextxy(220,125,"Recorded Songs");
setcolor(BLACK);
for(x=140,j=160;x<300,j<300;x+=20,j+=20)
{  setfillstyle(SOLID_FILL,WHITE);
   bar(x,240,j,300);
}
for(x=140,j=160;x<300,j<300;x+=20,j+=20)
{  setcolor(BLACK);
   rectangle(x,240,j,300);
}
setfillstyle(SOLID_FILL,BLACK);
bar(105+50,240,115+50,280);
bar(125+50,240,135+50,280);
bar(165+50,240,175+50,280);
bar(185+50,240,195+50,280);
bar(205+50,240,215+50,280);
//guitar
setfillstyle(SOLID_FILL,WHITE);
bar(450+30,240,453+30,300);
setfillstyle(6,BROWN);
bar(320+30,240,450+30,300);
int i;
for(i=0,x=245;i<5;i++,x+=12)
{  setcolor(LIGHTGRAY);
   line(320+30,x,450+30,x);
}
setfillstyle(SOLID_FILL,CYAN);
setcolor(CYAN);
rectangle(260,355,310,425);
floodfill(280,375,CYAN);
setfillstyle(SOLID_FILL,RED);
setcolor(RED);
line(300,395,350,395);
line(350,395,350,385);
line(350,385,370,395);
line(350,395,350,405);
line(350,405,370,395);
floodfill(355,395,RED);
setcolor(BLUE);
settextstyle(5,0,3);
outtextxy(120,310,"  Keyboard");
outtextxy(338,310,"  Guitar");
outtextxy(240,430, " Main Menu");
}
void top()
{
setcolor(MAGENTA);
circle(310, 60, 50);
setcolor(BLUE);
line(310, 10, 261, 60);
line(261,60,310,110);
line(310,110,360,60);
line(360,60,310,10);
setcolor(RED);
settextstyle(4, 0, 5);
outtextxy(279, 30, "MX");
settextstyle(4, 0, 4);
  setcolor(BLUE);
  outtextxy(179, 105, "MUSICATRONIX");
setcolor(MAGENTA);
line(0,150,650,150);
line(0,155,650,155);
for(int x=0,j=5;x<=640,j<=645;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,150,j,155);
}
settextstyle(3, 0, 5);
setcolor(BLUE);
outtextxy(195, 150, "RECORDED SONGS");
setcolor(BLUE);
}
void recordson()
{        int flag=1,button,x,  y ;
     initmouse();
	recordsoninterface();
	sound(200);
	delay(100);
	nosound();
	   showmouseptr();
while(flag!=0)
{while( 1 )
     {
	getmousepos( &button, &x, &y);
      if( button & 1 == 1 )
       {        if(x>=115&&x<=315&&y>=230&&y<=310)
		{       cleardevice();
			top();
			fstream file,file2;
			file.open("C:\\TC\\DSGSDG\\KEYBOARD.DAT",ios::in|ios::binary);
			file.read((char*)&song,sizeof(song));
			int pos,pos2,flag=0;
			Exit=0,dir=0;
			while(!file.eof())
			{    pos=file.tellg();
			     dir=0;
			     Exit=0;
			     if(strcmpi(song.instrument,"Keyboard")==0)
			     {  cleardevice();
				song.rm();
					if(Exit==1)
					{break;}
					else
					if(dir==-1)
					{  flag=0;
					   if(pos!=sizeof(song))
					  {	file2.open("C:\\TC\\DSGSDG\\SONGS.DAT",ios::in|ios::binary);
					   do
					   {
					   file2.read((char*)&song,sizeof(song));
					   if(file2.tellg()==pos-sizeof(song))
					   {flag=1; file.seekg(pos-sizeof(song));}
					   }while(flag==0);
					   file2.close();
					   }
					}
					else
					if(dir==1)
					{
					file.read((char*)&song,sizeof(song));
					}
			     }
			     else
			     {file.read((char*)&song,sizeof(song));}
			}
			file.close();
			cleardevice();
			recordsoninterface();
			showmouseptr();
		}
		else
		if(x>=315&&x<=515&&y>=230&&y<=310)
			{       cleardevice();
			top();
			fstream file,file2;
			file.open("C:\\TC\\DSGSDG\\GUITAR.DAT",ios::in|ios::binary);
			file.read((char*)&song,sizeof(song));
			int pos=0,flag=0; Exit=0;dir=0;
			while(!file.eof()&&Exit==0)
			{    pos=file.tellp();
			     dir=0;
			     Exit=0;
			     if(strcmpi(song.instrument,"Guitar")==0)
			     {  cleardevice();
				song.rm();
					if(Exit==1)
					{break;}
					else
					if(dir==-1)
					{  if(pos!=0)
					  { flag=0;
						file2.open("C:\\TC\\DSGSDG\\GUITAR2.DAT",ios::in|ios::binary);
					   do
					   {
					   file2.read((char*)&song,sizeof(song));
					   if(file2.tellg()==pos-sizeof(song))
					   {flag=1;
					    file.seekg(pos-sizeof(song));}
					   }while(flag==0);
					   file2.close();
					  }
					}
					else
					if(dir==1)
					{
					file.read((char*)&song,sizeof(song));
					}
			     }
			     else
			     file.read((char*)&song,sizeof(song));
			}
			file.close();
			cleardevice();
			recordsoninterface();
			showmouseptr();
		}
		if(x>=215&&x<=415&&y>=325&&y<=405)      //bar(215,325,415,405);
		{       flag=0;
			break;
		}
      }
      }
     }
}
void about()
{cleardevice();
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
cleardevice();
setcolor(MAGENTA);
circle(319, 22, 20);
setcolor(BLUE);
line(319, 2, 297, 20);
line(297,20,319,42);
line(319,42,341,20);
line(341,20,319,2);
line(308,11,308,31);
line(308,31,330,31);
line(330,31,330,11);
line(330,11,308,11);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(306, 10, "MX");
settextstyle(4, 0, 1);
  setcolor(BLUE);
outtextxy(247, 40, "MUSICATRONIX");
settextstyle(5, 0, 4);
  setcolor(RED);
outtextxy(60,60,"The World of Music at your fingertips");
setcolor(MAGENTA);
line(20,120,637,120);
line(25,125,632,125);
line(25,125,25,470);
line(20,120,20,475);
line(25,470,632,470);
line(20,475,637,475);
line(632,470,632,125);
line(637,475,637,120);
for(int x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,120,j,125);

}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(20,x,25,j);
}
for(x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,470,j,475);

}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(632,x,637,j);
}
setcolor(CYAN);
settextstyle(5, 0, 4);
  setcolor(CYAN);
outtextxy(285,130,"About");
settextstyle(6,0,2);
setcolor(MAGENTA);
outtextxy(30,175,"Musicatronix is an initiative/project taken up by 2 musicians named");
outtextxy(30,195,"Melroy Dsa a.k.a Lamborghini & Gagan G Gaonkar a.k.a 3G of class ");
outtextxy(30,215,"XII C to show how important music is by showing young talent how to ");
outtextxy(30,235,"play the piano and guitar . Our wide range of demo and pre-recorded ");
outtextxy(30,255,"songs allows the learner to have a basic idea on the concepts of music . ");
outtextxy(30,275,"The virtual keyboard and guitar helps the learner practice notes using  ");
outtextxy(30,295,"the PC's keypad and mouse . The project had begun on February of ");
outtextxy(30,315,"2019 and was completed on November of 2019 . It is ");
outtextxy(30,335,"called \"Musicatronix v.1.0.\" . This team wishes good luck to everyone  ");
outtextxy(30,355,"who uses it .");
settextstyle(4,0,2);
setcolor(BLUE);
outtextxy(450,390,"- Musicatronix");
settextstyle(5,0,1);
outtextxy(590,389,"team .");
getch();
}
void mainmenuinterface()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
cleardevice();
setcolor(MAGENTA);
circle(319, 22, 20);
setcolor(BLUE);
line(319, 2, 297, 20);
line(297,20,319,42);
line(319,42,341,20);
line(341,20,319,2);
line(308,11,308,31);
line(308,31,330,31);
line(330,31,330,11);
line(330,11,308,11);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(306, 10, "MX");
settextstyle(4, 0, 1);
  setcolor(BLUE);
outtextxy(247, 40, "MUSICATRONIX");
settextstyle(5, 0, 4);
  setcolor(RED);
outtextxy(60,60,"The World of Music at your fingertips");
setcolor(MAGENTA);
line(20,120,637,120);
line(25,125,632,125);
line(25,125,25,470);
line(20,120,20,475);
line(25,470,632,470);
line(20,475,637,475);
line(632,470,632,125);
line(637,475,637,120);
for(int x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,120,j,125);

}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(20,x,25,j);
}
for(x=20,j=25;x<=630;x+=5,j+=5)
{       setcolor(CYAN);
	line(x,470,j,475);

}
for(x=125,j=130;x<=470,j<=475;x+=5,j+=5)
{       setcolor(CYAN);
	line(632,x,637,j);
}
settextstyle(5, 0, 4);
  setcolor(CYAN);
outtextxy(235,130,"Main Menu");
setcolor(LIGHTCYAN);
outtextxy(50,250,"Keyboard");
outtextxy(270,250,"Guitar");
outtextxy(420,250,"Recorded Songs");
outtextxy(50,400,"Recorder");
outtextxy(270,400,"About");
outtextxy(420,400,"Exit");
setcolor(BLACK);
for(x=40,j=60;x<200,j<200;x+=20,j+=20)
{  setfillstyle(SOLID_FILL,WHITE);
bar(x,200,j,260);
}
for(x=40,j=60;x<200,j<200;x+=20,j+=20)
{  setcolor(BLACK);
rectangle(x,200,j,260);
}
setfillstyle(SOLID_FILL,BLACK);
bar(55,200,65,240);
bar(75,200,85,240);
bar(115,200,125,240);
bar(135,200,145,240);
bar(155,200,165,240);
//guitar
setfillstyle(6,BROWN);
bar(220+20,250-30,350+40,280-30);
int i;
for(i=0,x=255;i<5;i++,x+=5)
{  setcolor(LIGHTGRAY);
   line(220+20,x-30,350+40,x-30);
}
setfillstyle(SOLID_FILL,WHITE);
bar(350+40,250-30,353+40,280-30);
int count;
for(x=215,j=215,count=0;count<5;count++,x+=7,j+=7)
{ setcolor(CYAN);
line(420+5,x,600+5,j);
}
setcolor(RED);
setfillstyle(SOLID_FILL,RED);
line(444+5,243,444+5,217);
circle(440+5,283-40,4);
floodfill(442+5,282-40,RED);
floodfill(442+5,284-40,RED);
line(474+5,280-40,474+5,254-40);
circle(470+5,280-40,4);
floodfill(472+5,279-40,RED);
floodfill(472+5,277-40,RED);
line(504+5,273-40,504+5,247-40);
circle(500+5,276-40,4);
floodfill(502+5,275-40,RED);
floodfill(502+5,277-40,RED);
line(534+5,270-40,534+5,244-40);
circle(530+5,273-40,4);
floodfill(532+5,272-40,RED);
floodfill(532+5,274-40,RED);
line(564+5,267-40,564+5,293-40);
circle(560+5,269-40,4);
floodfill(562+5,268-40,RED);
floodfill(562+5,270-40,RED);
line(594+5,264-40,594+5,290-40);
circle(590+5,266-40,4);
floodfill(592+5,265-40,RED);
floodfill(592+5,263-40,RED);
setcolor(RED);
circle(308+10,386-30,32);
circle(308+10,386-30,37);
setcolor(CYAN);
circle(308+10,386-30,50);
setcolor(RED);
floodfill(273+10,383-30,RED);
setcolor(RED);
floodfill(342+10,383-30,RED);
settextstyle(0,0,6);
outtextxy(285+10,365-30,"i");
setcolor(CYAN);
setfillstyle(SOLID_FILL,CYAN);
rectangle(420,330-30,490,450-40);
floodfill(450,400,CYAN);
setcolor(RED);
rectangle(420,330-30,490,450-40);
setfillstyle(SOLID_FILL,RED);
line(460,390-30,530,390-30);
line(530,390-30,530,380-30);
line(530,380-30,550,390-30);
line(530,390-30,530,400-30);
line(530,400-30,550,390-30);
floodfill(535,390-30,RED);
setcolor(WHITE);
circle(107+20,385-15,15);
circle(107+20,385-15,30);
floodfill(115+20,410-15,WHITE);
setcolor(BLUE);
setfillstyle(SOLID_FILL,WHITE);
bar(158+20,355-15,170+20,415-15);
bar(178+20,355-15,190+20,415-15);
setcolor(WHITE);
setfillstyle(SOLID_FILL,WHITE);
line(20+20,355-15,20+20,415-15);
line(20+20,355-15,68+20,385-15);
line(20+20,415-15,68+20,385-15);
floodfill(35+20,383-15,WHITE);
}
void mainmenu()
{    int button, x, y ;
     initmouse();
     showmouseptr();
     mainmenuinterface();
     showmouseptr();
     setcolor(BLUE);
while( 1 )
     {
	getmousepos( &button, &x, &y);
if( button & 1 == 1 )
       {if( x>=410 && x<= 610 && y>=345 && y<= 425 )
	   exit(0) ;
	  if(x>=10&&x<=210&&y>=230&&y<=310)
		{  keyboard();
		   cleardevice();
		   showmouseptr();
		     mainmenuinterface();
			   showmouseptr();
		}
		if(x>=210&&x<=410&&y>=230&&y<=310)
		{   guitar();
		     cleardevice();
		     mainmenuinterface();
		     showmouseptr();
		}
		if(x>=10&&x<=210&&y>=345&&y<=425)
		{    recordm();
		     cleardevice();
		     mainmenuinterface();
		     showmouseptr();
		}
		if(x>=410&&x<=610&&y>=230&&y<=310)
		{  recordson();
		cleardevice();
		showmouseptr();
		     mainmenuinterface();
		     showmouseptr();
		}
		if(x>=281&&x<=355&&y>=319&&y<=393)
		{   about();
		    cleardevice();
		     mainmenuinterface();
		     showmouseptr();
		}
      }
   }
}
void logo()
{ cleardevice();	 // x=319 y=239
setcolor(BROWN);
circle(319, 239, 175);//outer circle
setcolor(RED);
circle(319, 239, 135);              //inner circle
setcolor(BLACK);
ellipse(319, 239, 230, 309 ,135, 135);    //to cover a part of the circle
setcolor(RED);//red
ellipse(320,345,198,335,100,30);          //first curve
setcolor(RED);       //red
ellipse(319,375,200,336,100,30);          //second curve
line(225,355,225,385);                    //lines
line(410,358,410,388);
line(232,343,225,355);
line(404,343,410,358);
setfillstyle(SOLID_FILL,RED);
floodfill(319,239,RED);
setcolor(BROWN);//WHITE
circle(319, 239, 135);
line(232,343,232,359);
line(404,343,404,360);
setcolor(BROWN); //RED
ellipse(319, 239, 230, 309 ,135, 135);
setcolor(WHITE);       //white
ellipse(320,345,198,335,100,30);
setcolor(BLACK);
ellipse(319, 239, 220, 320 ,175, 175);
setcolor(WHITE);//white
ellipse(319,375,200,336,100,30);
line(225,355,225,385);
line(410,358,410,388);
line(232,343,225,355);
line(404,343,410,358);
setcolor(BROWN);
ellipse(172,370,193,330,60,15);
line(118,376,145,365);
line(145,365,135,349);
ellipse(183,345,193,330,50,15);
ellipse(469,378,193,330,60,15);  //right side
ellipse(459,355,193,330,50,15);
line(490,380,520,387);
line(490,380,502,364);   /**/
setcolor(BROWN);
ellipse(320,345,198,335,100,30);
ellipse(319,375,200,336,100,30);
line(225,355,225,385);
line(410,358,410,388);
line(232,343,225,355);
line(404,343,410,358);
ellipse(172,370,193,335,60,15);
line(118,376,145,365);
line(145,365,135,349);
ellipse(183,345,193,330,50,15);
ellipse(469,378,193,330,60,15);  //right side
ellipse(459,355,193,330,50,15);
line(490,380,520,387);
line(490,380,502,364);
setfillstyle(SOLID_FILL,BROWN);
floodfill(320,400,BROWN);
floodfill(200,370,BROWN);
floodfill(430,380,BROWN);
setcolor(BROWN);  //white
circle(319, 239, 135);
line(232,343,232,359);
line(404,343,404,360);
setcolor(RED); //RED
ellipse(319, 239, 230, 309 ,135, 135);
setcolor(BROWN);       //white
ellipse(320,345,198,335,100,30);
setcolor(BROWN);
ellipse(319, 239, 220, 320 ,175, 175);
setcolor(BLACK);
ellipse(319, 239, 235, 300 ,175, 175);
setcolor(BROWN);//white
ellipse(319,375,200,336,100,30);
line(225,355,225,385);
line(410,358,410,388);
line(232,343,225,355);
line(404,343,410,358);
setcolor(BROWN);//white
ellipse(172,370,193,330,60,15);
line(118,376,145,365);
line(145,365,135,349);
ellipse(183,345,193,330,50,15);
ellipse(469,378,193,330,60,15);  //right side
ellipse(459,355,193,330,50,15);
line(490,380,520,387);
line(490,380,502,364);   /**/
floodfill(165,239,BROWN);
setcolor(WHITE);  //white
circle(319, 239, 135);
line(232,343,232,359);
line(404,343,404,360);
setcolor(RED); //RED
ellipse(319, 239, 230, 309 ,135, 135);
setcolor(WHITE);       //white
ellipse(320,345,198,335,100,30);
setcolor(BROWN);
ellipse(319, 239, 220, 320 ,175, 175);
setcolor(BLACK);
ellipse(319, 239, 235, 300 ,175, 175);
setcolor(WHITE);//white
ellipse(319,375,200,336,100,30);
line(225,355,225,385);
line(410,358,410,388);
line(232,343,225,355);
line(404,343,410,358);
setcolor(WHITE);//white
ellipse(172,370,193,330,60,15);
line(118,376,145,365);
line(145,365,135,349);
ellipse(183,345,193,330,50,15);
ellipse(469,378,193,330,60,15);  //right side
ellipse(459,355,193,330,50,15);
line(490,380,520,387);
line(490,380,502,364);   /**///shapes are over
setcolor(BLACK);
settextstyle(1,0,3);        //1
outtextxy(290,375,"1982");
settextstyle(1,0,1);        //1
outtextxy(297,325,"INDIA");
outtextxy(270,300,"BRAHMAVAR");
setcolor(WHITE);//start
circle(319,150,12);
setfillstyle(SOLID_FILL,WHITE);
floodfill(319,150,WHITE);
line(260,160,210,280);        //start of L
ellipse(215,282,120,0,5,2);
line(260,160,275,160);
line(275,160,230,270);
ellipse(235,270,120,0,5,2);
line(237,272,300,272);
line(217,284,300,284);
line(300,284,300,273);	       //End of L
setfillstyle(SOLID_FILL,WHITE);
floodfill(225,270,WHITE);
setcolor(BLACK);
line(260,160,210,280);        //start of L
ellipse(215,282,120,0,5,2);
line(260,160,275,160);
line(275,160,230,270);
ellipse(235,270,120,0,5,2);
line(237,272,300,272);
line(217,284,300,284);
line(300,284,300,273);                   //End of L
setcolor(WHITE);
line(338,284,421,284);		   //start of S
line(338,272,401,272);
line(338,272,338,284);
ellipse(403,270,180,60,5,2);
ellipse(422,282,180,60,5,2);
line(408,270,358,160);
ellipse(363,160,0,270,5,2);
line(363,158,415,158);
line(415,158,415,167);
line(415,167,375,167);
line(375,167,426,280);             //end of s
floodfill(370,170,WHITE);
setcolor(BLACK);
line(338,284,421,284);		   //start of S
line(338,272,401,272);
line(338,272,338,284);
ellipse(403,270,180,60,5,2);
ellipse(422,282,180,60,5,2);
line(408,270,358,160);
ellipse(363,160,0,270,5,2);
line(363,158,415,158);
line(415,158,415,167);
line(415,167,375,167);
line(375,167,426,280);             //end of s
setcolor(WHITE);                //start ofr
line(300,220,300,265);
ellipse(304,221,0,270,4,2);
line(306,219,340,219);
ellipse(339,221,270,180,4,2);
line(342,221,342,240);
ellipse(339,240,270,90,4,2);
line(342,242,332,242);
line(332,242,342,265);
line(342,265,335,265);
line(335,265,324,243);
line(300,265,307,265);
line(307,265,307,243);
line(307,243,324,243);
line(307,225,330,225);
line(310,235,327,235);
ellipse(310,225,180,270,3,10);
ellipse(327,225,270,0,3,10);               //end of r
floodfill(310,222,WHITE);
setcolor(BLACK);                //start ofr
line(300,220,300,265);
ellipse(304,221,0,270,4,2);
line(306,219,340,219);
ellipse(339,221,270,180,4,2);
line(342,221,342,240);
ellipse(339,240,270,90,4,2);
line(342,242,332,242);
line(332,242,342,265);
line(342,265,335,265);
line(335,265,324,243);
line(300,265,307,265);
line(307,265,307,243);
line(307,243,324,243);
line(307,225,330,225);
line(310,235,327,235);
ellipse(310,225,180,270,3,10);
ellipse(327,225,270,0,3,10);               //end of r
setfillstyle(SOLID_FILL,WHITE);
bar(312,219,327,170);
setcolor(BLACK);
rectangle(312,219,327,170);
setcolor(BLACK);//start
circle(319,150,12);
}
void loglogo()
{ cleardevice();
setcolor(MAGENTA);
circle(319, 239, 120);
setcolor(BLUE);delay(250);
line(319, 120, 200, 239);delay(250);
line(200,239,319,360);delay(250);
line(319,360,440,239);delay(250);
line(440,239,319,120);delay(250);
line(380,180,260,180); delay(250);
line(260,180,260,300); delay(250);
line(260,300,380,300); delay(250);
line(380,300,380,180); delay(250);delay(500);
setcolor(RED);
settextstyle(4, 0, 8);
outtextxy(260, 185, "MX");
settextstyle(4, 0, 6);
  setcolor(BLUE);delay(500);
outtextxy(100, 370, "MUSICATRONIX");
delay(100);
for(int i=0;i<2;i++)
{
sound(830.61);delay(200);nosound();
sound(932.33);delay(200);nosound();
sound(987.77);delay(200);nosound();
sound(1108.73);delay(200);nosound();
sound(1244.51);delay(200);nosound();
sound(987.77);delay(200);nosound();
sound(1108.73);delay(200);nosound();
sound(1244.51);delay(200);nosound();
sound(1318.51);delay(200);nosound();
sound(1479.98);delay(200);nosound();
sound(1318.51);delay(200);nosound();
sound(1479.98);delay(200);nosound();
sound(1567.98);delay(200);nosound();
sound(1661.22);delay(200);nosound();
sound(1300.00);delay(200);nosound();
}
}
void logo2()
{   int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
cleardevice();
line(319,0,319,600);
setcolor(WHITE);
setfillstyle(SOLID_FILL,WHITE);
for(int i=200;i>=0;i--)
{ setfillstyle(SOLID_FILL,WHITE);
circle(319,239,i);
floodfill(319,239,WHITE);
 delay(10);
 setfillstyle(SOLID_FILL,BLACK);
 circle(319,239,i);
floodfill(319,239,BLACK);
}
setbkcolor(WHITE);
delay(1000);
setbkcolor(BLACK);
settextstyle(6,0,4);
for(int x=850,y=-600;x>=-700;x--,y++)
{   setcolor(RED);
    outtextxy(x,150,"Melroy Dsa a.k.a Lamborghini");
    setcolor(YELLOW);
    outtextxy(y,200,"Gagan G Gaonkar a.k.a 3G");
    delay(5);
    setcolor(BLACK);
    outtextxy(x,150,"Melroy Dsa a.k.a Lamborghini");
    outtextxy(y,200,"Gagan G Gaonkar a.k.a 3G");
}
delay(2000);
settextstyle(6,0,5);
setcolor(WHITE);
outtextxy(170,200,"In association with...");
delay(2000);
logo();
delay(2000);
cleardevice();
settextstyle(6,0,7);
setcolor(WHITE);
outtextxy(200,200,"Presents...");
delay(1000);
cleardevice();
for(int s=270,f=270;s>=90;s--,f++)
{ delay(20);
  if(f==360)
  {   f=0;
  }
  setcolor(WHITE);
 ellipse(319,239,s,f,120,120);
}
for(s=90,f=90;s<=270;s++,f--)
{ delay(20);
  if(f==0)
  {   f=360;
  }
  setcolor(MAGENTA);
 ellipse(319,239,f,s,120,120);
}
setcolor(MAGENTA);
circle(319, 239, 120);
setcolor(BLUE);delay(250);
line(319, 120, 200, 239);delay(250);
line(200,239,319,360);delay(250);
line(319,360,440,239);delay(250);
line(440,239,319,120);delay(250);
line(380,180,260,180); delay(250);
line(260,180,260,300); delay(250);
line(260,300,380,300); delay(250);
line(380,300,380,180); delay(250);delay(500);
setcolor(RED);
settextstyle(4, 0, 8);
outtextxy(260, 185, "MX");
settextstyle(4, 0, 6);
  setcolor(BLUE);delay(500);
outtextxy(100, 370, "MUSICATRONIX");
delay(100);
for(i=0;i<2;i++)
{
sound(830.61);delay(200);nosound();
sound(932.33);delay(200);nosound();
sound(987.77);delay(200);nosound();
sound(1108.73);delay(200);nosound();
sound(1244.51);delay(200);nosound();
sound(987.77);delay(200);nosound();
sound(1108.73);delay(200);nosound();
sound(1244.51);delay(200);nosound();
sound(1318.51);delay(200);nosound();
sound(1479.98);delay(200);nosound();
sound(1318.51);delay(200);nosound();
sound(1479.98);delay(200);nosound();
sound(1567.98);delay(200);nosound();
sound(1661.22);delay(200);nosound();
sound(1300.00);delay(200);nosound();
}
getch();
}
void newu()
{   int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
int fla=0;
username[0]='\0';
naes=0;
password[0]='\0';
pas=0;
do
{
cleardevice();
if(flags==1)
{setcolor(RED);
  settextstyle(6,0,1);
outtextxy(160,270,"Username entered already exists");}
else
if(flags==2)
{setcolor(RED);
  settextstyle(6,0,1);
outtextxy(160,270,"Username entered is too short");}
else
if(flags==3)
{setcolor(RED);
  settextstyle(6,0,1);
outtextxy(160,270,"Password entered is not strong");}
else
if(flags==4)
{setcolor(RED);
  settextstyle(6,0,1);
outtextxy(160,270,"Passwords entered are incorrect");}
if(flags>0)
{
settextstyle(7,0,1);
setcolor(WHITE);
outtextxy(166,122,fname);
outtextxy(166,185,lname);
outtextxy(166,248,username);
settextstyle(1,0,3);
outtextxy(166,315,disp);
outtextxy(166,380,disp2);
}
flags=0;
setcolor(WHITE);
outtextxy(10,10,"X");
setcolor(RED);
rectangle(150,10,500,460);
settextstyle(6,0,3);
setcolor(MAGENTA);
circle(319, 35, 20);
setcolor(BLUE);
line(319,15, 299, 35);
line(299,35,319,55);
line(319,55,339,35);
line(339,35,319,15);
line(309,25,309,45);
line(309,45,329,45);
line(329,45,329,25);
line(329,25,309,25);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(305, 23, "MX");
settextstyle(4, 0, 2);
setcolor(BLUE);
outtextxy(235, 55, "MUSICATRONIX");
setcolor(LIGHTGRAY);
rectangle(160,125,490,145);
rectangle(160,188,490,208);
rectangle(160,251,490,271);
rectangle(160,315,490,335);
rectangle(160,380,490,400);
setcolor(CYAN);
outtextxy(160,100,"First name:");
outtextxy(160,163,"Last name:");
outtextxy(160,227,"Username:");
outtextxy(160,290,"Password:");
outtextxy(160,355,"Confirm Password:");
setfillstyle(SOLID_FILL,CYAN);
bar(160,420,490,455);
setcolor(BLACK);
outtextxy(287,425,"Sign Up");
setcolor(WHITE);
settextstyle(7,0,1);
flag=1;
  int button, x1, y1 ;
     initmouse();
     showmouseptr();
login=0;
while(flag==1&&login==0)
{	getmousepos( &button, &x1, &y1);
	if( button & 1 == 1 )
	{
		 if(x1>=0&&x1<=60&&y1>=0&&y1<=60)
			{login=1;}
		 else
			if( x1>=160 && x1<= 490 && y1>=125 && y1<= 145 )
				{settextstyle(7,0,1);
				 enter=0;
				 setcolor(WHITE);
				 rectangle(160,125,490,145);
					while(g!=27&&enter==0)
					{ g=getch();
					  if(g=='\r')
						{enter=1;setcolor(LIGHTGRAY);
						 rectangle(160,125,490,145);
						}
					  else
					  if(g=='\b')
						{
						 fame--;
						 fname[fame]='\0';
						 setfillstyle(SOLID_FILL,BLACK);
						 bar(161,126,489,144);
						 outtextxy(166,122,fname);
						}
					  else
					  if(g>32&&g<127)
						{
						fname[fame]=g;
						fame++;
						setfillstyle(SOLID_FILL,BLACK);
						bar(161,126,489,144);
						outtextxy(166,122,fname);
						}
				}//while
				}//nested if
		   else
			if( x1>=160 && x1<= 490 && y1>=188 && y1<= 208 )
				{settextstyle(7,0,1);
				 enter=0;
				 setcolor(WHITE);
				 rectangle(160,188,490,208);
					while(g!=27&&enter==0)
					{ g=getch();
						if(g=='\r')
						{enter=1;setcolor(LIGHTGRAY);
						 rectangle(160,188,490,208);
						}
						else
						if(g=='\b')
						{
						lame--;
						lname[lame]='\0';
						setfillstyle(SOLID_FILL,BLACK);
						bar(161,189,489,207);
						outtextxy(166,185,lname);
						}
						else
						if(g>32&&g<127)
						{
						lname[lame]=g;
						lame++;
						setfillstyle(SOLID_FILL,BLACK);
						bar(161,189,489,207);
						outtextxy(166,185,lname);
						}
					}//while
				}//if
		   else
			if( x1>=160 && x1<= 490 && y1>=251 && y1<= 271 )
				{settextstyle(7,0,1);
				 enter=0;
				 setcolor(WHITE);
				 rectangle(160,251,490,271);
					while(g!=27&&enter==0)
					{ g=getch();
					  setcolor(WHITE);
					  rectangle(160,251,490,271);
						if(g=='\r')
						{enter=1;setcolor(LIGHTGRAY);
						 rectangle(160,251,490,271);
						}
						else
						if(g=='\b')
						{naes--;
						 if(naes<0)
						 {naes=0;}
						 username[naes]='\0';
						 setfillstyle(SOLID_FILL,BLACK);
						 bar(161,252,489,270);
						 outtextxy(166,248,username);
						}
						else
						if(g>32&&g<127)
						{
						username[naes]=g;
						naes++;
						setfillstyle(SOLID_FILL,BLACK);
						bar(161,252,489,270);
						outtextxy(166,248,username);
						}

					} //while
				}//if
	else
       if(x1>=160&&x1<=490&&y1>=315&&y1<=335)
       {          enter=0;setcolor(WHITE);rectangle(160,315,490,335);settextstyle(1,0,3);
		  while(g!=27&&enter==0)
		    {  g=getch();
		       if(g=='\r')
		       {
			enter=1;setcolor(LIGHTGRAY);rectangle(160,315,490,335);
		       }
		       else
		       if(g=='\b')
		       {
		       pas--;
		       if(pas<0)
		       {pas=0;
		       }
		       password[pas]='\0';
		       disp[pas]='\0';
		       setfillstyle(SOLID_FILL,BLACK);
		       bar(161,316,489,334);
		       outtextxy(166,315,disp);
		       }
		       else
		       if(g>32&&g<127)
		       {
			password[pas]=g;
			disp[pas]='*';
			pas++;
			disp[pas]='\0';
		      setfillstyle(SOLID_FILL,BLACK);
			    bar(161,316,489,334);
		       outtextxy(166,315,disp);
		       }
		     }
       }
       else
	if(x1>=160&&x1<=490&&y1>=380&&y1<=400)
       {          enter=0;setcolor(WHITE);rectangle(160,380,490,400);settextstyle(1,0,3);
		   while(g!=27&&enter==0)
		    {  g=getch();
		       if(g=='\r')
		       {
			enter=1;setcolor(LIGHTGRAY);rectangle(160,380,490,400);
		       }
		       else
		       if(g=='\b')
		       {  pas2--;
				if(pas2<0)
			       {	pas2=0;}
				con[pas2]='\0';
		       disp2[pas2]='\0';
		       setfillstyle(SOLID_FILL,BLACK);
		       bar(161,381,489,399);
		       outtextxy(166,380,disp2);
		       }
		       else
		       if(g>32&&g<127)
		       {
			con[pas2]=g;
			disp2[pas2]='*';
			pas2++;
			disp2[pas2]='\0';
		      setfillstyle(SOLID_FILL,BLACK);
			    bar(161,381,489,399);
		       outtextxy(166,380,disp2);

		       }
		     }
       }
       if(x1>=160&&x1<=490&&y1>=420&&y1<=455)
       {flag=0;username[naes]='\0';fname[fame]='\0';lname[lame]='\0';
	password[pas]='\0';con[pas2]='\0';
	setfillstyle(SOLID_FILL,BLACK);
	bar(160,420,490,455);
	settextstyle(4,0,1);
	delay(200);
	setfillstyle(SOLID_FILL,CYAN);
	bar(157,417,487,452);
	setcolor(BLACK);
	outtextxy(287,425,"Sign Up");
	delay(200);
	bar(160,420,490,455);
	outtextxy(287,425,"Sign Up");
	break;
       }
}
}
//1)username exists 2)username not strong 3)password not strong 4)Passwords do not match
int len1,len2;
if(login==0)
{len1=strlen(username);
len2=strlen(password);
fstream file;
file.open("C:\\TC\\DSGSDG\\EXIST.DAT",ios::in|ios::binary);
file.read((char*)&song,sizeof(song));
while(!file.eof())
{
	if(strcmpi(song.username,username)==0)
	{
	flags=1;break;
	}
	else
	file.read((char*)&song,sizeof(song));
}
file.close();
if(flags==0)
{	if(len1<5)
	{flags=2;}
	else
	if(len2<=5)
	{flags=3;}
	else
	if(strcmpi(password,con)!=0)
	{flags=4;}
}
file.open("C:\\TC\\DSGSDG\\EXIST.DAT",ios::app|ios::binary);
if(flags==0)
{fla=1;}
if(fla==1)
{strcpy(song.fname,fname);
strcpy(song.lname,lname);
strcpy(song.username,username);
strcpy(song.password,password);
file.write((char*)&song,sizeof(song));
song2=song;
file.close();
}
}
else
fla=1;
}while(fla==0);
}
void log()
{   int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
    cleardevice();
if(err==1)
{ setcolor(RED);
  settextstyle(6,0,1);
  outtextxy(200,240,"Incorrect username or password");
}
int len;
len=strlen(username);
if(len>0)
{                          settextstyle(7,0,1);
			       setcolor(WHITE);
			setfillstyle(SOLID_FILL,BLACK);
			bar(211,221,429,239);
			outtextxy(215,218,username);
}
setcolor(WHITE);
outtextxy(10,10,"X");
setcolor(RED);
rectangle(150,110,500,460);
settextstyle(6,0,3);
setcolor(MAGENTA);
circle(319, 135, 20);
setcolor(BLUE);
line(319, 115, 299, 135);
line(299,135,319,155);
line(319,155,339,135);
line(339,135,319,115);
line(309,125,309,145);
line(309,145,329,145);
line(329,145,329,125);
line(329,125,309,125);
setcolor(RED);
settextstyle(4, 0, 1);
outtextxy(305, 123, "MX");
settextstyle(4, 0, 2);
setcolor(BLUE);
outtextxy(235, 155, "MUSICATRONIX");
setcolor(LIGHTGRAY);
rectangle(210,220,430,240);
rectangle(210,285,430,305);
setcolor(CYAN);
outtextxy(210,195,"Enter Username:");
outtextxy(210,260,"Password:");
setfillstyle(SOLID_FILL,CYAN);
bar(210,325,430,355);
setcolor(BLACK);
outtextxy(290,325,"Log In");
setcolor(WHITE);
outtextxy(180,370,"Don't have an account? Sign Up");
line(180,395,465,395);
line(180,395,465,395);    settextstyle(3,0,3);          char disp[30];char pass[30];
int pas=0;int flag=0;
password[pas]='\0';
  int button, x, y ;
     initmouse();
     showmouseptr();
flag=1;
while(flag==1)
     {
	getmousepos( &button, &x, &y);
	if( button & 1 == 1 )
		{ if(x>=0&&x<=20&&y>=0&&y<=20)
		  {exit(0);}
		  else
		  if( x>=210 && x<= 430 && y>=220 && y<= 240 )
		   {           settextstyle(7,0,1);
			       flag=0;
			       setcolor(WHITE);
		       rectangle(210,220,430,240);
		      while(g!=27&&flag==0)
		     { g=getch();
		       setcolor(WHITE);
		       rectangle(210,220,430,240);
		       if(g=='\r')
		       {flag=1;setcolor(LIGHTGRAY);
		       rectangle(210,220,430,240);
		       }
		       else
		       if(g=='\b')
		       {
			naes--;
			if(naes<0)
			{naes=0;}
			username[naes]='\0';
			setfillstyle(SOLID_FILL,BLACK);
			bar(211,221,429,239);
			outtextxy(215,218,username);
		       }
		       else
		       if(g>32&&g<127)
		       {
			username[naes]=g;
			naes++;
			setfillstyle(SOLID_FILL,BLACK);
			bar(211,221,429,239);
			outtextxy(215,218,username);
		       }


		     }
		   }
		   else
       if(x>=210&&x<=430&&y>=285&&y<=305)
       {          flag=0;setcolor(WHITE);rectangle(210,285,430,305);settextstyle(1,0,3);
		  while(g!=27&&flag==0)
		    {  g=getch();
		       if(g=='\r')
		       {
			flag=1;setcolor(LIGHTGRAY);rectangle(210,285,430,305);
		       }
		       if(g=='\b')
		       {pas--;
			if(pas<0)
			{
				pas=0;
			}
			password[pas]='\0';
			disp[pas]='\0';
			 setfillstyle(SOLID_FILL,BLACK);
			bar(211,286,429,304);
			outtextxy(215,283,disp);
		       }
		       if(g>32&&g<127)
		       {
			password[pas]=g;
			disp[pas]='*';
			pas++;
			disp[pas]='\0';
		      setfillstyle(SOLID_FILL,BLACK);
			bar(211,286,429,304);
			outtextxy(215,283,disp);
		       }
		     }
       }
       else
       if(x>=210&&x<=430&&y>=325&&y<=355)
       {flag=0;username[naes]='\0';password[pas]='\0';
	setfillstyle(SOLID_FILL,BLACK);
	bar(210,325,430,355);
	settextstyle(4,0,1);
	delay(200);
	setfillstyle(SOLID_FILL,CYAN);
	bar(213,328,427,352);
	setcolor(BLACK);
	outtextxy(290,325,"Log In");
	delay(200);
	bar(210,325,430,355);
	outtextxy(290,325,"Log In");
	break;
       }
       else
       if(x>=180&&x<=465&&y>=375&&y<=395)
       {       newu();
	       if(login==0)
	     {  logo2();mainmenu();flag=0;}
       }
}
}
err=0;
fstream file;
file.open("C:\\TC\\DSGSDG\\EXIST.DAT",ios::in|ios::binary);
if(!file)
{cout<<"FILE ERROR";getch();exit(0);}
else
{       file.read((char*)&song,sizeof(song));
	while(!file.eof())
	{
		if(strcmpi(song.username,username)!=0)
		{
		err=1;
		}
		else
		if(strcmpi(song.username,username)==0)
		{
			if(strcmpi(song.password,password)!=0)
			{
			err=1;
			break;
			}
			else
			if(strcmpi(song.password,password)==0)
			{
			err=0;
			break;
			}
		}
		file.read((char*)&song,sizeof(song));
	}

}
if(err==1)
{ setcolor(RED);
  settextstyle(6,0,1);
  outtextxy(200,240,"Incorrect username or password");
}
else
if(err==0)
{file.close();
loglogo();
   song2=song;
}
}
void main()
{   int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
cleardevice();
naes=0;
log();
if(err==1)
{ setcolor(RED);
  settextstyle(6,0,1);
  outtextxy(200,240,"Incorrect username or password");
}
if(err==1)
{   while(err==1)
    { log();
    };
}

mainmenu();
getch();
}

