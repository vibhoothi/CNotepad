#include<string.h>
#include<fstream.h>
#include<process.h>
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>

union REGS i,o;
char inputbuf[150];
int input_pos = 0;
char name[20],c;
int ox=71,oy=85;
void draw();
void count_words( char[] );
void intro();
int input(char []);
void restrictmouseptr(int ,int ,int ,int );
int callmouse();
class file

{ public: char notes[150];
    void write();
    void read();
};
void file::write()

{ outtextxy(80,85,"|");
    gotoxy(12,6);
    gets(notes);
}
void file::read()

{ char array[2];
    for(int i=0;notes[i]!=' ';i++)

    {
	array[0]=notes[i];
	array[1]='\0';
	outtextxy(ox,oy,array);
	ox+=8;
	if(ox>=380)

	{
	    ox=71;
	    oy+=8;
	}
    }
}

class notepad

{
    public:
    int field;
    int menu;
    int outline;
    int popup;
    void draw();
    notepad()

    { field=15;
	menu=4;
	outline=3;
	popup=6;
    }
};
   void notepad:: draw()

    {
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"");
	int margin,top,bottom,right,left;
	restrictmouseptr(45,30,410,405);
	callmouse();
	margin=50;
        left=margin;
        top=margin;
	bottom=400;
        right=400;
        setfillstyle(SOLID_FILL,field);
        bar(left,top,right,bottom);
        rectangle(left,top,right,bottom);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL,outline);
	//top bar
        bar(45,30,410,50);
        rectangle(45,30,410,50);
        //left bar
        bar(45,50,55,405);
	rectangle(45,50,55,405);
        //right bar
        bar(400,49,410,405);
        rectangle(400,49,410,405);
        //bottom bar
        bar(45,400,410,405);
        rectangle(45,400,410,420);
	setcolor(BLACK);
        setfillstyle(SOLID_FILL,menu);
        bar(45,47,410,60);
        rectangle(45,47,410,60);
        outtextxy(47,50,"File");
	outtextxy(85,50,"Edit");
	outtextxy(125,50,"Help");
	outtextxy(165,50,"Mods");
	outtextxy(52,35,"NOTEPAD++ ");
	outtextxy(135,35,"Beta Mode");
	outtextxy(395,35,"X");
    }


void restrictmouseptr(int x1,int y1,int x2,int y2)

{
    i.x.ax=7;
    i.x.cx=x1;
    i.x.dx=x2;
    int86(51,&i,&o);
    i.x.ax=8;
    i.x.cx=y1;
    i.x.dx=y2;
    int86(51,&i,&o);
}
int callmouse()

{ i.x.ax=1;
    int86(51,&i,&o);
    return 1;
}
void getmousepos(int &xpos,int &ypos,int &cl)

{ i.x.ax=3;
    int86(51,&i,&o);
    cl=o.x.bx;
    xpos=o.x.cx;
    ypos=o.x.dx;
}


void intro()
{
    int gd=DETECT,gm;
    int margin,top,bottom,right,left;
    initgraph(&gd,&gm,"");
    char str[300];
    int i,j,location,n;
    char ch;
    strcpy(str,"          NOTEPAD++          ");
    outtextxy(350,300,"PRESS ANY KEY");
    for(i=0;i<10;i++)
    {
	setfillstyle(SOLID_FILL,BLACK);
        bar(50,50,600,90);
        settextstyle(3,HORIZ_DIR,4);
        outtextxy(50,50,str);
        setcolor(i);
        delay(100);
	ch = str[0];
        n=strlen(str);
        location=0;
        for(j=location;j<n;j++)
        {
            str[j] = str[j+1];
        }
    }
    str[n-1]=ch;
    str[n]=NULL;
    bar(230,150,350,268);
    rectangle(230,150,380,268);
    setcolor(CYAN);
    circle(362,140,25);
    settextstyle(2,HORIZ_DIR,4);
    outtextxy(244,160,"C++ NOTEPAD");
    delay(400);
    outtextxy(244,172,"Developed by VIBHOOTHI ");
    delay(400);
    outtextxy(244,238,"LOADING");
    int inx=294;
    for( i=0;i<8;++i)
    {
        outtextxy(inx,238,".");
        inx+=6;
        delay(300);
    }
    outtextxy(244,250 ,"DONE");
    getch();
}

void main()

{
    int flag=0;
    notepad n;
    fstream f,f1;
    intro();
    n.draw();
    int x,y,cl=0;
    file s;
    while(1)

    {
	fstream f;
	getmousepos(x,y,cl);
	gotoxy(5,8); //  cout<<"ntMouse Position is: X: "<<x<<" Y: "<<y; // cout<<"CLICK:"<<cl;
	if((x>=45 && x<=78)&&(y>=49&&y<=56)&&(cl==1))

	{ //pop up
	    flag=1;
	    cleardevice();  // system("CLS");
	    n. draw();
	    setfillstyle(SOLID_FILL,n.popup);
	    delay(500);
	    bar(45,60,110,99);
	    rectangle(45,60,110,99);
	    outtextxy(46,65,"NEW");
	    outtextxy(46,76,"OPEN");
	    outtextxy(46,86,"ADD");
	}

  }

}